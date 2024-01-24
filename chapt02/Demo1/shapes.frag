#version 450 core
out vec4 FragColor;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0f); // 使用从顶点着色器传递来的颜色值
}
