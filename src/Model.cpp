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
  Particle *p;
  for(uint i = 0; i < mesh.getNumVerts(); i++)
  {
    p = new Particle;
    p->setPosition(mesh.getVertexList().at(i));
    p->setID(i);
    ParticleList.push_back(p);
  }
}
