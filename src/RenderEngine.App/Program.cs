using System;
using RenderEngine.Core;

namespace RenderEngine.App
{
    class Program
    {
        static void Main(string[] args)
        {
            var engine = new GraphicsBufferOf<Color3b>(100, 200);

            engine.Fill(
                new Color3b
                {
                    Blue = 255,
                    Red = 0,
                    Green = 255
                });

            engine.SaveSnapshot("./Test.jpeg");
        }
    }
}
