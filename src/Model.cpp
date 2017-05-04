#include "Model.h"
#include <memory>


Model::Model()
{

}


Model::~Model()
{

}

void Model::loadMesh(std::string _file)
{
  m_mesh.reset(new ngl::Obj(_file));
  m_mesh->createVAO();
}

void Model::move(ngl::Vec3 _delta)
{
  m_position += _delta;
}

void Model::makeParticles(uint numDivsX, uint numDivsY, uint numDivsZ)
{

  float XDepth = m_mesh->getBBox().maxX() - m_mesh->getBBox().minX();
  float YDepth = m_mesh->getBBox().maxY() - m_mesh->getBBox().minY();
  float ZDepth = m_mesh->getBBox().maxZ() - m_mesh->getBBox().minZ();

  float XIncrement = XDepth / numDivsX;
  float YIncrement = YDepth / numDivsY;
  float ZIncrement = ZDepth / numDivsZ;

  for(uint i = 0; i < numDivsX; i++)
  {
    std::cout<<i * (100 / numDivsX)<<"%\n";
    for(uint j = 0; j < numDivsY; j++)
    {
      for(uint k = 0; k < numDivsZ; k++)
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

        m_container.makeParticleAt(ngl::Vec3(m_mesh->getBBox().maxX() - (((numDivsX - 1) - i) * XIncrement),
                                             m_mesh->getBBox().maxY() - (((numDivsY - 1) - j) * YIncrement),
                                             m_mesh->getBBox().maxZ() - (((numDivsZ - 1) - k) * ZIncrement)),
                                   m_mesh);
//        m_Container.makeParticleAt(ngl::Vec3(mesh->getBBox().minX() + (i * XIncrement),
//                                             mesh->getBBox().minY() + (j * YIncrement),
//                                             mesh->getBBox().minZ() + (k * ZIncrement)));

      }
    }
  }

  std::cout<<"100% \nFinding neighbours\n";
  m_container.setParticleNeighbours(XIncrement, YIncrement, ZIncrement);


}












