#version 410 core
layout (location=0) in vec3 inVert;
layout (location=1) in vec2 inUV;
layout (location=2) in vec3 inNormal;

uniform samplerBuffer TBO;
uniform mat4 mouseTX;
uniform mat4 VP;
uniform bool Normalize;
uniform vec3 viewerPos;
out vec3 fragmentNormal;
out vec2 vertUV;

struct Lights
{
  vec4 position;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float spotCosCutoff;
  float spotCosInnerCutoff;
  float spotExponent;
  float constantAttenuation;
  float linearAttenuation;
  float quadraticAttenuation;
};

uniform Lights light;
out vec3 lightDir;
out vec3 halfVector;
out vec3 eyeDirection;
uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 normalMatrix;
uniform mat4 M;

void main()
{
  fragmentNormal = (normalMatrix * inNormal);

  if(Normalize == true)
  {
    fragmentNormal = normalize(fragmentNormal);
  }

  mat4 tx=mat4(texelFetch(TBO,gl_InstanceID*4),
               texelFetch(TBO,gl_InstanceID*4+1),
               texelFetch(TBO,gl_InstanceID*4+2),
               texelFetch(TBO,gl_InstanceID*4+3));
  gl_Position=VP * mouseTX * tx * vec4(inVert,1.0);
//  gl_Position = MVP*vec4(inVert, 1.0);

  vec4 eyeCoord = MV*vec4(inVert, 1.0);

  lightDir = vec3(light.position.xyz-eyeCoord.xyz);
  vec4 worldPosition = M * vec4(inVert, 1.0);
  eyeDirection = normalize(viewerPos - worldPosition.xyz);

  float dist;
  lightDir = (light.position.xyz - worldPosition.xyz);
  dist = length(lightDir);
  lightDir /= dist;
  halfVector = normalize(eyeDirection + lightDir);

//  mat2 rot=mat2(cos(gl_InstanceID),sin(gl_InstanceID),
//                -sin(gl_InstanceID),cos(gl_InstanceID));

//  vertUV=rot*inUV;


}
