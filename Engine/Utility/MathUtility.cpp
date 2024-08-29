#include <Engine/PreCompiled.h>

#include <Engine/Utility/MathUtility.h>

namespace StarEngine::MathUtility
{
    VOID DecomposeTransform(R32M4 const& Transform, R32V3& Position, R32V3& Rotation, R32V3& Scale)
    {
        Position = Transform[3];

        R32V3 C0(Transform[0]);
        R32V3 C1(Transform[1]);
        R32V3 C2(Transform[2]);

        Scale.x = glm::length(C0);
        Scale.y = glm::length(C1);
        Scale.z = glm::length(C2);

        R32M3 RotationMatrix(glm::normalize(C0), glm::normalize(C1), glm::normalize(C2));

        Rotation = glm::degrees(glm::eulerAngles(glm::quat_cast(RotationMatrix)));
    }
}