#include <stdio.h>
#include "raylib.h"

void draw_background();

typedef struct ball
{
  float x;
  float y;
  float r;
  Color color;
} Ball;

int main()
{
  int factor = 80;
  int width = factor * 10;
  int height = factor * 10;
  SetTargetFPS(60);
  InitWindow(width, height, "Ball");

  Color background_color = {0x14, 0x14, 0x14, 0xFF};
  Ball ball = {
      width / 2,
      height / 2,
      60.0f,
      RED};
  float gravity = 1000;

  Vector2 speed = {400.0f, 600.0f};
  while (!WindowShouldClose())
  {
    float dt = GetFrameTime();
    speed.y += gravity * dt;
    ball.x += speed.x * dt;
    ball.y += speed.y * dt;

    if (ball.x >= width - ball.r || ball.x <= ball.r)
    {
      speed.x *= -1.0f;
    }

    if (ball.y >= height - ball.r || ball.y <= ball.r)
    {
      speed.y *= -0.9f;
      ball.y = height - ball.r;
    }
    BeginDrawing();
    ClearBackground(background_color);
    draw_background();
    DrawCircle(ball.x, ball.y, ball.r, ball.color);
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