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
  mesh.reset(new ngl::Obj(_file));
  mesh->createVAO();
}

void Model::draw()
{
  mesh->draw();
}

void Model::setPosition(ngl::Vec3 _newPos)
{
  m_Position = _newPos;
}

void Model::move(ngl::Vec3 _delta)
{
//  m_Position += _delta;
//  for(uint i = 0; i < m_Container.particleList.size(); i++)
//  {
//    m_Container.particleList.at(i)->move(_delta);
//  }
}

void Model::makeParticles()
{
//  makeCells(5);
//  ParticleList.clear();
//  cell Test;
//  Test.centre = mesh.getBBox().center();
//  Test.max = ngl::Vec3(mesh.getBBox().maxX(), mesh.getBBox().maxY(), mesh.getBBox().maxZ());
//  Test.min = ngl::Vec3(mesh.getBBox().minX(), mesh.getBBox().minY(), mesh.getBBox().minZ());
//  for(uint i = 0; i < mesh.getNumVerts(); i++)
//  {
//    std::unique_ptr<Particle> p = make_unique<Particle>();
//    p->setPosition(mesh.getVertexList().at(i) + m_Position);
//    p->setID(i);
//    ParticleList.push_back(std::move(p));
//  }

//  std::unique_ptr<Particle> p = make_unique<Particle>();
//  p->setPosition(Test.centre + m_Position);
//  ParticleList.push_back(std::move(p));

}

void Model::makeCells(uint numCells)
{

  float XDepth = mesh->getBBox().maxX() - mesh->getBBox().minX();
  float YDepth = mesh->getBBox().maxY() - mesh->getBBox().minY();
  float ZDepth = mesh->getBBox().maxZ() - mesh->getBBox().minZ();

  float XIncrement = XDepth / numCells;
  float YIncrement = YDepth / numCells;
  float ZIncrement = ZDepth / numCells;

  for(uint i = 0; i < numCells; i++)
  {
    for(uint j = 0; j < numCells; j++)
    {
      for(uint k = 0; k < numCells; k++)
      {
        cell c;
        c.min = ngl::Vec3(mesh->getBBox().minX() + (i * XIncrement),
                          mesh->getBBox().minY() + (j * YIncrement),
                          mesh->getBBox().minZ() + (k * ZIncrement));
        c.max = ngl::Vec3(mesh->getBBox().maxX() - (((numCells - 1) - i) * XIncrement),
                          mesh->getBBox().maxY() - (((numCells - 1) - j) * YIncrement),
                          mesh->getBBox().maxZ() - (((numCells - 1) - k) * ZIncrement));
        CellList.push_back(c);
      }
    }
  }


}












