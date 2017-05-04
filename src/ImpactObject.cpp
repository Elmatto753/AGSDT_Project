#include "ImpactObject.h"

ImpactObject::ImpactObject()
{

}

ImpactObject::~ImpactObject()
{

}

void ImpactObject::setDirection(ngl::Vec3 _dir)
{
  _dir.normalize();
  m_direction = _dir;
}

void ImpactObject::setVelocity(float _vel)
{
  m_velocity = _vel;
}

void ImpactObject::setMass(float _mass)
{
  m_mass = _mass;
}

void ImpactObject::setRadius(float _rad)
{
  m_radius = _rad;
}

void ImpactObject::loadMesh(std::string _file)
{
  m_mesh.reset(new ngl::Obj(_file));
  m_mesh->scale(1.0f, 1.0f, 1.0f);
  m_mesh->createVAO();
  m_meshSize = m_mesh->getMeshSize();
}

void ImpactObject::update()
{
  m_position += m_direction * m_velocity;
}




