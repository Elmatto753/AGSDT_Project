#ifndef IMPACTOBJECT_H_
#define IMPACTOBJECT_H_

#include "BaseObject.h"


class ImpactObject : public BaseObject
{
public:

  ImpactObject();
  ~ImpactObject();

//  ngl::Vec3 getPosition() { return m_Position; }
//  void setPosition(ngl::Vec3 _pos);
  ngl::Vec3 getDirection() { return m_Direction; }
  void setDirection(ngl::Vec3 _dir);
  float getVelocity() { return m_Velocity; }
  void setVelocity(float _vel);
  float getMass() { return m_Mass; }
  void setMass(float _mass);
  float getRadius() {return m_Radius; }
  void setRadius(float _rad);
//  std::shared_ptr<ngl::Obj> getMesh() { return m_Mesh; }
  void loadMesh(std::string _file);

  void update();

private:

//  ngl::Vec3 m_Position;

  ngl::Vec3 m_Direction;

  float m_Velocity;

  float m_Mass;

  float m_Radius;

//  std::shared_ptr<ngl::Obj> m_Mesh;


};

#endif
