#include "ParticleContainer.h"

ParticleContainer::ParticleContainer()
{

  m_numParticles = 10;
  particleList.push_back(baseParticle);

}

ParticleContainer::~ParticleContainer()
{

}

void ParticleContainer::loadParticleModel()
{
  baseParticle->m_ID = 0;
  baseParticle->m_Mesh.reset(new ngl::Obj("models/Sphere.obj"));
  baseParticle->m_Mesh->createVAO();
}

void ParticleContainer::drawParticles()
{
  baseParticle->m_Mesh->bindVAO();
}


