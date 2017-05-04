#ifndef COLLISIONTHREAD_H_
#define COLLISIONTHREAD_H_

#include <QThread>
#include "Model.h"
#include "ImpactObject.h"
#include "ObjectUpdateThread.h"

class CollisionThread : public QThread
{
  Q_OBJECT
public:

  CollisionThread(Model mesh, ImpactObject object, ObjectUpdateThread *thread);
  ~CollisionThread();

  void run();

  bool initialTest(Model _mesh, ImpactObject _object);

  std::vector<Particle*> fullTest();

  void impartForce(std::vector<Particle*> _impartTo);

  void calcBreakpoint();


protected:

  Model m_mesh;
  ImpactObject m_object;
  ObjectUpdateThread *m_OUthread;

};



#endif
