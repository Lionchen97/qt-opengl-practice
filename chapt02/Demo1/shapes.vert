#version 450 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;
uniform vec2 xyoffset;
out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos.x+xyoffset.x,aPos.y+xyoffset.y,aPos.z,1.0f); // 重组(Swizzling)
    ourColor = vec3(aColor.x+xyoffset.x,aColor.y+xyoffset.y,aColor.z);

}
