#ifndef RAY_H_
#define RAY_H_

#include <ngl/Vec3.h>

typedef struct Ray
{
  ngl::Vec3 m_StartPoint = ngl::Vec3(0.0f, 0.0f, 0.0f);
  ngl::Vec3 m_EndPoint = ngl::Vec3(0.0f, 0.0f, 0.0f);

  ngl::Vec3 m_Direction = ngl::Vec3(0.0f, 1.0f, 0.0f);

}Ray;


#endif
