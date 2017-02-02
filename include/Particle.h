#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <ngl/Vec3.h>

class Particle
{
public:

  // Getter for particle's position
  ngl::Vec3 getPosition() { return m_Position; }

  // Set particle's position in the world
  void setPosition(ngl::Vec3 newPos);

  // Move particle by amount delta
  void move(ngl::Vec3 delta);


private:

  Particle();

  ~Particle();

  ngl::Vec3 m_Position;

};



#endif
