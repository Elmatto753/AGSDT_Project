#include "ObjectUpdateThread.h"


ObjectUpdateThread::ObjectUpdateThread()
{
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(UpdateObjects()));
  timer->start(16.6); // Roughly 60 updates per second
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

  m_Impact.loadMesh("models/Sphere.obj");
}

void ObjectUpdateThread::UpdateObjects()
{
  QMutexLocker ml(&m_Mutex);
  m_Impact.update();
//  x++;
//  std::cout<<x<<"\n";
//  std::cout<<"This is thread yo\n";
}

void ObjectUpdateThread::setImpactObjectDirection(ngl::Vec3 _dir)
{
  m_Impact.setDirection(_dir);
}

void ObjectUpdateThread::setImpactObjectMass(float _mass)
{
  m_Impact.setMass(_mass);
}

void ObjectUpdateThread::setImpactObjectRadius(float _rad)
{
  m_Impact.setRadius(_rad);
  std::cout<<m_Impact.getRadius()<<"\n";
}

void ObjectUpdateThread::setImpactObjectVelocity(float _vel)
{
  m_Impact.setVelocity(_vel);
}

void ObjectUpdateThread::setImpactObjectPosition(ngl::Vec3 _pos)
{
  m_Impact.setPosition(_pos);
}
