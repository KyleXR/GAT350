#version 430 core 
  
in vec3 reflection_dir;

out vec4 fcolor;

layout (binding = 0) uniform samplerCube cubeMap;
  
void main() 
{ 
	fcolor = texture(cubeMap, reflection_dir);
 
} 