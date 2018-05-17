/*--------------
Fragment Shader: filename "fTexture.glsl"
---------------*/
// #version 150   // YJC: Comment/un-comment this line to resolve compilation errors
                  //      due to different settings of the default GLSL version

in  vec4 color;
in  vec2 texCoord;

uniform sampler2D texture_2D; /* Note: If using multiple textures,
                                       each texture must be bound to a
                                       *different texture unit*, with the
                                       sampler uniform var set accordingly.
                                 The (fragment) shader can access *all texture units*
                                 simultaneously.
                              */
uniform int Texture_app_flag; // 0: no texture application: obj color
                              // 1: texutre color
                              // 2: (obj color) * (texture color)
out vec4 fColor;

void main() 
{ 
  if (Texture_app_flag == 0)
     fColor = color;
  else if (Texture_app_flag == 1)
     fColor = texture( texture_2D, texCoord );
  else // Texture_app_flag == 2
     fColor = color * texture( texture_2D, texCoord );  
} 

