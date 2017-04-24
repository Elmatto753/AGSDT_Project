#include "ParticleContainer.h"

ParticleContainer::ParticleContainer()
{
  baseParticle = new Particle;

  m_numParticles = 10;
  //particleList.push_back(baseParticle);

}

ParticleContainer::~ParticleContainer()
{

}

void ParticleContainer::loadParticleModel()
{
  baseParticle->m_ID = 0;
  baseParticle->m_Mesh.reset(new ngl::Obj("models/Sphere.obj"));
  baseParticle->m_Mesh->scale(3.0f, 3.0f, 3.0f);
  baseParticle->m_Mesh->createVAO();
  baseParticle->m_meshSize = baseParticle->m_Mesh->getMeshSize();

}

void ParticleContainer::drawParticles()
{
  baseParticle->m_Mesh->bindVAO();
}


