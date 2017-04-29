#ifndef MODEL_H_
#define MODEL_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ngl/Obj.h>
#include "ParticleContainer.h"

class Model
{
private:

  struct cell
  {
    ngl::Vec3 min;
    ngl::Vec3 max;
    ngl::Vec3 centre;
  };
  std::shared_ptr<ngl::Obj> mesh;

  ngl::Vec3 m_Position;
  ngl::Mat4 m_Transform;

  std::vector<cell> CellList;

  ParticleContainer m_Container;

public:

  Model();
  ~Model();

  void loadModel(std::string _file);
  void draw();
  ngl::Vec3 getPosition() { return m_Position; }
  ParticleContainer* getContainer() { return &m_Container; }
  ngl::Mat4 getTransform() { return m_Transform; }
  void setPosition(ngl::Vec3 _newPos);
  void move(ngl::Vec3 _delta);

  // Divides the mesh's BBox in the specified number of cells in each direction
  // numCells * numCells * numCells
  void makeCells(uint numCellsX, uint numCellsY, uint numCellsZ);
  cell getCell(uint _cellIndex) { if(_cellIndex < CellList.size())
                                        return CellList.at(_cellIndex); }
  int getNumCells() { return CellList.size(); }

  std::shared_ptr<ngl::Obj> getMesh() { return mesh; }

  void makeParticles();



  // To stick with C++11, implement C++14 function make_unique
//  template<typename T, typename ...Args>
//  std::unique_ptr<T> make_unique(Args&& ...args) const
//  {
//    return std::unique_ptr<T>( new T(std::forward<Args>(args)... ) );
//  }

  //std::vector<std::unique_ptr<Particle>> ParticleList;

};



#endif
