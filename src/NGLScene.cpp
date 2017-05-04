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
  ObjectUpdater->deleteLater();
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_cam.setShape( 45.0f, static_cast<float>(_w)/_h, 0.05f, 350.0f );
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

  Input.loadMesh("models/Bomberman_fixed.obj");
  //Input.makeParticles();
  Input.getContainer()->loadParticleModel();
  std::cout<<"Filling mesh with particles...\n";
  Input.makeParticles(10, 10, 10);

  //Impact.loadMesh("models/Sphere.obj");

  m_cam.set(ngl::Vec3(0.0f, 5.0f, 15.0f),
          ngl::Vec3(0.0f, 4.0f, 0.0f),
          ngl::Vec3(0.0f, 1.0f, 0.0f));

  m_cam.setShape(45.0f, 720.0f/576.0f, 0.05f, 350.0f);

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

//  for(uint i=0; i< m_Container.getParticleList().size(); i++)
//  {
//    m_Container.setParticlePosition(i, ngl::Vec3(0.0f, 5.0f, 3.0f));
//    std::cout<<m_Container.getParticleList().at(i)->m_Position.m_x<<"\n";
//  }

  glEnable(GL_DEPTH_TEST);

  m_light.reset(new ngl::Light(m_lightPos, ngl::Colour(1,1,1,1), ngl::LightModes::POINTLIGHT));
  ngl::Mat4 vm = m_cam.getViewMatrix();
  vm.transpose();
  m_light->setTransform(vm);
  m_light->loadToShader("light");

  ngl::Material m;
  m.setAmbient(ngl::Colour(0.1, 0.1, 0.1, 1.0));
  m.setDiffuse(ngl::Colour(1.0, 0.4, 0.1));
  m.setSpecular(ngl::Colour(1, 1, 1));
  m.setSpecularExponent(80);
  m.loadToShader("material");

  glGenBuffers(1, &tbo);

  setMultipleTransforms(ngl::Vec3(1.0f, 1.0f, 1.0f));


  //setAllTransforms(Input.getContainer()->getBaseParticle()->m_Position, ngl::Vec3(1.0f, 1.0f, 1.0f));

//  for(auto &t : transforms)
//  {
//    tx = m_Container.getBaseParticle()->m_Position;
//    auto yScale=rng->randomPositiveNumber(2.0f)+0.5f;
//    pos.translate(tx.m_x,0.0f,tx.m_z);
//    scale.scale(yScale,yScale,yScale);
//    t=scale*pos;
//  }


//  for(uint i = 0; i < Input.getContainer()->getParticleList().size(); i++)
//  {
//    Input.getContainer()->getParticleList().at(i)->m_Position = ngl::Vec3(0.0f, 0.0f, float(i));
//  }

  glGenTextures(1, &m_tboID);
  glActiveTexture( GL_TEXTURE0 );
  glBindTexture(GL_TEXTURE_BUFFER, m_tboID);

  glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, tbo);

  ngl::Texture t("models/Firefox_wallpaper.png");
  t.setMultiTexture(1);
  m_textureID=t.setTextureGL();
  shader->setShaderParam1i("tex",1);
  shader->setShaderParam1i("TBO",0);

  ObjectUpdater = new ObjectUpdateThread;
  ObjectUpdater->start();
  ObjectUpdater->setUp();

}



void NGLScene::loadToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  MV=M*m_mouseGlobalTX*m_cam.getViewMatrix();
  MVP=MV*m_cam.getProjectionMatrix();
  normalMatrix=MV;
  normalMatrix.inverse();
  shader->setRegisteredUniform("MV",MV);
  shader->setShaderParamFromMat4("M",M);
  shader->setRegisteredUniform("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shader->setShaderParam3f("viewerPos",m_cam.getEye().m_x,m_cam.getEye().m_y,m_cam.getEye().m_z);

  (*shader)["Colour"]->use();
  m_light->setPosition(m_lightPos);
  m_light->loadToShader("light");
  shader->setUniform("mouseTX", m_mouseGlobalTX);
  shader->setUniform("VP", m_cam.getVPMatrix());
}

void NGLScene::setMultipleTransforms(ngl::Vec3 _scale)
{
  Input.getContainer()->getParticleList().shrink_to_fit();
  transforms.clear();
  transforms.resize(Input.getContainer()->getNumParticles());
  //std::cout<<"numParticles: "<<Input.getContainer()->getNumParticles()<<"\n";
  ngl::Mat4 pos;
  ngl::Mat4 scale;

  ngl::Vec3 position;

  for(uint i = 0; i < transforms.size(); i++)
  {
    transforms.resize(Input.getContainer()->getNumParticles());
    position = Input.getContainer()->getParticleList().at(i)->m_Position;
//    auto yScale=_scale;
    pos.translate(position.m_x, position.m_y, position.m_z);
    if(Input.getContainer()->getParticleList().at(i)->m_isBroken == false)
    {
      scale.scale(_scale.m_x, _scale.m_y, _scale.m_z);
    }
    else
    {
      Input.getContainer()->removeParticle(Input.getContainer()->getParticleList().at(i));
      //scale.scale(0.0f, 0.0f, 0.0f);
    }
    transforms.at(i)=scale*pos;
  }

  glBindBuffer(GL_TEXTURE_BUFFER, tbo);
  glBufferData(GL_TEXTURE_BUFFER, transforms.size() * sizeof(ngl::Mat4), &transforms[0].m_00, GL_STATIC_DRAW);
  //glGenTextures(1, &m_tboID);
  glActiveTexture( GL_TEXTURE0 );
  glBindTexture(GL_TEXTURE_BUFFER, m_tboID);

  glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, tbo);

}

void NGLScene::setSingleTransform(ngl::Mat4 _transform, ngl::Vec3 _pos, ngl::Vec3 _scale)
{
  ngl::Mat4 pos;
  ngl::Mat4 scale;
//  auto t = transforms.at(_at);
  pos.translate(_pos.m_x, _pos.m_y, _pos.m_z);
  scale.scale(_scale.m_x, _scale.m_y, _scale.m_z);
  _transform=scale*pos;
  glBindBuffer(GL_TEXTURE_BUFFER, tbo);
  glBufferData(GL_TEXTURE_BUFFER, sizeof(ngl::Mat4), &_transform.m_00, GL_STATIC_DRAW);
  //glGenTextures(1, &m_tboID);
  glActiveTexture( GL_TEXTURE0 );
  glBindTexture(GL_TEXTURE_BUFFER, m_tboID);

  glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, tbo);

}

void NGLScene::setMouseGlobal(ngl::Vec3 _pos)
{
  m_mouseGlobalTX.m_m[3][0] = _pos.m_x;
  m_mouseGlobalTX.m_m[3][1] = _pos.m_y;
  m_mouseGlobalTX.m_m[3][2] = _pos.m_z;
}


void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  //std::cout<<"PaintGL begin "<<durr<<"\n";
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);

  loadToShader();

  //Input.getContainer()->getBaseParticle()->m_Position.m_y += 0.1;

  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  rotX.rotateX(m_win.spinXFace);
  rotY.rotateY(m_win.spinYFace);

  Input.setPosition(ngl::Vec3(0.0f, 0.0f, 0.0f));
  setSingleTransform(Input.getTransform() , Input.getPosition(), ngl::Vec3(1.0f, 1.0f, 1.0f));

  m_mouseGlobalTX=rotY*rotX;

  Input.getMesh()->drawBBox();
  setMouseGlobal(Input.getPosition());

  if(showInput == 1)
  {
    Input.getMesh()->bindVAO();
    loadToShader();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_BUFFER, m_tboID);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glDrawArrays(GL_TRIANGLES, 0, Input.getMesh()->getMeshSize());
    Input.getMesh()->unbindVAO();
  }

  setMultipleTransforms(ngl::Vec3(1.0f, 1.0f, 1.0f));

  //setMouseGlobal(Input.getContainer()->getBaseParticle()->m_Position);

  Input.getContainer()->getMesh()->bindVAO();
  //loadToShader(ngl::Vec4(1.0f, 0.0f, 1.0f, 0.0f));

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_BUFFER, m_tboID);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_textureID);

  glDrawArraysInstanced(GL_TRIANGLES, 0, Input.getContainer()->getMeshSize(), Input.getContainer()->getNumParticles());
  Input.getContainer()->getMesh()->unbindVAO();

  setSingleTransform(ObjectUpdater->getImpactObject().getTransform(),
                     ObjectUpdater->getImpactObject().getPosition(),
                     2 * ngl::Vec3(ObjectUpdater->getImpactObject().getRadius(), ObjectUpdater->getImpactObject().getRadius(), ObjectUpdater->getImpactObject().getRadius()));

  ObjectUpdater->getImpactObject().getMesh()->bindVAO();
  loadToShader();

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_BUFFER, m_tboID);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, m_textureID);

  glDrawArrays(GL_TRIANGLES, 0, ObjectUpdater->getImpactObject().getMesh()->getMeshSize());

  ObjectUpdater->getImpactObject().getMesh()->unbindVAO();


  update();
  //std::cout<<"PaintGL end "<<durr<<"\n";
  //durr++;

}

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quit
  case Qt::Key_Escape :
      {
        QGuiApplication::exit(EXIT_SUCCESS); break;
      }
  case Qt::Key_R :
      {
        m_win.spinXFace=0;
        m_win.spinYFace=0;
       // m_modelPos.set(ngl::Vec3::zero());
        break;
      }
  case Qt::Key_V :
      {
        showInput = 1 - showInput;
        break;
      }
  case Qt::Key_Space :
      {
        // Wrap in braces to allow mutex locker usage
        std::cout<<"starting\n";
        QMutexLocker ml(ObjectUpdater->getMutex());
        ObjectUpdater->setImpactObjectPosition(m_cam.getEye().toVec3());
//        std::cout<<cam.getLook().toVec3().m_x<<" "<<cam.getLook().toVec3().m_y<<" "<<cam.getLook().toVec3().m_z<<"\n";
        ObjectUpdater->setImpactObjectDirection(ngl::Vec3((m_cam.getLook() - m_cam.getEye()).toVec3()));
        ObjectUpdater->setImpactObjectVelocity(0.2f);
        ObjectUpdater->setImpactObjectMass(1000.0f);
        ObjectUpdater->setImpactObjectRadius(1.0f);
        Collisions = new CollisionThread(Input, ObjectUpdater->getImpactObject(), ObjectUpdater);
        Collisions->start();
        std::cout<<"set thread variables\n";
        break;
      }
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}
