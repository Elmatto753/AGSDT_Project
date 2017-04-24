#version 410 core
layout (location=0) in vec3 inVert;
layout (location=1) in vec2 inUV;
layout (location=2) in vec3 inNormal;

uniform samplerBuffer TBO;
uniform mat4 mouseTX;
uniform mat4 VP;
out vec2 vertUV;

void main()
{
  mat2 rot=mat2(cos(gl_InstanceID),sin(gl_InstanceID),
                -sin(gl_InstanceID),cos(gl_InstanceID));

  vertUV=rot*inUV;

  mat4 tx=mat4(texelFetch(TBO,gl_InstanceID*4),
               texelFetch(TBO,gl_InstanceID*4+1),
               texelFetch(TBO,gl_InstanceID*4+2),
               texelFetch(TBO,gl_InstanceID*4+3));
  gl_Position=VP * mouseTX * tx * vec4(inVert,1.0);

}
