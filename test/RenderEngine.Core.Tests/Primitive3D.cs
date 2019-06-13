using System;
using Xunit;

namespace RenderEngine.Core.Tests
{
    public class Primitive3D
    {
        [Fact]
        public void Factory_creates_valid_point()
        {
            var factory = new PrimitivesFactory();

            var point = factory.CreatePoint3D(1, 2, 3);

            Assert.IsType<Point3D>(point);
            Assert.IsNotType<Point3D>(point);

            Assert.Equal(1, point.Item1);
            Assert.Equal(2, point.Item2);
            Assert.Equal(3, point.Item3);

            Assert.Equal(1, point.Item4);
        }

        [Fact]
        public void Factory_creates_valid_vector()
        {
            var factory = new PrimitivesFactory();

            var vector = factory.CreateVector3D(1, 2, 3);

            Assert.IsType<Vector3D>(vector);
            Assert.IsNotType<Point3D>(vector);

            Assert.Equal(1, vector.Item1);
            Assert.Equal(2, vector.Item2);
            Assert.Equal(3, vector.Item3);

            Assert.Equal(0, vector.Item4);
        }
    }
}
