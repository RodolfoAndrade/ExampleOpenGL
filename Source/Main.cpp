#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   color = aColor;\n"
"}\0"; 

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 color;\n"
"void main()\n" 
"{\n"
"   FragColor = vec4(color, 1.0f);\n"
"}\0";

void update(GLfloat *vertices, float angles[]) {
    vertices[6*1] = sin(angles[0]) / 2;
    vertices[6*1+1] = cos(angles[0]) / 2;
    vertices[6*2] = sin(angles[1]) / 2;
    vertices[6*2+1] = cos(angles[1]) / 2;
    vertices[6*4] = sin(angles[1]) / 2;
    vertices[6*4+1] = cos(angles[1]) / 2;
    vertices[6*5] = sin(angles[2]) / 2;
    vertices[6*5+1] = cos(angles[2]) / 2;
    vertices[6*7] = sin(angles[2]) / 2;
    vertices[6*7+1] = cos(angles[2]) / 2;
    vertices[6*8] = sin(angles[3]) / 2;
    vertices[6*8+1] = cos(angles[3]) / 2;
    vertices[6*10] = sin(angles[3]) / 2;
    vertices[6*10+1] = cos(angles[3]) / 2;
    vertices[6*11] = sin(angles[4]) / 2;
    vertices[6*11+1] = cos(angles[4]) / 2;
    vertices[6*13] = sin(angles[4]) / 2;
    vertices[6*13+1] = cos(angles[4]) / 2;
    vertices[6*14] = sin(angles[5]) / 2;
    vertices[6*14+1] = cos(angles[5]) / 2;
    vertices[6*16] = sin(angles[5]) / 2;
    vertices[6*16+1] = cos(angles[5]) / 2;
    vertices[6*17] = sin(angles[6]) / 2;
    vertices[6*17+1] = cos(angles[6]) / 2;
    vertices[6*19] = sin(angles[6]) / 2;
    vertices[6*19+1] = cos(angles[6]) / 2;
    vertices[6*20] = sin(angles[7]) / 2;
    vertices[6*20+1] = cos(angles[7]) / 2;
}

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

    float pi = 2 * acos(0.0);
    float angle = 2 * pi / 7;
    float angles[] = { 0, angle, 2*angle, 3*angle, 4*angle, 5*angle, 6*angle, 7*angle};
    GLfloat vertices[] = {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        sin(angles[0]) / 2, cos(angles[0]) / 2, 0.0f, 1.0f, 0.0f, 0.0f,
        sin(angles[1]) / 2, cos(angles[1]) / 2, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 0.647f, 0.0f,
        sin(angles[1]) / 2, cos(angles[1]) / 2, 0.0f, 1.0f, 0.647f, 0.0f,
        sin(angles[2]) / 2, cos(angles[2]) / 2, 0.0f, 1.0f, 0.647f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        sin(angles[2]) / 2, cos(angles[2]) / 2, 0.0f, 1.0f, 1.0f, 0.0f,
        sin(angles[3]) / 2, cos(angles[3]) / 2, 0.0f, 1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.502f, 0.0f,
        sin(angles[3]) / 2, cos(angles[3]) / 2, 0.0f, 0.0f, 0.502f, 0.0f,
        sin(angles[4]) / 2, cos(angles[4]) / 2, 0.0f, 0.0f, 0.502f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        sin(angles[4]) / 2, cos(angles[4]) / 2, 0.0f, 0.0f, 0.0f, 1.0f,
        sin(angles[5]) / 2, cos(angles[5]) / 2, 0.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.294f, 0.0f, 0.51f,
        sin(angles[5]) / 2, cos(angles[5]) / 2, 0.0f, 0.294f, 0.0f, 0.51f,
        sin(angles[6]) / 2, cos(angles[6]) / 2, 0.0f, 0.294f, 0.0f, 0.51f,
        0.0f, 0.0f, 0.0f, 0.933f, 0.51f, 0.933f,
        sin(angles[6]) / 2, cos(angles[6]) / 2, 0.0f, 0.933f, 0.51f, 0.933f,
        sin(angles[7]) / 2, cos(angles[7]) / 2, 0.0f, 0.933f, 0.51f, 0.933f
    };

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //Load GLAD so it configures OpenGL
    gladLoadGL();
    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, 480, 480);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Render triagle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3*7);

        // Spin the geometry but incrementing the angles
        for (size_t i = 0; i < 8; i++)
        {
            angles[i] = angles[i] + 2 * pi / 1000;
            if (angles[i] > 2 * pi) angles[i] = 0;
        }
        update(vertices, angles);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}