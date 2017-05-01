#ifndef PARTICLECONTAINER_H_
#define PARTICLECONTAINER_H_

#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Obj.h>
#include "Particle.h"
#include "Ray.h"


class ParticleContainer
{

public:

  ParticleContainer();

  ~ParticleContainer();

  void loadParticleModel();

  void drawParticles();

  std::shared_ptr<ngl::Obj> getMesh() { return m_Mesh; }

  uint getMeshSize() { return m_MeshSize; }

  int getNumParticles() { return particleList.size(); }

  Particle* getBaseParticle() { return baseParticle; }

  std::vector<Particle*> getParticleList() { return particleList; }

  void setParticlePosition(uint _at, ngl::Vec3 _position);

  void makeParticleAt(ngl::Vec3 _pos, std::shared_ptr<ngl::Obj> _mesh);

  void setParticleNeighbours(float _Xtest, float _Ytest, float _Ztest);


  //-----------------------------------------------------------------------------------
  ///@brief tests for intersection between an upwards ray from particle and the mesh
  /// @param[in] _at particle reference
  /// @param[in] _mesh mesh to test against
  ///@returns true if particle is inside the mesh
  //-----------------------------------------------------------------------------------
  bool testParticleInMesh(Particle *p, std::shared_ptr<ngl::Obj> _mesh);

private:

  int maxParticles = 100000;

//  GLfloat* g_particle_position_size_data = new GLfloat[maxParticles * 4];

//  GLubyte* g_particle_colour_data = new GLubyte[maxParticles * 4];

  int m_numParticles;

  Particle *baseParticle;

  std::vector<Particle*> particleList;

  std::shared_ptr<ngl::Obj> m_Mesh;

  uint m_MeshSize;


};



#endif
