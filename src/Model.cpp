#include "Model.h"


Model::Model()
{

}


Model::~Model()
{

}

void Model::loadModel(std::string _file)
{
  mesh.load(_file);
  mesh.createVAO();

}

void Model::draw()
{
  mesh.draw();
}
