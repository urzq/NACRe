#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;

// Values that stay constant for the whole mesh.
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 UV;

void main()
{	
	gl_Position = projection * view * model * vec4(position, 1.0f);
	UV = uv;
}

