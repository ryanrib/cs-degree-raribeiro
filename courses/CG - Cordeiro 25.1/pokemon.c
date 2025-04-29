#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535898
// Definindo cores (RGB)
#define SKY_BLUE_R  0.53f
#define SKY_BLUE_G  0.81f
#define SKY_BLUE_B  0.98f

#define GRASS_GREEN_R  0.0f
#define GRASS_GREEN_G  0.6f
#define GRASS_GREEN_B  0.0f

#define VOLTORB_RED_R  1.0f
#define VOLTORB_RED_G  0.0f
#define VOLTORB_RED_B  0.0f

#define VOLTORB_WHITE_R 1.0f
#define VOLTORB_WHITE_G 1.0f
#define VOLTORB_WHITE_B 1.0f

// Definindo cor das nuvens
#define CLOUD_WHITE_R 1.0f
#define CLOUD_WHITE_G 1.0f
#define CLOUD_WHITE_B 1.0f

// Cores das árvores
#define TREE_TRUNK_R 0.29f
#define TREE_TRUNK_G 0.2f
#define TREE_TRUNK_B 0.0f

#define TREE_LEAVES_R 0.13f
#define TREE_LEAVES_G 0.55f
#define TREE_LEAVES_B 0.13f

// Tamanhos
#define VOLTORB_RADIUS 0.5f  // Raio do voltorb

// Posição da mata
#define GROUND_HEIGHT -0.4f

// Posição do Voltorb
#define VOLTORB_CX 0.0f
#define VOLTORB_CY -0.2f

// Suavidade dos círculos
#define CIRCLE_SEGMENTS 100

// Define shadow color
#define SHADOW_R 0.2f
#define SHADOW_G 0.2f
#define SHADOW_B 0.2f


// Protótipos de funções
void desenhaSemicirculo(float cx, float cy, float r, int anguloInicio, int anguloFim, int numSegmentos);
void desenhaElipse(float cx, float cy, float rx, float ry, int numSegmentos);
void desenhaCeu();
void desenhaMata();
void desenhaCorpoVoltorb();
void desenhaOlhos();
void desenhaPupilas();
void desenhaReflexos();
void desenhaPokemon();
void inicializa();
void desenhaElipsePreenchida(float cx, float cy, float rx, float ry, int numSegmentos);
void desenhaNuvem(float x, float y, float tamanhoX, float tamanhoY);
void desenhaNuvens();
void desenhaArvore(float x, float y, float altura);
void desenhaArvores();
void desenhaSombra();
void desenhaElipseVermelha();
void desenhaBordaInferiorElipse(float cx, float cy, float rx, float ry, int numSegmentos);
void desenhaTrianguloRetangulo(float x, float y, float base, float altura);
void desenhaTrianguloReflexo();
void desenhaElipseNoTriangulo(float xTriangulo, float yTriangulo, float base, float altura);
void desenhaRaiosEletricos();
void desenhaVoltorb();
void desenhaCena();

// Implementações das funções
void desenhaSemicirculo(float cx, float cy, float r, int anguloInicio, int anguloFim, int numSegmentos) {
    glBegin(GL_POLYGON);
    for (int i = anguloInicio; i <= anguloFim; i++) {
        float theta = 2.0f * PI * (float)i / (float)numSegmentos;
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void desenhaElipse(float cx, float cy, float rx, float ry, int numSegmentos) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegmentos; i++) {
        float theta = 2.0f * PI * (float)i / (float)numSegmentos;
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void desenhaCeu() {
    glColor3f(SKY_BLUE_R, SKY_BLUE_G, SKY_BLUE_B);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f,  1.0f);
        glVertex2f(-1.0f,  1.0f);
    glEnd();
}

void desenhaMata() {
    glColor3f(GRASS_GREEN_R, GRASS_GREEN_G, GRASS_GREEN_B);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f( 1.0f, -1.0f);
        glVertex2f( 1.0f, GROUND_HEIGHT);
        glVertex2f(-1.0f, GROUND_HEIGHT);
    glEnd();
}

void desenhaCorpoVoltorb() {
    float cx = VOLTORB_CX, cy = VOLTORB_CY, raio = VOLTORB_RADIUS;
    int segmentos = CIRCLE_SEGMENTS;

    // Corpo vermelho (semicírculo superior)
    glColor3f(VOLTORB_RED_R, VOLTORB_RED_G, VOLTORB_RED_B); // vermelho
    desenhaSemicirculo(cx, cy, raio, 0, segmentos / 2, segmentos);

    // Metade inferior branca (semicírculo inferior)
    glColor3f(VOLTORB_WHITE_R, VOLTORB_WHITE_G, VOLTORB_WHITE_B); // branco
    desenhaSemicirculo(cx, cy, raio, segmentos / 2, segmentos, segmentos);

    // Contorno preto do Voltorb
    glColor3f(0.0f, 0.0f, 0.0f); // preto
    glLineWidth(10.0f); // Aumentado de 5.0f para 7.0f
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= segmentos; i++) {
        float theta = 2.0f * PI * (float)i / (float)segmentos;
        float x = raio * cosf(theta);
        float y = raio * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void desenhaOlhos() {
    // Branco dos olhos
    glColor3f(VOLTORB_WHITE_R, VOLTORB_WHITE_G, VOLTORB_WHITE_B);
    
    // Olho esquerdo
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f, 0.3f);
    glVertex2f(-0.3f, 0.4f);
    glVertex2f(-0.1f, 0.3f);
    glVertex2f(-0.2f, 0.2f);
    glEnd();

    // Olho direito
    glBegin(GL_POLYGON);
    glVertex2f(0.1f, 0.3f);
    glVertex2f(0.2f, 0.4f);
    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.3f, 0.2f);
    glEnd();

    // Contorno preto dos olhos
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.4f, 0.3f);
    glVertex2f(-0.3f, 0.4f);
    glVertex2f(-0.1f, 0.3f);
    glVertex2f(-0.2f, 0.2f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.1f, 0.3f);
    glVertex2f(0.2f, 0.4f);
    glVertex2f(0.4f, 0.3f);
    glVertex2f(0.3f, 0.2f);
    glEnd();
}

void desenhaPupilas() {
    glColor3f(0.0f, 0.0f, 0.0f); // preto para pupilas
    
    // Pupila esquerda (elipse menor)
    desenhaElipse(-0.25f, 0.35f, 0.03f, 0.07f, 30);  // Menor e mais estreita

    // Pupila direita (elipse menor)
    desenhaElipse(0.25f, 0.35f, 0.03f, 0.07f, 30);   // Menor e mais estreita
}

void desenhaReflexos() {
    glColor3f(VOLTORB_WHITE_R, VOLTORB_WHITE_G, VOLTORB_WHITE_B); // branco para reflexos

    // Reflexo em forma de gota - Posição ajustada para dentro do Voltorb menor
    glBegin(GL_POLYGON);
    glVertex2f(-0.2f, 0.5f);  // Ajustado para ficar mais dentro da área do Voltorb
    glVertex2f(-0.1f, 0.55f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.05f, 0.45f);
    glEnd();

    // Reflexo linear alongado - Posição ajustada para ficar bem dentro do círculo
    glBegin(GL_POLYGON);
    glVertex2f(-0.1f, 0.6f);  // Ajustado para posição mais alta dentro do Voltorb
    glVertex2f(0.0f, 0.65f);
    glVertex2f(0.0f, 0.6f);
    glVertex2f(-0.1f, 0.55f);
    glEnd();
}

// Função para desenhar uma elipse preenchida (para nuvens)
void desenhaElipsePreenchida(float cx, float cy, float rx, float ry, int numSegmentos) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy); // Centro da elipse
    for (int i = 0; i <= numSegmentos; i++) {
        float theta = 2.0f * PI * (float)i / (float)numSegmentos;
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Função para desenhar uma nuvem
void desenhaNuvem(float x, float y, float tamanhoX, float tamanhoY) {
    glColor3f(CLOUD_WHITE_R, CLOUD_WHITE_G, CLOUD_WHITE_B);
    
    // Parte central da nuvem
    desenhaElipsePreenchida(x, y, tamanhoX, tamanhoY, 50);
    
    // Partes laterais da nuvem
    desenhaElipsePreenchida(x - tamanhoX * 0.8f, y, tamanhoX * 0.6f, tamanhoY * 0.7f, 50);
    desenhaElipsePreenchida(x + tamanhoX * 0.8f, y, tamanhoX * 0.6f, tamanhoY * 0.7f, 50);
    
    // Partes adicionais para tornar a nuvem mais fofa
    desenhaElipsePreenchida(x - tamanhoX * 0.4f, y + tamanhoY * 0.3f, tamanhoX * 0.5f, tamanhoY * 0.6f, 50);
    desenhaElipsePreenchida(x + tamanhoX * 0.4f, y + tamanhoY * 0.3f, tamanhoX * 0.5f, tamanhoY * 0.6f, 50);
}

// Função para desenhar múltiplas nuvens no céu
void desenhaNuvens() {
    // Nuvem grande à esquerda
    desenhaNuvem(-0.7f, 0.7f, 0.2f, 0.1f);
    
    // Nuvem média no centro
    desenhaNuvem(0.0f, 0.8f, 0.15f, 0.08f);
    
    // Nuvem pequena à direita
    desenhaNuvem(0.6f, 0.6f, 0.18f, 0.09f);
    
    // Nuvem adicional no fundo
    desenhaNuvem(0.3f, 0.9f, 0.12f, 0.06f);
}

// Função para desenhar uma árvore
void desenhaArvore(float x, float y, float altura) {
    // Tronco
    glColor3f(TREE_TRUNK_R, TREE_TRUNK_G, TREE_TRUNK_B);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x, y + altura);
        glVertex2f(x + 0.05f, y + altura);
        glVertex2f(x + 0.05f, y);
    glEnd();
    
    // Folhas - posições ajustadas para conectar com o tronco
    glColor3f(TREE_LEAVES_R, TREE_LEAVES_G, TREE_LEAVES_B);
    desenhaElipsePreenchida(x + 0.025f, y + altura + 0.1f, 0.25f, 0.15f, 50);
    desenhaElipsePreenchida(x + 0.025f, y + altura + 0.2f, 0.15f, 0.12f, 50);
}

// Função para posicionar várias árvores na cena
void desenhaArvores() {
    // Árvore à direita
    desenhaArvore(0.7f, GROUND_HEIGHT, 0.3f);
    
    // Árvore à esquerda
    desenhaArvore(-0.8f, GROUND_HEIGHT, 0.35f);
    
    // Árvore menor ao centro-direita
    desenhaArvore(0.3f, GROUND_HEIGHT, 0.2f);
    
    // Árvore média ao centro-esquerda
    desenhaArvore(-0.4f, GROUND_HEIGHT, 0.25f);
}

// Função para desenhar a sombra do Voltorb
void desenhaSombra() {
    glColor3f(SHADOW_R, SHADOW_G, SHADOW_B);
    
    // Elipse achatada para simular a sombra
    desenhaElipsePreenchida(VOLTORB_CX - 0.05f, GROUND_HEIGHT - 0.05f, VOLTORB_RADIUS * 0.9f, VOLTORB_RADIUS * 0.3f, 50);
}

// Função para desenhar a borda inferior de uma elipse
void desenhaBordaInferiorElipse(float cx, float cy, float rx, float ry, int numSegmentos) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(10.0f);
    
    glBegin(GL_LINE_STRIP);
    // Desenha apenas a metade inferior da elipse
    for (int i = 0; i <= numSegmentos; i++) {
        float theta = PI + PI * (float)i / (float)numSegmentos;
        float x = rx * cosf(theta);
        float y = ry * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Função para desenhar a elipse vermelha central do Voltorb
void desenhaElipseVermelha() {
    float cx = VOLTORB_CX;
    float cy = VOLTORB_CY;
    
    glColor3f(VOLTORB_RED_R, VOLTORB_RED_G, VOLTORB_RED_B);
    
    // Elipse central do Voltorb
    desenhaElipsePreenchida(cx, cy, VOLTORB_RADIUS, VOLTORB_RADIUS * 0.3f, 50);

    // Borda preta na parte inferior
    desenhaBordaInferiorElipse(cx, cy, VOLTORB_RADIUS, VOLTORB_RADIUS * 0.3f, 50);
}

// Função para desenhar os olhos triangulares do Voltorb
void desenhaTrianguloRetangulo(float x, float y, float base, float altura) {
    // Área branca do olho
    glColor3f(VOLTORB_WHITE_R, VOLTORB_WHITE_G, VOLTORB_WHITE_B);
    
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y);                  // Ângulo reto
        glVertex2f(x + base, y);           // Base do olho
        glVertex2f(x, y + altura);         // Parte superior do olho
    glEnd();

    // Contorno preto do olho
    glColor3f(0.0f, 0.0f, 0.0f);           
    glLineWidth(4.0f);                     
    
    glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);                  
        glVertex2f(x + base, y);           
        glVertex2f(x, y + altura);         
    glEnd();
}

// Função para desenhar o reflexo de luz no Voltorb
void desenhaTrianguloReflexo() {
    glColor3f(VOLTORB_WHITE_R, VOLTORB_WHITE_G, VOLTORB_WHITE_B);
    
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.35f, 0.1f);   // Ponto inferior esquerdo
        glVertex2f(-0.2f, 0.2f);    // Ponto inferior direito
        glVertex2f(-0.28f, 0.18f);  // Ponto superior
    glEnd();
}

// Função para desenhar as pupilas nos olhos do Voltorb
void desenhaElipseNoTriangulo(float xTriangulo, float yTriangulo, float base, float altura) {
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // Posicionamento da pupila dentro do olho
    float centroX, centroY;
    
    if (base > 0) {
        // Olho esquerdo (base positiva)
        centroX = xTriangulo + base * 0.40f;
        centroY = yTriangulo + altura * 0.50f;
    } else {
        // Olho direito (base negativa)
        centroX = xTriangulo + base * 0.40f;
        centroY = yTriangulo + altura * 0.50f;
    }
    
    // Dimensões da pupila achatada
    float raioX = fabs(base) * 0.05f;
    float raioY = altura * 0.15f;
 
    desenhaElipsePreenchida(centroX, centroY, raioX, raioY, 30);
}

// Função para desenhar os raios elétricos ao redor do Voltorb
void desenhaRaiosEletricos() {
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(3.0f);
    
    // Raio superior direito
    glBegin(GL_LINE_STRIP);
        glVertex2f(0.3f, 0.1f);     // Origem
        glVertex2f(0.5f, 0.25f);    // Primeiro segmento
        glVertex2f(0.45f, 0.3f);    // Segundo segmento
        glVertex2f(0.65f, 0.4f);    // Ponta
    glEnd();
    
    // Raio superior esquerdo
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.3f, 0.1f);    
        glVertex2f(-0.4f, 0.3f);    
        glVertex2f(-0.35f, 0.35f);  
        glVertex2f(-0.5f, 0.5f);    
    glEnd();
    
    // Raio lateral direito
    glBegin(GL_LINE_STRIP);
        glVertex2f(0.45f, -0.15f);  
        glVertex2f(0.65f, -0.1f);   
        glVertex2f(0.6f, -0.05f);   
        glVertex2f(0.8f, 0.0f);     
    glEnd();
    
    // Raio lateral esquerdo
    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.45f, -0.15f); 
        glVertex2f(-0.6f, -0.05f);  
        glVertex2f(-0.55f, 0.0f);   
        glVertex2f(-0.7f, 0.2f);    
    glEnd();
}

// Função para agrupar os elementos do Voltorb
void desenhaVoltorb() {
    desenhaCorpoVoltorb();
    desenhaElipseVermelha();
    desenhaTrianguloReflexo();

    // Coordenadas para os olhos
    float olhoEsqX = -0.3f, olhoEsqY = -0.2f, olhoEsqBase = 0.2f, olhoEsqAltura = 0.15f;
    float olhoDirX = 0.3f, olhoDirY = -0.2f, olhoDirBase = -0.2f, olhoDirAltura = 0.15f;
    
    // Desenha os olhos e pupilas
    desenhaTrianguloRetangulo(olhoEsqX, olhoEsqY, olhoEsqBase, olhoEsqAltura);  // Olho esquerdo
    desenhaTrianguloRetangulo(olhoDirX, olhoDirY, olhoDirBase, olhoDirAltura);  // Olho direito
    desenhaElipseNoTriangulo(olhoEsqX, olhoEsqY, olhoEsqBase, olhoEsqAltura);   // Pupila esquerda
    desenhaElipseNoTriangulo(olhoDirX, olhoDirY, olhoDirBase, olhoDirAltura);   // Pupila direita
    
    // Efeitos elétricos
    desenhaRaiosEletricos();
}

// Função principal para desenhar toda a cena
void desenhaCena() {
    glClear(GL_COLOR_BUFFER_BIT);  

    // Desenha o cenário
    desenhaCeu();
    desenhaNuvens();
    desenhaMata();
    desenhaArvores();
    
    // Desenha a sombra antes do Voltorb
    desenhaSombra();
    
    // Desenha o Pokémon Voltorb
    desenhaVoltorb();

    glFlush();
}

void inicializa() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Voltorb - Ryan Ribeiro");
    inicializa();
    glutDisplayFunc(desenhaCena);  
    glutMainLoop();
    return 0;
}
