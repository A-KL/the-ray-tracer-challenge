using System;

namespace RenderEngine.Core
{
    public static class Mathf
    {
        public const float Epsilon = 0.00001f;

        public static bool Approximately(float a, float b)
        {
            return Math.Abs(a - b) < Epsilon;
        }
    }
}