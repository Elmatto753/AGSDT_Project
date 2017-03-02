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

  void makeParticles();

  // To stick with C++11, implement C++14 function make_unique
  template<typename T, typename ...Args>
  std::unique_ptr<T> make_unique(Args&& ...args) const
  {
    return std::unique_ptr<T>( new T(std::forward<Args>(args)... ) );
  }

  std::vector<std::unique_ptr<Particle>> ParticleList;

private:

  ngl::Obj mesh;


};



#endif
