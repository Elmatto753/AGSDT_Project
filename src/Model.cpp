#include "Model.h"
#include <memory>


Model::Model()
{

}


Model::~Model()
{

}

void Model::draw()
{
  m_Mesh->draw();
}

void Model::loadMesh(std::string _file)
{
  m_Mesh.reset(new ngl::Obj(_file));
  m_Mesh->createVAO();
}

void Model::move(ngl::Vec3 _delta)
{
  m_Position += _delta;
//  for(uint i = 0; i < m_Container.particleList.size(); i++)
//  {
//    m_Container.particleList.at(i)->move(_delta);
//  }
}

void Model::makeParticles(uint numCellsX, uint numCellsY, uint numCellsZ)
{

  float XDepth = m_Mesh->getBBox().maxX() - m_Mesh->getBBox().minX();
  float YDepth = m_Mesh->getBBox().maxY() - m_Mesh->getBBox().minY();
  float ZDepth = m_Mesh->getBBox().maxZ() - m_Mesh->getBBox().minZ();

  float XIncrement = XDepth / numCellsX;
  float YIncrement = YDepth / numCellsY;
  float ZIncrement = ZDepth / numCellsZ;

  for(uint i = 0; i < numCellsX; i++)
  {
    std::cout<<i * (100 / numCellsX)<<"%\n";
    for(uint j = 0; j < numCellsY; j++)
    {
      for(uint k = 0; k < numCellsZ; k++)
      {
//        cell c;
//        c.min = ngl::Vec3(mesh->getBBox().minX() + (i * XIncrement),
//                          mesh->getBBox().minY() + (j * YIncrement),
//                          mesh->getBBox().minZ() + (k * ZIncrement));
//        c.max = ngl::Vec3(mesh->getBBox().maxX() - (((numCells - 1) - i) * XIncrement),
//                          mesh->getBBox().maxY() - (((numCells - 1) - j) * YIncrement),
//                          mesh->getBBox().maxZ() - (((numCells - 1) - k) * ZIncrement));
//        c.centre = c.min + (0.5 * (c.max-c.min));
//        m_Container.makeParticleAt(c.centre);
//        CellList.push_back(c);

        m_Container.makeParticleAt(ngl::Vec3(m_Mesh->getBBox().maxX() - (((numCellsX - 1) - i) * XIncrement),
                                             m_Mesh->getBBox().maxY() - (((numCellsY - 1) - j) * YIncrement),
                                             m_Mesh->getBBox().maxZ() - (((numCellsZ - 1) - k) * ZIncrement)),
                                   m_Mesh);
//        m_Container.makeParticleAt(ngl::Vec3(mesh->getBBox().minX() + (i * XIncrement),
//                                             mesh->getBBox().minY() + (j * YIncrement),
//                                             mesh->getBBox().minZ() + (k * ZIncrement)));

      }
    }
  }

  std::cout<<"100% \nFinding neighbours\n";
  m_Container.setParticleNeighbours(XIncrement, YIncrement, ZIncrement);


}












