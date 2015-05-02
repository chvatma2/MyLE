#version 330

in vec4 fragmentColor;

out vec4 color;

uniform float time;

void main(void)
{
    color = vec4(fragmentColor.x * ((cos(time)+1.0)/2),
                 fragmentColor.y * ((cos(time + 1.0)+1.0)/2),
                 fragmentColor.z * ((sin(time)+1.0)/2),
                 fragmentColor.w);
}

