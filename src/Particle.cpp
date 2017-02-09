#include "Particle.h"


Particle::Particle()
{
  mesh.load("models/Sphere.obj");
  mesh.createVAO();
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

void::Particle::draw()
{
  mesh.draw();
}
