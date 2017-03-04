// -------------------------------------------------------------------------------------------------
// Default shader with tiling parameter
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
// vertex_shader
// -------------------------------------------------------------------------------------------------
#version 130

uniform mat4 camera_to_local_matrix;

varying vec2 uv;
varying mat3 tbn_matrix;
varying vec3 eye_vector;
varying float depth;
uniform float tiling;

void main()
{
    uv = gl_MultiTexCoord0.xy*tiling;

    tbn_matrix[0] = gl_MultiTexCoord1.xyz;
    tbn_matrix[1] = gl_MultiTexCoord2.xyz;
    tbn_matrix[2] = gl_Normal.xyz;

    eye_vector = (gl_Vertex.xyz-camera_to_local_matrix[3].xyz) * tbn_matrix;

    tbn_matrix = gl_NormalMatrix*tbn_matrix;

    vec4 position = gl_ModelViewMatrix*gl_Vertex;
    depth = position.z;
    gl_Position = gl_ProjectionMatrix*position;
}

// -------------------------------------------------------------------------------------------------
// fragment_shader
// -------------------------------------------------------------------------------------------------
#version 130
#extension GL_ARB_texture_rectangle : enable
#include "../../coffee/assets/shaders/helpers.glslh"

uniform sampler2D base_texture;
uniform sampler2D normal_texture;
uniform sampler2D height_texture;
uniform vec4 albedo;
uniform float height;

varying vec2 uv;
varying mat3 tbn_matrix;
varying vec3 eye_vector;
varying float depth;

void main()
{
    vec2 parallax_uv = ComputeParallax(uv, eye_vector, texture2D(height_texture, uv).x, height);
    
    // Write packed linear depth
    gl_FragData[0].xy = PackDepth(depth);    
    
    // Write normal layer
    vec3 normal = texture2D(normal_texture, parallax_uv).xyz*2.0-1.0;
    normal.xy = -normal.xy;
    normal = normalize(tbn_matrix*normal);
    gl_FragData[1].xyz = PackNormal(normal);
        
    // Write color layer
    gl_FragData[2].xyz = texture2D(base_texture, parallax_uv).xyz*albedo.xyz;    
    
    // Write material layer
    gl_FragData[3].x = 0.2;
    gl_FragData[3].y = 0.8;
}
