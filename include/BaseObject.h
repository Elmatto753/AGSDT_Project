#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <assert.h>
#include <ngl/Obj.h>
#include <ngl/Mat4.h>
#include <QObject>

//----------------------------------------------------------------------------------------------------------------------
/// @file BaseObject.h
/// @brief Base class for object types
/// @author Matt Skellon
/// @version 1.0
/// @date 04/05/17
/// @class BaseObject
/// Revision History :
/// Initial version
//----------------------------------------------------------------------------------------------------------------------

class BaseObject
{
public:

  BaseObject();
  ~BaseObject();

public:
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Getter for an object's position
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 getPosition() { return m_position; }
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets an object's position
    /// @param [in] _pos the new position
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setPosition(ngl::Vec3 _pos);
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Getter for the object's mesh
  //----------------------------------------------------------------------------------------------------------------------
  std::shared_ptr<ngl::Obj> getMesh() { return m_mesh; }
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Virtual function for loading in a mesh (to be overriden)
  //----------------------------------------------------------------------------------------------------------------------
  virtual void loadMesh() {}
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Getter for the object's transformation matrix
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat4 getTransform() { return m_transform; }
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Getter for the size of the mesh
  //----------------------------------------------------------------------------------------------------------------------
  uint getMeshSize() { return m_meshSize; }

protected:
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief The object's world position
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_position;
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief The object mesh
  //----------------------------------------------------------------------------------------------------------------------
  std::shared_ptr<ngl::Obj> m_mesh;
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Transformation matrix for drawing the object
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat4 m_transform;
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Size of the mesh
  //----------------------------------------------------------------------------------------------------------------------
  uint m_meshSize;

};




#endif
