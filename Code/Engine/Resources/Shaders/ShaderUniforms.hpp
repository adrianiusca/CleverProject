#pragma once

namespace cp
{
    enum ShaderUniforms
    {
        VIEW_MATRIX,
        MODEL_MATRIX,
        PROJECTION_MATRIX,

        CAMERA_POSITION,

        MATERIAL_DIFFUSE_COLOR,
        MATERIAL_SPECULAR_COLOR,
        MATERIAL_SPECULAR_SHININESS,

        MATERIAL_DIFFUSE_TEXTURE_1,
        MATERIAL_DIFFUSE_TEXTURE_2,

        DIRECTIONAL_LIGHT_DIFFUSE,
        DIRECTIONAL_LIGHT_SPECULAR,
        DIRECTIONAL_LIGHT_DIRECTION,

        AMBIENT_LIGHT
    };
}