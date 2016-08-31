#version 430

layout(local_size_x = 128) in;

struct Transform2d
{
  vec2 position;
  float rotation;
  vec2 size;
};

layout(std430, binding = 0) writeonly buffer Output
{
  vec2 corners[];
};

layout(std430, binding = 1) readonly buffer Input0
{
  Transform2d transforms[];
};

uniform mat4 points;

void main()
{
  uint ind = gl_GlobalInvocationID.x;
  Transform2d transform = transforms[ind / 4];

  float cosRotation = cos(transform.rotation);
  float sinRotation = sin(transform.rotation);
  mat2 rotation = mat2(cosRotation, -sinRotation, sinRotation, cosRotation);

  vec2 corner = points[ind % 4].xy;
  corner = rotation * (transform.size * corner);
  corner += transform.position;

  corners[ind] = corner;
}
