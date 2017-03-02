#include "Model.h"
#include <memory>


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
    std::unique_ptr<Particle> p = make_unique<Particle>();
    p->setPosition(mesh.getVertexList().at(i));
    p->setID(i);
    ParticleList.push_back(std::move(p));
  }
}
