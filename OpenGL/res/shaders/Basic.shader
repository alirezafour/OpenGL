#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureCoord;

out vec2 v_TextureCoord;

void main()
{
	gl_Position = position;
	v_TextureCoord = textureCoord;
};

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec2 v_TextureCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 textureColor = texture(u_Texture, v_TextureCoord);
	color = textureColor;
};