#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>

void drawPixel() {
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, -0.5f);
    glEnd();
}

void drawPixelLine(){
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_POINTS);

    for (float x = -0.5f; x <= 0.5; x )
    {
        glVertex2f(x,x);
        x = x + 0.001f;
    }
    glEnd();
    
}

void drawLine() {
    // Establecer el color de la línea (en este caso, rojo)
    glColor3f(1.0f, 0.0f, 0.0f);

    // Dibujar la línea utilizando glBegin y glEnd
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f); // Punto inicial de la línea
    glVertex2f(1.0f, 0.0f);   // Punto final de la línea
    glEnd();
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) {
        fprintf(stderr, "Error iniciando GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(400, 400, "AAAA", NULL, NULL);
    if (!window) {
        fprintf(stderr,"Error creando la ventana GLFW\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();

        //drawLine(); // Llamar a la función para dibujar la línea
        //drawPixel();
        drawPixelLine();

        glfwSwapBuffers(window);
        glfwPollEvents();
        //glClear(GL_COLOR_BUFFER_BIT);
    }

    glfwTerminate();
    return 0;
}
