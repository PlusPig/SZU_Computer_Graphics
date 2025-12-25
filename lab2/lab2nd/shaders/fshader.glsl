#version 330 core

in vec3 color;
out vec4 fColor;

uniform float brightness;  // 明暗控制因子（0.0 ~ 1.0）

void main()
{
    fColor = vec4(color, 1.0);
}

