attribute vec4 posAttr;
uniform vec4 playerPosition;
uniform vec4 colUni;
uniform mat4 matrix;
varying vec4 col;

void main()
{
    gl_Position = matrix * posAttr;
//    float dist = distance(posAttr , playerPosition);
//    if (dist < 1.3)
//        col = vec4(0.6, 0.6, 0.6, 0.8);
//    else
//        col = colUni;
    vec4 pp= vec4(0.0,0.0,0.0,0.0);
    if (pp.x < 0.5)
        col = vec4(1,0,0,0.8);
//    else if (playerPosition.x < -0.3)
//        col=vec4(0,1,0,0.8);
//    else if (playerPosition.x < 0)
//        col = vec4(0,0,1,0.8);
//    else
//        col = vec4(0.6, 0.6, 0.6, 0.8);

}
