#ifndef PARTICLECONTAINER_H_
#define PARTICLECONTAINER_H_

#include <ngl/Vec3.h>
#include <ngl/Obj.h>
#include "Particle.h"


class ParticleContainer
{

public:

  ParticleContainer();

  ~ParticleContainer();

  void loadParticleModel();

  void drawParticles();

  uint getBufferSize() { return baseParticle->m_meshSize; }

  int getNumParticles() { return m_numParticles; }

  Particle* getBaseParticle() { return baseParticle; }

  std::vector<Particle*> getParticleList() { return particleList; }

  void setParticlePosition(uint _at, ngl::Vec3 _position);

private:

  int maxParticles = 100000;

//  GLfloat* g_particle_position_size_data = new GLfloat[maxParticles * 4];

//  GLubyte* g_particle_colour_data = new GLubyte[maxParticles * 4];

  int m_numParticles;

  Particle *baseParticle;

  std::vector<Particle*> particleList;


};





#endif
