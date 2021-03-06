#include "ParticleContainer.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file ParticleContainer.cpp
/// @brief A container class for manipulating particles filling the mesh
//----------------------------------------------------------------------------------------------------------------------

ParticleContainer::ParticleContainer()
{

}

ParticleContainer::~ParticleContainer()
{

}

// Loads in the particle model
void ParticleContainer::loadParticleModel()
{
  m_mesh.reset(new ngl::Obj("models/Particle.obj"));
  m_mesh->scale(0.5f, 0.5f, 0.5f);
  m_mesh->createVAO();
  m_meshSize = m_mesh->getMeshSize();
}

// Makes a particle at the given position if it is inside the given mesh
void ParticleContainer::makeParticleAt(ngl::Vec3 _Pos, std::shared_ptr<ngl::Obj> _Mesh)
{
  if(testParticleInMesh(_Pos, _Mesh) == true)
  {
    Particle *p = new Particle;
    p->m_position = _Pos;
    p->m_ID = particleList.size();
    particleList.push_back(p);
  }
}

// Casts a ray upward to test if a point is in the given mesh
bool ParticleContainer::testParticleInMesh(ngl::Vec3 _Pos, std::shared_ptr<ngl::Obj> _Mesh)
{
  uint numHits = 0; // If this is odd, the particle is in the mesh
  Ray r;
  r.m_direction = ngl::Vec3(0.0f, 1.0f, 0.0f); // Up vector
  r.m_startPoint = _Pos;
  r.m_endPoint = (_Pos + (_Mesh->getBBox().height() * r.m_direction)); // The height of the mesh's bounding box, ensuring the ray travels far enough
  ngl::Vec3 u, v; // Triangle edge vectors
  ngl::Vec3 n; // Triangle normal
  ngl::Vec3 w0; // Vector between Ray start and triangle vertex
  ngl::Vec3 w; // Vector between intersection triangle vertex
  ngl::Vec3 I; // Intersection point of Ray with plane
  // Loop though the mesh faces
  // This code was adapted from http://geomalgorithms.com/a06-_intersect-2.html
  // Written by Dan Sunday
  for(ngl::Face f : _Mesh->getFaceList())
  {
    //Test for degenerate tris
    u = _Mesh->getVertexAtIndex(f.m_vert.at(1)) - _Mesh->getVertexAtIndex(f.m_vert.at(0));
    v = _Mesh->getVertexAtIndex(f.m_vert.at(2)) - _Mesh->getVertexAtIndex(f.m_vert.at(0));
    n = u.cross(v);
    if(n.lengthSquared() == 0.0)
    {
      std::cerr<<"Error in triangle in input mesh\n";
      continue;
    }

    w0 = r.m_startPoint - _Mesh->getVertexAtIndex(f.m_vert.at(0));
    float a = -(n.dot(w0));
    float b = n.dot(r.m_direction);
    if(fabs(b) < 0.0000001f) // Ray is parallel to triangle
    {
      if(a == 0) // Ray passes through triangle plane
      {
        numHits++;
        continue;
      }
      else // Ray does not pass through triangle plane
      {
        continue;
      }
    }

    // Test intersect point of ray with plane
    float x = a / b;
    if( x < 0.0f ) // Ray moves away from triangle
    {
      continue;
    }

    I = r.m_startPoint + (x * r.m_direction); // Intersection

    // Test if Intersection with plane is in triangle
    w = I - _Mesh->getVertexAtIndex(f.m_vert.at(0));
    float uu = u.dot(u);
    float uv = u.dot(v);
    float vv = v.dot(v);
    float wu = w.dot(u);
    float wv = w.dot(v);
    float D = (uv * uv) - (uu * vv);

    float s = ((uv * wv) - (vv * wu)) / D;
    if( s < 0.0f || s > 1.0f ) // I is not in triangle
    {
      continue;
    }

    float t = ((uv * wu) - (uu * wv)) / D;
    if( t < 0.0f || (s + t) > 1.0f) // I is not in triangle
    {
      continue;
    }

    numHits++; // I is in triangle
  }

  if(numHits % 2 == 0) // Passes through an even number of tris
  {
    return false; // Is outside mesh
  }

  return true; // Is inside mesh

}

// Finds the neighbouring particles for each particle
void ParticleContainer::setParticleNeighbours(float _Xtest, float _Ytest, float _Ztest)
{
  for(Particle *p : particleList)
  {
    for(Particle *q : particleList)
    {
      if(p->m_position + ngl::Vec3(_Xtest, 0.0f, 0.0f) == q->m_position ||
         p->m_position - ngl::Vec3(_Xtest, 0.0f, 0.0f) == q->m_position ||
         p->m_position + ngl::Vec3(0.0f, _Ytest, 0.0f) == q->m_position ||
         p->m_position - ngl::Vec3(0.0f, _Ytest, 0.0f) == q->m_position ||
         p->m_position + ngl::Vec3(0.0f, 0.0f, _Ztest) == q->m_position ||
         p->m_position - ngl::Vec3(0.0f, 0.0f, _Ztest) == q->m_position)
      {
        p->connectedParticles.push_back(q);
      }
    }
  }
}

// Removes a particle from the particle list using the "Erase-remove idiom"
void ParticleContainer::removeParticle(Particle *p)
{
  particleList.erase(std::remove(particleList.begin(), particleList.end(), p), particleList.end());
  particleList.shrink_to_fit();
}


