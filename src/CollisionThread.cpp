#include "CollisionThread.h"

CollisionThread::CollisionThread(Model mesh, ImpactObject object, ObjectUpdateThread *thread)
{
  m_mesh = mesh;
  m_object = object;
  m_OUthread = thread;

}

CollisionThread::~CollisionThread()
{

}

void CollisionThread::run()
{

  std::cout<<"Hi\n";
  if(initialTest(m_mesh, m_object) == true)
  {
    std::cout<<"There is gonna be collision\n";
    while(true)
    {
      std::vector<Particle*> hitParticles = fullTest();
      if(hitParticles.size() == 0)
      {
        //std::cout<<"Not colliding\n";
      }
      else
      {
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
    std::cout<<"success\n";
    // check for collision
  }
}

bool CollisionThread::initialTest(Model _mesh, ImpactObject _object)
{
  Ray ray;
  ray.m_Direction = _object.getDirection();
  ray.m_StartPoint = _object.getPosition();
  ray.m_EndPoint = ray.m_StartPoint + (ray.m_Direction * 100000000); // In the absence of infinity

  for(Particle *p : _mesh.getContainer()->getParticleList())
  {
    ngl::Vec3 dist = ray.m_StartPoint - p->m_Position;
    if(dist.dot(ray.m_Direction) > 0 || dist.lengthSquared() < (_object.getRadius() * _object.getRadius()))
    {
      continue; // Sphere not travelling in the direction of the particle
    }

    ngl::Vec3 approach = dist - (dist.dot(ray.m_Direction) * ray.m_Direction);

    if(approach.lengthSquared() > (_object.getRadius() * _object.getRadius()))
    {
      continue; // Object misses particle
    }

    return true;

  }

  return false;

}

std::vector<Particle*> CollisionThread::fullTest()
{
  m_object = m_OUthread->getImpactObject();
  std::vector<Particle*> o_collidesWith;
  for(Particle *p : m_mesh.getContainer()->getParticleList())
  {
    if(ngl::Vec3(m_object.getPosition() - p->m_Position).length() <= m_object.getRadius() * 0.5f)
    {
      o_collidesWith.push_back(p);
    }
  }
  return o_collidesWith;
}

void CollisionThread::impartForce(std::vector<Particle *> _impartTo)
{
  m_object = m_OUthread->getImpactObject();
  float force = m_object.getMass() * m_object.getVelocity();
  assert(_impartTo.size() != 0); // This should never happen
  force /= _impartTo.size();
  for(Particle *p : _impartTo)
  {
    p->m_InForce = force;
  }
  m_OUthread->setImpactObjectVelocity(m_object.getVelocity() * 0.5f);
}

void CollisionThread::calcBreakpoint()
{
//  for(uint i = 0; i < 20; i++)
//  {
    for(Particle *p : m_mesh.getContainer()->getParticleList())
    {
      if(p->m_InForce == 0)
      {
        continue;
      }
      if(p->m_isBroken == true)
      {
        continue;
      }
      if(p->m_InForce > p->m_BondStrength)
      {
        p->m_isBroken = true;
        m_mesh.getContainer()->removeParticle(p);
        for(Particle *np : p->connectedParticles)
        {
          np->connectedParticles.erase(std::remove(np->connectedParticles.begin(), np->connectedParticles.end(), p), np->connectedParticles.end());
        }
        std::cout<<p->m_ID<<"is broken\n";
        continue;
      }
      for(Particle *np : p->connectedParticles)
      {
        if(np== p->receivedForceFrom)
        {
          //std::cout<<"works\n";
          continue;
        }
        np->m_InForce += p->m_InForce/p->connectedParticles.size();
        p->m_InForce = 0;
        np->receivedForceFrom = p;
        //std::cout<<"particle "<<np->m_ID<<" force = "<<np->m_InForce<<"\n";
      }
    }
 // }
}







