#include <stdio.h>
#include "raylib.h"

void draw_background();

typedef struct ball
{
  float x;
  float y;
  float r;
  Color color;
  Vector2 speed;
  float gravity;
} Ball;
void update_ball(Ball *ball);
void create_balls(Ball balls[], int size);
int main()
{
  int factor = 80;
  int width = factor * 10;
  int height = factor * 10;
  SetTargetFPS(60);
  InitWindow(width, height, "Ball");

  Color background_color = {0x14, 0x14, 0x14, 0xFF};
  // Ball ball;
  // ball.x = width / 2;
  // ball.y = height / 2;
  // ball.r = 60.0f;
  // ball.color = RED;
  // ball.speed = (Vector2){400.0f, 600.0f};
  // ball.gravity = 1000;
  const int size = 20;
  Ball balls[size];
  create_balls(balls, size);
  while (!WindowShouldClose())
  {
    for (int i = 0; i <= size; i++)
    {
      update_ball(&balls[i]);
    }
    BeginDrawing();
    ClearBackground(background_color);
    draw_background();

    for (int i = 0; i <= size; i++)
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
  char scoreText[] = "100";
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
  ball->x += ball->speed.x * dt;
  ball->y += ball->speed.y * dt;
  if (ball->x >= width - ball->r || ball->x <= ball->r)
  {
    ball->speed.x *= -1.0f;
  }

  if (ball->y >= height - ball->r || ball->y <= ball->r)
  {
    ball->speed.y *= -0.9f;
    ball->y = height - ball->r;
  }
}

void create_balls(Ball balls[], int size)
{
  for (int i = 0; i <= size; i++)
  {
    float r = (float)GetRandomValue(5, 15);
    Ball ball = {
        .x = GetRandomValue(r, GetScreenWidth() - r),
        .y = GetRandomValue(r, GetScreenHeight() - r),
        .color = YELLOW,
        .gravity = 1000,
        .r = r,
        .speed = (Vector2){400, 600}};
    balls[i] = ball;
  }
}