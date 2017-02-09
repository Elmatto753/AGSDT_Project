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

void Model::makeParticles()
{
  ParticleList.clear();
  for(uint i = 0; i < mesh.getNumVerts(); i++)
  {
    Particle *p;
    p = new Particle;
    p->setPosition(mesh.getVertexList().at(i));
  }
}
