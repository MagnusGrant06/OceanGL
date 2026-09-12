#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

struct Material{
    float shininess;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
struct DirectionalLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 calcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir, Material material){
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal,lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = (diff * material.diffuse) * light.diffuse;
    vec3 specular = (material.specular * spec) * light.specular;

    return (ambient + diffuse + specular);
}

vec3 calcPtLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, Material material){
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * material.ambient;
    vec3 diffuse = (diff * material.diffuse) * light.diffuse;
    vec3 specular = (material.specular * spec) * light.specular;

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

uniform Material material;

uniform PointLight pointLight;

uniform DirectionalLight dirLight;

uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 lightPos;
void main()
{

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    vec3 result = calcDirLight(dirLight, norm, viewDir, material);

    result += calcPtLight(pointLight, norm, FragPos, viewDir, material);

    FragColor = vec4(result, 1.0);

}