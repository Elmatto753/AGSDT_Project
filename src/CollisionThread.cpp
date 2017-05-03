#include "CollisionThread.h"

CollisionThread::CollisionThread(Model mesh, ImpactObject object)
{
  m_Mesh = mesh;
  m_Object = object;

}

CollisionThread::~CollisionThread()
{

}

void CollisionThread::run()
{

  std::cout<<"Hi\n";
  if(initialTest(m_Mesh, m_Object) == true)
  {
    std::cout<<"There is collision\n";
    // check for collision
  }
}

bool CollisionThread::initialTest(Model _mesh, ImpactObject _object)
{
  Ray ray;
  ray.m_Direction = _object.getDirection();
  ray.m_StartPoint = _object.getPosition();
  ray.m_EndPoint = ray.m_StartPoint + (ray.m_Direction * 100000000); // In the absence of infinity

  for(Particle *p :_mesh.getContainer()->getParticleList())
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
