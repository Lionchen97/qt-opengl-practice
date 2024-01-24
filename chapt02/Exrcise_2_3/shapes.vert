#version 450 core
layout(location=0) in vec3 aPos;

out vec3 ourPosition;

void main()
{
    gl_Position = vec4(aPos,1.0f); // 重组(Swizzling)
    ourPosition = aPos;

}
