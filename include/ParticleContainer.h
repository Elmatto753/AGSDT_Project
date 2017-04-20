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

  void initBuffers();

  void updateBuffers();

  void bindBuffers();

  GLuint getBuffer() { return m_buffer; }

  uint getBufferSize() { return baseParticle->getMeshSize(); }

  int getNumParticles() { return m_numParticles; }

private:

  // Buffers for particle generation (currently using billboards)

//  GLuint billboard_vertex_buffer;

//  GLuint particles_position_buffer;

//  GLuint particles_colour_buffer;

  GLuint m_buffer;

  int maxParticles = 100000;

  GLfloat* g_particle_position_size_data = new GLfloat[maxParticles * 4];

  GLubyte* g_particle_colour_data = new GLubyte[maxParticles * 4];

  int m_numParticles;

  Particle* baseParticle = new Particle;

  std::vector<Particle> particleList;


};





#endif
