

#include "raylib.h"
#include "stdio.h"
typedef enum GameScreen
{
  LOGO = 0,
  LOGSC,
  TITLE,
  GAMEPLAY,
  ENDING
} GameScreen;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
#define MAX_LASER 10
#define bullets 20
#define rects 5

static void InitGame(void);
bool paused = false;

struct shooy
{

  Rectangle rec[4];
  Vector2 position;
  Vector2 speed;
  bool active;
  Color color;
  // struct laser;
  /* data */
};
struct shooy shoot; // struct shooy shoot;

struct ship
{
  Vector2 speed;
};
struct ship shiip;

struct astro
{
  Vector2 speed;

  // Vector2 asti2;
};
struct astro astro1;

struct screen
{
  Vector2 top;
  Vector2 top1;
  Texture2D space;
  Texture2D space1;
  /* data */
};
struct screen scrn;

struct stars
{
  Rectangle rect[100];
  Vector2 speed;
};
struct stars staar;

static bool gameover = false;
static bool lasercol = false;
static bool active = false; // false
static int eni = 0;
static int score = 0;
static bool gamerun = false;

static int shot[MAX_LASER] = {0};
int main(void)
{
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 750;
  const int screenHeight = 450;
  // InitGame();
  //{
  SetTargetFPS(60);
  int screenUpperLimit = 40;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - space shooter");
  InitAudioDevice();

  GameScreen currentScreen = LOGO;
  int framesCounter = 0;

  Sound lasersound = LoadSound("./source/laser2.mp3");
  Sound collosound = LoadSound("./source/collo.wav");
  Sound gamesound = LoadSound("./source/gamemusic.mp3");

  // vectors//

  int spacey = 0;
  int spacey2 = 0;
  int spacey3 = 0;

  Vector2 shipi = {(float)250, (float)250}; // a vector for the ship object/texture
  // Vector2 spacemov= { (float)screenWidth, (float)screenHeight};// a vector for space

  Vector2 asti = {(float)screenWidth / 4, (float)screenHeight / 4};
  Vector2 asti1 = {(float)screenWidth / 3, (float)screenHeight / 3};
  Vector2 asti2 = {(float)screenWidth / 6, (float)screenHeight / 6};
  Vector2 asti3 = {(float)screenWidth / 6, (float)screenHeight / 6};
  Vector2 bully = {(float)screenWidth / 4, (float)screenHeight / 4};
  Vector2 gully = {(float)screenWidth / 4, (float)screenHeight / 4};
  // Vector2 reco ={ (float)screenWidth/7, (float)screenHeight/7 };
  // Vector2 seco = {(float)screenWidth / 4, (float)screenHeight / 4};

  // Vector2 top={(float)screenWidth/4,(float)screenHeight/4};
  Vector2 top = {(float)800, (float)450};
  Vector2 top1 = {(float)800, (float)450};

  // vectors//

  // textures used in game//
  Texture2D logo = LoadTexture("./source/logo1.png");
  Texture2D button = LoadTexture("./source/play.png");
  Texture2D space = LoadTexture("./source/sp5.png");  // load space image
  Texture2D space1 = LoadTexture("./source/sp4.png"); // spacebg2
  Texture2D ship = LoadTexture("./source/ship.png");  // load ship image
  Texture2D asto = LoadTexture("./source/asta.png");  // load asteroids
  Texture2D asto1 = LoadTexture("./source/asta.png");
  Texture2D asto2 = LoadTexture("./source/newast.png"); // diff asteroid
  Texture2D asto3 = LoadTexture("./source/asta.png");
  Texture2D bullet[10] = {LoadTexture("./source/laser.png"), LoadTexture("./source/laser.png"), LoadTexture("./source/laser.png"), LoadTexture("./source/laser.png"), LoadTexture("./source/laser.png")}; // load bullet png
  Texture2D explosion = LoadTexture("source/explo.png");
  Texture2D over = LoadTexture("source/over.png");
  Texture2D xcr = LoadTexture("./source/scr.png");

  // Texture2D space =LoadTexture("./source/spacebg2.png");//load space image
  // textures//

  Rectangle rect[4]; // rect
  Rectangle srect;
  Rectangle orect;
  Rectangle prect;
  Rectangle qrect;
  Rectangle cute[10];
  Rectangle bull;
  Rectangle btbound;
  Rectangle point;

  Rectangle buttonp;

  float scrolling = 0.0f;
  space.width = -1000; // background space
  space.height = -750;
  space1.width = -1000;
  space1.height = -750;

  bool collision[4] = {false, false, false, false}; // array of collision
  bool collision1 = false;
  bool collision2 = false;
  bool collision3 = false;
  bool collision77 = false;
  bool btact = false; // buttonaction
  Vector2 mousePoint = {0.0f, 0.0f};

  Rectangle boxCollision = {0};
  // Rectangle boxCollision1 = {0};

  // rect.x=shipi.x;
  // rect.y=shipi.y;

  // srect.x=asti.x;
  // srect.y=asti.y;

  // structs

  // for (int k = 0; k <= MAX_LASER; k++)
  //  {
  //  shoot[k].rec[k].x= shipi.x-20;
  // shoot.rec[k].y = shipi.y + 20;
  // shoot[k].rec.width = 10;
  // shoot[k].rec.height = 5;
  // shoot[k].speed.x = 7;
  // shoot[k].speed.y = 0;
  // shoot[k].active = false;
  // shoot[k].color = MAROON;
  // }

  // DrawRectangleRec(cute[o], ORANGE);
  // cute[o].y = shipi.y;
  // bully.x=bully.x;
  bully.x = shipi.x;
  bully.y = shipi.y;
  // bully.y=bully.y-2;  //stopper

  // void InitGame(void)
  // {
  // static laser laser[MAX_LASER] = {0};

  // for (int k = 0; k < MAX_LASER; k++)

  // {
  // laser[k].rec.x = shipi.x;
  // laser[k].rec.y = shipi.y + 20;
  // laser[k].rec.width = 10;
  // laser[k].rec.height = 5;
  // laser[k].speed.x = 7;
  // laser[k].speed.y = 0;
  // laser[k].active = false;
  // laser[k].color = MAROON;
  // }
  //}
  //}
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------
    switch (currentScreen)
    {
    case LOGO:
    {

      framesCounter++; // Count frames

      // Wait for 2 seconds (120 frames) before jumping to TITLE screen
      if (framesCounter > 180)
      {
        currentScreen = TITLE;
      }
    }
    case LOGSC:
    {
      if (IsKeyPressed(KEY_MINUS)) /////|| IsGestureDetected(GESTURE_TAP))
      {
        currentScreen = GAMEPLAY;
      }
    }

    break;
    case TITLE:
    {

      if (IsKeyPressed(KEY_ENTER)) /////|| IsGestureDetected(GESTURE_TAP))
      {

        currentScreen = GAMEPLAY;
        gamerun = true;
        collision[2] = true;
      }
    }
    break;
    case GAMEPLAY:
    {

      if (collision[0])
      {
        currentScreen = ENDING;
      }
    }
    break;
    case ENDING:
    {

      if (IsKeyPressed(KEY_BACKSPACE) || IsGestureDetected(GESTURE_TAP))
      {
        currentScreen = TITLE;
        score = 0;
        // CloseWindow();
        // EndDrawing();
        shipi.y += screenHeight + 500;
      }
    }
    break;
    default:
      break;
    }

    mousePoint = GetMousePosition();
    btact = false;

    // Check button state
    if (CheckCollisionPointRec(mousePoint, btbound))
    {
      if (IsGestureDetected(GESTURE_TAP))
      {

        DrawText("button pressed", 0.0f, 2.0f, 30, RED);
        btact = true;
      }
    }
    if (btact)
    {
      // currentScreen = GAMEPLAY;
    }

    // Drawvoid DrawRectangleRec(Rectangle rec, Color color);
    if ((shipi.x + ship.width) >= GetScreenWidth())
      shipi.x = GetScreenWidth() - ship.width;
    else if (shipi.x <= 0)
      shipi.x = 0;

    if ((shipi.y + ship.height) >= GetScreenHeight())
      shipi.y = GetScreenHeight() - ship.height;
    else if (shipi.y <= screenUpperLimit)
      shipi.y = (float)screenUpperLimit;

    rect[0].height = 30;
    rect[0].width = 30;
    rect[1].height = 30;
    rect[1].width = 30;
    prect.height = 57;
    prect.width = 70; // big asto
    orect.height = 30;
    orect.width = 30;
    srect.height = 80;
    srect.width = 50;
    bull.height = 24;
    bull.width = 13;
    btbound.width = 150;
    btbound.height = 70;

    cute[4].height = 50;
    cute[4].width = 50;

    buttonp.width = 150;
    buttonp.height = 70;
    buttonp.x = screenWidth / 5.0f;
    buttonp.y = screenHeight / 1.7f;
    point.x = mousePoint.x;
    point.y = mousePoint.y + 20;

    //  for (int i = 0; i < MAX_LASER; i++)
    // {
    //    shoot[i].rec.x = player.rec.x;
    //   shoot[i].rec.y = player.rec.y + player.rec.height/4;
    //  shoot[i].rec.width = 10;
    // shoot[i].rec.height = 5;
    //  shoot[i].speed.x = 7;
    // shoot[i].speed.y = 0;
    // shoot[i].active = false;
    //   shoot[i].color = MAROON;
    // }

    // UnloadTexture(space1);
    // UnloadTexture(space);

    // reco.x = shipi.x;
    // reco.y = shipi.y;
    // seco.x = asti.x;
    // seco.y = asti.y;

    // int i = GetRandomValue(1,0);
    eni == rects;
    for (int i = -1; i <= 1; i++)
    {

      collision[1] = CheckCollisionRecs(rect[i], srect); // collsion1
                                                         // collision[1] = CheckCollisionRecs(rect[i], srect);

      // Get collision rectangle (only on collision)
      if (collision[1])
        boxCollision = GetCollisionRec(rect[i], srect); // box collision1
      // boxCollision = GetCollisionRec(rect[i], srect);

      // DrawTexture(over, 800, 450, WHITE);
      gameover = true;
    }
    // break;
    // continue;

    for (int j = -1, y = -1; j <= 0, y <= 1; j++, y++)
    {
      // for(int j=2;j<=1;j--)
      //  {

      collision[0] = CheckCollisionRecs(rect[j], srect) || CheckCollisionRecs(orect, srect) || CheckCollisionRecs(prect, srect) || CheckCollisionRecs(rect[y], srect);

      // collision[2] = CheckCollisionRecs(rect[j], bull);

      // Get collision rectangle (only on collision)
      // if (collision[0])
      // boxCollision = GetCollisionRec(rect[j], srect);
      // boxCollision = GetCollisionRec(rect[j], bull);

      // DrawTexture(over, 800, 450, WHITE); //
      // gameover = true;
      // lasercol=true;             // true

      // break;
      // continue;
    }

    for (int k = -1, l = -1; k <= 1, l <= 0; k++, l++)
    {
      // for(int j=2;j<=1;j--)

      // collision[2] = CheckCollisionRecs(bull, rect[k]);
      collision[2] = CheckCollisionRecs(rect[k], bull) || CheckCollisionRecs(prect, bull) || CheckCollisionRecs(orect, bull) || CheckCollisionRecs(rect[l], bull);
      // Get collision rectangle (only on collision)
    }
    if (collision[2] == true)
    {
      score += 10;
      // boxCollision = GetCollisionRec(bull, rect[k]);
      // boxCollision = GetCollisionRec(rect[k], bull);
      // boxCollision=GetCollisionRec(prect,bull);
      // boxCollision=GetCollisionRec(orect,bull);

      // DrawTexture(over, 800, 450, WHITE); //
      // gameover = true;                    // true
      // lasercol =true;
      // break;
      // continue;
    }
    //}
    if (collision[0])
    {
      // PlaySound(collosound);
    }

    if (paused)
    {
      top.y -= 5;
      top1.y -= 10;
      asti3.y -= 200;
    }
    if (IsKeyDown(KEY_SPACE))
    {
      // DrawRectangle(shipi.x+34,shipi.y+3,10,10,ORANGE);
      // for (int o = 0; o < 10; o++)
      //{
      // DrawRectangleRec(cute[o], ORANGE);
      //  cute[o].y = shipi.y;
      // bully.x=bully.x;
      //}
      // DrawTexture(bullet[10], bully.x, bully.y, ORANGE);
      // DrawTexture(bullet, gully.x, gully.y, ORANGE);
      // bully.y = bully.y -10;
      bully.x = shipi.x + 34;
      PlaySound(lasersound);

      // gully.y = gully.y - 15;
      active = true;
    }
    if (IsKeyDown(KEY_M))
    {
      PlaySound(gamesound);
      // StopMusicStream(gamesound);
    }

    // else
    //{

    // active=false;
    // }
    if (!active)
    {
      if (bully.x < shipi.x)
      {
        bully.x = shipi.x + 34;
      }
      if (bully.x > shipi.x)
      {
        bully.x = shipi.x + 34;
      }
      if (bully.y > shipi.y)
      {
        bully.y = shipi.y + 30;
      }
      if (bully.y < shipi.y)
      {
        bully.y = shipi.y + 30;
      }
    }

    //  if(!btact)
    //   {
    //     top.y -= 1;          // vector of space bg movement
    // asti.y = asti.y - 1; // asteroid movement
    // asti1.y = asti1.y - 2;  //3
    // asti2.y = asti2.y - 3;   //5
    // asti3.y = asti3.y - 2.5;   //2
    // top1.y = top1.y - 1;
    // shipi.y= screenHeight+400;

    //  }
    // else if(btact)
    // {

    //    UnloadTexture(logo);
    //    UnloadTexture(button);
    //    top.y += 1;          // vector of space bg movement
    // asti.y = asti.y +1; // asteroid movement
    // asti1.y = asti1.y + 2;  //3
    // asti2.y = asti2.y + 3;   //5
    // asti3.y = asti3.y + 2.5;   //2
    // top1.y = top1.y + 1;
    // shipi.y= 250;

    //}

    if (top.y >= screenHeight + 300) // shipi.y + 500) // top  //if end of bg > ship pos thn
    {
      // space.height  + top.y;   //*2
      // top.y = -0.0f; // returns to origin //0.0f
      top1.y = top.y + 10 + space.height;
    }
    if (top1.y >= screenHeight + 300) // shipi.y + 500) // top  //if end of bg > ship pos thn
    {
      // space.height  + top.y;   //*2
      // top.y = -0.0f; // returns to origin //0.0f
      top.y = top1.y + 10 + space1.height;
    }

    if (bully.y <= screenUpperLimit - 100)
    {
      bully.y = shipi.y;
      bully.x = shipi.x + 34;
      // UnloadTexture(bullet[MAX_LASER]);
    }

    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch (currentScreen)
    {
    case LOGO:
    {

      DrawRectangle(screenWidth / 2 - 128, screenHeight / 2 - 128, 256, 256, BLACK);
      DrawRectangle(screenWidth / 2 - 112, screenHeight / 2 - 112, 224, 224, RAYWHITE);

      DrawText("raylib", screenWidth / 2 - 44, screenHeight / 2 + 48, 50, BLACK);

      DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
      DrawText("WAIT for 20 SECONDS...", 290, 220, 20, GRAY);
    }
    break;
    case TITLE:
    {

      DrawTexture(logo, 0.0, 2.0, WHITE);
      DrawTexture(button, screenWidth / 5.0f, screenHeight / 1.7f, WHITE);
      DrawRectangleRec(buttonp, BLANK);
      DrawRectangleRec(point, BLUE);
      collision77 = CheckCollisionRecs(point, buttonp);
      if (collision77)
      {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
          DrawText("prssd", 20, 20, 70, MAROON);
          currentScreen = GAMEPLAY;
          gamerun = true;
        }
        // DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
        // DrawTexture(logo,screenWidth,screenHeight,WHITE);
        // DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
        // DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
      }
    }
    break;
    case GAMEPLAY:
    {

      // DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
      // DrawTexture(xcr,800,500,WHITE);
      // DrawTexture(xcr,screenWidth/200,screenHeight/100,WHITE);
      // DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
      // DrawTexture(xcr,800,500,WHITE);
      rect[0].x = asti.x;
      rect[0].y = asti.y;
      rect[1].x = asti3.x;
      rect[1].y = asti3.y;
      cute[4].x = asti3.x;
      cute[4].x = asti3.y;

      srect.x = shipi.x;
      srect.y = shipi.y;

      orect.x = asti1.x;
      orect.y = asti1.y;

      prect.x = asti2.x; // big asteroid
      prect.y = asti2.y;
      btbound.x = screenWidth / 5.0f;
      btbound.y = screenHeight / 1.7f;

      bull.x = bully.x;
      bull.y = bully.y;

      point.x = 10;
      point.y = 10;

      // qrect.x = asti3.x;
      // qrect.y = asti3.y;
      // DrawTexture(logo,screenWidth,screenHeight,WHITE);
      DrawTextureV(space1, top1, WHITE);
      DrawTextureV(space, top, WHITE);
      // DrawTexture(logo,0.0,2.0,WHITE);
      // DrawTexture(button,screenWidth/5.0f,screenHeight/1.7f,WHITE);
      //  DrawRectangleRec(btbound,GREEN);
      // DrawText("", 190, 200, 20, LIGHTGRAY);
      // DrawTexture(xcr,screenWidth/200,screenHeight/100,WHITE);

      // DrawTextureV(space,spacemov,WHITE);
      // DrawTextureV(space,top,WHITE);
      // DrawTextureV(space1, top1, WHITE);  // drawing space    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
      // DrawTextureV(space, top, WHITE);
      // DrawTextureV(space, top1, WHITE); // draw space bg XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
      // DrawTextureEx(space, (Vector2){ 0, spacey2 }, 0.0f, 1.0f, WHITE);
      // DrawTextureEx(space, (Vector2){ 0, spacey2 }, 0.0f, 1.0f, WHITE);
      // DrawTextureEx(space, (Vector2){ 0, spacey3 }, 0.0f, 1.0f, WHITE);DrawTextureV(space1, top1, WHITE);

      // DrawTextureV(space1, top1, WHITE);
      //  DrawTextureV(space, top, WHITE);

      // top.y-=space.height;
      // top.y+=space.height;
      //  top1.y=top1.y+1;

      if (gamerun == true)
      {

        top.y += 1;              // vector of space bg movement
        asti.y = asti.y + 1;     // asteroid movement
        asti1.y = asti1.y + 2;   // 3
        asti2.y = asti2.y + 3;   // 5
        asti3.y = asti3.y + 2.5; // 2
        top1.y = top1.y + 1;     // 1

        // DrawText("checking",0.0f,2.0f,80,BLUE);
        // DrawTextre(over, 800/6, 450/6, WHITE);
      }

      else if (gamerun == false)
      {
        score = 0;
        collision[2] = false;
        // top.y = top.y - 1;   // vector of space bg movement
        // asti.y = asti.y - 1;
        // asti1.y = asti1.y - 2;   // 3
        //  asti2.y = asti2.y - 3;   // 5
        // asti3.y = asti3.y - 2.5; // 2
        //  top1.y = top1.y - 1; // asteroid movement
        //  asti1.y = asti1.y - 3;
        //  asti2.y = asti2.y - 5;
        // asti3.y = asti3.y - 2;
        // top1.y = top1.y - 1;
        // DrawText("rayuga", 0.0f, 2.0f, 80, BLUE);
        // DrawTexture(over, 800/6, 450/6, WHITE);
        //}
      }

      if (active)

      {
        for (int i = 0; i < MAX_LASER; i++)
        {
          DrawTexture(bullet[1], bully.x, bully.y, ORANGE);
          bully.y = bully.y - 2;

          if (bully.y < screenUpperLimit - 100)
          {
            active = false;
          }
          // DrawTexture(bullet[2], bully.x, bully.y+40, ORANGE);
          //  UnloadTexture(bullet[i]);
        }
      }
      if (IsKeyDown(KEY_ENTER))
      {
        // UnloadTexture(logo);
        // UnloadTexture(button);
        // ClearBackground(WHITE);
      }

      // UnloadTexture(bullet[0]);
      // UnloadTexture(bullet[1]);
      // UnloadTexture(bullet[2]);

      // space.width*2+top.y;
      //  DrawTextureEx(space, (Vector2){ scrolling, 20 }, 0.0f, 2.0f, WHITE);
      // DrawTextureEx(space, (Vector2){ space.width*2 + scrolling, 20 }, 0.0f,2.0f, WHITE);   // 0.0f ,0.2f

      DrawTextureV(ship, shipi, WHITE); // draw texture with(texturename,vector2 po if (scrolling <= -space.width*2) scrolling = 0;sition,color)
      // DrawTexture(asto,0.0f,5.0f,WHITE);
      DrawTextureV(asto, asti, WHITE); // draw asteroid asti=vectorname,asto=texture  //not that
      DrawTextureV(asto1, asti1, RED); // yes
      DrawTextureV(asto2, asti2, WHITE);
      DrawTextureEx(asto3, asti3, 0.0F, 0.5, WHITE);
      // DrawRectangle(rect.x,rect.y,80,80,ORANGE);
      // DrawRectangle(asti.x, asti.y, 50, 38, VIOLET);if (collision) boxCollision = GetCollisionRec(rect, srect);
      DrawRectangleRec(srect, BLANK);   // rectangle of ship
      DrawRectangleRec(rect[0], BLANK); // orange
      DrawRectangleRec(rect[1], BLANK); // purple
      DrawRectangleRec(orect, BLANK);
      DrawRectangleRec(prect, BLANK);
      DrawRectangleRec(qrect, BLANK);
      DrawRectangleRec(bull, BLANK);
      DrawText(TextFormat("%04i", score), 25, 25, 45, GRAY);
      // DrawTexture(xcr,screenWidth/200,screenHeight/100,WHITE);

      // DrawRectangle()
      // DrawTextureV(bullet[10],bully,ORANGE);//draw bullet

      // for (int i = 0; i < MAX_LASER; i++)
      //{
      //  DrawTextureV(bullet[i], gully, GREEN);
      //  DrawTextureV(bullet[i], bully, RED);
      //}

      // scrolling--;
      // if (scrolling <= -space.width*2) scrolling = 0;

      // if((rect.x==srect.x)&&(rect.y==srect.y))
      // {
      //     DrawText("gameover",0.0f,2.0f,100,ORANGE);
      //}

      // if (top.y > shipi.y + 100) // top  //if end of bg > ship pos thn
      // {
      // // space.height * 0 + top.y;
      //  top.y = 0.0f; // returns to origin
      // top1.y = top.y+500;  // top.y+
      // space1.width=space.width+space1.height;
      // space.width*2 + top.y;
      // top.y=top1.y-100;
      // top1.y=top1.y+2;

      // space.width*2;
      //  space.height=space.height-100;
      // space.width=space.width-50;
      // }
      if (asti.y > 600) // asteroid pos > ship pos thn
      {
        asti.y = GetRandomValue(0, 0); // generate asteroid at random value
        asti.x = GetRandomValue(0, 1000);
        rect[0].height = GetRandomValue(20, 100);
        rect[0].width = GetRandomValue(10, 80);
      }

      if (asti1.y > 600) // ship.y+100
      {
        asti1.y = GetRandomValue(0, 0); // generate asteroid at random value
        asti1.x = GetRandomValue(0, 1000);
      }

      if (asti2.y > 600)
      {
        asti2.y = GetRandomValue(0, 0); // generate asteroid at random value
        asti2.x = GetRandomValue(0, 1000);
      }

      if (asti3.y > 1000)
      {
        asti3.y = GetRandomValue(0, 0); // generate asteroid at random value
        asti3.x = GetRandomValue(0, 1000);
      }
      for (int n = 0; n <= 1; n++)
      {

        if (collision[n])

        {
          DrawText("Gone ", 0.0f, 2.0f, 50, ORANGE);
          DrawTexture(explosion, shipi.x, shipi.y, WHITE);
        }
      }
      // if (collision1)

      //{
      // DrawText("out!!", 0.0f, 2.0f, 50, ORANGE);
      // DrawTexture(explosion, shipi.x, shipi.y, WHITE);
      //  void CloseWindow(void);
      //}

      if (CheckCollisionRecs(rect[0], bull))

      {
        // UnloadTexture(asto);
        // asto=LoadTexture("./source/explo.png");
        DrawText("lasercol", 0.0f, 2.0f, 50, ORANGE);
        DrawTexture(explosion, bully.x, bully.y, WHITE);
        void CloseWindow(void);
        asti.y = GetRandomValue(1000, 2000);
      }
      else if (CheckCollisionRecs(prect, bull))
      {
        // asti1.y=GetRandomValue(1000,2000);
        // asti.y=GetRandomValue(1000,2000);
        asti2.y = GetRandomValue(1000, 2000);
        DrawTexture(explosion, bully.x, bully.y, WHITE);
        // asti3.y=GetRandomValue(1000,2000);
      }
      else if (CheckCollisionRecs(orect, bull))
      {
        asti1.y = GetRandomValue(1000, 2000);
        DrawTexture(explosion, bully.x, bully.y, WHITE);
      }
      else if ((CheckCollisionRecs(rect[1], bull)))
      {
        asti3.y = GetRandomValue(1000, 2000);
        DrawTexture(explosion, bully.x, bully.y, WHITE);
      }

      if (CheckCollisionRecs(rect[0], srect))

      {
        // UnloadTexture(asto);
        // asto=LoadTexture("./source/explo.png");
        DrawText("lasercol", 0.0f, 2.0f, 50, ORANGE);
        PlaySound(collosound);
        // DrawTexture(explosion, bully.x, bully.y, WHITE);
        void CloseWindow(void);
        asti.y = GetRandomValue(1000, 2000);
      }
      else if (CheckCollisionRecs(prect, srect))
      {
        // asti1.y=GetRandomValue(1000,2000);
        // asti.y=GetRandomValue(1000,2000);
        asti2.y = GetRandomValue(1000, 2000);
        PlaySound(collosound);
        // DrawTexture(explosion, bully.x, bully.y, WHITE);
        // asti3.y=GetRandomValue(1000,2000);
      }
      else if (CheckCollisionRecs(orect, srect))
      {
        asti1.y = GetRandomValue(1000, 2000);
        PlaySound(collosound);
        // DrawTexture(explosion, bully.x, bully.y, WHITE);
      }
      else if ((CheckCollisionRecs(rect[1], srect)))
      {
        asti3.y = GetRandomValue(1000, 2000);
        PlaySound(collosound);
        // DrawTexture(explosion, bully.x, bully.y, WHITE);
      }

      // speed up//
      if (score > 1000)
      {
        top.y += 2;
        top1.y += 2;
        asti1.y += 2;
        asti2.y += 2;
        asti3.y += 2;
        asti.y += 2;
      }
      if (score > 2000)
      {
        top.y += 5;
        top1.y += 5;
        asti1.y += 5;
        asti2.y += 5;
        asti3.y += 5;
        asti.y += 5;
      }

      if ((srect.x == prect.x) && (srect.y == prect.y))
      {
        DrawText("2 gone ", 0.0f, 2.0f, 50, ORANGE);
      }

      if (IsKeyDown(KEY_W))
      {
        shipi.y -= 10;
      }
      if (IsKeyDown(KEY_S))
      {
        shipi.y += 10;
      }

      if (IsKeyDown(KEY_A))
      {
        shipi.x -= 10;
      }
      if (IsKeyDown(KEY_D))
      {
        shipi.x += 10;
      }

      // if (IsKeyDown(KEY_E))
      // {
      // DrawRectangle(shipi.x+34,shipi.y+3,10,10,ORANGE);

      // DrawTexture(bullet,shipi.x+34,shipi.y+1,ORANGE);
      //  bully.y = bully.y - 2;
      //  gully.y = gully.y - 5;
      // }
      if (IsKeyDown(KEY_P))
      {
        paused = !paused;
      }

      if (paused)
      {
        DrawText("paused", 20.0, 20.0, 70, RED);
      }
      // DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
    }
    break;
    case ENDING:
    {
      DrawTexture(over, 0.0f, 2.0f, WHITE);
      DrawText(TextFormat("%04i", score), 475, 250, 55, BLUE);
      DrawText("Score", 245, 250, 55, BLUE);
      // scanf("\n enter your name");
      DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
      // DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
    }
    break;
    default:
      break;
    }
    // }
    EndDrawing();
    //-------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  UnloadSound(lasersound);
  UnloadSound(collosound); // Unload sound

  CloseAudioDevice();
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}