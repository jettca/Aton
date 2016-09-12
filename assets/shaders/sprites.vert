#version 150

uniform mat4 ciModelViewProjection;

in vec4 ciPosition;
in vec2 ciTexCoord0;

in vec3 aPosition;
in float aRotation;
in vec2 aSize;

out vec2 uv;

void main()
{
  float cosRotation = cos(aRotation);
  float sinRotation = sin(aRotation);
  mat2 rotation = mat2(vec2(cosRotation, sinRotation), vec2(-sinRotation, cosRotation));
  vec4 position = ciPosition;
  position.xy = rotation * (aSize.xy * position.xy);
  position.xy += aPosition.xy;
  position.z += aPosition.z;

  gl_Position = ciModelViewProjection * position;
  uv = ciTexCoord0;
}