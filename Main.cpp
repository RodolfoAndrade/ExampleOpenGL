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
    // square
    GLfloat vertices[] = {
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.8f, 1.0f, 0.0f, 1.0f, 1.0f,
        -0.8f, 0.8f, 0.0f, 1.0f, 0.0f,
        -0.8f, 0.8f, 0.0f, 1.0f, 0.0f,
        -1.0f, 0.8f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };

    // Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, 480, 480);

    Shader shader = Shader("default.vert", "default.frag");

    //// VAO and VBO of heptagon
    VAO vao = VAO();
    vao.Bind();

    VBO vbo = VBO(hep.getVertices(), hep.getSizeOf());
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    vbo.Bind();

    Shader shader2 = Shader("texture.vert", "texture.frag");

    // VAO and VBO of quad
    VAO vao2 = VAO();
    vao2.Bind();

    VBO vbo2 = VBO(vertices, sizeof(vertices));
    vao2.LinkAttrib(vbo2, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao2.LinkAttrib(vbo2, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vbo2.Bind();

    // Texture
	// Stores the width, height, and the number of color channels of the image
    int widthImg, heightImg, numColCh;
    // Flips the image so it appears right side up
    stbi_set_flip_vertically_on_load(true);
    // Reads the image from a file and stores it in bytes
    unsigned char* bytes = stbi_load("./images/rd.jpg", &widthImg, &heightImg, &numColCh, 0);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Configures the type of algorithm that is used to make the image smaller or bigger
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Configures the way the texture repeats (if it does at all)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Extra lines in case you choose to use GL_CLAMP_TO_BORDER
    // float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    // Assigns the image to the OpenGL Texture object
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    // Generates MipMaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Deletes the image data as it is already in the OpenGL Texture object
    stbi_image_free(bytes);

    // Unbinds the OpenGL Texture object so that it can't accidentally be modified
    glBindTexture(GL_TEXTURE_2D, 0);

    // Gets the location of the uniform
    GLuint texUni = glGetUniformLocation(shader2.ID, "tex0");
    // Shader needs to be activated before changing the value of a uniform
    shader2.Activate();
    glUniform1i(texUni, 0.5f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //// Render triagle
        shader.Activate();
        //// Draw heptagon
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3*7);

        // Draw quad
        shader2.Activate();
        // Sets the value of the uniform
        glUniform1i(texUni, 0.5f);
        glBindTexture(GL_TEXTURE_2D, texture);
        vao2.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 3 * 2);

        //// Updating heptagon
        hep.update();
        vbo.Bind();
        vbo.Update(hep.getVertices(), hep.getSizeOf());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    vao2.Delete();
    vbo2.Delete();
    shader.Delete();
    shader2.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}