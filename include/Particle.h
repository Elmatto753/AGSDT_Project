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
  //------------------------------------------------------------------------
  /// @brief vector for particle's velocity
  //------------------------------------------------------------------------
  ngl::Vec3 m_Velocity = ngl::Vec3(0.0f, 0.0f, 0.0f);
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
  float m_BondStrength = 5.0f;
  //------------------------------------------------------------------------
  /// @brief Force being exerted on this particle (if this exceeds bond strength, the particle will break)
  //------------------------------------------------------------------------
  float m_InForce = 0.0f;
  //------------------------------------------------------------------------
  /// @brief Flag to indicate if particle has received excessive force
  //------------------------------------------------------------------------
  bool m_isBroken = false;
  //------------------------------------------------------------------------
  /// @brief Where the particle received force from, prevents force going "backwards"
  //------------------------------------------------------------------------
  Particle *receivedForceFrom;

} Particle;

#endif
