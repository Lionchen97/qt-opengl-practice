#version 450 core
out vec4 FragColor;
in vec4 vertexColor;
void main()
{
    //FragColor = vertexColor;
    FragColor = vec4(vertexColor.xxy,0);
}
