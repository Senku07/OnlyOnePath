#include <stdio.h>
#include <iostream>
#include "include/glad/glad.h"
#include "glad.c"
#include "GLFW/glfw3.h"
#include "glm/common.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.eg"
#include "camera.h"
#include "LevelOne.h"
#include "BoxMove.h"
#include "offScreenShader.h"
#include "DrawBox.h"

enum GameState
{
    HomeScreen,
    LevelChooseScreen,
    PlayScreen,
    LevelOneScreen,
    ReplayAndNextScreen

};

typedef unsigned int UI;
UI Pgm;
UI ScreenPgm;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWmonitor *PrimaryScreen = glfwGetPrimaryMonitor();
    const GLFWvidmode *WindowRatio = glfwGetVideoMode(PrimaryScreen);

    // printf("%d,%d", WindowRatio->width, WindowRatio->height);

    GLFWwindow *window = glfwCreateWindow(WindowRatio->width, WindowRatio->height, "OnlyOnePath:OOP", 0, 0);
    glfwMakeContextCurrent(window);

    gladLoadGL();

    UI vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, 0);
    glCompileShader(vs);

    char info[1000];
    glGetShaderInfoLog(vs, 1000, 0, info);
    printf("%s", info);

    UI fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderSource, 0);
    glCompileShader(fs);
    glGetShaderInfoLog(fs, 1000, 0, info);
    printf("%s", info);

    Pgm = glCreateProgram();
    glAttachShader(Pgm, vs);
    glAttachShader(Pgm, fs);
    glLinkProgram(Pgm);
    glGetProgramInfoLog(Pgm, 1000, 0, info);
    printf("%s", info);

    UI VSscreen = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VSscreen, 1, &vertexScreenShaderSource, 0);
    glCompileShader(VSscreen);

    char ScreenInfo[1000];
    glGetShaderInfoLog(VSscreen, 1000, 0, ScreenInfo);
    printf("%s", ScreenInfo);

    UI FSscreen = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FSscreen, 1, &fragmentScreenShaderSource, 0);
    glCompileShader(FSscreen);
    glGetShaderInfoLog(FSscreen, 1000, 0, ScreenInfo);
    printf("%s", ScreenInfo);

    ScreenPgm = glCreateProgram();
    glAttachShader(ScreenPgm, VSscreen);
    glAttachShader(ScreenPgm, FSscreen);
    glLinkProgram(ScreenPgm);
    glGetProgramInfoLog(ScreenPgm, 1000, 0, ScreenInfo);
    printf("%s", ScreenInfo);

    BoxPos move;
    move.X = 49;
    move.Y = 2;
    move.Z = 49;

    double mouseX = 0;
    double mouseY = 0;

    glViewport(0, 0, WindowRatio->width, WindowRatio->height);

    // TODO time variable
    DWORD systemStarting;
    DWORD systemEndingTime;
    bool LevelOneTime = false;
    DWORD DIFFtime = 0;

    //* player movement
    bool MoveTheBox = true;
    // TODO SWap Interval
    glfwSwapInterval(1);

    //* DAta of Boxes and Texture
    Data a = BoxData();
    Data string = DataString("../Img/fontSprite.png");
    Data BackGround = ImgData("../Img/back.png");
    Data ButtonBG = ImgData("../Img/border.png");
    Data LevelOneImg = ImgData("../Img/LevelOne.png");
    Data Border = ImgData("../Img/border.png");
    Data Exit = ImgData("../Img/exit.png");
    Data BackButton = ImgData("../Img/backButton.png");
    // TODO enum assign here
    enum GameState currentState = HomeScreen;

    // TODO FPS logic
    LARGE_INTEGER FPSstart, FPSend, frequency;
    LARGE_INTEGER FPScount, FPS;

    QueryPerformanceCounter(&FPSstart);

    HWND fullWindow = GetForegroundWindow();
    ShowWindow(fullWindow, SW_MAXIMIZE);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.2, 1);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // TODO onLine game
        glfwGetCursorPos(window, &mouseX, &mouseY);

        //? game Screen Renderingi

        if (currentState == LevelOneScreen)
        {
            glfwSwapInterval(1);
            glUseProgram(Pgm);
            glm::mat4 Proj(1.0f);
            Proj = glm::perspective(glm::radians(45.0f), (float)WindowRatio->width / (float)WindowRatio->height, 0.1f, 10.0f);
            glUniformMatrix4fv(glGetUniformLocation(Pgm, "Proj"), 1, 0, glm::value_ptr(Proj));

            Camera(Pgm, window);

            for (int y = 0; y < 50; y++)
            {
                float colorX = 1;
                float colorY = 1;
                float colorZ = 1;
                for (int x = 0; x < 50; ++x)
                {
                    if (LevelOne[y * 50 + x] == true)
                    {

                        DrawBox(a, Pgm, x, 0, y, colorX / 52.0f, colorY / 59.0f, colorZ / 90.0f);
                        DrawBox(a, Pgm, x, 1, y, colorX / 52.0f, colorY / 59.0f, colorZ / 90.0f);

                        colorX++;
                        colorY++;
                        colorZ++;
                    }
                    DrawBox(a, Pgm, x, -1, y, 0.234, 0.234, 0.234);
                    DrawBox(a, Pgm, 25, 1, 25, 0.4, 0, 0.4);
                }
            }

            //* player bx
            DrawBox(a, Pgm, (move.X), move.Y, move.Z, 0.9, 0.9, 0.9);

            ModelViewX = move.X;
            // ModelViewY = move.Y;
            ModelViewZ = move.Z;
            CameraPosZ = move.Z + 1;
            CameraPosX = move.X;
            CameraPosY = 10;
            ModelViewY = -85;
            glUniform3f(glGetUniformLocation(Pgm, "CameraPos"), move.X, move.Y, move.Z);
            move = MovePlayer(move, window, MoveTheBox);
        }

        // TODO off Screen Rendering
        glDisable(GL_DEPTH_TEST);
        glUseProgram(ScreenPgm);

        glm::mat4 ScreenProj = glm::ortho(0.0f, (float)WindowRatio->width, (float)WindowRatio->height, 0.0f);
        glUniformMatrix4fv(glGetUniformLocation(ScreenPgm, "Proj"), 1, GL_FALSE, glm::value_ptr(ScreenProj));

        //? string rendering

        if (currentState == LevelOneScreen)
        {
            // TODO time

            if (LevelOneTime == true)
            {
                DWORD SystemcurrentTime = GetTickCount();

                DIFFtime = SystemcurrentTime - systemStarting;
                DIFFtime = 60 - (DIFFtime / 1000);
                Sleep(1);
                char CountingBuffer[60];
                snprintf(CountingBuffer, sizeof(CountingBuffer), "%lu", DIFFtime);

                if (DIFFtime > 1)
                {
                    DrawChar(CountingBuffer, string, ScreenPgm, WindowRatio->width - 300, WindowRatio->height / 2 - 300, 50, 50, 1, 1, 1, 30);
                }
                else
                {
                    LevelOneTime = false;
                }
            }

            if (DIFFtime < 2 && (move.X != 25 || move.Z != 25))
            {
                DrawChar("!FAIL!", string, ScreenPgm, WindowRatio->width / 2 - 100, WindowRatio->height / 2 - 50, 50, 50, 1, 1, 1, 30);
                DrawChar("!Time Up!", string, ScreenPgm, WindowRatio->width - 600, WindowRatio->height / 2 - 300, 50, 50, 1, 1, 1, 30);
                MoveTheBox = false;
            }

            // TODO cong
            if (move.X == 25 && move.Z == 25)
            {
                DrawChar("!Level Compeleted!", string, ScreenPgm, WindowRatio->width / 2 - 400, WindowRatio->height / 2 - 200, 50, 50, 1, 1, 1, 50);
                MoveTheBox = false;
            };
        }

        if (currentState == HomeScreen)
        {
            DrawImgRec(BackGround, ScreenPgm, 0, 0, WindowRatio->width, WindowRatio->height, 1, 1, 1);
            DrawImgRec(ButtonBG, ScreenPgm, WindowRatio->width / 2 - 150, WindowRatio->height / 2 - 70, 300, 100, 1, 1, 1);
            DrawChar("Play", string, ScreenPgm, WindowRatio->width / 2 - 100, WindowRatio->height / 2 - 50, 50, 50, 1, 1, 1, 50);

            if (mouseX > (WindowRatio->width / 2 - 150) && (mouseX < (WindowRatio->width / 2 + 150)))
            {
                if (mouseY > (WindowRatio->height / 2 - 90) && mouseY < (WindowRatio->height / 2 + 10))
                {
                    DrawImgRec(Border, ScreenPgm, WindowRatio->width / 2 - 155, WindowRatio->height / 2 - 75, 310, 110, 1, 1, 1);

                    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
                    {
                        currentState = LevelChooseScreen;
                    }
                }
            };
        }

        if (currentState == LevelChooseScreen)
        {
            DrawImgRec(BackGround, ScreenPgm, 0, 0, WindowRatio->width, WindowRatio->height, 1, 1, 1);
            DrawImgRec(LevelOneImg, ScreenPgm, 50, 100, 100, 100, 1, 1, 1);
            if (mouseX >= 50 && (mouseX <= 150))
            {
                if (mouseY > 100 && mouseY < 200)
                {
                    DrawImgRec(Border, ScreenPgm, 45, 100, 110, 100, 1, 1, 1);

                    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
                    {
                        currentState = LevelOneScreen;
                        LevelOneTime = true;
                        systemStarting = GetTickCount();
                    }
                }
            };
        };

        // TODO back button
        if (currentState != HomeScreen)
        {

            if (mouseX > WindowRatio->width - 150 && mouseX < WindowRatio->width - 50)
            {
                if (mouseY > WindowRatio->height / 17 && mouseY < (WindowRatio->height) / 8)
                {
                    DrawImgRec(Border, ScreenPgm, WindowRatio->width - 150, WindowRatio->height / 17, 100, 100, 1, 1, 1);

                    if(currentState == LevelChooseScreen && (glfwGetKey(window,GLFW_KEY_ENTER) == GLFW_PRESS || glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS))
                    {
                        currentState = HomeScreen;
                    }
                }
            }
            DrawImgRec(BackButton, ScreenPgm, WindowRatio->width - 150, WindowRatio->height / 17, 100, 100, 1, 1, 1);
        }
        QueryPerformanceCounter(&FPSend);
        FPScount.QuadPart = FPSend.QuadPart - FPSstart.QuadPart;
        FPSstart = FPSend;

        QueryPerformanceFrequency(&frequency);
        FPS.QuadPart = frequency.QuadPart / FPScount.QuadPart;
        char FPSbuffer[100];
        snprintf(FPSbuffer, sizeof(FPSbuffer), "%lld", FPS);
        DrawChar(FPSbuffer, string, ScreenPgm, 100, 100, 50, 50, 1, 1, 1, 50);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 07;
}