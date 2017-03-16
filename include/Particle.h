#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <ngl/Vec3.h>
#include <ngl/Obj.h>

class ParticleContainer
{
public:

  ParticleContainer();

  ~ParticleContainer();

  // Getter for particle's position
  ngl::Vec3 getPosition() { return m_Position; }

  // Getter for particle ID
  uint getID() { return m_ID; }

  // Getter for next particle's ID
  uint getNext() { return m_next; }

  // Set particle's position in the world
  void setPosition(ngl::Vec3 newPos);

  // Set particle ID
  void setID(uint newID);

  // Set next particle
  void setNext(ParticleContainer *_nextParticle);

  // Move particle by amount delta
  void move(ngl::Vec3 delta);

  void draw();

  void initBuffers();


private:


  ngl::Vec3 m_Position;
  ngl::Obj mesh;

  // ID of next particle
  uint m_next;

  uint m_ID;

  // Buffers for particle generation (currently using billboards)



  GLuint billboard_vertex_buffer;

  GLuint particles_position_buffer;

  GLuint particles_colour_buffer;




};



#endif
