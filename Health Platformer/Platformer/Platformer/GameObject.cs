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

    public delegate void RemovedEventHandler(GameObject sender);

    public class GameObject
    {


        public GameObject(World world)
        {
            World = world;
        }

        public event RemovedEventHandler Removed;

        protected virtual void Remove()
        {
            if (Removed != null)
            {
                Removed(this);
            }
        }


        public Texture2D Sprite;
        public Vector2 Size;

        public Body Body;
        public Vector2 Position;
        public float Rotation;

        public World World;
        public ObjectManager ObjectManager;

        public virtual void Init() { }
        public virtual void LoadAssets(ContentManager content) { }
        public virtual void Update(GameTime gameTime) {
            Position = Body.Position;
            Rotation = Body.Rotation;
        }
        public virtual void Draw(SpriteBatch spriteBatch) { }

    }
}
