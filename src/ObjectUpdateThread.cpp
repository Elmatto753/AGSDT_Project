#include "ObjectUpdateThread.h"


ObjectUpdateThread::ObjectUpdateThread()
{
  m_timer = new QTimer(this);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(UpdateObjects()));
  m_timer->start(16.6); // Roughly 60 updates per second
}

ObjectUpdateThread::~ObjectUpdateThread()
{

}

void ObjectUpdateThread::run()
{
//  while(true)
//  {

//  }
}

void ObjectUpdateThread::setUp()
{

  m_impact.loadMesh("models/Sphere.obj");
}

void ObjectUpdateThread::UpdateObjects()
{
  QMutexLocker ml(&m_mutex);
  m_impact.update();
//  x++;
//  std::cout<<x<<"\n";
//  std::cout<<"This is thread yo\n";
}

void ObjectUpdateThread::setImpactObjectDirection(ngl::Vec3 _dir)
{
  m_impact.setDirection(_dir);
}

void ObjectUpdateThread::setImpactObjectMass(float _mass)
{
  m_impact.setMass(_mass);
}

void ObjectUpdateThread::setImpactObjectRadius(float _rad)
{
  m_impact.setRadius(_rad);
}

void ObjectUpdateThread::setImpactObjectVelocity(float _vel)
{
  m_impact.setVelocity(_vel);
}

void ObjectUpdateThread::setImpactObjectPosition(ngl::Vec3 _pos)
{
  m_impact.setPosition(_pos);
}
