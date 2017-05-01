#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <ngl/Vec3.h>
#include <ngl/Obj.h>



typedef struct Particle
{
  //------------------------------------------------------------------------
  /// @brief vector for particle's position
  //------------------------------------------------------------------------
  ngl::Vec3 m_Position = ngl::Vec3(0.0f, 0.0f, 0.0f);
//  std::shared_ptr<ngl::Obj> m_Mesh;

  //uint m_meshSize;


  //------------------------------------------------------------------------
  /// @brief ID of next particle
  //------------------------------------------------------------------------
  uint m_next = 0;

  //------------------------------------------------------------------------
  /// @brief pointers to neighbouring particles
  //------------------------------------------------------------------------
  std::vector<Particle *> connectedParticles;

  //------------------------------------------------------------------------
  /// @brief particle ID
  //------------------------------------------------------------------------
  uint m_ID = 0;

  //------------------------------------------------------------------------
  /// @brief strength of connection to other particles (the more particles connected, the stronger the particle
  //------------------------------------------------------------------------
  float m_BondStrength = 0.0f;

  //------------------------------------------------------------------------
  /// @brief
  //------------------------------------------------------------------------
  float m_Radius = 0.0f;

  //------------------------------------------------------------------------
  /// @brief force being exerted on this particle (if this exceeds bond strength, the particle will break)
  //------------------------------------------------------------------------
  float m_InForce = 0.0f;

} Particle;

#endif
