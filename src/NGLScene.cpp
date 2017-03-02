#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <iostream>

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Blank NGL");
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}


void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  ngl::ShaderLib *shader =ngl::ShaderLib::instance();

  shader->createShaderProgram("Colour");
  shader->attachShader("ColourVertex",ngl::ShaderType::VERTEX);
  shader->attachShader("ColourFragment",ngl::ShaderType::FRAGMENT);

  shader->loadShaderSource("ColourVertex","shaders/VertShader.glsl");
  shader->loadShaderSource("ColourFragment","shaders/FragShader.glsl");

  shader->compileShader("ColourVertex");
  shader->compileShader("ColourFragment");

  shader->attachShaderToProgram("Colour","ColourVertex");
  shader->attachShaderToProgram("Colour","ColourFragment");
  shader->linkProgramObject("Colour");
  (*shader)["Colour"]->use();
  shader->autoRegisterUniforms("Colour");
  shader->printProperties();
  shader->printRegisteredUniforms("Colour");

  shader->setRegisteredUniform("Colour",1.0f,1.0f,1.0f,0.0f);
  shader->setRegisteredUniform("lightPos",m_lightPos);
  shader->setRegisteredUniform("lightDiffuse",1.0f,1.0f,1.0f,1.0f);

  // Create the projection matrix
  cam.move(0.0, 2.0, 2.0);
  cam.moveLook(0.0f, 3.0f, 0.0f);
  m_proj=ngl::perspective(90.0f,float(width()/height()),0.1,200);
  m_view=ngl::lookAt(cam.getEye().toVec3(), cam.getLook().toVec3(), ngl::Vec3(0.0f, 1.0f, 0.0f));

  Input.loadModel("models/Bomberman.obj");
  Input.makeParticles();


}

void NGLScene::loadToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  shader->use("Colour");

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  ngl::Mat4 R;

  shader->setRegisteredUniform("lightPos", m_lightPos);
  M=m_transform.getMatrix()/**m_mouseGlobalTX*/;
//  MV=  M*ngl::Mat4(cam.getSideVector().m_x, cam.getSideVector().m_y, cam.getSideVector().m_z, 0.0f,
//                   0.0f,1.0f,0.0f,0.0f,
//                   cam.getForwardVector().m_x, cam.getForwardVector().m_y, cam.getForwardVector().m_z, 0.0f,
//                   1.0f,1.0f,1.0f,1.0f);
  m_view = ngl::lookAt(cam.getEye().toVec3(), cam.getLook().toVec3(), ngl::Vec3(0.0f, 1.0f, 0.0f));
//  R= m_transform.getRotation();
  MV = M*m_view;
  MVP = MV*m_proj;
  normalMatrix=MV;
  normalMatrix.inverse();
//  shader->setShaderParamFromMat4("MV",MV);
//  shader->setShaderParamFromMat4("MVP",MVP);
//  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
//  shader->setShaderParamFromMat4("M",M);
  shader->setUniform("MVP",MVP);
  shader->setShaderParam4f("Colour", 0.5f, 0.5f, 0.5f, 1.0f);
}

void NGLScene::rotateCamAboutLook(float _x, float _y)
{
  //float radius = ngl::Vec3(cam.getLook().toVec3() - cam.getEye().toVec3()).length();
//  m_transform.addRotation(_x, _y, 0.0f);
//  cam.moveEye(m_transform.getRotation().m_x, m_transform.getRotation().m_y, m_transform.getRotation().m_z);
}


void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);
  m_transform.setRotation(0.0f, 0.0f, 0.0f);
  m_transform.setScale(1.0f, 1.0f, 1.0f);
  for(uint i = 0; i < Input.ParticleList.size(); i++)
  {
    m_transform.setPosition(Input.ParticleList.at(i)->getPosition());
    Input.ParticleList.at(i)->setPosition(m_transform.getPosition());
    loadToShader();
    Input.ParticleList.at(i)->draw();
  }
//  Input.draw();

  update();

}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quit
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());

  break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}
