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
using FarseerPhysics.Common;
using FarseerPhysics.Common.PolygonManipulation;
using FarseerPhysics.Collision;
using FarseerPhysics.Collision.Shapes;

namespace Platformer
{
    class TileMap : GameObject
    {

        List<GameObject> Walls;

        public float NodeSize = 1f;
        int Width;
        int Height;
        int[,] Nodes;

        public World World;
        public ObjectManager ObjectManager;

        Texture2D Level;

        public TileMap(World world, ObjectManager objectMgr, int width, int height) : base(world)
        {
            Position = new Vector2(Width, Height);

            Nodes = new int[width,height];
            Width = width;
            Height = height;
            Walls = new List<GameObject>();

            World = world;
            ObjectManager = objectMgr;

            Body = new Body(World, "wall");

            Body.BodyType = BodyType.Static;
        }

        public void LoadGrid()
        {
            for (int x = 0; x < Width; x++)
            {
                for (int y = 0; y < Height; y++)
                {

                    Color[] tileColor = new Color[1];
                    Rectangle getPixel = new Rectangle(x, y, 1, 1);

                    Level.GetData<Color>(0, getPixel, tileColor, 0, 1);

                    Nodes[x,y] = 0;

                    Color wall = new Color(255, 255, 255);
                    Color player = new Color(0, 0, 255);

                    if (tileColor[0] == wall)
                    {
                        Nodes[x, y] = 1;
                    }
                    if (tileColor[0] == player)
                    {
                        Player newPlayer = new Player(World, new Vector2(x * NodeSize, y * NodeSize));
                        ObjectManager.AddObject(newPlayer);
                    }
                }
            }

            List<Vertices> shapes = BuildCollisionShapeFromLayer(Nodes);

            foreach (Vertices verts in shapes)
            {
                LoopShape newShape = new LoopShape(verts);
                Body.CreateFixture(newShape, "wall");
            }
        }

        private List<Vertices> BuildCollisionShapeFromLayer(int[,] collisionRect)
        {
            List<EdgeShape> edgeList = new List<EdgeShape>();
            for (int i = 0; i < collisionRect.GetLength(0); ++i)
            {
                for (int j = 0; j < collisionRect.GetLength(1); ++j)
                {
                    if (collisionRect[i, j] == 1)
                    {
                        // Check the four adjacent tiles and add edges between colliding
                        // and non-coliding tiles to a list
                        if (i == 0 || collisionRect[i - 1, j] == 0)
                        {
                            edgeList.Add(new EdgeShape(new Vector2((float)i * NodeSize, (float)j * NodeSize),
                                                  new Vector2((float)i * NodeSize, (float)(j + 1) * NodeSize)));
                        }
                        if (i == collisionRect.GetLength(0) - 1 || collisionRect[i + 1, j] == 0)
                        {
                            edgeList.Add(new EdgeShape(new Vector2((float)(i + 1) * NodeSize, (float)(j + 1) * NodeSize),
                                                  new Vector2((float)(i + 1) * NodeSize, (float)j * NodeSize)));
                        }
                        if (j == 0 || collisionRect[i, j - 1] == 0)
                        {
                            edgeList.Add(new EdgeShape(new Vector2((float)(i + 1) * NodeSize, (float)j * NodeSize),
                                                  new Vector2((float)i * NodeSize, (float)j * NodeSize)));
                        }
                        if (j == collisionRect.GetLength(1) - 1 || collisionRect[i, j + 1] == 0)
                        {
                            edgeList.Add(new EdgeShape(new Vector2((float)i * NodeSize, (float)(j + 1) * NodeSize),
                                         new Vector2((float)(i + 1) * NodeSize, (float)(j + 1) * NodeSize)));
                        }
                    }
                }
            }

            // Combine edges which share a point to a closed polygon
            List<Vertices> collisionShape = new List<Vertices>();
            while (edgeList.Count > 0)
            {
                Vertices output = new Vertices();
                output.Add(edgeList[0].Vertex1);
                output.Add(edgeList[0].Vertex2);
                edgeList.RemoveAt(0);
                bool closed = false;
                int index = 0;
                while (!closed && edgeList.Count > 0)
                {
                    if (output[output.Count - 1] == edgeList[index].Vertex1)
                    {
                        if (edgeList[index].Vertex2 == output[0])
                        {
                            closed = true;
                        }
                        else
                        {
                            output.Add(edgeList[index].Vertex2);
                        }
                        edgeList.RemoveAt(index);
                        --index;
                    }
                    if (!closed && ++index == edgeList.Count)
                    {
                        index = 0;
                    }
                }
                // remove colinear points from polygon
                output = SimplifyTools.CollinearSimplify(output);
                collisionShape.Add(output);
            }
            return collisionShape;
        }

        public override void Init()
        {

        }

        public override void LoadAssets(ContentManager content)
        {
            Sprite = content.Load<Texture2D>("pix");
            Level = content.Load<Texture2D>("level");

            LoadGrid();
        }

        public override void Update(GameTime gameTime)
        {

        }

        public override void Draw(SpriteBatch spriteBatch)
        {
            for (int x = 0; x < Nodes.GetLength(0); x++)
            {
                for (int y = 0; y < Nodes.GetLength(1); y++)
                {
                    if (Nodes[x, y] == 1)
                    {
                        Vector2 spritePos = ConvertUnits.ToScreen(new Vector2(x * NodeSize + NodeSize / 2, y * NodeSize + NodeSize / 2));
                        Vector2 spriteSize = ConvertUnits.ToScreen(new Vector2(NodeSize));
                        Vector2 scale = new Vector2(spriteSize.X / Sprite.Width, spriteSize.Y / Sprite.Height);
                        spriteBatch.Draw(Sprite, spritePos, new Rectangle(0, 0, Sprite.Width, Sprite.Height), Color.White, Rotation, new Vector2(0.5f), scale, SpriteEffects.None, 0);
                    }
                }
            }
        }
    }
}
