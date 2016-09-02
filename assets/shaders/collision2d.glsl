#version 430

layout(local_size_x = 32, local_size_y = 32) in;

layout(std430, binding = 3) buffer Output
{
  uint collides[]
}

layout(r32f, binding = 0) readonly uniform image2D image0;
layout(r32f, binding = 1) readonly uniform image2D image1;

readonly uniform mat3 transform

void main()
{
  ivec2 ind = gl_GlobalInvocationID.xy;
  bool hit0 = imageLoad(image0, ind).w > 0;

  vec2 size0 = imageSize(image0);
  vec2 size1 = imageSize(image1);

  vec3 scaledPosHom = transform * vec3(ind / size0, 1);
  vec2 scaledPos = scaledPosHom.xy / scaledPosHom.z;
  bool inBounds = scaledPos.x >= 0 && scaledPos.x < 1 &&
                  scaledPos.y >= 0 && scaledPos.y < 1;

  ivec2 coords = ivec2(scaledPos * size1);
  bool hit1 = inBounds && imageLoad(image1, coords).w > 0;

  atomicOr(collides[0], hit0 && hit1);
}
