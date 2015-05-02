#version 330

in vec2 vertexPosition;
in vec4 vertexColor;

out vec4 fragmentColor;

void main(void)
{
    gl_Position.xy = vertexPosition;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;

    fragmentColor = vertexColor;
}

