#ifndef THREAD_H_
#define THREAD_H_

#include <QThread>
#include <QThreadPool>

#include "ImpactObject.h"

class Thread : public QThread
{


public:

  Thread();
  ~Thread();

  void setUp();

  void run();

  ImpactObject getImpactObject() { return m_Impact; }


protected:

  ImpactObject m_Impact;

};


#endif
