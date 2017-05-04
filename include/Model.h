#ifndef MODEL_H_
#define MODEL_H_

#include "BaseObject.h"
#include "ParticleContainer.h"

class Model : public BaseObject
{
private:

  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Object to hold and manipulate the particles in this mesh
  //----------------------------------------------------------------------------------------------------------------------
  ParticleContainer m_Container;

public:

  Model();
  ~Model();

  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Loads in a mesh. Overrides virtual function in BaseObject.h
    /// @param [in] _file The file to load the mesh from
  //----------------------------------------------------------------------------------------------------------------------
  void loadMesh(std::string _file);
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Getter for the particle container
  //----------------------------------------------------------------------------------------------------------------------
  ParticleContainer* getContainer() { return &m_Container; }
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Moves this object
    /// @param [in] _delta The amount to move the object by
  //----------------------------------------------------------------------------------------------------------------------
  void move(ngl::Vec3 _delta);

  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Fills this object's mesh with particles by dividing the bounding box
    /// and testing if points are inside the mesh
    /// @param [in] _divX Number of divisions in the X-direction
    /// @param [in] _divY Number of divisions in the Y-direction
    /// @param [in] _divZ Number of divisions in the Z-direction
  //----------------------------------------------------------------------------------------------------------------------
  void makeParticles(uint numDivsX, uint numDivsY, uint numDivsZ);

};



#endif
