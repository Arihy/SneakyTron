attribute vec4 posAttr;
uniform vec4 playerPosition;
uniform vec4 colUni;
uniform mat4 matrix;
varying vec4 col;

void main()
{
    //gl_PointSize = 10.0;
    gl_Position = matrix * posAttr;
    float dist = distance(gl_Position , playerPosition);
    if (dist < 3.01)
        col = vec4(0.6, 0.6, 0.6, 0.8);
    else
        col = colUni;
}
