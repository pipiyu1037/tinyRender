#version 330 core
out vec4 FragColor;  

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D shadowMap;
uniform float glossiness;

in VS_OUT {
    vec2 TexCoord;
    vec3 TangentLightDirection;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec4 FragPosLightSpace;
} fs_in;

struct DirectionalLight {
    vec3 direction;
    vec3 color;
    float intensity;
};

uniform DirectionalLight dirlight0;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // 执行透视除法
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // 变换到[0,1]的范围
    projCoords = projCoords * 0.5 + 0.5;
    // 取得当前片段在光源视角下的深度
    float currentDepth = projCoords.z;


    // 检查当前片段是否在阴影中
    float bias = max((1.0 - dot(vec3(0.0, 0.0, 1.0), fs_in.TangentLightDirection)), 1.0) * 0.002;
    float shadow = 0;

    vec2 texelSize = 1.0 / textureSize(shadowMap, 0) / 2.0;
    for(int x = -3; x <= 3; ++x) {
        for(int y = -3; y <= 3; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 49.0;

    if(projCoords.z > 1.0) {
        shadow = 0.0;
    }

    return shadow;
}

void main()
{
    vec3 diffuseColor = texture(texture_diffuse1, fs_in.TexCoord).rgb;
    vec3 specularColor = texture(texture_specular1, fs_in.TexCoord).rgb;

    vec3 ambient = diffuseColor * 0.2 * dirlight0.color;

    vec3 normal = texture(texture_normal1, fs_in.TexCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0); 
    
    vec3 lightDir = normalize(-fs_in.TangentLightDirection);
    vec3 diffuse = diffuseColor * max(dot(normal, lightDir), 0.0) * dirlight0.color;

    float attenuation = dirlight0.intensity;

    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    vec3 specular = specularColor * pow(max(dot(normal, halfwayDir), 0.0), glossiness) * dirlight0.color;

    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
    
    FragColor = vec4(ambient + (1.0 - shadow) * (diffuse + specular) * attenuation, 1.0);
}