using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;

namespace Platformer
{
    static class ConvertUnits
    {

        static float UnitSize = 25;

        public static Vector2 ToWorld(Vector2 screenCoords)
        {
            return screenCoords / UnitSize;
        }

        public static Vector2 ToScreen(Vector2 worldCoords)
        {
            return worldCoords * UnitSize;
        }



    }
}
