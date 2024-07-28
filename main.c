#include <stdio.h>
#include <math.h>
#include "raylib.h"

void draw_background();

#define NUMBER_OF_BALLS 1

typedef struct ball
{
  float x;
  float y;
  float r;
  Color color;
  Vector2 speed;
  Vector2 init_speed;
  float gravity;
} Ball;
void update_ball(Ball *ball);
void create_balls(Ball balls[], int size);
int main()
{
  int factor = 80;
  int width = factor * 16;
  int height = factor * 9;
  SetTargetFPS(60);
  InitWindow(width, height, "Ball");

  Color background_color = {0x14, 0x14, 0x14, 0xFF};
  Ball balls[NUMBER_OF_BALLS];
  create_balls(balls, NUMBER_OF_BALLS);
  while (!WindowShouldClose())
  {
    if (IsKeyPressed(KEY_SPACE))
    {
      for (int i = 0; i < NUMBER_OF_BALLS; i++)
      {
        balls[i].speed.x = (balls[i].speed.x / fabsf(balls[i].speed.x)) * balls[i].init_speed.x * 2;
        balls[i].speed.y = (balls[i].speed.y / fabsf(balls[i].speed.y)) * balls[i].init_speed.y * 2;
      }
    }
    for (int i = 0; i < NUMBER_OF_BALLS; i++)
    {
      update_ball(&balls[i]);
    }
    BeginDrawing();
    ClearBackground(background_color);
    draw_background();

    for (int i = 0; i < NUMBER_OF_BALLS; i++)
    {
      DrawCircle(balls[i].x, balls[i].y, balls[i].r, balls[i].color);
    }
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

void draw_background()
{
  int score_size = 300;
  char scoreText[10] = "";
  sprintf(scoreText, "%d", NUMBER_OF_BALLS);
  Color score_color = {0x63, 0x63, 0x63, 0x55};
  int font_width = MeasureText(scoreText, score_size);
  DrawText(scoreText, GetScreenWidth() / 2 - font_width / 2, GetScreenHeight() / 2 - score_size / 2, score_size, score_color);
}

void update_ball(Ball *ball)
{
  int height = GetScreenHeight();
  int width = GetScreenWidth();
  float dt = GetFrameTime();
  ball->speed.y += ball->gravity * dt;
  float nx = ball->x + ball->speed.x * dt;
  float ny = ball->y + ball->speed.y * dt;
  float rg = 2;
  if (nx >= width - ball->r || nx <= ball->r)
  {
    ball->speed.x *= -0.7f;

    // ball->r += rg;
    // ball->x += nx <= ball->r ? rg : -rg;
  }
  else
  {
    ball->x = nx;
  }
  if (ny >= height - ball->r || ny <= ball->r)
  {
    ball->speed.y *= -0.9f;
    // ball->r += rg;
    // ball->y += ny <= ball->r ? rg : -rg;
  }
  else
  {
    ball->y = ny;
  }
}

void create_balls(Ball balls[], int size)
{
  Color colors[] = {
      RED,
      YELLOW,
      GREEN,
      BLUE,
      PURPLE,
      GOLD,
      ORANGE,
      PINK};

  for (int i = 0; i < size; i++)
  {
    float r = (float)GetRandomValue(60, 70);
    Vector2 speed = {GetRandomValue(500, 1000), GetRandomValue(500, 1000)};
    Ball ball = {
        .x = GetRandomValue(r, GetScreenWidth() - r),
        .y = GetRandomValue(r, GetScreenHeight() - r),
        .color = colors[GetRandomValue(0, (sizeof colors / sizeof colors[0]) - 1)],
        .gravity = 1000,
        .r = r,
        .speed = speed,
        .init_speed = speed,
    };
    balls[i] = ball;
  }
}