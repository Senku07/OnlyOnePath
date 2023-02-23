#pragma once

#include "include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/common.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

float CameraPosX = 49;
float CameraPosY = 3;
float CameraPosZ = 50;

float ModelViewX = 0;
float ModelViewY = 0;
float ModelViewZ = 0;

float OriantationX = 0;
float OriantationY = 1;
float OriantationZ = 0;

void Camera(unsigned int Program, GLFWwindow *window)
{
    glm::mat4 View(1.0f);
    View = glm::lookAt(glm::vec3(CameraPosX, CameraPosY, CameraPosZ), glm::vec3(ModelViewX, ModelViewY, ModelViewZ), glm::vec3(OriantationX, OriantationY, OriantationZ));
    glUniformMatrix4fv(glGetUniformLocation(Program, "View"), 1, 0, glm::value_ptr(View));
    glUniform3f(glGetUniformLocation(Program, "cameraPosition"), CameraPosX, CameraPosY, CameraPosZ);
}