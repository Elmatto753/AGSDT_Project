#include "ParticleContainer.h"

ParticleContainer::ParticleContainer()
{
  baseParticle = new Particle;

//  m_numParticles = 10;

//  particleList.resize(m_numParticles);

//  for(auto &i : particleList)
//  {
//    i = new Particle;
//  }
}

ParticleContainer::~ParticleContainer()
{

}

void ParticleContainer::loadParticleModel()
{
  //baseParticle->m_ID = 0;
  m_Mesh.reset(new ngl::Obj("models/Sphere.obj"));
  m_Mesh->scale(0.5f, 0.5f, 0.5f);
  m_Mesh->createVAO();
  //m_Mesh->getMeshSize();

}

void ParticleContainer::drawParticles()
{
  //baseParticle->m_Mesh->bindVAO();
}

void ParticleContainer::setParticlePosition(uint _at, ngl::Vec3 _position)
{
  particleList.at(_at)->m_Position = _position;
}

void ParticleContainer::makeParticleAt(ngl::Vec3 _pos, std::shared_ptr<ngl::Obj> _mesh)
{
  Particle *p = new Particle;
  p->m_Position = _pos;
  p->m_ID = particleList.size();
  if(testParticleInMesh(p, _mesh) == true)
  {
    particleList.push_back(p);
  }
}

bool ParticleContainer::testParticleInMesh(Particle *p, std::shared_ptr<ngl::Obj> _mesh)
{
  uint numHits = 0;
  Ray r;
  r.m_Direction = ngl::Vec3(0.0f, 1.0f, 0.0f);
  r.m_StartPoint = p->m_Position;
  r.m_EndPoint = (p->m_Position + (_mesh->getBBox().height() * r.m_Direction));
  ngl::Vec3 u, v; // Triangle edge vectors
  ngl::Vec3 n; // Triangle normal
  ngl::Vec3 w0; // Vector between Ray start and triangle vertex
  ngl::Vec3 w; // Vector between intersection triangle vertex
  ngl::Vec3 I; // Intersection point of Ray with plane
//  ngl::Vec3 pos = p->m_Position;
  for(ngl::Face f : _mesh->getFaceList())
  {
    //Test for degenerate tris
    u = _mesh->getVertexAtIndex(f.m_vert.at(1)) - _mesh->getVertexAtIndex(f.m_vert.at(0));
    v = _mesh->getVertexAtIndex(f.m_vert.at(2)) - _mesh->getVertexAtIndex(f.m_vert.at(0));
    n = u.cross(v);
    if(n.lengthSquared() == 0.0)
    {
      std::cerr<<"Error in triangle in input mesh\n";
      continue;
    }

    w0 = r.m_StartPoint - _mesh->getVertexAtIndex(f.m_vert.at(0));
    float a = -(n.dot(w0));
    float b = n.dot(r.m_Direction);
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

    I = r.m_StartPoint + (x * r.m_Direction); // Intersection

    // Test if Intersection with plane is in triangle
    w = I - _mesh->getVertexAtIndex(f.m_vert.at(0));
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

