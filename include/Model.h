#ifndef MODEL_H_
#define MODEL_H_

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ngl/Obj.h>

class Model
{

public:

  Model();
  ~Model();

  void loadModel(std::string _file);
  void draw();

private:

  ngl::Obj mesh;


};



#endif
