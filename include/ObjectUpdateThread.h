#ifndef THREAD_H_
#define THREAD_H_

#include <QThread>
#include <QThreadPool>
#include <QMutexLocker>
#include <QTimer>

#include "ImpactObject.h"

class ObjectUpdateThread : public QThread
{
  Q_OBJECT
public:

  ObjectUpdateThread();
  ~ObjectUpdateThread();

  void run();

  void setUp();

  void setImpactObjectDirection(ngl::Vec3 _dir);

  void setImpactObjectVelocity(float _vel);

  void setImpactObjectMass(float _mass);

  void setImpactObjectRadius(float _rad);

  void setImpactObjectPosition(ngl::Vec3 _pos);

  ImpactObject getImpactObject() { return m_Impact; }

  QMutex *getMutex() { return &m_Mutex; }

public slots:

  void UpdateObjects();

protected:

  ImpactObject m_Impact;

  QMutex m_Mutex;

  uint x = 0;

  QTimer *timer;

};


#endif
