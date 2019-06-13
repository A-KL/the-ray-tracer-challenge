namespace RenderEngine.Core
{
    public static class Primitive3DExtensions
    {
        public static Point3D ToPoint3D(this Primitive3D primitive)
        {
            return new Point3D(primitive);
        }

        public static Vector3D ToVector3D(this Primitive3D primitive)
        {
            return new Vector3D(primitive);
        }
    }
}
