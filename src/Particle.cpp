#include "Particle.h"


ParticleContainer::ParticleContainer()
{
//  mesh.load("models/Sphere.obj");
//  mesh.scale(0.1, 0.1, 0.1);
//  mesh.createVAO();
}

ParticleContainer::~ParticleContainer()
{

}

void ParticleContainer::setPosition(ngl::Vec3 newPos)
{
  m_Position = newPos;
}

void ParticleContainer::setID(uint newID)
{
  m_ID = newID;
}

void ParticleContainer::setNext(ParticleContainer *_nextParticle)
{
  m_next = _nextParticle->getID();
}

void ParticleContainer::move(ngl::Vec3 delta)
{
  m_Position += delta;
}

void::ParticleContainer::draw()
{
  mesh.calcDimensions();
  mesh.draw();
}

void ParticleContainer::initBuffers()
{
//  g_vertex_buffer_data[0] =
//  {
//    -0.5f, -0.5f, 0.0f,
//    0.5f, -0.5f, 0.0f,
//    -0.5f, 0.5f, 0.0f,
//    0.5f, 0.5f, 0.0f
//  };

  static const GLfloat g_vertex_buffer_data[] =
  {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f
  };

  glGenBuffers(1, &billboard_vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  glGenBuffers(1, &particles_position_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
  glBufferData(GL_ARRAY_BUFFER, /*maximum particles*/ 1000000 * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

  glGenBuffers(1, &particles_colour_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, particles_colour_buffer);
  glBufferData(GL_ARRAY_BUFFER, /*maximum particles*/ 1000000 * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

}
