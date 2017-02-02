#include "Particle.h"


Particle::Particle()
{

}

Particle::~Particle()
{

}

void Particle::setPosition(ngl::Vec3 newPos)
{
  m_Position = newPos;
}

void Particle::move(ngl::Vec3 delta)
{
  m_Position += delta;
}
