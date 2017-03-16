#ifndef MODEL_H_
#define MODEL_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ngl/Obj.h>
#include <Particle.h>

class Model
{

public:

  Model();
  ~Model();

  void loadModel(std::string _file);
  void draw();
  ngl::Vec3 getPosition() { return m_Position; }
  void setPosition(ngl::Vec3 _newPos);
  void move(ngl::Vec3 _delta);

  void makeParticles();

  // Divides the mesh's BBox in the specified number of cells in each direction
  // numCells * numCells * numCells
  void makeCells(uint numCells);

  struct cell
  {
    ngl::Vec3 min;
    ngl::Vec3 max;
    ngl::Vec3 centre = min + (0.5 * (max-min));
  };

  // To stick with C++11, implement C++14 function make_unique
  template<typename T, typename ...Args>
  std::unique_ptr<T> make_unique(Args&& ...args) const
  {
    return std::unique_ptr<T>( new T(std::forward<Args>(args)... ) );
  }

  std::vector<std::unique_ptr<ParticleContainer>> ParticleList;

  std::vector<cell> CellList;
private:

  ngl::Obj mesh;

  ngl::Vec3 m_Position;



};



#endif
