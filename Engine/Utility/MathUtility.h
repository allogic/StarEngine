#pragma once

namespace StarEngine::MathUtility
{
    VOID DecomposeTransform(R32M4 const& Transform, R32V3& Position, R32V3& Rotation, R32V3& Scale);
}