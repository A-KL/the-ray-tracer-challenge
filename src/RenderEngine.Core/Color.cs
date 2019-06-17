using System.Runtime.InteropServices;

namespace RenderEngine.Core
{
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Color3f
    {
        public float Blue;

        public float Green;
       
        public float Red;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Color3b
    {
        public byte Blue;

        public byte Green;        

        public byte Red;
    }
}
