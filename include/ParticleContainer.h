#ifndef PARTICLECONTAINER_H_
#define PARTICLECONTAINER_H_

#ifdef __CUDACC__
#define CUDA_CALLABLE_MEMBER __host__ __device__
#else
#define CUDA_CALLABLE_MEMBER
#endif

#include <algorithm>
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

  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Loads the particle mesh
  //----------------------------------------------------------------------------------------------------------------------
  void loadParticleModel();
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Getter for the particle mesh
  //----------------------------------------------------------------------------------------------------------------------
  std::shared_ptr<ngl::Obj> getMesh() { return m_Mesh; }
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Getter for the size of the particle mesh
  //----------------------------------------------------------------------------------------------------------------------
  uint getMeshSize() { return m_MeshSize; }
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Getter for the number of particles inside the mesh
  //----------------------------------------------------------------------------------------------------------------------
  int getNumParticles() { return particleList.size(); }
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Getter for the list of particles
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<Particle*> getParticleList() { return particleList; }
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Removes a particle from the particle list
    /// @param *p Pointer to the particle to be removed
  //----------------------------------------------------------------------------------------------------------------------
  void removeParticle(Particle *p);
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Makes a particle at the given position if it is within the given mesh
    /// @param [in] _pos Position to attempt to place a particle
    /// @param [in] _mesh Mesh to test against
  //----------------------------------------------------------------------------------------------------------------------
  void makeParticleAt(ngl::Vec3 _Pos, std::shared_ptr<ngl::Obj> _Mesh);
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Establishes particle bonds by seeking neighbours in each direction
    /// @param [in] _Xtest distance to test to in the X-direction
    /// @param [in] _Ytest distance to test to in the Y-direction
    /// @param [in] _Ztest distance to test to in the Z-direction
  //----------------------------------------------------------------------------------------------------------------------
  void setParticleNeighbours(float _Xtest, float _Ytest, float _Ztest);
  //-----------------------------------------------------------------------------------
  ///@brief tests for intersection between an upwards ray from particle and the mesh
  /// @param[in] _at particle reference
  /// @param[in] _mesh mesh to test against
  ///@returns true if particle is inside the mesh
  //-----------------------------------------------------------------------------------
  bool testParticleInMesh(ngl::Vec3 _Pos, std::shared_ptr<ngl::Obj> _Mesh);

private:
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief List of particles within the mesh
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<Particle*> particleList;
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Mesh to be used for displaying particles
  //----------------------------------------------------------------------------------------------------------------------
  std::shared_ptr<ngl::Obj> m_Mesh;
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Size of the mesh
  //----------------------------------------------------------------------------------------------------------------------
  uint m_MeshSize;

};

#endif
