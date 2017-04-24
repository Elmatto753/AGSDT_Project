#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <ngl/Vec3.h>
#include <ngl/Obj.h>



typedef struct Particle
{
  ngl::Vec3 m_Position = ngl::Vec3(0.0f, 0.0f, 0.0f);

  std::unique_ptr<ngl::Obj> m_Mesh;

  uint m_meshSize;

  // ID of next particle
  uint m_next = 0;

  std::vector<Particle> connectedParticles;

  uint m_ID = 0;

  float m_bondStrength = 0;

} Particle;


//class Particle2
//{
//public:

//  Particle2();

//  ~Particle2();

//  // Getter for particle's position
//  ngl::Vec3 getPosition() { return m_Position; }

//  // Getter for particle ID
//  uint getID() { return m_ID; }

//  // Getter for next particle's ID
//  uint getNext() { return m_next; }

//  const ngl::Obj* getMesh() { return mesh; }

//  float getBondStrength() { return m_bondStrength; }

//  int getMeshSize() const { return m_meshSize; }
//  // Set particle's position in the world
//  void setPosition(ngl::Vec3 newPos);

//  // Set particle ID
//  void setID(uint newID);

//  // Set next particle
//  void setNext(Particle2 *_nextParticle);

//  // Move particle by amount delta
//  void move(ngl::Vec3 delta);

//  void draw();

//  void loadModel(std::string _file);


//private:


//  ngl::Vec3 m_Position;

//  ngl::Obj *mesh;
//  uint m_meshSize;

//  // ID of next particle
//  uint m_next;

//  std::vector<Particle2> connectedParticles;

//  uint m_ID;

//  float m_bondStrength;





//};



#endif
