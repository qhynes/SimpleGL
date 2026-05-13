#version 330 core

#define MAX_POINT_LIGHTS 32
#define MAX_SPOT_LIGHTS 16

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct DirLight {
    vec3 radiance;
    vec3 direction; // direction light rays travel, normalized
};

struct PointLight {
    vec3 radiance;

    vec3 position;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 radiance;

    vec3 position;
    vec3 direction; // direction spotlight points, normalized

    float innerCutoff;
    float outerCutoff;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;

uniform vec3 ambientColor;
uniform float ambientStrength;

uniform bool hasDirLight;
uniform DirLight dirLight;

uniform int numPointLights;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

uniform int numSpotLights;
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

vec3 calcDirLight(vec3 norm, vec3 viewDir, vec3 albedo, vec3 specularMap);
vec3 calcPointLight(int index, vec3 norm, vec3 viewDir, vec3 albedo, vec3 specularMap);
vec3 calcSpotLight(int index, vec3 norm, vec3 viewDir, vec3 albedo, vec3 specularMap);

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 albedo = vec3(texture(material.diffuse, TexCoords));
    vec3 specularMap = vec3(texture(material.specular, TexCoords));

    vec3 result = ambientColor * ambientStrength * albedo;

    if (hasDirLight) result += calcDirLight(norm, viewDir, albedo, specularMap);

    for (int i = 0; i < numPointLights; i++) {
        result += calcPointLight(i, norm, viewDir, albedo, specularMap);
    }

    for (int i = 0; i < numSpotLights; i++) {
        result += calcSpotLight(i, norm, viewDir, albedo, specularMap);
    }

    FragColor = vec4(result, 1.0);
}

vec3 calcDirLight(
    vec3 norm,
    vec3 viewDir,
    vec3 albedo,
    vec3 specularMap
) {
    vec3 dirToLight = -dirLight.direction;

    float lambertTerm = max(dot(norm, dirToLight), 0.0);
    vec3 diffuse = dirLight.radiance * lambertTerm * albedo;

    vec3 reflectDir = reflect(-dirToLight, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = dirLight.radiance * spec * specularMap;

    return diffuse + specular;
}

vec3 calcPointLight(
    int index,
    vec3 norm,
    vec3 viewDir,
    vec3 albedo,
    vec3 specularMap
) {
    vec3 fragToLight = pointLights[index].position - FragPos;

    float distanceToLight = length(fragToLight);
    vec3 dirToLight = fragToLight / distanceToLight;

    float lambertTerm = max(dot(norm, dirToLight), 0.0);
    vec3 diffuse = pointLights[index].radiance * lambertTerm * albedo;

    vec3 reflectDir = reflect(-dirToLight, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = pointLights[index].radiance * spec * specularMap;

    float distanceSquared = distanceToLight * distanceToLight;

    float attenuation = 1.0 / (
        pointLights[index].constant +
        pointLights[index].linear * distanceToLight +
        pointLights[index].quadratic * distanceSquared
    );

    return (diffuse + specular) * attenuation;
}

vec3 calcSpotLight(
    int index,
    vec3 norm,
    vec3 viewDir,
    vec3 albedo,
    vec3 specularMap
) {
    vec3 fragToLight = spotLights[index].position - FragPos;

    float distanceToLight = length(fragToLight);
    vec3 dirToLight = fragToLight / distanceToLight;

    float theta = dot(-dirToLight, spotLights[index].direction);

    float epsilon = spotLights[index].innerCutoff - spotLights[index].outerCutoff;

    float spotIntensity = clamp((theta - spotLights[index].outerCutoff) / epsilon, 0.0, 1.0);

    float lambertTerm = max(dot(norm, dirToLight), 0.0);
    vec3 diffuse = spotLights[index].radiance * lambertTerm * albedo;

    vec3 reflectDir = reflect(-dirToLight, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spotLights[index].radiance * spec * specularMap;

    float distanceSquared = distanceToLight * distanceToLight;

    float attenuation = 1.0 / (
        spotLights[index].constant +
        spotLights[index].linear * distanceToLight +
        spotLights[index].quadratic * distanceSquared
    );

    return (diffuse + specular) * attenuation * spotIntensity;
}
