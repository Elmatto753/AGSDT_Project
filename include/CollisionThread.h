#ifndef COLLISIONTHREAD_H_
#define COLLISIONTHREAD_H_

#include <QThread>
#include "Model.h"
#include "ImpactObject.h"
#include "ObjectUpdateThread.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file CollisionThread.h
/// @brief Collision handling thread object, subclassing QThread
/// @author Matt Skellon
/// @version 1.0
/// @date 04/05/17
/// @class CollisionThread
/// Revision History :
/// Initial version
//----------------------------------------------------------------------------------------------------------------------

class CollisionThread : public QThread
{
  Q_OBJECT
public:

  CollisionThread(Model mesh, ImpactObject object, ObjectUpdateThread *thread);
  ~CollisionThread();

  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Overwitten run function from QThread
  //----------------------------------------------------------------------------------------------------------------------
  void run();
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Tests if a collision will occur on the impact object's current trajectory
    /// @param _mesh Mesh to test against
    /// @param _object Object to hit with
  //----------------------------------------------------------------------------------------------------------------------
  bool initialTest(Model _mesh, ImpactObject _object);
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief The full particle test, returns any particles that the object has collided with
  //----------------------------------------------------------------------------------------------------------------------
  std::vector<Particle*> fullTest();
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Imparts force onto hit particles
    /// @param _impartTo Particles to add force to
  //----------------------------------------------------------------------------------------------------------------------
  void impartForce(std::vector<Particle*> _impartTo);
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Calculates which (if any) particles will break from the impact
  //----------------------------------------------------------------------------------------------------------------------
  void calcBreakpoint();


protected:

  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Input mesh to test against
  //----------------------------------------------------------------------------------------------------------------------
  Model m_mesh;
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Object that will do the colliding
  //----------------------------------------------------------------------------------------------------------------------
  ImpactObject m_object;
  //----------------------------------------------------------------------------------------------------------------------
    /// @brief Pointer to the object update thread
  //----------------------------------------------------------------------------------------------------------------------
  ObjectUpdateThread *m_OUthread;

};



#endif
