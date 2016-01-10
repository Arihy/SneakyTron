attribute vec4 posAttr;
uniform vec4 playerPosition;
uniform vec4 colUni;
uniform mat4 matrix;
varying vec4 col;

uniform vec4 lol = vec4(1,0,0,0.8);
//uniform bool ok = (playerPosition.x < -0.3);


void main()
{
    gl_Position = matrix * posAttr;
    float dist = distance(posAttr , playerPosition);
    if (dist < 1.3)
        col = colUni;
    else
        col = vec4(0.6, 0.6, 0.6, 0.8);
//    vec4 pp= vec4(0.0,0.0,0.0,0.0);
//    if (lol.x < 1)
//        col = colUni;
//    else if (playerPosition.x < -0.3)
//        col=vec4(0,1,0,0.8);
//    else if (playerPosition.x < 0)
//        col = vec4(0,0,1,0.8);
//    else
//        col = vec4(0.6, 0.6, 0.6, 0.8);
//    col = lol;

}
