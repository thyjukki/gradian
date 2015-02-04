#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;
  
uniform mat4 model;
uniform mat4 projection;

void main()
{
    gl_Position = projection * model * vec4(position.x, position.y, 0.0f, 1.0f);
    ourColor = color;
    TexCoord = vec2(texCoord.x, texCoord.y);
}