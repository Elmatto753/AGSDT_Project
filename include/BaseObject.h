#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ngl/Obj.h>

class BaseObject
{
public:

  BaseObject();
  ~BaseObject();

  ngl::Vec3 getPosition() { return m_Position; }
  void setPosition(ngl::Vec3 _pos);

  std::shared_ptr<ngl::Obj> getMesh() { return m_Mesh; }
  virtual void loadMesh() {}

protected:

  ngl::Vec3 m_Position;

  std::shared_ptr<ngl::Obj> m_Mesh;


};






#endif
