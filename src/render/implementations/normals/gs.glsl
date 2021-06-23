#version 330 core
layout(triangles) in;

layout(line_strip, max_vertices=12) out;

float normal_length = 0.001;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in Vertex
{
    vec4 position;
    vec4 normal;
    vec4 tangent;
    vec4 color;
} vertex[];

out vec4 vertex_color;

void main()
{
    int i;
    mat4 mvp = projectionMatrix * viewMatrix * transformationMatrix;
    for(i=0; i<gl_in.length(); i++)
    {
        vec3 P = vertex[i].position.xyz;
        vec3 N = vertex[i].normal.xyz;

        gl_Position =  mvp * vec4(P, 1.0);
        vertex_color = vertex[i].color;
        EmitVertex();

        gl_Position = mvp * vec4(P + N * normal_length, 1.0);
        vertex_color =vertex[i].color;
        EmitVertex();

        EndPrimitive();

        N = vertex[i].tangent.xyz;

        gl_Position =  mvp * vec4(P, 1.0);
        vertex_color = vertex[i].color;
        EmitVertex();

        gl_Position = mvp * vec4(P + N * normal_length, 1.0);
        vertex_color = vertex[i].color;
        EmitVertex();

        EndPrimitive();

    }
}
