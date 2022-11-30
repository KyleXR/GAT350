#version 430 core 
  
in vec2 texcoord; 
  
out vec4 fcolor; 

const float screen_height = 600.0;

uniform float offset;
  
uniform sampler2D textureMap; 
  
void main() 
{ 
	//fcolor = texture(textureMap, texcoord);
	
//----------------------------------------------------------------------

	// Black & White Effect **

//----------------------------------------------------------------------
//
//	vec3 color = texture(textureMap, texcoord).rgb; 
//	// black / white 
//	float avg = (color.r + color.g + color.b) / 3.0; 
//	fcolor = vec4(vec3(avg), 1); 
//
//----------------------------------------------------------------------

	// ** Invert Color Effect **

//----------------------------------------------------------------------
//
	vec3 color = texture(textureMap, texcoord).rgb; 
  
	// invert 
	fcolor = vec4(1.0 - color, 1.0); 
//
//----------------------------------------------------------------------

	// ** ScanLine Effect **

//----------------------------------------------------------------------
//
//	vec3 color = texture(textureMap, texcoord).rgb; 
// 
//	 // get the screen y position (uv coordinates range 0 <-> 1) 
//	 int y = int(texcoord.y * screen_height); 
//	 // set the alpha based on the modulus of the y position 
//	 float alpha = (y % 3 != 0) ? 1 : 0; 
// 
//	 fcolor = vec4(color * alpha, 1); 
//
//-----------------------------------------------------------------------

	// ** Wave Effect **

//----------------------------------------------------------------------
//
	// wave 
// vec2 ttexcoord = texcoord; 
// ttexcoord.x += sin(ttexcoord.y * 30.0 + offset) / 100.0; 
// fcolor = texture(textureMap, ttexcoord); 
//
//----------------------------------------------------------------------
} 
