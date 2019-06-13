namespace RenderEngine.Core
{
    public class Vector3D : Primitive3D
    {
        public Vector3D(float x, float y, float z)
            : base(x, y, z, 0)
        { }

        internal Vector3D(Primitive3D primitive)
            : base(primitive)
        { }

        public static Vector3D operator +(Vector3D left, Vector3D right)
        {
            return left.Add(right).ToVector3D();
        }

        public static Vector3D operator -(Vector3D left, Vector3D right)
        {
            return left.Subtract(right).ToVector3D();
        }
    }
}