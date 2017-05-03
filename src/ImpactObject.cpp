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
  m_Direction = _dir;
}

void ImpactObject::setVelocity(float _vel)
{
  m_Velocity = _vel;
}

void ImpactObject::setMass(float _mass)
{
  m_Mass = _mass;
}

void ImpactObject::setRadius(float _rad)
{
  m_Radius = _rad;
}

void ImpactObject::loadMesh(std::string _file)
{
  m_Mesh.reset(new ngl::Obj(_file));
  m_Mesh->scale(1.0f, 1.0f, 1.0f);
  m_Mesh->createVAO();
  m_MeshSize = m_Mesh->getMeshSize();
}

void ImpactObject::update()
{
  m_Position += m_Direction * m_Velocity;
}




