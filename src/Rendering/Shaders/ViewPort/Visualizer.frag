#version 330 core

in vec2 screenPos;

out vec4 FragColor;

uniform vec2 scale;
uniform vec2 offset;
uniform float param1;
uniform float param2;
uniform float param3;
uniform float param4;
uniform float param5;
uniform float param6;
uniform float param7;

const float PI = 3.14;

const float DIAG = 1.414213562373095;
const float R3 = 1.732;

mat2 mRot(float angle)
{
    angle *= PI / 180.0;
    float s=sin(angle), c=cos(angle);
    return mat2( c, -s,
    s,  c );
}

vec2 rot(vec2 p, float a){
    float c = cos(a);
    float s = sin(a);
    return mat2(c,-s,s,c)*p;
}

// texture samplers
uniform sampler2D texture1;

int i = -1;

float getParam(){
    i += 1;
    if (i==0){
        return param1;
    }else if (i==1){
        return param2;
    }else if (i==2){
        return param3;
    }else if (i==3){
        return param4;
    }else if (i==4){
        return param5;
    }else if (i==5){
        return param6;
    }
    return 0.0;
}

void main()
{
    vec2 uv = screenPos / scale + offset;

    //Working *442
    /*uv += 1.0f;
    uv = mod(uv, vec2(2.0));
    uv -= 1.0f;
    uv = abs(uv);
    uv.x -= 1.0f;
    uv.x *= -1.0f;
    uv *= rot(45.0);
    uv.x = abs(uv.x);
    uv *= rot(-45.0);
    uv.x *= -1.0f;
    uv.x += 1.0f;*/
    
    //Truc Stylé
    /*
    uv.y -= R3/2;
    uv.y = mod(uv.y, R3);
    uv.y -= R3/2;
    uv.y = abs(uv.y);
    uv *= rot(60.0);
    uv.y -= R3/2;
    uv.y = mod(uv.y, R3);
    uv.y -= R3/2;
    uv.y = abs(uv.y);
    uv *= rot(60.0);
    uv.y -= R3/2;
    uv.y = mod(uv.y, R3);
    uv.y -= R3/2;
    uv.y = abs(uv.y);
    uv *= rot(60.0);
    uv.y -= R3/2;
    uv.y = mod(uv.y, R3);
    uv.y -= R3/2;
    uv.y = abs(uv.y);
    uv *= rot(60.0);
    uv.y -= R3/2;
    uv.y = mod(uv.y, R3);
    uv.y -= R3/2;
    uv.y = abs(uv.y);
    uv *= rot(60.0);
    uv.y -= R3/2;
    uv.y = mod(uv.y, R3);
    uv.y -= R3/2;
    uv.y = abs(uv.y);
    */



    uv*=6.;

    vec2 uv1 = fract(uv);
    vec2 uv2 = fract(rot(uv,3.1416/3.));
    vec2 uv3 = fract(rot(uv,-3.1416/3.));

    vec2 tuv = vec2(uv2.y, uv3.y);
    if(1.-tuv.y<tuv.x) tuv = 1.-tuv;
    //tuv -= .5;
    tuv *= 2.;
    
    /// UNCOMMENT TO HAVE OTHONORMAL(?) TRIANGLE UV (TUV)
    /*
    tuv = rot(tuv, 3.1416/4.);
    tuv.x *= 2.;
    */
    
    vec3 col = vec3(clamp(tuv, 0., 1.), 0.);

    vec2 ftuv = fract(tuv*2.);

    if(ftuv.x < .05 || ftuv.y < .05) col = mix(col, vec3(0.), .2);

    if(length(tuv-vec2(0., 0.))<.05) col = vec3(1.);
    if(length(tuv-vec2(0., .5))<.05) col = vec3(1.);
    if(length(tuv-vec2(.5, 0.))<.05) col = vec3(1.);
    if(length(tuv-vec2(.5, .5))<.05) col = vec3(1.);
    // Output to screen

    if(uv1.y < .01 || uv2.y < .01 || uv3.y < .01) col = vec3(0.);
    if(uv1.y > .99 || uv2.y > .99 || uv3.y > .99) col = vec3(0.);
    FragColor = vec4(col,1.0);
    if(length(screenPos / scale + offset) <0.01f){
        FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    }
}