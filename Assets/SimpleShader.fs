#version 330

out vec4 out_color;

struct Material
{
	vec3 diffuse;
};

uniform Material u_material;

void main()
{
	out_color = vec4(u_material.diffuse, 1.0);
}