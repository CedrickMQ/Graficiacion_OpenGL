#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>

// Elementos para la interface
#define NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#include <nuklear.h>
#include <nuklear_glfw_gl2.h>

#define max_vertex_memory 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

float x1, x2, y1, y2;

void drawPixel() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);

    glVertex2f(0.5f, 0.5f);
    glVertex2f(0, 0);
    
    glEnd();
}

void drawPixelLine(float x1, float y1, float x2, float y2){
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);

    float XDiag, YDiag, XRecta, YRecta;

    float dy = (y2 - y1);
    float dx = (x2 - x1);

    float Dis = 0.001f;

    if (dy >= 0)
    {
        YDiag = Dis;
    } else {
        dy = -dy;
        YDiag = -Dis;
    }

    if (dx >= 0)
    {
        XDiag = Dis;
    } else {
        dx = -dx;
        XDiag = -Dis;
    }

    if (dx >= dy)
    {
        YRecta = 0;
        XRecta = XDiag;
    } else {
        XRecta = 0;
        YRecta = YDiag;
    }

    float x = x1;
    float y = y1;

    float avR = 2 * dy;
    float av = avR - dx;
    float avI = av - dx; 

    for(;((x <= x2) && (y <= y2));)
    {
        glVertex2f(x,y);
 
        if (av >= 0)
        {
            x = x + XDiag;
            y = y + YDiag;
            av = av + avI;
        } else {
            x = x + XRecta;
            y = y + YRecta;
            av = av + avR;
        }
    }

    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2) {
    // Establecer el color de la línea (en este caso, rojo)
    glColor3f(1.0f, 0.0f, 0.0f);

    // Dibujar la línea utilizando glBegin y glEnd
    glBegin(GL_LINES);
    glVertex2f(x1, y1); // Punto inicial de la línea
    glVertex2f(x2, y2);   // Punto final de la línea
    glEnd();
}

int main(void) {
    GLFWwindow* window;

    x1 = -1.0;
    y1 = -0.0;

    x2 = 1.0;
    y2 = 0.3;

    if (!glfwInit()) {
        fprintf(stderr, "Error iniciando GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(600, 600, "AAAA", NULL, NULL);
    if (!window) {
        fprintf(stderr,"Error creando la ventana GLFW\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);  

    struct nk_context* nk = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();

        glfwPollEvents();

        nk_glfw3_new_frame();

        if(nk_begin(nk, "hello, world!", nk_rect(50,50,200,200), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
            nk_layout_row_dynamic(nk,30,1);
            nk_label(nk,"hello world", NK_TEXT_CENTERED);
        }

        nk_end(nk);

        nk_glfw3_render(NK_ANTI_ALIASING_ON);

        // drawLine(x1, y1, x2, y2); // Llamar a la función para dibujar la línea
        // drawPixel();
        // drawPixelLine(x1, y1, x2, y2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    nk_glfw3_shutdown();
    glfwTerminate();
    return 0;
}
