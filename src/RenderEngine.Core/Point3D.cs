namespace RenderEngine.Core
{
    public class Point3D : Primitive3D
    {
        public Point3D(float x, float y, float z)
            : base(x, y, z, 1)
        { }

        internal Point3D(Primitive3D primitive)
            : base(primitive)
        { }

        public static Vector3D operator -(Point3D left, Point3D right)
        {
            return left.Subtract(right).ToVector3D();
        }

        public static Point3D operator +(Point3D left, Vector3D right)
        {
            return left.Add(right).ToPoint3D();
        }

        public static Point3D operator -(Point3D left, Vector3D right)
        {
            return left.Subtract(right).ToPoint3D();
        }
    }
}