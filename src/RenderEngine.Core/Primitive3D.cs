using System;

namespace RenderEngine.Core
{
    public class Primitive3D : Tuple<float, float, float, int>,
        IEquatable<Primitive3D>
    {
        protected Primitive3D(Primitive3D primitive)
            : base(primitive.Item1, primitive.Item2, primitive.Item3, primitive.Item4)
        { }

        protected Primitive3D(float x, float y, float z, int w)
            : base(x, y, z, w)
        { }

        #region Equals

        public bool Equals(Primitive3D other)
        {
            return
                Item4.Equals(other.Item4) &&
                Mathf.Approximately(Item1, other.Item1) &&
                Mathf.Approximately(Item2, other.Item2) &&
                Mathf.Approximately(Item3, other.Item3);
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != this.GetType()) return false;

            return Equals((Primitive3D)obj);
        }

        #endregion

        #region Operators

        public static bool operator ==(Primitive3D left, Primitive3D right)
        {
            return Equals(left, right);
        }

        public static bool operator !=(Primitive3D left, Primitive3D right)
        {
            return !Equals(left, right);
        }

        protected Primitive3D Add(Primitive3D other)
        {
            return new Primitive3D(
                Item1 + other.Item1,
                Item2 + other.Item2,
                Item3 + other.Item3,
                Item4 + other.Item4);
        }

        protected Primitive3D Subtract(Primitive3D other)
        {
            return new Primitive3D(
                Item1 - other.Item1,
                Item2 - other.Item2,
                Item3 - other.Item3,
                Item4 - other.Item4);
        }

        #endregion

        #region GetHashCode

        public override int GetHashCode()
        {
            var hashCode = 352033288;

            hashCode = hashCode * -1521134295 + Item1.GetHashCode();
            hashCode = hashCode * -1521134295 + Item2.GetHashCode();
            hashCode = hashCode * -1521134295 + Item3.GetHashCode();
            hashCode = hashCode * -1521134295 + Item4.GetHashCode();

            return hashCode;
        }

        #endregion
    }
}
