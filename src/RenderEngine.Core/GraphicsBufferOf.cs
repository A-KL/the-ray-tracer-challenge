using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace RenderEngine.Core
{
    public class GraphicsBufferOf<TColor>
        where TColor : struct
    {
        private readonly int _width;
        private readonly int _height;

        private readonly TColor[] _buffer;

        public GraphicsBufferOf(int width, int height)
        {
            _width = width;
            _height = height;

            _buffer = new TColor[_width * _height];
        }

        public void Fill(TColor color)
        {
            for (var i = 0; i < _buffer.Length; ++i)
            {
                _buffer[i] = color;
            }
        }

        public void SaveSnapshot(string fileName)
        {
            var bytesPerPixel = Marshal.SizeOf(typeof(TColor));

            var intPtr = Marshal.UnsafeAddrOfPinnedArrayElement(_buffer, 0);

            var stride = _width * bytesPerPixel;

            using (var image = new Bitmap(_width, _height, stride, PixelFormat.Format24bppRgb, intPtr))
            {
                image.Save(fileName, ImageFormat.Jpeg);
            }
        }
    }
}
