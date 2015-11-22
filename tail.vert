attribute vec4 posAttr;
uniform vec4 colAttr;
uniform mat4 matrix;
varying vec4 col;

void main()
{
    gl_PointSize = 5.0;
    gl_Position = matrix * posAttr;
    col = colAttr;
}
