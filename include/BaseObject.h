#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <assert.h>
#include <ngl/Obj.h>
#include <ngl/Mat4.h>
#include <QObject>

class BaseObject
{
public:

  BaseObject();
  ~BaseObject();

public:

  ngl::Vec3 getPosition() { return m_Position; }
  virtual void setPosition(ngl::Vec3 _pos);

  std::shared_ptr<ngl::Obj> getMesh() { return m_Mesh; }
  virtual void loadMesh() {}

  ngl::Mat4 getTransform() { return m_Transform; }

  uint getMeshSize() { return m_MeshSize; }

protected:

  ngl::Vec3 m_Position;

  std::shared_ptr<ngl::Obj> m_Mesh;

  ngl::Mat4 m_Transform;

  uint m_MeshSize;

};




#endif
