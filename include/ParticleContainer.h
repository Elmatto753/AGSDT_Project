#ifndef PARTICLECONTAINER_H_
#define PARTICLECONTAINER_H_

#include <ngl/Vec3.h>
#include <ngl/Obj.h>
//#include "Particle.h"


class ParticleContainer
{

public:

  ParticleContainer();

  ~ParticleContainer();

  void loadParticleModel();

  void drawParticles();

  uint getBufferSize() { return baseParticle->m_meshSize; }

  int getNumParticles() { return m_numParticles; }

  typedef struct Particle
  {
    ngl::Vec3 m_Position = ngl::Vec3(0.0f, 0.0f, 0.0f);

    std::shared_ptr<ngl::Obj> m_Mesh;

    uint m_meshSize = 0;

    // ID of next particle
    uint m_next = 0;

    std::vector<Particle> connectedParticles;

    uint m_ID = 0;

    float m_bondStrength = 0;

  } Particle;

  Particle* getBaseParticle() { return baseParticle; }


private:

  int maxParticles = 100000;

//  GLfloat* g_particle_position_size_data = new GLfloat[maxParticles * 4];

//  GLubyte* g_particle_colour_data = new GLubyte[maxParticles * 4];

  int m_numParticles;

  Particle *baseParticle;

  std::vector<Particle*> particleList;


};





#endif
