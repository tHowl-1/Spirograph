#include <cmath>
#include <raylib.h>
#include <iostream>
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main()
{
    // TODO : Automatic resolution detection
    const int screenWidth = 1600;
    const int screenHeight = 900;

    Image icon = LoadImage("resources/spirograph.png");

    InitWindow(screenWidth, screenHeight, "Spirograph");
    SetWindowIcon(icon);

    enum GameState
    {
        DRAW,
        SET,
        PLANET
    };

    GameState state = DRAW;

    SetTargetFPS(60);

    //Variables
    float R = 200;
    float r = 55;
    float p = 55;
    float thickness = 3;
    float speed = 0.0167;
    bool firstDraw = true;
    bool playPause = false;
    bool rainbowColor = true;
    float colorValue = 1;

    Vector2 center = {screenWidth / 2, screenHeight / 2};

    //Spacetime
    float t  = 0;
    Vector2 position = center;
    Vector2 previous = position;

    //Constants
    float l = p / r;
    float k = r / R;



    //Drawing
    Color clearColor = RAYWHITE;
    RenderTexture2D renderingTexture = LoadRenderTexture(screenWidth, screenHeight);
    
    while(!WindowShouldClose())
    {
        //-------------------------
        //         UPDATE
        //-------------------------

        //  Input Update
        // TODO : Keys into buttons
        if (IsKeyPressed('1'))
        {
            state = DRAW;
            clearColor = RAYWHITE;

            BeginTextureMode(renderingTexture);
            ClearBackground(RAYWHITE);
            EndTextureMode();

            t = 0;
            firstDraw = true;
        }
        else if (IsKeyPressed('2'))
        {
            state = SET;
            clearColor = RAYWHITE;
        }
        else if (IsKeyPressed('3'))
        {   
            state = PLANET;
            clearColor = BLACK;
        }

        //  State Update
        // TODO : Add LOGO Screen
        switch (state)
        {
            case DRAW:
            {
                l = p / r;
                k = r / R;

                position.x = center.x + (R * (((1 - k) * cos(t)) + (l * k * cos((1 - k) / k * t))));
                position.y = center.y + (R * (((1 - k) * sin(t)) - (l * k * sin((1 - k) / k * t))));
                t += speed;

                if (firstDraw)
                {
                    previous = position;
                    firstDraw = false;
                }
                
                
                break;
            };
            case SET:
            {
                
                break;
            }
            case PLANET:
            {
                // TODO : PLANET Mode
                break;
            }
            default:
                break;
        }

        //-------------------------
        //          DRAW
        //-------------------------

        BeginDrawing();
    
        ClearBackground(clearColor);
        

        switch(state)
        {
            case DRAW:
            {
                BeginTextureMode(renderingTexture);
                if (rainbowColor)
                {
                    DrawLineEx(previous, position, thickness, ColorFromHSV(t * 2, 1.0f, 1.0f));
                    DrawCircle(position.x, position.y, thickness / 2, ColorFromHSV(t * 2, 1.0f, 1.0f));
                } else
                {
                    DrawLineEx(previous, position, thickness, ColorFromHSV(colorValue * 2, 1.0f, 1.0f));
                    DrawCircle(position.x, position.y, thickness / 2, ColorFromHSV(colorValue * 2, 1.0f, 1.0f));
                }
                EndTextureMode();

                previous = position;

                DrawTexture(renderingTexture.texture, 0, 0, WHITE);
                //TODO : Add set circle drawing
                
                DrawText("DRAW MODE", 60, 40, 40, GRAY);
                break;
            }
            case SET:
            {
                DrawCircleLines(center.x + R - r, center.y, r, BLUE);
                DrawCircle(center.x + R - r + p, center.y, thickness / 2, BLUE);
                DrawLineEx((Vector2){center.x + R - r, center.y}, (Vector2){center.x + R - r + p, center.y}, 2, BLUE);
                DrawCircleLines(center.x, center.y, R, BLUE);
                DrawText("SET MODE", 60, 40, 40, GRAY);
                break;
            }
            case PLANET:
            {
                DrawText("PLANET MODE", 60, 40, 40, GRAY);
                break;
            }
            default:
                break;
        }

        // TODO : Add gui for color changing
        R = GuiSlider((Rectangle){60, 80, 450, 30}, "R", TextFormat("%1.0f", (float)R), R, -150, 300);
        r = GuiSlider((Rectangle){60, 120, 400, 30}, "r", TextFormat("%0.2f", (float)r), r, -200, 200);
        p = GuiSlider((Rectangle){60, 160, 200, 30}, "p", TextFormat("%0.2f", (float)p), p, -100, 100);
        thickness = GuiSlider((Rectangle){60, 200, 160, 25}, "thickness", TextFormat("%0.2f", (float)thickness), thickness, 0, 10);
        speed = GuiSlider((Rectangle){60, 240, 160, 25}, "speed", TextFormat("%0.4f", (float)speed), speed, 0, 1);
        rainbowColor = GuiCheckBox((Rectangle){ 60, 280, 35, 35 }, "Enable Rainbow", rainbowColor);
        playPause = GuiCheckBox((Rectangle){100, 280, 35, 35}, "Play/Pause", playPause);
        colorValue = GuiSlider((Rectangle){60, 320, 300, 40}, "Color", TextFormat("%1.0f", (float)colorValue), colorValue, 0, 300);

        EndDrawing();
    }

    CloseWindow();

    //Deinitialization
    UnloadRenderTexture(renderingTexture);
    UnloadImage(icon);

    return 0;
}