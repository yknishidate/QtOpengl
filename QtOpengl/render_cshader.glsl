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
layout(std430, binding = 1) buffer Theta {
        float _Theta;
};
layout(std430, binding = 2) buffer Phi {
        float _Phi;
};

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

  if (discriminant > 0) //D > 0
  {
    t = (-b - sqrt(discriminant)) / a; //small t
    if (0 < t && t < h.t)
    {
      h.t = t;
      h.pos = r.origin + t * r.direction;
      h.nor = normalize(h.pos - s.center);
      return true;
    }

    t = (-b + sqrt(discriminant)) / a; //big t
    if (0 < t && t < h.t)
    {
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
vec4 ToneMap(in vec4 Color, in float White)
{
  return clamp(Color * (1 + Color / White) / (1 + Color), 0, 1);
}

//Gamma Correction
vec4 GammaCorrect(in vec4 Color, in float Gamma)
{
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
void mat_background(inout ray r, in hit h){
    r.depth = DEPTH; //backgroundに当たった時点でdepth最大
    r.emission = texture(background, vec2((PI - atan(-r.direction.x, -r.direction.z)) / (2 * PI), acos(r.direction.y) / PI)).xyz;
}

// Light
void mat_light(inout ray r, in hit h) {
  r.depth = DEPTH;
  r.scatter = r.scatter * vec3(1);
  r.emission = vec3(10);
}

// Diffuse
void mat_diffuse(inout ray r, in hit h) {
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
  r.scatter = r.scatter * vec3(1);
  r.emission = vec3(0);
}

//Mirror
void mat_mirror(inout ray r, in hit h)
{
  r.depth = r.depth + 1;
  r.origin = h.pos + h.nor * 0.001f;
  r.direction = 2 * dot(-r.direction, h.nor) * h.nor + r.direction;
  r.scatter = r.scatter * vec3(1);
  r.emission = vec3(0);
}

//Glass
void mat_glass(inout ray r, in hit h)
{
  r.depth = r.depth + 1;
  float n = 1.5;
  vec3 N;
  if (dot(-r.direction, h.nor) > 0) {
    n = 1.0 / n;
    N = h.nor;
  }
  else {
    n = n / 1.0;
    N = -h.nor;
  }
  if (rand() < fresnel(n, dot(-r.direction, N))) {
    r.origin = h.pos + N * 0.001f;
    r.direction = 2 * dot(-r.direction, N) * N + r.direction;
  }
  else {
    r.origin = h.pos - N * 0.001f;
    float t = dot(-r.direction, N);
    r.direction = n * r.direction +
                  (n * t - sqrt(1 - pow2(n) * (1 - pow2(t)))) * N;
  }

  r.scatter = r.scatter * vec3(1);
  r.emission = vec3(0);
}

void mat_nor(inout ray r, in hit h) {
  r.depth = DEPTH;
  r.scatter = r.scatter * vec3(h.nor*sin(_AccumN/100));
  r.emission = vec3(3);
}

//--------------------------------------------------
//                    Main
//--------------------------------------------------
void main() {
    vec4 pixel = vec4(0, 0, 0, 0);
    vec4 A = imageLoad(img_input, _WorkID.xy);  //今まで計算した画像

    // Seed
    _xors ^= imageLoad(seed, _WorkID.xy);

    vec3 eye = vec3(0, 0, 18);
    vec3 screen_position;

    ray _rays;
    hit h;
    h.t = 10000;
    h.pos = vec3(0);

    // Sphere
    sphere floor;
    floor.center = vec3(0, -10000, 0);
    floor.radius = 9998;

    sphere s1;
    s1.center = vec3(0, 0, 0);
    s1.radius = 2;

    sphere s2;
    s2.center = vec3(-3, 0, -2);
    s2.radius = 2;

    sphere s3;
    s3.center = vec3(3, 0, -2);
    s3.radius = 2;


    //Sample Loop
    for (int n = 0; n < SPP; n++)
    {
        screen_position.x = float(_WorkID.x + rand()) / _WorksN.x * 16 - 8;
        screen_position.y = float(_WorkID.y + rand()) / _WorksN.y * 9 - 4.5;
        screen_position.z = eye.z - 9;

        // Ray
        mat3 M1 = mat3( cos(_Theta), 0, sin(_Theta), 0, 1, 0, -sin(_Theta), 0, cos(_Theta));
        mat3 M2 = mat3(1, 0, 0, 0, cos(_Phi), -sin(_Phi), 0, sin(_Phi), cos(_Phi));
        _rays.origin = M1 * M2 * eye;
        _rays.direction = normalize( M1 * M2 * (screen_position - eye));


        _rays.scatter  = vec3(1);
        _rays.emission = vec3(0);
        _rays.depth = 0;

        while (_rays.depth < DEPTH)
        {
            h.t = 10000;
            h.pos = vec3(0);
            h.nor = vec3(0);
            h.mat = 0;

            if (hit_sphere(floor, _rays, h)) h.mat = 1;
            if (hit_sphere(s1, _rays, h)) h.mat = 1;
            if (hit_sphere(s2, _rays, h)) h.mat = 3;
            if (hit_sphere(s3, _rays, h)) h.mat = 2;

            switch(h.mat) {
                case 0: mat_background(_rays, h); break;
                case 1: mat_diffuse(_rays, h); break;
                case 2: mat_glass(_rays, h); break;
                case 3: mat_mirror(_rays, h); break;
                case 4: mat_light(_rays, h); break;
            }
        }

        pixel.rgb = _rays.scatter * _rays.emission;
        A.rgb += (pixel.rgb - A.rgb) / _AccumN;
    }


    // Output
    A.rgb += (pixel.rgb - A.rgb) / _AccumN;
    if (_WorkID.xy == ivec2(0)) _AccumN += SPP;
    imageStore(img_output, _WorkID.xy, GammaCorrect(ToneMap(A, 100), 2.2));
    imageStore(img_input, _WorkID.xy, A);
    imageStore(seed, _WorkID.xy, _xors);
}
