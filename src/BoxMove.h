#pragma once
#include "GLFW/glfw3.h"
#include "LevelOne.h"
#include "Windows.h"

struct BoxPos
{
    float X;
    float Y;
    float Z;
};

BoxPos MovePlayer(BoxPos a, GLFWwindow *window, bool timeUp)
{
    if (timeUp == true)
    {
        if (a.Z >= 1)
        {
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && LevelOne[(int)(a.Z - 1) * 50 + (int)(a.X)] == true)
            {
                a.Z -= 1;
            }
        }

        if (a.Z <= 48)
        {
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && LevelOne[(int)(a.Z + 1) * 50 + (int)(a.X)] == true)
            {
                a.Z += 1;
            }
        }

        if (a.X >= 1)
        {
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && LevelOne[(int)a.Z * 50 + (int)(a.X - 1)] == true)
            {
                a.X -= 1;
            }
        }

        if (a.X <= 48)
        {
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && LevelOne[(int)a.Z * 50 + (int)(a.X + 1)] == true)
            {
                a.X += 1;
            }
        }
    }
    return a;
}
