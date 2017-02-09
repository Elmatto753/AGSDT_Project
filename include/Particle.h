#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <ngl/Vec3.h>
#include <ngl/Obj.h>

class Particle
{
public:

  Particle();

  ~Particle();

  // Getter for particle's position
  ngl::Vec3 getPosition() { return m_Position; }

  // Set particle's position in the world
  void setPosition(ngl::Vec3 newPos);

  // Move particle by amount delta
  void move(ngl::Vec3 delta);

  void draw();


private:


  ngl::Vec3 m_Position;
  ngl::Obj mesh;

  uint m_ID;

};



#endif
