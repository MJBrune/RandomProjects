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
    class Player : GameObject
    {


        float moveSpeed = 100;
        float jumpSpeed = 35;
        float lastYVel;

        float setShootCooldown = 0.1f;
        float shootCooldown;



        RayCastCallback GroundRay;

        bool onGround;

        public Player(World world, Vector2 pos) : base(world)
        {

            GroundRay = new RayCastCallback(HasGround);

            Size = new Vector2(1f, 1.5f);
            Position = pos;

            Body = BodyFactory.CreateRectangle(World, Size.X, Size.Y, 1);
            Body.Position = Position;
            Body.Mass = 50;
            Body.Friction = 0f;
            Body.LinearDamping = 0;
            Body.BodyType = BodyType.Dynamic;

            Body.UserData = "player";


            Body.FixedRotation = true;
        }

        public override void Init()
        {

        }

        public override void LoadAssets(ContentManager content)
        {
            Sprite = content.Load<Texture2D>("player");
        }

        float HasGround(Fixture fixture, Vector2 point, Vector2 normal, float fraction){

            if ((string)fixture.Body.UserData == "wall")
            {
                onGround = true;
            }
            return 0;
        }

        public override void Update(GameTime gameTime)
        {

            float moveDir = 0;
            KeyboardState keyState = Keyboard.GetState();
            MouseState mouseState = Mouse.GetState();

            onGround = false;
            World.RayCast(GroundRay, new Vector2(Position.X - Size.X / 2, Position.Y), new Vector2(Position.X - Size.X / 2, Position.Y + Size.Y / 2 + 0.05f));
            World.RayCast(GroundRay, new Vector2(Position.X, Position.Y), new Vector2(Position.X, Position.Y + Size.Y / 2 + 0.05f));
            World.RayCast(GroundRay, new Vector2(Position.X + Size.X / 2, Position.Y), new Vector2(Position.X + Size.X / 2, Position.Y + Size.Y / 2 + 0.05f));
            
            if (onGround)
            {
                Body.LinearVelocity = new Vector2(Body.LinearVelocity.X, 0);
            }

            if(keyState.IsKeyDown(Keys.A)){
                moveDir -= 1;
            }
            if (keyState.IsKeyDown(Keys.D))
            {
                moveDir += 1;
            }

            Vector2 shootDir = Vector2.Zero;
            if (keyState.IsKeyDown(Keys.Up)) shootDir.Y -= 1;
            if (keyState.IsKeyDown(Keys.Down)) shootDir.Y += 1;
            if (keyState.IsKeyDown(Keys.Left)) shootDir.X -= 1;
            if (keyState.IsKeyDown(Keys.Right)) shootDir.X += 1;

            if (shootDir.Length() != 0) Shoot(shootDir);



            if (keyState.IsKeyDown(Keys.W) && onGround)
            {
                Body.ApplyLinearImpulse(new Vector2(0, -jumpSpeed));
            }

            Body.LinearVelocity = new Vector2(Body.LinearVelocity.X * 0.90f, Body.LinearVelocity.Y);

            Body.ApplyForce(new Vector2(moveDir * moveSpeed, 0));

            if (shootCooldown > 0)
            {
                shootCooldown -= (float)gameTime.ElapsedGameTime.TotalSeconds;
            }
            else
            {
                shootCooldown = 0;
            }

            base.Update(gameTime);
        }

        public override void Draw(SpriteBatch spriteBatch)
        {
            Vector2 spriteSize = ConvertUnits.ToScreen(Size);
            Vector2 spritePos = ConvertUnits.ToScreen(Position);
            Vector2 scale = new Vector2(spriteSize.X / Sprite.Width, spriteSize.Y / Sprite.Height);

            spriteBatch.Draw(Sprite, spritePos, new Rectangle(0, 0, Sprite.Width, Sprite.Height), Color.White, Rotation, new Vector2(Sprite.Width / 2, Sprite.Height/2), scale, SpriteEffects.None, 0);
        }

        public void Shoot(Vector2 dir)
        {
            if (shootCooldown == 0)
            {
                ObjectManager.AddObject(new Bullet(World, Position, dir, this));
                shootCooldown = setShootCooldown;
            }
        }

        bool Collides(Fixture fix1, Fixture fix2, Contact contact){
            return false;
        }


    }
}
