#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

void draw_grid(int rows, int cols, int grid[][rows], int w, Color colors);
void mouse_input(int rows, int cols, int grid[][rows], int w, Vector2 mouse_pos);
void grid_update(int rows, int cols, int grid[][rows]);
void grid_side_update(int rows, int cols, int grid[][rows]);


int brush_size = 5;

int main(void)
{
    const int screenWidth = 1080;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Game");

    int w = 5;
    int rows, cols;

    Color colors = {205, 170, 109, 255};

    rows = screenHeight / w;
    cols = screenWidth / w;

    int grid[rows][cols];

    for(int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                grid[i][j] = 0;
            }
        }

Vector2 mouse_pos;

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        grid_update(rows, cols, grid);
        mouse_input(rows, cols, grid, w, mouse_pos);
        if(IsKeyPressed(KEY_R))
        {
            for(int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    grid[i][j] = 0;
                }
            }
        }
        BeginDrawing();
        ClearBackground((Color){colors.r + 50, colors.g + 50, colors.b + 50, 255});

        draw_grid(rows, cols, grid, w, colors);
        DrawText("PRESS R TO RESET", 20, 20, 20, (Color){colors.r - 50, colors.g - 50, colors.b - 50, 255});
        DrawText(TextFormat("BRUSH SIZE: %d", brush_size), 40, 40, 20, (Color){colors.r - 50, colors.g - 50, colors.b - 50, 255});
        EndDrawing();
        grid_side_update(rows, cols, grid);

    }

    CloseWindow();

    return 0;
}

void draw_grid(int rows, int cols, int grid[][rows], int w, Color colors)
{
    for(int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if(grid[i][j] == 1)
            {
                DrawRectangle(j * w, i * w, w, w, colors);
            }
        }
    }
}

void grid_update(int rows, int cols, int grid[][rows])
{
    for (int i = rows; 0 < i; i--)
    {
        for (int j = cols; 0 < j; j--)
        {
            if(grid[i][j] == 0 && grid[i - 1][j] == 1)
            {
                grid[i][j] = 1;
                grid[i - 1][j] = 0;
            }
        }
    }
}

void grid_side_update(int rows, int cols, int grid[][rows])
{
    for (int i = rows; 0 < i; i--)
    {
        for (int j = cols; 0 < j; j--)
        {
            if(j > 0 && i < rows -2 && i > 1 && grid[i][j] == 1 && grid[i+1][j] == 1 && grid[i+2][j] == 1)
            {
                if (grid[i+1][j + 1]  == 0 && grid[i+1][j - 1]  == 0)
                {
                    if(rand() % 2)
                    {
                        grid[i+2][j] = 0;
                        grid[i+1][j + 1] = 1;
                    }
                    else
                    {
                        grid[i+2][j] = 0;
                        grid[i+1][j -1] = 1;
                    }
                }

                if(grid[i+1][j + 1]  == 0 && grid[i+1][j - 1]  == 1)
                {
                    grid[i+2][j] = 0;
                    grid[i+1][j + 1] = 1; 
                }
                if(grid[i+1][j - 1]  == 0 && grid[i+1][j + 1]  == 1)
                {
                    grid[i+2][j] = 0;
                    grid[i+1][j - 1] = 1;
                }
            }
        }
    }
}

void mouse_input(int rows, int cols, int grid[][rows], int w, Vector2 mouse_pos)
{
    mouse_pos = GetMousePosition();

    if(IsKeyPressed(KEY_UP))
    {
        brush_size += 5;
    }
    if(IsKeyPressed(KEY_DOWN) && brush_size > 0)
    {
        brush_size -= 5;
    }
    printf("x:%f y:%f\n", mouse_pos.x, mouse_pos.y);
    if(IsMouseButtonDown(0))
    {
        for (int i = 0; i < brush_size; i++)
        {
            for (int j = 0; j < brush_size && mouse_pos.y > 0; j++)
            {
                grid[(int){(mouse_pos.y / w) + i}][(int){(mouse_pos.x / w) + j}] = 1;
            }
        }
    }
}