#version 410 core
//layout (location=0) in vec3 inVert;
//layout (location=2) in vec3 inNormal;

layout (location=0) in vec3 inPos;
layout (location=2) in vec2 texCoords;
layout (location=3) in mat4 instanceMatrix;

out vec2 TexCoords;

uniform mat4 MVP;
//out vec3 normal;

void main()
{
    gl_Position=MVP * instanceMatrix * vec4(inPos,1.0);
    //normal=inNormal;
    TexCoords = texCoords;
}
