#include <memory>
#include "Model.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file Model.cpp
/// @brief Input model to be turned into particles
//----------------------------------------------------------------------------------------------------------------------

Model::Model()
{

}

Model::~Model()
{

}

// Loads in a mesh from an input file
void Model::loadMesh(std::string _file)
{
  m_mesh.reset(new ngl::Obj(_file));
  m_mesh->createVAO();
}

// Moves the mesh
void Model::move(ngl::Vec3 _delta)
{
  m_position += _delta;
}

// Divides the mesh into sections and places a particle at any point inside the mesh
void Model::makeParticles(uint numDivsX, uint numDivsY, uint numDivsZ)
{

  // The bounding box's dimensions
  float XDepth = m_mesh->getBBox().maxX() - m_mesh->getBBox().minX();
  float YDepth = m_mesh->getBBox().maxY() - m_mesh->getBBox().minY();
  float ZDepth = m_mesh->getBBox().maxZ() - m_mesh->getBBox().minZ();

  // Particle placement step
  float XIncrement = XDepth / numDivsX;
  float YIncrement = YDepth / numDivsY;
  float ZIncrement = ZDepth / numDivsZ;

  for(uint i = 0; i < numDivsX; i++)
  {
    // This can take a long time, so give the user a progress update
    // Candidate for future parallelisation
    std::cout<<i * (100 / numDivsX)<<"%\n";
    for(uint j = 0; j < numDivsY; j++)
    {
      for(uint k = 0; k < numDivsZ; k++)
      {
        // Attempts to place a particle at this position
        m_container.makeParticleAt(ngl::Vec3(m_mesh->getBBox().maxX() - (((numDivsX - 1) - i) * XIncrement),
                                             m_mesh->getBBox().maxY() - (((numDivsY - 1) - j) * YIncrement),
                                             m_mesh->getBBox().maxZ() - (((numDivsZ - 1) - k) * ZIncrement)),
                                   m_mesh);
      }
    }
  }

  std::cout<<"100% \nFinding neighbours\n";
  // Stores nearby particles to be used when dispersing force
  m_container.setParticleNeighbours(XIncrement, YIncrement, ZIncrement);
}

