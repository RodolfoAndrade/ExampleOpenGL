#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <cmath>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "heptagon.h"

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    // Tell GLFW what version of OpenGL we are using 
    // In this case we are using OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW we are using the CORE profile
    // So that means we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Load heptagon
    heptagon hep = heptagon();

    // Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, 480, 480);

    Shader shader = Shader("default.vert", "default.frag");

    VAO vao = VAO();
    vao.Bind();

    VBO vbo = VBO(hep.getVertices(), hep.getSizeOf());
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    vbo.Bind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Render triagle
        shader.Activate();
        glDrawArrays(GL_TRIANGLES, 0, 3*7);

        hep.update();
        vbo.Bind();
        glBufferData(GL_ARRAY_BUFFER, hep.getSizeOf(), hep.getVertices(), GL_DYNAMIC_DRAW);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    shader.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}