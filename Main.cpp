#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "heptagon.h"
#include "logo.h"

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
    const unsigned int width = 480;
    const unsigned int height = 480;
    window = glfwCreateWindow(width, height, "Triangle", NULL, NULL);
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
    glViewport(0, 0, width, height);

    Shader shader = Shader("default.vert", "default.frag");

    //// VAO and VBO of heptagon
    VAO vao = VAO();
    vao.Bind();

    VBO vbo = VBO(hep.getVertices(), hep.getSizeOf());
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();

    Shader shader2 = Shader("texture.vert", "texture.frag");

    // VAO and VBO of icon
    VAO vao2 = VAO();
    vao2.Bind();

    // Texture
    GLuint uniID = glGetUniformLocation(shader2.ID, "scale");
    logo icon("./images/rd.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    icon.getTexture().texUnit(shader2, "tex0", 0);

    VBO vbo2 = VBO(icon.getVertices(), icon.getSizeOf());
    vao2.LinkAttrib(vbo2, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao2.LinkAttrib(vbo2, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao2.Unbind();
    vbo2.Unbind();

    float rotation = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Render triagle
        shader.Activate();

        // Initializes matrices so they are not the null matrix
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        rotation += 0.5f;
        // Assigns different transformations to each matrix
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, -1.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

        // Outputs the matrices into the Vertex Shader
        int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        int projLoc = glGetUniformLocation(shader.ID, "proj");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

        // Draw heptagon
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3*7);

        // Draw icon
        shader2.Activate();
        // Sets the value of the uniform
        glUniform1i(uniID, 0.5f);
        icon.getTexture().Bind();
        vao2.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3 * 2);

        // Updating heptagon
        //hep.update();
        //vbo.Bind();
        //vbo.Update(hep.getVertices(), hep.getSizeOf());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    vao2.Delete();
    vbo2.Delete();
    icon.getTexture().Delete();
    shader.Delete();
    shader2.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}