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

namespace Platformer
{
    public class ObjectManager
    {
        List<GameObject> Objects;
        List<GameObject> AddedObjects;
        List<GameObject> RemovedObjects;

        bool isInited = false;
        bool isLoaded = false;

        ContentManager Content;

        private RemovedEventHandler ObjectRemoved;

        public ObjectManager()
        {
            Objects = new List<GameObject>();
            AddedObjects = new List<GameObject>();
            RemovedObjects = new List<GameObject>();

            ObjectRemoved = new RemovedEventHandler(RemoveObject);
        }

        public void AddObject(GameObject newObject)
        {
            if (isInited) newObject.Init();
            if (isLoaded) newObject.LoadAssets(Content);

            newObject.ObjectManager = this;

            newObject.Removed += ObjectRemoved;

            if (!isInited && !isLoaded)
            {
                Objects.Add(newObject);
            }
            else
            {
                AddedObjects.Add(newObject);
            }
        }

        private void MergeObjects()
        {
            if (AddedObjects.Count == 0 && RemovedObjects.Count == 0) return;

            Objects.AddRange(AddedObjects);
            AddedObjects.Clear();

            foreach (GameObject removeObject in RemovedObjects)
            {
                Objects.Remove(removeObject);
            }
            RemovedObjects.Clear();
        }

        public void RemoveObject(GameObject rmObject)
        {
            RemovedObjects.Add(rmObject);
        }

        public void Init()
        {
            isInited = true;
            foreach (GameObject entity in Objects)
            {
                entity.Init();
            }
            MergeObjects();
        }

        public void LoadAssets(ContentManager content)
        {
            isLoaded = true;
            Content = content;
            foreach (GameObject entity in Objects)
            {
                entity.LoadAssets(content);
            }
            MergeObjects();
        }

        public void Update(GameTime gameTime)
        {
            foreach (GameObject entity in Objects)
            {
                entity.Update(gameTime);
            }
            MergeObjects();
        }

        public void Draw(SpriteBatch spriteBatch)
        {
            foreach (GameObject entity in Objects)
            {
                entity.Draw(spriteBatch);
            }
        }

    }
}
