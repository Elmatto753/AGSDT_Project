#ifndef COLLISIONTHREAD_H_
#define COLLISIONTHREAD_H_

#include <QThread>
#include "Model.h"
#include "ImpactObject.h"

class CollisionThread : public QThread
{
  Q_OBJECT
public:

  CollisionThread(Model mesh, ImpactObject object);
  ~CollisionThread();

  void run();

  bool initialTest(Model _mesh, ImpactObject _object);




protected:

  Model m_Mesh;
  ImpactObject m_Object;

};



#endif
