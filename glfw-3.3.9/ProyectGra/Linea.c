#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>

int main (void)
{
    GLFWwindow* window;
    
    if (!glfwInit())
    {
        fprintf(stderr, "error iniciando GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(400, 400, "AAAA", NULL, NULL);
    if (!window)
    {
        fprintf(stderr,"Error creando la ventana GLFW\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress); // este inicia lo que son las funciones de opengl
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT); // AAAAAAA
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


