attribute vec4 posAttr;
uniform vec4 colUni;
uniform mat4 matrix;
varying vec4 col;

void main()
{
    gl_PointSize = 10.0;
    gl_Position = matrix * posAttr;
    col = colUni;
}
