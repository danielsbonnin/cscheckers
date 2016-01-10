using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using AnimatedSprite;
namespace Checkers
{
    /// <summary>
    /// This is the main type for your game
    /// </summary>
    public class Game1 : Microsoft.Xna.Framework.Game
    {
        private AnimatedTexture redCheckAnimated;
        private const float Rotation = 0;
        private const float spritePicHeight = 150f;
        //private const float Scale = 1.0f;
        private const float Depth = 0.9f;
        private const int Frames = 12;
        private const int FramesPerSec = 6;

        GraphicsDeviceManager graphics;
        SpriteBatch spriteBatch;
        private const int height = 680;
        private const int width = 680;
        private const float Scale = ((float)height / ((float) 8 * spritePicHeight)); 
        Rectangle[] checkerPositions = new Rectangle[32];

        int[] xPos = new int[8];
        int[] yPos = new int[8];
        int curX = 0, curY = 0, spaceBetweenCols = 0, spaceBetweenRows = 0;

        CheckersGame game = new CheckersGame();

        public Game1()
        {
            graphics = new GraphicsDeviceManager(this);
            graphics.IsFullScreen = false;
            graphics.PreferredBackBufferHeight = height;
            graphics.PreferredBackBufferWidth = width;
            Content.RootDirectory = "Content";
            redCheckAnimated = new AnimatedTexture(Vector2.Zero,
                Rotation, Scale, Depth);
            this.IsMouseVisible = true;    
        }

        /// <summary>
        /// Allows the game to perform any initialization it needs to before starting to run.
        /// This is where it can query for any required services and load any non-graphic
        /// related content.  Calling base.Initialize will enumerate through any components
        /// and initialize them as well.
        /// </summary>
        protected override void Initialize()
        {
            spaceBetweenCols = width / 8;
            spaceBetweenRows = height / 8;
            curX = -(20 * spaceBetweenCols / 19);
            curY = -(20 * spaceBetweenRows / 19);
            xPos[0] = 0;// (spaceBetweenCols / 2);
            yPos[0] = 0;// (spaceBetweenRows / 2);
            for (int i = 0; i < 8; i++)
            {
                xPos[i] = curX += spaceBetweenCols;
                yPos[i] = curY += spaceBetweenRows;
            }

            // TODO: Add your initialization logic here
            for (int i = 0; i < 32; i++)
            {
                //Fill checkerPositions Rectangles with appropriate coordinates
                //from xPos and yPos.
                game.squares[i].location.X = xPos[((i / 4) % 2 == 0 ? (i % 4) * 2 : ((i % 4) * 2) + 1)];
                game.squares[31 - i].location.Y = yPos[(i / 4)];
                game.squares[31 - i].location.Height = height / 7;
                game.squares[31 - i].location.Width = width / 7;
            }

            base.Initialize();
        }
        // This is a texture we can render.
        Texture2D background;
        Texture2D rCheck, wCheck, rKing, wKing, rCheck_H, wCheck_H, rKing_H, wKing_H;
        Rectangle mainframe;
        
        // Store some information about the sprite's motion.
        /// <summary>
        /// LoadContent will be called once per game and is the place to load
        /// all of your content.
        /// </summary>
        protected override void LoadContent()
        {

            // Create a new SpriteBatch, which can be used to draw textures.
            spriteBatch = new SpriteBatch(GraphicsDevice);
            redCheckAnimated.Load(Content, "rCheckAnimated", Frames, FramesPerSec);
            rCheck = Content.Load<Texture2D>("rChecker");
            wCheck = Content.Load<Texture2D>("wChecker");
            rKing = Content.Load<Texture2D>("rKing");
            wKing = Content.Load<Texture2D>("wKing");
            rKing_H = Content.Load<Texture2D>("rKingHighlight");
            wKing_H = Content.Load<Texture2D>("wKingHighlight");
            rCheck_H = Content.Load<Texture2D>("rCheckerHighlight");
            wCheck_H = Content.Load<Texture2D>("wCheckerHighlight");
            background = Content.Load<Texture2D>("board");
            mainframe = new Rectangle(0, 0, GraphicsDevice.Viewport.Width, GraphicsDevice.Viewport.Height);

            //for (int i = 0; i < 12; i++)
            //    redCheckers[i] = Content.Load<Texture2D>("rChecker");

            // TODO: use this.Content to load your game content here
        }

        /// <summary>
        /// UnloadContent will be called once per game and is the place to unload
        /// all content.
        /// </summary>
        protected override void UnloadContent()
        {
            // TODO: Unload any non ContentManager content here
        }
        /// <summary>
        /// Allows the game to run logic such as updating the world,
        /// checking for collisions, gathering input, and playing audio.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Update(GameTime gameTime)
        {
            // TODO: Add your update logic here

            float elapsed = (float)gameTime.ElapsedGameTime.TotalSeconds;
            game.mouseHandler();
            redCheckAnimated.UpdateFrame(elapsed);
            base.Update(gameTime);
        }

        /// <summary>
        /// This is called when the game should draw itself.
        /// </summary>
        /// <param name="gameTime">Provides a snapshot of timing values.</param>
        protected override void Draw(GameTime gameTime)
        {

            graphics.GraphicsDevice.Clear(Color.CornflowerBlue);

            // Draw the sprite.
            spriteBatch.Begin(SpriteSortMode.Deferred, BlendState.AlphaBlend);
            //spriteBatch1.Begin(SpriteSortMode.BackToFront, BlendState.AlphaBlend);
            spriteBatch.Draw(background, mainframe, Color.White);
            for (int i = 0; i < 32; i++)
            {
                switch (game.squares[i].squareType)
                {
                    case CheckerType.redChecker:
                        if (game.squares[i].highlighted)
                            spriteBatch.Draw(rCheck_H, game.squares[i].location, Color.White);
                        else
                            redCheckAnimated.DrawFrame(spriteBatch, game.squares[i].location);
                            //spriteBatch.Draw(rCheck, game.squares[i].location, Color.White);
                        break;
                    case CheckerType.whiteChecker:
                        if (game.squares[i].highlighted)
                            spriteBatch.Draw(wCheck_H, game.squares[i].location, Color.White);
                        else
                            spriteBatch.Draw(wCheck, game.squares[i].location, Color.White);
                        break;
                    case CheckerType.redKing:
                        if (game.squares[i].highlighted)
                            spriteBatch.Draw(rKing_H, game.squares[i].location, Color.White);
                        else
                            spriteBatch.Draw(rKing, game.squares[i].location, Color.White);
                        break;
                    case CheckerType.whiteKing:
                        if (game.squares[i].highlighted)
                            spriteBatch.Draw(wKing_H, game.squares[i].location, Color.White);
                        else
                            spriteBatch.Draw(wKing, game.squares[i].location, Color.White);
                        break;
                }
            }
            spriteBatch.End();
            //spriteBatch1.End();

            base.Draw(gameTime);
        }
    }
}
