#pragma once

#include <stdio.h>
#include "iostream"
#include "include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/common.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "Image.h"

typedef unsigned int UI;

struct Data
{
    UI VAO;
    UI VBO;
    UI Texture;
};

Data BoxData()
{
    Data a = {};

    float Rec[] =
        {
            -0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,

            -0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,

            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,

            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,

            -0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            0.5f,
            -0.5f,
            -0.5f,
            -0.5f,

            -0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            0.5f,
            -0.5f,
            0.5f,
            -0.5f,
        };
    glGenVertexArrays(1, &a.VAO);
    glBindVertexArray(a.VAO);
    glGenBuffers(1, &a.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, a.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Rec), Rec, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, 0);

    return a;
};

void DrawBox(Data a, UI Program, float transX, float transY, float transZ, float colorX, float colorY, float colorZ)
{
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(transX, transY, transZ));

    glUniformMatrix4fv(glGetUniformLocation(Program, "Model"), 1, GL_FALSE, glm::value_ptr(model));

    glUniform3f(glGetUniformLocation(Program, "ObjColor"), colorX, colorY, colorZ);
    glBindVertexArray(a.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, a.VBO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
};

Data DataString(const char *filePath)
{
    Data a = {};

    glGenVertexArrays(1, &a.VAO);
    glBindVertexArray(a.VAO);

    glGenBuffers(1, &a.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, a.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, 0, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 16, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 16, (void *)8);

    glGenTextures(1, &a.Texture);
    glBindTexture(GL_TEXTURE_2D, a.Texture);

    int ImgWidth, ImgHeight, ImgChannel;

    // stbi_set_flip_vertically_on_load(false);

    unsigned char *ImgData = stbi_load(filePath, &ImgWidth, &ImgHeight, &ImgChannel, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ImgWidth, ImgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImgData);

    if (ImgData)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to Load Img On Rec");
    };

    stbi_image_free(ImgData);

    return a;
};

void DataChar(Data a, UI Program, int transX, int transY, int scaleX, int scaleY, float colorX, float colorY, float colorZ, int y, int x)
{
    float minX = (x * 240.0f) / 1920.0f;
    float minY = (y * 240.0f) / 1200.0f;
    float maxX = 240.0f / 1920.0f;
    float maxY = 240.0f / 1200.0f;

    float CharRec[] =

        {
            0, 0, minX, minY,
            0, 1, minX, minY + maxY,
            1, 1, minX + maxX, minY + maxY,
            1, 1, minX + maxX, minY + maxY,
            1, 0, minX + maxX, minY,
            0, 0, minX, minY};
    glBindBuffer(GL_ARRAY_BUFFER, a.VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(CharRec), CharRec);
    glBindVertexArray(a.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, a.VBO);
    glBindTexture(GL_TEXTURE_2D, a.Texture);

    glm::mat4 CharModel(1.0f);
    CharModel = glm::translate(CharModel, glm::vec3(transX, transY, 0));
    CharModel = glm::scale(CharModel, glm::vec3(scaleX, scaleY, 0));
    glUniformMatrix4fv(glGetUniformLocation(Program, "model"), 1, GL_FALSE, glm::value_ptr(CharModel));
    glUniform3f(glGetUniformLocation(Program, "ObjColor"), colorX, colorY, colorZ);

    glDrawArrays(GL_TRIANGLES, 0, 6);
};

void DrawChar(const char *text, Data a, UI Program, int transX, int transY, int scaleX, int scaleY, float colorX, float colorY, float colorZ, int fontSize)
{
    int i = 0;
    for (int k = 0; k < strlen(text); ++k)
    {
        if (text[k] == 'A' || text[k] == 'a')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 0, 0);
        }
        else if (text[k] == 'B' || text[k] == 'b')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 0, 1);
        }
        else if (text[k] == 'C' || text[k] == 'c')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 0, 2);
        }
        else if (text[k] == 'D' || text[k] == 'd')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 0, 3);
        }
        else if (text[k] == 'E' || text[k] == 'e')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 0, 4);
        }
        else if (text[k] == 'F' || text[k] == 'f')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 0, 5);
        }
        else if (text[k] == 'G' || text[k] == 'g')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 0, 6);
        }
        else if (text[k] == 'H' || text[k] == 'h')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 0, 7);
        }
        else if (text[k] == 'I' || text[k] == 'i')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 1, 0);
        }
        else if (text[k] == 'J' || text[k] == 'j')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 1, 1);
        }
        else if (text[k] == 'K' || text[k] == 'k')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 1, 2);
        }
        else if (text[k] == 'L' || text[k] == 'l')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 1, 3);
        }
        else if (text[k] == 'M' || text[k] == 'm')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 1, 4);
        }
        else if (text[k] == 'N' || text[k] == 'n')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 1, 5);
        }
        else if (text[k] == 'O' || text[k] == 'o')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 1, 6);
        }
        else if (text[k] == 'P' || text[k] == 'p')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 1, 7);
        }
        else if (text[k] == 'Q' || text[k] == 'q')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 2, 0);
        }
        else if (text[k] == 'R' || text[k] == 'r')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 2, 1);
        }
        else if (text[k] == 'S' || text[k] == 's')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 2, 2);
        }
        else if (text[k] == 'T' || text[k] == 't')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 2, 3);
        }
        else if (text[k] == 'U' || text[k] == 'u')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 2, 4);
        }
        else if (text[k] == 'V' || text[k] == 'v')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 2, 5);
        }
        else if (text[k] == 'W' || text[k] == 'w')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 2, 6);
        }
        else if (text[k] == 'X' || text[k] == 'x')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 2, 7);
        }
        else if (text[k] == 'Y' || text[k] == 'y')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 3, 0);
        }
        else if (text[k] == 'Z' || text[k] == 'z')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 3, 1);
        }
        else if (text[k] == '0')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 3, 2);
        }
        else if (text[k] == '1')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 3, 3);
        }
        else if (text[k] == '2')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 3, 4);
        }
        else if (text[k] == '3')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 3, 5);
        }
        else if (text[k] == '4')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 3, 6);
        }
        else if (text[k] == '5')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 3, 7);
        }
        else if (text[k] == '6')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 4, 0);
        }
        else if (text[k] == '7')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 4, 1);
        }
        else if (text[k] == '8')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 4, 2);
        }
        else if (text[k] == '9')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 4, 3);
        }
        else if (text[k] == '$')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 4, 4);
        }
        else if (text[k] == ':')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 4, 5);
        }
        else if (text[k] == '?')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 4, 6);
        }
        else if (text[k] == '!')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 4, 7);
        }
        else if (text[k] == ' ')
        {
            DataChar(a, Program, transX + i, transY, scaleX, scaleY, colorX, colorY, colorZ, 4, 8);
        }
        i += fontSize;
    }
};

Data ImgData(const char *filePath)
{
    Data b = {};

    float Rec[] =
        {
            0, 0, 0, 1,
            0, 1, 0, 0,
            1, 1, 1, 0,
            1, 1, 1, 0,
            1, 0, 1, 1,
            0, 0, 0, 1

        };

    glGenVertexArrays(1, &b.VAO);
    glBindVertexArray(b.VAO);

    glGenBuffers(1, &b.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, b.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, Rec, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 16, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 16, (void *)8);

    glGenTextures(1, &b.Texture);
    glBindTexture(GL_TEXTURE_2D, b.Texture);

    int Width, Height, Channel;

    stbi_set_flip_vertically_on_load(true);

    unsigned char *Data = stbi_load(filePath, &Width, &Height, &Channel, 0);

  

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);


    if (Data)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("Failed to Load Img On Rec");
    };

    stbi_image_free(Data);

    return b;
};

void DrawImgRec(Data a, UI Program, int transX, int transY, int scaleX, int scaleY, float colorX, float colorY, float colorZ)
{
    glBindVertexArray(a.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, a.VBO);
    glBindTexture(GL_TEXTURE_2D, a.Texture);

    glm::mat4 ImgModel(1.0f);
    ImgModel = glm::translate(ImgModel, glm::vec3(transX, transY, 0));
    ImgModel = glm::scale(ImgModel, glm::vec3(scaleX, scaleY, 0));
    glUniformMatrix4fv(glGetUniformLocation(Program, "model"), 1, GL_FALSE, glm::value_ptr(ImgModel));
    glUniform3f(glGetUniformLocation(Program, "ObjColor"), colorX, colorY, colorZ);
    glDrawArrays(GL_TRIANGLES, 0, 6);
};