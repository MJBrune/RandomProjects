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
using FarseerPhysics.Dynamics;
using FarseerPhysics.Dynamics.Contacts;


namespace Platformer
{
    class PlayState : GameState
    {

        Player player;
        World world;
        TileMap grid;

        ObjectManager ObjectManager;

        public override void Init(){
            ObjectManager = new ObjectManager();
            world = new World(new Vector2(0, 50));

            grid = new TileMap(world, ObjectManager, 32, 24);
            ObjectManager.AddObject(grid);

            ObjectManager.Init();
        }

        public override void LoadAssets(ContentManager content)
        {
            ObjectManager.LoadAssets(content);
        }

        public override void Update(GameTime gameTime)
        {


            ObjectManager.Update(gameTime);

            world.Step((float)gameTime.ElapsedGameTime.TotalSeconds);
        }

        public override void Draw(SpriteBatch spriteBatch)
        {
            spriteBatch.Begin(SpriteSortMode.BackToFront, BlendState.Additive, SamplerState.PointClamp, DepthStencilState.None, RasterizerState.CullNone);

            ObjectManager.Draw(spriteBatch);

            spriteBatch.End();
        }



    }
}
