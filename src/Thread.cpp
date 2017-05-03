#include "Thread.h"


Thread::Thread()
{

}

Thread::~Thread()
{

}

void Thread::run()
{
  while(true)
  {
    m_Impact.update();
    std::cout<<"This is thread yo\n";
  }
}

void Thread::setUp()
{
  m_Impact.loadMesh("models/Sphere.obj");
}
