#version 330 core

#define MAX_BONE_INFLUENCE 4

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in int BoneId[MAX_BONE_INFLUENCE];
layout (location = 6) in float Weight[MAX_BONE_INFLUENCE];

out VS_OUT {
    vec2 TexCoord;
    vec3 TangentLightDirection;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 model;
uniform mat4 normalInv;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPos;
uniform mat4 lightSpaceMatrix;

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

uniform DirectionalLight dirlight0;

void main()
{
    vec3 T = normalize(vec3(normalInv * vec4(aTangent,   0.0)));
    vec3 N = normalize(vec3(normalInv * vec4(aNormal,    0.0)));
    vec3 B = normalize(vec3(normalInv * vec4(aBitangent, 0.0)));
    if (dot(cross(T, N), B) < 0.0){
        T.x = -T.x;
    }
    B = normalize(cross(T, N));
    mat3 TBN = transpose(mat3(T, B, N));

    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vs_out.TexCoord = aTexCoord;
    //Normal = mat3(normalInv) * aNormal;
    vs_out.TangentLightDirection = TBN * dirlight0.direction;
    vs_out.TangentViewPos = TBN * viewPos;
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.TangentFragPos = TBN * FragPos;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
}