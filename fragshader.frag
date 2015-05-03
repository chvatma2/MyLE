#version 130

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform float time;
uniform sampler2D testTexture;

void main(void)
{
    vec4 textureColor = texture(testTexture, fragmentUV);
    color = textureColor;
    color = vec4(fragmentColor.x * ((cos(time)+1.0)/2),
                 fragmentColor.y * ((cos(time + 1.0)+1.0)/2),
                 fragmentColor.z * ((sin(time)+1.0)/2),
                 fragmentColor.w);
    color = textureColor;
}

