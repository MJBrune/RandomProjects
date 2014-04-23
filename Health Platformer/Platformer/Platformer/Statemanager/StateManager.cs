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
    class StateManager
    {

        
        private List<GameState> States;
        private SpriteBatch spriteBatch;

        public StateManager(GraphicsDevice graphicsDevice)
        {
            States = new List<GameState>();
            spriteBatch = new SpriteBatch(graphicsDevice);
        }

        public void AddState(GameState state){
            //Do required stuff with the gamestate here later

            States.Add(state);
        }

        public void RemoveState(GameState state)
        {
            States.Remove(state);
        }

        public void Init()
        {
            foreach (GameState state in States)
            {
                state.Init();
            }
        }

        public void LoadAssets(ContentManager content)
        {
            foreach (GameState state in States)
            {
                state.LoadAssets(content);
            }
        }


        public void Update(GameTime gameTime)
        {
            foreach (GameState state in States)
            {
                state.Update(gameTime);
            }
        }

        public void Draw(GameTime gameTime)
        {
            foreach (GameState state in States)
            {
                state.Draw(spriteBatch);
            }
        }

    }
}
