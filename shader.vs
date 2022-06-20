#version 330 core
layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aTex;

out vec3 ourColor;
out vec2 TexCoords;
void main()
{
	gl_Position = vec4(aPos, 1.0);

	ourColor = vec3(1.0f, 0.5f, 0.0f);
	TexCoords = aTex;
}
