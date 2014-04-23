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
using FarseerPhysics.Common;
using FarseerPhysics.Factories;
using FarseerPhysics.Collision.Shapes;
using FarseerPhysics.Dynamics.Joints;

namespace Platformer
{
    class Bullet : GameObject
    {

        

        float moveSpeed = 20;

        Vector2 MoveDir;

        bool removeOnNext = false;

        public Bullet(World world, Vector2 pos, Vector2 moveDir, GameObject parent) : base(world)
        {

            MoveDir = Vector2.Normalize(moveDir);


            Size = new Vector2(0.2f);
            Position = pos;

            Body = BodyFactory.CreateRectangle(World, Size.X, Size.Y, 1);
            Body.Position = Position;
            Body.Mass = 1;
            Body.Friction = 0f;
            Body.LinearDamping = 0;
            Body.IgnoreGravity = true;
            Body.IsBullet = true;
            Body.BodyType = BodyType.Dynamic;
            Body.FixedRotation = true;
            Body.UserData = "bullet";

            Body.OnCollision += Collides;


            Body.LinearVelocity = MoveDir * moveSpeed;
        }

        public override void Init()
        {
            
        }

        public override void LoadAssets(ContentManager content)
        {
            Sprite = content.Load<Texture2D>("pix");
        }


        public override void Update(GameTime gameTime)
        {
            if (removeOnNext)
            {
                Remove();
            }

            base.Update(gameTime);
        }

        public override void Draw(SpriteBatch spriteBatch)
        {
            Vector2 spriteSize = ConvertUnits.ToScreen(Size);
            Vector2 spritePos = ConvertUnits.ToScreen(Position);
            Vector2 scale = new Vector2(spriteSize.X / Sprite.Width, spriteSize.Y / Sprite.Height);

            spriteBatch.Draw(Sprite, spritePos, new Rectangle(0, 0, Sprite.Width, Sprite.Height), Color.Yellow, Rotation, new Vector2(0.5f), scale, SpriteEffects.None, 0);
        }

        public bool Collides(Fixture fix1, Fixture fix2, Contact contact){
            if ((string)fix2.Body.UserData != "player" && (string)fix2.Body.UserData != "bullet")
            {
                removeOnNext = true;
            }
            return false;
        }

    }
}
