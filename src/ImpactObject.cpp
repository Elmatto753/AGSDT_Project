#include "ImpactObject.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file ImpactObject.cpp
/// @brief Defines the object that is used to hit the particles
//----------------------------------------------------------------------------------------------------------------------

ImpactObject::ImpactObject()
{

}

ImpactObject::~ImpactObject()
{

}

void ImpactObject::setDirection(ngl::Vec3 _dir)
{
  // Normalise to give unit direction vector
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

// Loads in the mesh from a given file
void ImpactObject::loadMesh(std::string _file)
{
  m_mesh.reset(new ngl::Obj(_file));
  m_mesh->scale(1.0f, 1.0f, 1.0f);
  m_mesh->createVAO();
  m_meshSize = m_mesh->getMeshSize();
}

// Updates the object's position based on velocity and direction
void ImpactObject::update()
{
  m_position += m_direction * m_velocity;
}




