#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>

float x1, x2, y1, y2;

void drawPixel() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);

    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, -0.5f);
    
    glEnd();
}

void drawPixelLine(float Name, float x1, float y1, float x2, float y2){
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);

    float y = y1;
    float x = x1;

    if (Name = 1)
    {
        for (float init = x1; init <= x2; init)
        {
            glVertex2f(init, init);
            init = init + 0.001f;
        }
    } else if (Name > 1)
    {
        glVertex2f(0,0);

        while (y >= y2)
        {
            for (int Vx = 0 ; Vx < 2; Vx++)
            {
                x = x + 1;
                glVertex2f(x,y);
            }
            
        }
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

    x1 = -0.5;
    y1 = -0.5;

    x2 = 0.5;
    y2 = 0.5;

    float XDistancia = x1 - x2;
    if (XDistancia < 0)
    {
        XDistancia = XDistancia * -1;
    }

    float YDistancia = y1 - x2;
    if (YDistancia < 0)
    {
        YDistancia = YDistancia * -1;
    }
    
    float Name ;
    if (XDistancia > YDistancia) {
        Name = XDistancia / YDistancia; 
    } else {
        Name = YDistancia / XDistancia;
    }
    

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
        drawPixelLine(Name, x1, y1, x2, y2);

        glfwSwapBuffers(window);
        glfwPollEvents();
        //glClear(GL_COLOR_BUFFER_BIT);
    }

    glfwTerminate();
    return 0;
}
