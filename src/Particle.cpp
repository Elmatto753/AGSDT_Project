#include "Particle.h"


Particle::Particle()
{
  mesh.load("models/Sphere.obj");
  mesh.scale(0.1, 0.1, 0.1);
  mesh.createVAO();
}

Particle::~Particle()
{

}

void Particle::setPosition(ngl::Vec3 newPos)
{
  m_Position = newPos;
}

void Particle::setID(uint newID)
{
  m_ID = newID;
}

void Particle::setNext(Particle *_nextParticle)
{
  m_next = _nextParticle->getID();
}

void Particle::move(ngl::Vec3 delta)
{
  m_Position += delta;
}

void::Particle::draw()
{
  mesh.calcDimensions();
  mesh.draw();
}
