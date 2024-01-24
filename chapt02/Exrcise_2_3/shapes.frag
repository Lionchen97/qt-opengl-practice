#version 450 core
out vec4 gl_FragColor;
in vec3 ourPosition;
void main()
{
    gl_FragColor = vec4(ourPosition, 1.0);
}
