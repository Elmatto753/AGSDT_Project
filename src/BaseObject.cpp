#include "BaseObject.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file BaseObject.cpp
/// @brief Provides some common attributes
//----------------------------------------------------------------------------------------------------------------------

BaseObject::BaseObject()
{

}

BaseObject::~BaseObject()
{

}

// Sets the object's position
void BaseObject::setPosition(ngl::Vec3 _pos)
{
  m_position = _pos;
}

