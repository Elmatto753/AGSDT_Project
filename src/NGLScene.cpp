#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/Random.h>
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
  cam.setShape( 45.0f, static_cast<float>(_w)/_h, 0.05f, 350.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}


void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(0.5f, 0.6f, 0.5f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  Input.loadModel("models/Bomberman.obj");
  //Input.makeParticles();
  m_Container.loadParticleModel();
  cam.set(ngl::Vec3(0.0f, 100.0f, 280.0f),
          ngl::Vec3(0.0f, 10.0f, 0.0f),
          ngl::Vec3(0.0f, 1.0f, 0.0f));

  cam.setShape(45.0f, 720.0f/576.0f, 0.05f, 350.0f);

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

//  shader->autoRegisterUniforms("Colour");
//  shader->printProperties();
//  shader->printRegisteredUniforms("Colour");

//  shader->setRegisteredUniform("Colour",1.0f,1.0f,1.0f,0.0f);
//  shader->setRegisteredUniform("lightPos",m_lightPos);
//  shader->setRegisteredUniform("lightDiffuse",1.0f,1.0f,1.0f,1.0f);

  glEnable(GL_DEPTH_TEST);

  GLuint tbo;
  glGenBuffers(1, &tbo);

  std::vector<ngl::Mat4> transforms(50000);
  ngl::Random *rng=ngl::Random::instance();
  ngl::Vec3 tx;
  ngl::Mat4 pos;
  ngl::Mat4 scale;

  for(auto &t : transforms)
  {
    tx = m_Container.getBaseParticle()->m_Position;
    auto yScale=rng->randomPositiveNumber(2.0f)+0.5f;
    pos.translate(tx.m_x,0.0f,tx.m_z);
    scale.scale(yScale,yScale,yScale);
    t=scale*pos;
  }

  glBindBuffer(GL_TEXTURE_BUFFER, tbo);
  glBufferData(GL_TEXTURE_BUFFER, transforms.size() * sizeof(ngl::Mat4), &transforms[0].m_00, GL_STATIC_DRAW);

  glGenTextures(1, &m_tboID);
  glActiveTexture( GL_TEXTURE0 );
  glBindTexture(GL_TEXTURE_BUFFER, m_tboID);

  glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, tbo);

  ngl::Texture t("models/Firefox_wallpaper.png");
  t.setMultiTexture(1);
  m_textureID=t.setTextureGL();
  shader->setShaderParam1i("tex",1);
  shader->setShaderParam1i("TBO",0);


  // Create the projection matrix
  m_proj=ngl::perspective(90.0f,float(width()/height()),0.1,200);
  m_view=ngl::lookAt(cam.getEye().toVec3(), cam.getLook().toVec3(), ngl::Vec3(0.0f, 1.0f, 0.0f));

  //m_Container.initBuffers();

  //Input.move(ngl::Vec3(0.0f, -5.0f, 0.0f));


}

void NGLScene::loadToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
//  shader->use("Colour");

//  ngl::Mat4 MV;
//  ngl::Mat4 MVP;
//  ngl::Mat3 normalMatrix;
//  ngl::Mat4 M;
//  ngl::Mat4 R;

//  shader->setRegisteredUniform("lightPos", m_lightPos);
//  M=m_transform.getMatrix()/**m_mouseGlobalTX*/;
////  MV=  M*ngl::Mat4(cam.getSideVector().m_x, cam.getSideVector().m_y, cam.getSideVector().m_z, 0.0f,
////                   0.0f,1.0f,0.0f,0.0f,
////                   cam.getForwardVector().m_x, cam.getForwardVector().m_y, cam.getForwardVector().m_z, 0.0f,
////                   1.0f,1.0f,1.0f,1.0f);
//  m_view = ngl::lookAt(cam.getEye().toVec3(), cam.getLook().toVec3(), ngl::Vec3(0.0f, 1.0f, 0.0f));
////  R= m_transform.getRotation();
//  MV = M*m_view;
//  MVP = MV*m_proj;
//  normalMatrix=MV;
//  normalMatrix.inverse();
////  shader->setShaderParamFromMat4("MV",MV);
////  shader->setShaderParamFromMat4("MVP",MVP);
////  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
////  shader->setShaderParamFromMat4("M",M);
//  shader->setUniform("MVP",MVP);
//  shader->setShaderParam4f("Colour", 0.5f, 0.5f, 0.5f, 1.0f);

  (*shader)["Colour"]->use();
  shader->setUniform("mouseTX",m_mouseGlobalTX);
  shader->setUniform("VP",cam.getVPMatrix());
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
//  m_transform.setRotation(0.0f, 0.0f, 0.0f);
//  m_transform.setScale(1.0f, 1.0f, 1.0f);
  m_Container.getBaseParticle()->m_Position.m_y += 0.1;

  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  rotX.rotateX(m_win.spinXFace);
  rotY.rotateY(m_win.spinYFace);

  m_mouseGlobalTX=rotY*rotX;

  m_mouseGlobalTX.m_m[3][0] = m_Container.getBaseParticle()->m_Position.m_x;
  m_mouseGlobalTX.m_m[3][1] = m_Container.getBaseParticle()->m_Position.m_y;
  m_mouseGlobalTX.m_m[3][2] = m_Container.getBaseParticle()->m_Position.m_z;

  m_Container.getBaseParticle()->m_Mesh->bindVAO();
  loadToShader();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_BUFFER, m_tboID);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_textureID);

  glDrawArraysInstanced(GL_TRIANGLES, 0, m_Container.getBaseParticle()->m_Mesh->getMeshSize(),1000);
  m_Container.getBaseParticle()->m_Mesh->unbindVAO();

  Input.getMesh()->bindVAO();
  loadToShader();
  glDrawArrays(GL_TRIANGLES, 0, Input.getMesh()->getMeshSize());

//  glEnableClientState(GL_VERTEX_ARRAY);
//  glBindBuffer(GL_ARRAY_BUFFER, m_Container.getBuffer());
//  glVertexPointer(3, GL_FLOAT, 0, 0);
//  glDrawArraysInstanced( GL_TRIANGLE_STRIP, 0, m_Container.getBufferSize(), m_Container.getNumParticles() );
//  for(uint i = 0; i < Input.CellList.size(); i++)
//  {
////    m_transform.setPosition(Input.ParticleList.at(i)->getPosition());
////    Input.ParticleList.at(i)->setPosition(m_transform.getPosition());
////    loadToShader();
////    Input.ParticleList.at(i)->draw();
//    m_transform.setPosition(Input.ParticleList.at(i)->getPosition() +
//                            ngl::Vec3(cam.getViewMatrix().m_00, cam.getViewMatrix().m_10, cam.getViewMatrix().m_20) * -0.5f * 1.0f +
//                            cam.getUp().toVec3() * 0.5f * 1.0f);
//    loadToShader();
//    Input.ParticleList.at(i)->draw();
//  }

  //Draw the model
//  std::cout<<Input.getPosition().m_x<<" "<<Input.getPosition().m_y<<" "<<Input.getPosition().m_z<<"\n";
//  m_transform.setPosition(Input.getPosition());
//  loadToShader();
//  Input.getMesh()->bindVAO();

//  loadToShader();

//  glDrawArraysInstanced(GL_TRIANGLES, 0, Input.getMesh()->getMeshSize(), 10);
//  Input.getMesh()->unbindVAO();
//  m_Container.drawParticles();

//  m_transform.setPosition(Input.ParticleList.back()->getPosition());
//  loadToShader();
//  Input.ParticleList.back()->draw();

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
