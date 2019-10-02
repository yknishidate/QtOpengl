#version 430
#define PI (3.14159265359)
#define R3 (1.73205080757)
#define DEPTH (10)
#define SPP 8


layout(local_size_x = 1, local_size_y = 1) in;

layout(rgba32f, binding = 0) uniform image2D img_input;

layout(rgba32f, binding = 1) uniform image2D img_output;

layout(rgba32ui, binding = 2) uniform uimage2D seed;

layout(binding = 3) uniform sampler2D background;



ivec3 _WorkGrupsN = ivec3(gl_NumWorkGroups);
ivec3 _WorkItemsN = ivec3(gl_WorkGroupSize);
ivec3 _WorksN = _WorkGrupsN * _WorkItemsN;
ivec3 _WorkID = ivec3(gl_GlobalInvocationID);

layout(std430, binding = 0) buffer AccumN {
    uint _AccumN;
};

// Sphere Date
layout(std430, binding = 1) buffer SphereRadius {
    float rad[];
};
layout(std430, binding = 2) buffer SpherePosition {
    vec4 pos[];
};

// Material Data
layout(std430, binding = 3) buffer MaterialType {
    int materialType[];
};
layout(std430, binding = 4) buffer MaterialDiffColor {
    vec4 materialDiffColor[];
};
layout(std430, binding = 5) buffer MaterialSpecColor {
    vec4 materialSpecColor[];
};
layout(std430, binding = 6) buffer MaterialTransColor {
    vec4 materialTransColor[];
};
layout(std430, binding = 7) buffer MaterialLightColor {
    vec4 materialLightColor[];
};
layout(std430, binding = 8) buffer MaterialIor {
    float materialIor[];
};

// Camera
layout(location = 0) uniform float _Theta;
layout(location = 1) uniform float _Phi;
layout(location = 2) uniform float _Distance;
layout(location = 3) uniform int RenderMode;
layout(location = 4) uniform bool Dof;
//layout(location = 4) uniform int Dof;

// Structs
struct ray {
    vec3 origin;
    vec3 direction;
    vec3 scatter;
    vec3 emission;
    int depth;
};
struct hit{
    float t;
    vec3 pos;
    vec3 nor;
    uint mat;
};
struct sphere {
    vec3 center;
    float radius;
};
float pow2(float x) {
    return x * x;
}
float pow5(float x) {
    return x * x * x * x * x;
}
float fresnel(in float n, in float u) {
    float f0 = pow2((n - 1) / (n + 1));
    return f0 + (1 - f0) * pow5(1 - u);
}

//Hit
bool hit_sphere(in sphere s, in ray r, inout hit h) {
    vec3 oc = r.origin - s.center;
    float a = dot(r.direction, r.direction);
    float b = dot(oc, r.direction);
    float c = dot(oc, oc) - pow2(s.radius);
    float discriminant = pow2(b) - a * c; //解の公式のD
    float t;

    if (discriminant > 0) { //D > 0
        t = (-b - sqrt(discriminant)) / a; //small t
        if (0 < t && t < h.t)
        {
        h.t = t;
        h.pos = r.origin + t * r.direction;
        h.nor = normalize(h.pos - s.center);
        return true;
    }

    t = (-b + sqrt(discriminant)) / a; //big t
    if (0 < t && t < h.t){
      h.t = t;
      h.pos = r.origin + t * r.direction;
      h.nor = normalize(h.pos - s.center);
      return true;
    }
  }
  return false;
}

//XORshift
uvec4 _xors;
float rand() {
    uint t = (_xors[0] ^ (_xors[0] << 11));
    _xors[0] = _xors[1];
    _xors[1] = _xors[2];
    _xors[2] = _xors[3];
    _xors[3] = (_xors[3] ^ (_xors[3] >> 19)) ^ (t ^ (t >> 8));
    return _xors[3] / 4294967295.0f;
}

// ToneMap
vec4 ToneMap(in vec4 Color, in float White){
    return clamp(Color * (1 + Color / White) / (1 + Color), 0, 1);
}

//Gamma Correction
vec4 GammaCorrect(in vec4 Color, in float Gamma){
    vec4 Result;
    float G = 1 / Gamma;
    Result.r = pow(Color.r, G);
    Result.g = pow(Color.g, G);
    Result.b = pow(Color.b, G);
    Result.a = 1;
    return Result;
}


//--------------------------------------------------
//                  Material
//--------------------------------------------------
// Background
void mat_background(inout ray r, in hit h){
    r.depth = DEPTH; //backgroundに当たった時点でdepth最大
    r.emission = texture(background, vec2((PI - atan(-r.direction.x, -r.direction.z)) / (2 * PI), acos(r.direction.y) / PI)).xyz;
}
// Background None
void mat_backNone(inout ray r, in hit h){
    r.depth = DEPTH; //backgroundに当たった時点でdepth最大
    r.emission = vec3(0);
}
// Background for AmbientOcclusion
void mat_backao(inout ray r, in hit h) {
    if(r.depth == 0){
        r.emission = vec3(0);  //直接見ると0
    }else if(r.depth == 1){
        r.emission = vec3(10); //物体からの反射の時はライト
    }
    r.depth = DEPTH;
}

// Light
void mat_light(inout ray r, in hit h, vec3 color) {
    r.depth = DEPTH;
    r.scatter = r.scatter * color;
    r.emission = vec3(10);
}

// Diffuse
void mat_diffuse(inout ray r, in hit h, vec3 color) {
    r.depth = r.depth + 1; //depthインクリメント

    r.direction.y = sqrt(rand());
    float d = sqrt(1 - pow2(r.direction.y));
    float v = rand() * 2 * PI;
    vec3 UppVec;
    vec3 BinVec;
    vec3 TanVec;
    vec3 EX = vec3(1, 0, 0); float DX = abs(dot(h.nor, EX));
    vec3 EY = vec3(0, 1, 0); float DY = abs(dot(h.nor, EY));
    vec3 EZ = vec3(0, 0, 1); float DZ = abs(dot(h.nor, EZ));
    if (DY < DX) {
        if (DZ < DY) UppVec = EZ;
        else UppVec = EY;
    }
    else // DX <= DY
    {
        if (DZ < DX) UppVec = EZ;
        else UppVec = EX;
    }
    TanVec = normalize(cross(UppVec, h.nor));
    BinVec = normalize(cross(TanVec, h.nor));
    r.direction = normalize(BinVec * d * cos(v) + h.nor * r.direction.y + TanVec * d * sin(v));
    r.origin = h.pos + h.nor * 0.001f;
    r.scatter = r.scatter * color;
    r.emission = vec3(0);
}

//Mirror
void mat_mirror(inout ray r, in hit h, vec3 color){
    r.depth = r.depth + 1;
    r.origin = h.pos + h.nor * 0.001f;
    r.direction = 2 * dot(-r.direction, h.nor) * h.nor + r.direction;
    r.scatter = r.scatter * color;
    r.emission = vec3(0);
}

//Glass
void mat_glass(inout ray r, in hit h, vec4 color, float ior)
{
    r.depth = r.depth + 1;
    float n = ior;
    vec3 N;
    if (dot(-r.direction, h.nor) > 0) {
        n = 1.0 / n;
        N = h.nor;
    }else {
        n = n / 1.0;
        N = -h.nor;
    }
    if (rand() < fresnel(n, dot(-r.direction, N))) {
        r.origin = h.pos + N * 0.001f;
        r.direction = 2 * dot(-r.direction, N) * N + r.direction;
    }else {
        r.origin = h.pos - N * 0.001f;
        float t = dot(-r.direction, N);
        r.direction = n * r.direction +
                  (n * t - sqrt(1 - pow2(n) * (1 - pow2(t)))) * N;
    }
    r.scatter = r.scatter * color.xyz;
    r.emission = vec3(0);
}


// Ambient Occlusion
// TODO:距離を変更可能にする
void mat_ao(inout ray r, in hit h)
{
    r.depth = r.depth + 1;
    if(r.depth == 1){ //最初のヒット
        r.direction.y = sqrt(rand());
        float d = sqrt(1 - pow2(r.direction.y));
        float v = rand() * 2 * PI;
        vec3 UppVec;
        vec3 BinVec;
        vec3 TanVec;
        vec3 EX = vec3(1, 0, 0); float DX = abs(dot(h.nor, EX));
        vec3 EY = vec3(0, 1, 0); float DY = abs(dot(h.nor, EY));
        vec3 EZ = vec3(0, 0, 1); float DZ = abs(dot(h.nor, EZ));
        if (DY < DX) {
            if (DZ < DY) UppVec = EZ;
            else UppVec = EY;
        }
        else {
            if (DZ < DX) UppVec = EZ;
            else UppVec = EX;
        }
        TanVec = normalize(cross(UppVec, h.nor));
        BinVec = normalize(cross(TanVec, h.nor));
        r.direction = normalize(BinVec * d * cos(v) + h.nor * r.direction.y + TanVec * d * sin(v));
        r.origin = h.pos + h.nor * 0.001f;
        r.emission = vec3(0);
    }
    if(r.depth == 2){
        r.depth = DEPTH;
        if(h.t < 1){
            r.emission = vec3(0);
        }else{
            r.emission = vec3(10);
        }
    }
}

//Depth
// TODO: 距離を変更可能にする
float maxDist = 4.0;
void mat_depth(inout ray r, in hit h) {
    r.depth = DEPTH; //depthを最大にして終了させる
    r.scatter = r.scatter * vec3(1);
    r.emission = vec3(10.0 - 10.0/maxDist * h.t);
}

// Normal
void mat_nor(inout ray r, in hit h) {
    r.depth = DEPTH;
    r.emission = vec3(h.nor)/2.0 + vec3(0.5);
}

//--------------------------------------------------
//                    Main
//--------------------------------------------------
void main() {
    vec4 pixel = vec4(0, 0, 0, 0);

    vec4 A = imageLoad(img_input, _WorkID.xy);
    if(_AccumN < 10){
        A = vec4(0, 0, 0, 0);
    }

    // Seed
    _xors ^= imageLoad(seed, _WorkID.xy);

    ray _rays;
    hit h;
    h.t = 10000;
    h.pos = vec3(0);

    // Cornel Box
    bool CornelBox = false;
    sphere floor;
    floor.center = vec3(0, -10000, 0);
    floor.radius = 9998;
    sphere wall_left;
    wall_left.center = vec3(-10000, 0, 0);
    wall_left.radius = 9994;
    sphere wall_right;
    wall_right.center = vec3(10000, 0, 0);
    wall_right.radius = 9994;
    sphere wall_flont;
    wall_flont.center = vec3(0, 0, -10000);
    wall_flont.radius = 9992;
    sphere wall_top;
    wall_top.center = vec3(0, 10000, 0);
    wall_top.radius = 9992;

    // Default Scene
    bool DefaultScene = false;
    sphere s1;
    s1.center = vec3(0, 0, 0);
    s1.radius = 2;
    sphere s2;
    s2.center = vec3(-3, 0, -3);
    s2.radius = 2;
    sphere s3;
    s3.center = vec3(3, 0, -3);
    s3.radius = 2;

    sphere s[16]; // Max = 16
    int modelN = rad.length();
    for(int i = 0; i < modelN; i++){
        s[i].center = pos[i].xyz;
        s[i].radius = rad[i];
    }


    vec3 screen_position;
    vec3 camPos = vec3(0, 0, _Distance);
    vec3 camForward = vec3( 0, 0,-1);
    vec3 camUp      = vec3( 0, 1, 0);
    vec3 camRight   = vec3(-1, 0, 0);

    float a = 1.6; //イメージセンサーからレンズ中心までの距離
    float b; //レンズ中心からピントの合う平面までの距離
    float f; //焦点距離
    float lensRadius = 0.5;
    vec3  lensCenter = camPos + a*camForward;

//    vec3  focusPoint = vec3(0, 0, 0);
//    float cosine = dot(camForward, normalize(focusPoint - camPos));
//    b = cosine * (focusPoint - camPos).length() - a;
     b = _Distance-a;
     f = 1/(1/a + 1/b);

    // Sample Loop
    for (int n = 0; n < SPP; n++){
        // Pinhole Camera
//          screen_position.x = float(_WorkID.x + rand()) / _WorksN.x * -16 + 8;
//          screen_position.y = float(_WorkID.y + rand()) / _WorksN.y * -9 + 4.5;
//          screen_position.z = camPos.z ;

//          mat3 M1 = mat3( cos(_Theta), 0, sin(_Theta), 0, 1, 0, -sin(_Theta), 0, cos(_Theta));
//          mat3 M2 = mat3(1, 0, 0, 0, cos(_Phi), -sin(_Phi), 0, sin(_Phi), cos(_Phi));
//          _rays.origin = M1 * M2 * screen_position;
//          _rays.direction = normalize( M1 * M2 * ((camPos + vec3(0, 0, -9)) - screen_position) );

        float aspect = 16.0/9.0;
        float width = 3.1; // small -> zoom
        float height = width/aspect;
        if(Dof){
            // Lens Model Rendering
            screen_position.x = float(_WorkID.x) / _WorksN.x * - width + width/2.0;
            screen_position.y = float(_WorkID.y) / _WorksN.y * - height + height/2.0;
            screen_position.z = camPos.z ;

            vec3 r  = normalize(lensCenter - screen_position);
            vec3 pf = screen_position + (a+b)/dot(camForward, r) * r;

            // Sample Disk
            float x, y;
            float u1 = rand();
            float u2 = rand();
            x = sqrt(u1) * cos(2*PI*u2);
            y = sqrt(u1) * sin(2*PI*u2);
            vec3 l = lensCenter + lensRadius*(x*camRight + y*camUp); // Origin

            mat3 M1 = mat3( cos(_Theta), 0, sin(_Theta), 0, 1, 0, -sin(_Theta), 0, cos(_Theta));
            mat3 M2 = mat3(1, 0, 0, 0, cos(_Phi), -sin(_Phi), 0, sin(_Phi), cos(_Phi));
            _rays.origin = M1 * M2 * l;
            _rays.direction = normalize( M1 * M2 * normalize(pf - l) );
        }else{
            screen_position.x = float(_WorkID.x + rand()) / _WorksN.x * 16 - 8;
            screen_position.y = float(_WorkID.y + rand()) / _WorksN.y * 9 - 4.5;
            screen_position.z = camPos.z - 9;

            mat3 M1 = mat3( cos(_Theta), 0, sin(_Theta), 0, 1, 0, -sin(_Theta), 0, cos(_Theta));
            mat3 M2 = mat3(1, 0, 0, 0, cos(_Phi), -sin(_Phi), 0, sin(_Phi), cos(_Phi));
            _rays.origin = M1 * M2 * camPos;
            _rays.direction = normalize( M1 * M2 * (screen_position - camPos));
        }

        _rays.scatter  = vec3(1);
        _rays.emission = vec3(0);
        _rays.depth = 0;

        while (_rays.depth < DEPTH){
            h.t = 10000;
            h.pos = vec3(0);
            h.nor = vec3(0);
            vec3 diffColor = vec3(1);
            vec3 specColor = vec3(1);
            vec4 transColor = vec4(1);
            vec3 lightColor = vec3(1);
            float ior = 1.5;

            switch(RenderMode){
            case 0: // RGBA
                h.mat = 10; // Sky
                if(CornelBox){ // Cornel Box
                    if (hit_sphere(wall_left, _rays, h)) { h.mat = 0; diffColor = vec3(1, 0.3, 0.3); }
                    if (hit_sphere(wall_right, _rays, h)){ h.mat = 0; diffColor = vec3(0.3, 0.3, 1); }
                    if (hit_sphere(wall_flont, _rays, h)){ h.mat = 0; diffColor = vec3(1); }
                    if (hit_sphere(wall_top, _rays, h))  { h.mat = 0; diffColor = vec3(1); }
                }
                if(DefaultScene){ // Default
                    if (hit_sphere(floor, _rays, h)) { h.mat = 0; diffColor = vec3(1); }
                    if (hit_sphere(s1, _rays, h)) h.mat = 1;
                    if (hit_sphere(s2, _rays, h)) h.mat = 3;
                    if (hit_sphere(s3, _rays, h)) h.mat = 2;
                }
                // Scene Data
                for(int i = 0; i < modelN; i++){ // Sphere
                    if (hit_sphere(s[i], _rays, h)){
                        h.mat = materialType[i];
                        diffColor = materialDiffColor[i].xyz;
                        specColor = materialSpecColor[i].xyz;
                        transColor = materialTransColor[i];
                        lightColor = materialLightColor[i].xyz;
                        ior = materialIor[i];
                    }
                }
                break;

            case 1: // AO
                h.mat = 11; // Sky
                if(CornelBox){
                    if (hit_sphere(wall_left, _rays, h)) h.mat = 5;
                    if (hit_sphere(wall_right, _rays, h)) h.mat = 5;
                    if (hit_sphere(wall_flont, _rays, h)) h.mat = 5;
                    if (hit_sphere(wall_top, _rays, h)) h.mat = 5;
                }
                if(DefaultScene){
                    if (hit_sphere(floor, _rays, h)) h.mat = 5;
                    if (hit_sphere(s1, _rays, h)) h.mat = 5;
                    if (hit_sphere(s2, _rays, h)) h.mat = 5;
                    if (hit_sphere(s3, _rays, h)) h.mat = 5;
                }
                // Scene Data
                for(int i = 0; i < modelN; i++){
                    if (hit_sphere(s[i], _rays, h)){
                        h.mat = 5;
                    }
                }
                break;

            case 2: // Depth
                h.mat = 12;
                if(CornelBox){
                    if (hit_sphere(wall_left, _rays, h)) h.mat = 6;
                    if (hit_sphere(wall_right, _rays, h)) h.mat = 6;
                    if (hit_sphere(wall_flont, _rays, h)) h.mat = 6;
                    if (hit_sphere(wall_top, _rays, h)) h.mat = 6;
                }
                if(DefaultScene){
                    if (hit_sphere(floor, _rays, h)) h.mat = 6;
                    if (hit_sphere(s1, _rays, h)) h.mat = 6;
                    if (hit_sphere(s2, _rays, h)) h.mat = 6;
                    if (hit_sphere(s3, _rays, h)) h.mat = 6;
                }
                // Scene Data
                for(int i = 0; i < modelN; i++){
                    if (hit_sphere(s[i], _rays, h)){
                        h.mat = 6;
                    }
                }
                break;

            case 3: // Normal
                h.mat = 12;
                if(CornelBox){
                    if (hit_sphere(wall_left, _rays, h)) h.mat = 7;
                    if (hit_sphere(wall_right, _rays, h)) h.mat = 7;
                    if (hit_sphere(wall_flont, _rays, h)) h.mat = 7;
                    if (hit_sphere(wall_top, _rays, h)) h.mat = 7;
                }
                if(DefaultScene){
                    if (hit_sphere(floor, _rays, h)) h.mat = 7;
                    if (hit_sphere(s1, _rays, h)) h.mat = 7;
                    if (hit_sphere(s2, _rays, h)) h.mat = 7;
                    if (hit_sphere(s3, _rays, h)) h.mat = 7;
                }
                // Scene Data
                for(int i = 0; i < modelN; i++){
                    if (hit_sphere(s[i], _rays, h)){
                        h.mat = 7;
                    }
                }
                break;
            }

            switch(h.mat) {
                case 0: mat_diffuse(_rays, h, diffColor); break;
                case 1: mat_mirror(_rays, h, specColor); break;
                case 2: mat_glass(_rays, h, transColor, ior); break;
                case 3: mat_light(_rays, h, lightColor); break;
                case 4:  break;
                case 5: mat_ao(_rays, h); break;
                case 6: mat_depth(_rays, h); break;
                case 7: mat_nor(_rays, h); break;
                case 10: mat_background(_rays, h); break;
                case 11: mat_backao(_rays, h); break;
                case 12: mat_backNone(_rays, h); break;
            }
        } // Depth Loop

        pixel.rgb = _rays.scatter * _rays.emission;
        A.rgb += (pixel.rgb - A.rgb) / _AccumN;
    } // Sample Loop


    // Output
    A.rgb += (pixel.rgb - A.rgb) / _AccumN;
    if (_WorkID.xy == ivec2(0)) _AccumN += SPP;
    imageStore(img_output, _WorkID.xy, GammaCorrect(ToneMap(A, 100), 2.2));
    imageStore(img_input, _WorkID.xy, A);
    imageStore(seed, _WorkID.xy, _xors);
}
