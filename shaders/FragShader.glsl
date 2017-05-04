#version 410 core

// This shader is adapted from one of Jon Macey's NGL demos on point lights
in vec3 fragmentNormal;

layout (location=0) out vec4 fragColour;

struct Materials
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

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

uniform Materials material;

uniform Lights light;
in vec3 lightDir;
in vec3 halfVector;
in vec3 eyeDirection;

in vec2 vertUV;
uniform sampler2D tex;

void pointLight(
                in vec3 _normal,
                inout vec4 _ambient,
                inout vec4 _diffuse,
                inout vec4 _specular
               )
{
  vec3 N = normalize(fragmentNormal);
  vec3 halfV;
  float ndothv;
  vec3 E = normalize(eyeDirection);
  vec3 L = normalize(lightDir);
  float lambertTerm = dot(N,L);
  if (lambertTerm > 0.0)
  {
    _diffuse+=material.diffuse*light.diffuse*lambertTerm;
    _ambient+=material.ambient*light.ambient;
    halfV = normalize(halfVector);
    ndothv = max(dot(N, halfV), 0.0);
    _specular+=material.specular*light.specular*pow(ndothv, material.shininess);
  }
}

void main()
{
  vec4 ambient = vec4(0.0);
  vec4 diffuse = vec4(0.0);
  vec4 specular = vec4(0.0);
  pointLight(fragmentNormal, ambient, diffuse, specular);
  fragColour = texture(tex, vertUV.st) * ambient+diffuse+specular;
}
