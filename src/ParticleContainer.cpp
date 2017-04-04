#include "ParticleContainer.h"

ParticleContainer::ParticleContainer()
{

}

ParticleContainer::~ParticleContainer()
{

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

//  static const GLfloat g_vertex_buffer_data[] =
//  {
//    -0.5f, -0.5f, 0.0f,
//    0.5f, -0.5f, 0.0f,
//    -0.5f, 0.5f, 0.0f,
//    0.5f, 0.5f, 0.0f
//  };

//  glGenBuffers(1, &billboard_vertex_buffer);
//  glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
//  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

//  glGenBuffers(1, &particles_position_buffer);
//  glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
//  glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

//  glGenBuffers(1, &particles_colour_buffer);
//  glBindBuffer(GL_ARRAY_BUFFER, particles_colour_buffer);
//  glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);

  glGenBuffers(1, &m_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
  glBufferData(GL_ARRAY_BUFFER, m_numParticles * sizeof(Particle), &particleList[0], GL_STATIC_DRAW);

  glBindVertexArray(baseParticle->getMesh().mapVAOVerts()); // not sure if this accesses the VAO, may even be done by ngl

}

//void ParticleContainer::updateBuffers()
//{
//  glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
//  glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
//  glBufferSubData(GL_ARRAY_BUFFER, 0, m_numParticles * sizeof(GLubyte) * 4, g_particle_position_size_data);

//  glBindBuffer(GL_ARRAY_BUFFER, particles_colour_buffer);
//  glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
//  glBufferSubData(GL_ARRAY_BUFFER, 0, m_numParticles * sizeof(GLubyte) * 4, g_particle_colour_data);
//}

//void ParticleContainer::bindBuffers()
//{
//  //vertices
//  glEnableVertexAttribArray(0);
//  glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
//  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

//  //particles centres
//  glEnableVertexAttribArray(1);
//  glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
//  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

//  //particle colours
//  glEnableVertexAttribArray(2);
//  glBindBuffer(GL_ARRAY_BUFFER, particles_colour_buffer);
//  glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0);

//  glVertexAttribDivisor(0, 0);
//  glVertexAttribDivisor(1, 1);
//  glVertexAttribDivisor(2, 1);

//  glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_numParticles);

//  glDisableVertexAttribArray(0);
//  glDisableVertexAttribArray(1);
//  glDisableVertexAttribArray(2);


//}
