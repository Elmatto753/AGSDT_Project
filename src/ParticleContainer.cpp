#include "ParticleContainer.h"

ParticleContainer::ParticleContainer()
{
  baseParticle = new Particle;

//  m_numParticles = 10;

//  particleList.resize(m_numParticles);

//  for(auto &i : particleList)
//  {
//    i = new Particle;
//  }
}

ParticleContainer::~ParticleContainer()
{

}

void ParticleContainer::loadParticleModel()
{
  //baseParticle->m_ID = 0;
  m_Mesh.reset(new ngl::Obj("models/Sphere.obj"));
  (*m_Mesh)->scale(0.2f, 0.2f, 0.2f);
  (*m_Mesh)->createVAO();
  (*m_Mesh)->getMeshSize();

}

void ParticleContainer::drawParticles()
{
  //baseParticle->m_Mesh->bindVAO();
}

void ParticleContainer::setParticlePosition(uint _at, ngl::Vec3 _position)
{
  particleList.at(_at)->m_Position = _position;
}

void ParticleContainer::makeParticleAt(ngl::Vec3 _pos)
{
  Particle *p = new Particle;
  p->m_Position = _pos;
  p->m_ID = particleList.size();
  particleList.push_back(p);
}

