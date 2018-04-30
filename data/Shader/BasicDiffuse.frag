#version 330 core

// centroid= better sampling when we turn on MSAA. It avoids texture bleeding.
// see this article: https://www.opengl.org/pipeline/article/vol003_6/
centroid in vec2 UV;

uniform sampler2D texture0;

out vec4 color;

void main()
{
	color = texture(texture0, UV);
}