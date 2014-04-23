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
    class GameState
    {

        ContentManager Content;

        public virtual void Init()
        {

        }
        public virtual void LoadAssets(ContentManager content)
        {

            Content = content;
        }
        public virtual void Update(GameTime dTime)
        {

        }
        public virtual void Draw(SpriteBatch spriteBatch)
        {

        }
    }
}
