#version 450 core
out vec4 FragColor;
uniform vec4 ourColor;
void main()
{

    //FragColor =vec4(0.4,0.6,0.8,1);
    gl_FragColor = ourColor;
}
