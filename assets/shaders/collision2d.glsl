#version 430

layout(local_size_x = 32, local_size_y = 32) in;

layout(std430, binding = 3) buffer Output
{
  uint collides[];
};

layout(rgba8, binding = 0) readonly uniform image2D image0;
layout(rgba8, binding = 1) readonly uniform image2D image1;

uniform mat3 transform;

void main()
{
  ivec2 ind = ivec2(gl_GlobalInvocationID);
  bool hit0 = imageLoad(image0, ind).a > 0;

  vec2 size0 = imageSize(image0);
  vec2 size1 = imageSize(image1);


  vec3 scaledPos = transform * vec3(ind / size0, 1);
  bool inBounds = scaledPos.x >= 0 && scaledPos.x < 1 &&
                  scaledPos.y >= 0 && scaledPos.y < 1;

  ivec2 coords = ivec2(scaledPos.xy * size1);
  bool hit1 = inBounds && imageLoad(image1, coords).a > 0;

  atomicOr(collides[0], uint(hit0 && hit1));
}
