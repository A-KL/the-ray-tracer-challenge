namespace RenderEngine.Core
{
    public class PrimitivesFactory
    {
        public Point3D CreatePoint3D(float x, float y, float z)
        {
            return new Point3D(x, y, z);
        }

        public Vector3D CreateVector3D(float x, float y, float z)
        {
            return new Vector3D(x, y, z);
        }
    }
}
