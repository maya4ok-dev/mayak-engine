#pragma once

namespace mayak::ecs {

    struct Transform {
        float x = 0, y = 0; // Position
        float w = 1, h = 1; // Size
        float angle = 0; // Rotation
    };
    
}