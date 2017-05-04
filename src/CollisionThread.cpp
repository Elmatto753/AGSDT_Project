#include "CollisionThread.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file CollisionThread.cpp
/// @brief Implements a thread to handle collision calculations to avoid slowing down the main thread
//----------------------------------------------------------------------------------------------------------------------

CollisionThread::CollisionThread(Model mesh, ImpactObject object, ObjectUpdateThread *thread)
{
  // Constructor, sets attributes and pointers to objects from other threads
  m_mesh = mesh;
  m_object = object;
  m_OUthread = thread;
}

CollisionThread::~CollisionThread()
{

}

// Executed on thread start
void CollisionThread::run()
{
  // Tests if the object will ever hit any particles
  if(initialTest(m_mesh, m_object) == true)
  {
    //loop
    while(true)
    {
      // Test if object has collided with any particles
      std::vector<Particle*> hitParticles = fullTest();
      if(hitParticles.size() != 0)
      {
        // Impart the object's force and calculate breakages
        while(m_object.getVelocity() > 0.01)
        {
          impartForce(hitParticles);
          calcBreakpoint();
        }
        m_OUthread->setImpactObjectVelocity(0.0f);
        m_OUthread->setImpactObjectPosition(ngl::Vec3(1000.0f, 1000.0f, 1000.0f));
        break;
      }
    }
  }
}

// Fires a ray from the object's start position and detects if it will collide with any particles
bool CollisionThread::initialTest(Model _mesh, ImpactObject _object)
{
  Ray ray;
  ray.m_direction = _object.getDirection();
  ray.m_startPoint = _object.getPosition();
  ray.m_endPoint = ray.m_startPoint + (ray.m_direction * 100000000); // In the absence of infinity

  // For each particle
  for(Particle *p : _mesh.getContainer()->getParticleList())
  {
    ngl::Vec3 dist = ray.m_startPoint - p->m_position;
    if(dist.dot(ray.m_direction) > 0 || dist.lengthSquared() < (_object.getRadius() * _object.getRadius()))
    {
      continue; // Sphere not travelling in the direction of the particle
    }

    ngl::Vec3 approach = dist - (dist.dot(ray.m_direction) * ray.m_direction);

    if(approach.lengthSquared() > (_object.getRadius() * _object.getRadius()))
    {
      continue; // Object misses particle
    }

    return true;
  }

  return false;
}

// Returns a std::vector of all particles the object is currently colliding with
std::vector<Particle*> CollisionThread::fullTest()
{
  m_object = m_OUthread->getImpactObject();
  std::vector<Particle*> o_collidesWith;
  for(Particle *p : m_mesh.getContainer()->getParticleList())
  {
    // If particle p is within the radius of the object
    if(ngl::Vec3(m_object.getPosition() - p->m_position).length() <= m_object.getRadius() * 0.5f)
    {
      o_collidesWith.push_back(p);
    }
  }
  return o_collidesWith;
}

// Imparts force onto particles that are hit
void CollisionThread::impartForce(std::vector<Particle *> _impartTo)
{
  m_object = m_OUthread->getImpactObject();
  float force = m_object.getMass() * m_object.getVelocity();
  assert(_impartTo.size() != 0); // This should never happen
  force /= _impartTo.size(); // force is exerted over multiple particles
  for(Particle *p : _impartTo)
  {
    p->m_inForce = force;
  }
  // Slow down the object
  m_OUthread->setImpactObjectVelocity(m_object.getVelocity() * 0.5f);
}

// Force travels in the object, potentially leading to particles other than the hit one breaking
void CollisionThread::calcBreakpoint()
{
  for(Particle *p : m_mesh.getContainer()->getParticleList())
  {
    // No need to disperse force if no force is present
    if(p->m_inForce == 0)
    {
      continue;
    }
    // This should be unnecessary, but a broken particle will not disperse force
    if(p->m_isBroken == true)
    {
      continue;
    }
    // If force exceeds bond strength, break the particle and remove it from the particle lists
    if(p->m_inForce > p->m_bondStrength)
    {
      p->m_isBroken = true;
      m_mesh.getContainer()->removeParticle(p);
      for(Particle *np : p->connectedParticles)
      {
        np->connectedParticles.erase(std::remove(np->connectedParticles.begin(), np->connectedParticles.end(), p), np->connectedParticles.end());
      }
      continue;
    }
    // Send force to other particles
    for(Particle *np : p->connectedParticles)
    {
      // But not to the particle this previously received force from
      if(np== p->receivedForceFrom)
      {
        continue;
      }
      np->m_inForce += p->m_inForce/p->connectedParticles.size();
      p->m_inForce = 0;
      np->receivedForceFrom = p;
    }
  }
}
