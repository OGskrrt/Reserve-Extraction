#include <GL/glut.h>
#include "freeglut.h"
#include "glut.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>



int grid_size = 64; 
float kare_size = 0.015625f;  

int uzunluk2;

int grafiknumarasi2;
int birimsondaj2;
int birimplat2;

void grid_ciz_4x4(void);
void grid_ciz_16x16(void);
void grid_ciz_64x64(void);
void Grid(void);
void sonrasaaparim(int dizi[], int uzunluk, int grafikNum);
float* floatdondurme(int dizi[], int uzunluk);
void grafikciz(int dizi[], int uzunluk, int grafikNum);
void Curl_Devam(void);
void bakicazartik(int dizi[], int uzunluk, int grafikNum);
void karebirimler(int dizi[], int uzunluk);
void kare_ciz2(float x, float y, float size, float r, float g, float b, float alpha);
void grid_ciz_16x162(void);
void nebula(int dizi[], int uzunluk);
void aktar(int grafiknumarasi, int birimsondaj, int birimplat);
/////////// ikinci aşama ////


void kare_ciz(float x, float y, float size, float r, float g, float b, float alpha) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(r, g, b, alpha);



    glBegin(GL_QUADS);
    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glVertex2f(x + size, y + size);
    glVertex2f(x - size, y + size);
    glEnd();
}

void kare_ciz2(float x, float y, float size, float r, float g, float b, float alpha) {


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(2.0);
    glColor4f(r, g, b, alpha);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    glBegin(GL_QUADS);
    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glVertex2f(x + size, y + size);
    glVertex2f(x - size, y + size);
    glEnd();

    glColor4f(r, g, b, alpha);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(1.0);

    glBegin(GL_QUADS);

    glVertex2f(x - size, y - size);
    glVertex2f(x + size, y - size);
    glVertex2f(x + size, y + size);
    glVertex2f(x - size, y + size);

    glEnd();
}

void grid_ciz_1x1(void) {
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            float x = -1.0 + (kare_size)+(2 * j * (kare_size));
            float y = 1.0 - (kare_size)-(2 * i * (kare_size));


            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glLineWidth(1.0);
            glColor3f(1.0, 1.0, 1.0);
            glBegin(GL_QUADS);

            glVertex2f(x - kare_size, y - kare_size);
            glVertex2f(x + kare_size, y - kare_size);
            glVertex2f(x + kare_size, y + kare_size);
            glVertex2f(x - kare_size, y + kare_size);

            glEnd();

            glLineWidth(2.0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            kare_ciz(x, y, kare_size, 0.9, 0.9, 0.9, 1.0);
        }
    }
}

void display(void) {
    aktar2(grafiknumarasi2, birimsondaj2, birimplat2);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //sonrasaaparım(dizi, uzunluk, grafikNum);
    Grid();
    Curl_Devam();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.1, 1.1, -1.1, 1.1);
    glMatrixMode(GL_MODELVIEW);
}
void grid_ciz_4x4(void) {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            float x = -1.0 + (kare_size * 2) + (2 * j * (kare_size * 2));
            float y = 1.0 - (kare_size * 2) - (2 * i * (kare_size * 2));

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            kare_ciz(x, y, 2 * kare_size, 0.7, 0.7, 0.7, 1.0);
        }
    }
}
void grid_ciz_16x16(void) {
    for (int i = 0; i < 16.0; i++) {
        for (int j = 0; j < 16.0; j++) {
            float x = -1.0 + (kare_size * 4) + (2 * j * (kare_size * 4));
            float y = 1.0 - (kare_size * 4) - (2 * i * (kare_size * 4));

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            kare_ciz(x, y, 4 * kare_size, 0.5, 0.5, 0.5, 1.0);
        }
    }
}
void grid_ciz_64x64(void) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            float x = -1.0 + (kare_size * 8) + (2 * j * (kare_size * 8));
            float y = 1.0 - (kare_size * 8) - (2 * i * (kare_size * 8));


            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            kare_ciz(x, y, 8 * kare_size, 0.3, 0.3, 0.3, 1.0);
        }
    }
}
void grid_ciz_16x162(void) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float x = -1.0 + (kare_size * 16) + (2 * j * (kare_size * 16));
            float y = 1.0 - (kare_size * 16) - (2 * i * (kare_size * 16));


            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            kare_ciz(x, y, 16 * kare_size, 0.1, 0.1, 0.1, 1.0);
        }
    }
}


void Grid(void) {
    glLineWidth(1.0);
    grid_ciz_1x1();
    //glLineWidth(2.0);
    grid_ciz_4x4();
    //glLineWidth(2.0);
    grid_ciz_16x16();
    //glLineWidth(3.0);
    grid_ciz_64x64();
    //glLineWidth(4.0);
    grid_ciz_16x162();
}

void sonrasaaparim(int dizi[], int uzunluk, int grafikNum) {
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    float* diziF = floatdondurme(dizi, uzunluk);
    float* yenidizi = diziF;
    uzunluk2 = uzunluk;
    //glTranslatef(1.0, 1.0, 0.0f);
    //ikinciasama(dizi, uzunluk, grafikNum);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.0, 1.0, 0.0, 0.5);

    glBegin(GL_POLYGON);
    for (int i = 0; i < uzunluk; i += 2) {
        glVertex2f(-1.0 + diziF[i], 1.0 - diziF[i + 1]);
    }
    glEnd();

    glLineWidth(3.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4f(0.0, 0.4, 0.0, 0.8);
    glBegin(GL_POLYGON);
    for (int i = 0; i < uzunluk; i += 2) {
        glVertex2f(-1.0 + diziF[i], 1.0 - diziF[i + 1]);
    }
    glEnd();

    free(diziF);
    dizi[uzunluk] = dizi[0];
    dizi[uzunluk + 1] = dizi[1];


    karebirimler(dizi, uzunluk);
    /*glutSwapBuffers();
    int devam;
    scanf("%d", &devam);
    ikinciasama(dizi, uzunluk);*/



}

float* floatdondurme(int dizi[], int uzunluk) {
    float* diziF = (float*)malloc(uzunluk * sizeof(float));
    for (int i = 0; i < uzunluk; i++) {
        diziF[i] = (float)dizi[i] * 0.03125f;
    }
    return diziF;
}

void aktar(int grafiknumarasi, int birimsondaj, int birimplat) {
    grafiknumarasi2 = grafiknumarasi;
    birimsondaj2 = birimsondaj;
    birimplat2 = birimplat;
}
void Curl_Devam(void) {
    FILE* dataFile = fopen("prolab1.txt", "r");
    if (dataFile == NULL) {
        fprintf(stderr, "Dosya açma hatası\n");
        return 1;
    }

    int vericekdizi[300] = { 0 };
    int dizi[300] = { 0 };
    int counter = 0;
    int c, d;
    int grafikNum = 0;

    while ((c = fgetc(dataFile)) != EOF) {
        if (c >= '0' && c <= '9') {
            d = fgetc(dataFile);
            if (d == 'B') {

                if (grafikNum == grafiknumarasi2)
                    grafikciz(dizi, counter, grafikNum);
                grafikNum++;
                counter = 0;
            }
            else if (d >= '0' && d <= '9') {
                if (counter < 300) {
                    if (d != 'B') {
                        dizi[counter] = ((c - '0') * 10) + (d - '0');
                    }
                    else {
                        dizi[counter] = c - '0';
                    }
                    counter++;
                }
            }
            else if (d != 'F') {
                if (c != 'B') {
                    dizi[counter] = c - '0';
                    counter++;
                }
            }
        }
    }
    if (counter > 0) {
        if (grafikNum == grafiknumarasi2)
            grafikciz(dizi, counter, grafikNum);
    }
    fclose(dataFile);

}

void grafikciz(int dizi[], int uzunluk, int grafikNum) {

    int graph[300] = { 0 };
    int grcnt = 0;
    int a = 0;

    for (int i = 0; i < uzunluk; i++) {
        graph[grcnt] = dizi[i];
        if ((i >= a) && (i % 2 == 1) && (i >= a + 2)) {
            if (dizi[a] == dizi[i - 1] && dizi[a + 1] == dizi[i]) {
                graph[grcnt] = 0;
                graph[grcnt - 1] = 0;
                sonrasaaparim(graph, grcnt - 1, grafikNum);
                grcnt = (-1);
                a = i + 1;
                for (int l = 0; l < 100; l++) {
                    graph[l] = 0;
                }
            }


        }
        grcnt++;
    }


}


void karebirimler(int dizi[], int* uzunluk) {
    //int dizi2 = dizi;
    //dizi2[uzunluk] = dizi[0];
    //dizi2[uzunluk+1] = dizi[1];

    int minx = dizi[0];
    int miny = dizi[1];
    int maxx = dizi[0];
    int maxy = dizi[1];

    for (int i = 2; i < uzunluk; i += 2) {
        if (dizi[i] < minx) {
            minx = dizi[i];
        }
        if (dizi[i] > maxx) {
            maxx = dizi[i];
        }
    }

    for (int i = 3; i < uzunluk; i += 2) {
        if (dizi[i] < miny) {
            miny = dizi[i];
        }
        if (dizi[i] > maxy) {
            maxy = dizi[i];
        }
    }

    int maxx2 = maxx;
    int maxy2 = maxy;
    int minx2 = minx;
    int miny2 = miny;

    int kacbirim = 0;

    for (int i = miny; i < maxy; i++) {
        for (int j = minx; j < maxx; j++) {
            float x = -1.0 + ((kare_size)*j * 2) + (kare_size);
            float y = 1.0 - ((kare_size)*i * 2) - (kare_size);
            //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            kare_ciz2(x, y, kare_size, 0.0, 0.0, 0.7, 0.45);
            kacbirim++;
        }
    }

    int a = 0;
    while (dizi[a + 2]) {
        int r = dizi[a];
        int t = dizi[a + 1];
        int y = dizi[a + 2];
        int u = dizi[a + 3];

        int o = abs(y - r);  
        int p = abs(u - t);
        int n = y - r;  
        int m = u - t;

        float k = (float)(o) / (float)(p);

        if (n > 0 && m > 0) {
            for (int c = 0; c < o; c++) {
                for (int v = 0; v < p; v++) {
                    if (c > v && (float)(c - v) >= k) {
                        float h = -1.0 + (float)(r + c) * 0.03125f + 0.015625f;
                        float j = 1.0 - (float)(t + v) * 0.03125f - 0.015625f;
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        glLineWidth(1.0);
                        glColor3f(1.0, 1.0, 1.0);
                        glBegin(GL_QUADS);

                        glVertex2f(h - kare_size, j - kare_size);
                        glVertex2f(h + kare_size, j - kare_size);
                        glVertex2f(h + kare_size, j + kare_size);
                        glVertex2f(h - kare_size, j + kare_size);

                        glEnd();

                        glLineWidth(2.0);
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        kare_ciz(h, j, kare_size, 0.9, 0.9, 0.9, 1.0);
                        kacbirim--;

                    }

                }
            }

        }
        if (n > 0 && m < 0) {
            for (int c = 0; c < o; c++) {
                for (int v = 0; v < p - k; v++) {
                    if (c * (1 / k) + v <= p - 1 - 1 / k) {
                        float h = -1.0 + (float)(r + c) * 0.03125f + 0.015625f;
                        float j = 1.0 - (float)(u + v) * 0.03125f - 0.015625f;
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        glLineWidth(1.0);
                        glColor3f(1.0, 1.0, 1.0);
                        glBegin(GL_QUADS);

                        glVertex2f(h - kare_size, j - kare_size);
                        glVertex2f(h + kare_size, j - kare_size);
                        glVertex2f(h + kare_size, j + kare_size);
                        glVertex2f(h - kare_size, j + kare_size);

                        glEnd();

                        glLineWidth(2.0);
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        kare_ciz(h, j, kare_size, 0.9, 0.9, 0.9, 1.0);
                        kacbirim--;
                    }


                }
            }

        }
        if (n < 0 && m > 0) {
            for (int c = 0; c < o; c++) {
                for (int v = 0; v < p; v++) {
                    if (c * (1 / k) + v >= p) {
                        float h = -1.0 + (float)(y + c) * 0.03125f + 0.015625f;
                        float j = 1.0 - (float)(t + v) * 0.03125f - 0.015625f;
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        glLineWidth(1.0);
                        glColor3f(1.0, 1.0, 1.0);
                        glBegin(GL_QUADS);

                        glVertex2f(h - kare_size, j - kare_size);
                        glVertex2f(h + kare_size, j - kare_size);
                        glVertex2f(h + kare_size, j + kare_size);
                        glVertex2f(h - kare_size, j + kare_size);

                        glEnd();

                        glLineWidth(2.0);
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        kare_ciz(h, j, kare_size, 0.9, 0.9, 0.9, 1.0);
                        kacbirim--;
                    }


                }
            }

        }
        if (n < 0 && m < 0) {
            for (int c = 0; c < o; c++) {
                for (int v = 0; v < p; v++) {
                    if (c < v && (float)(c - v) <= k) {
                        float h = -1.0 + (float)(y + c) * 0.03125f + 0.015625f;
                        float j = 1.0 - (float)(u + v) * 0.03125f - 0.015625f;
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        glLineWidth(1.0);
                        glColor3f(1.0, 1.0, 1.0);
                        glBegin(GL_QUADS);

                        glVertex2f(h - kare_size, j - kare_size);
                        glVertex2f(h + kare_size, j - kare_size);
                        glVertex2f(h + kare_size, j + kare_size);
                        glVertex2f(h - kare_size, j + kare_size);

                        glEnd();

                        glLineWidth(2.0);
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        kare_ciz(h, j, kare_size, 0.9, 0.9, 0.9, 1.0);
                        kacbirim--;
                    }

                }
            }

        }

        a += 2;
        //printf("%d", kacbirim);

    }
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glRasterPos2f(-1.0 + (float)(dizi[0]) * 0.03125f + 0.015625f, 1.0 - (float)(dizi[1]) * 0.03125f - 0.015625f);
    int rezerv = kacbirim * 10;
    char rezervalani[10];
    snprintf(rezervalani, sizeof(rezervalani), "%d", rezerv);
    char rezervalaniyazi[30] = { "Toplam rezerv alani : " };
    for (int i = 0; i < 30; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, rezervalaniyazi[i]);

    }
    for (int i = 0; i < 10; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, rezervalani[i]);

    }
    

    glColor4f(1.0, 0.0, 0.0, 1.0);
    glRasterPos2f(-1.0 + (float)(dizi[0]) * 0.03125f + 0.015625f, 1.0 - (float)(dizi[1]) * 0.03125f - 0.015625f*4);
    char birim[10];
    snprintf(birim, sizeof(birim), "%d", kacbirim);
    char j = '2';
    char B = 'B';
    char r = 'r';

    for (int i = 0; i < 10; i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, birim[i]);

    }
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (char)B);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (char)r);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (char)j);
    glRasterPos2f(0.0f, 0.0f);

}

///////////////////////////////////////////////    IKINCI ASAMA    ///////////////////////////////////////////////////


