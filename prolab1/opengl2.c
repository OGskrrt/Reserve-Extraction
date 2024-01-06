#include "opengl.h"
#include <GL/glut.h>
#include "freeglut.h"
#include "glut.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

void ikinciasama(void);
void grafikciz2(int dizi[], int uzunluk, int grafikNum);
void Curl_Devam2(void);
void sonrasaaparim2(int dizi[], int uzunluk, int grafikNum);
float* floatdondurme2(int dizi[], int uzunluk);
void karebirimler2(int dizi[], int* uzunluk);
int olurmu(int** matris, int i, int j, int kac, int n, int m);
void karebirim4x4(int** matris, int dizi[], int uzunluk);
int** olusturMatris(int satir, int sutun);
void kare_ciz3(float x, float y, float size, float r, float g, float b, float alpha);
void karebirim2x2(int** matris, int dizi[], int uzunluk);
void aktar2(int grafiknumarasi, int birimsondaj, int birimplat);
void karebirim8x8(int** matris, int dizi[], int uzunluk);
void karebirim16x16(int** matris, int dizi[], int uzunluk);
void hesapyap(int** matris, int* dizi, int minx, int miny, int n, int m, int kacbirim);

int grafiknumarasi3;
int birimsondaj3;
int birimplat3;

float kare_sizeyeni = 0.015625f;

void kare_ciz3(float x, float y, float size, float r, float g, float b, float alpha) {
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

void aktar2(int grafiknumarasi, int birimsondaj, int birimplat) {
    grafiknumarasi3 = grafiknumarasi;
    birimsondaj3 = birimsondaj;
    birimplat3 = birimplat;
}

void ikinciasama(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    Grid();
    Curl_Devam2();
    glutSwapBuffers();
    glFlush();

}
void Curl_Devam2(void) {
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

                if (grafikNum == grafiknumarasi3)
                    grafikciz2(dizi, counter, grafikNum);
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
        if (grafikNum == grafiknumarasi3)
            grafikciz2(dizi, counter, grafikNum);
        //glutSwapBuffers();
    }
    fclose(dataFile);

}

void grafikciz2(int dizi[], int uzunluk, int grafikNum) {

    int graph[300] = { 0 };
    int grcnt = 0;
    int a = 0;

    for (int i = 0; i < uzunluk; i++) {
        graph[grcnt] = dizi[i];
        if ((i >= a) && (i % 2 == 1) && (i >= a + 2)) {
            if (dizi[a] == dizi[i - 1] && dizi[a + 1] == dizi[i]) {
                graph[grcnt] = 0;
                graph[grcnt - 1] = 0;
                sonrasaaparim2(graph, grcnt - 1, grafikNum);
                //glutSwapBuffers();
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

float* floatdondurme2(int dizi[], int uzunluk) {
    float* diziF = (float*)malloc(uzunluk * sizeof(float));
    if (diziF == NULL) {
        printf("floatdondurmede sıkıntı var");
        return 1;

    }
    for (int i = 0; i < uzunluk; i++) {
        diziF[i] = (float)dizi[i] * 0.03125f;
    }
    return diziF;
}

void sonrasaaparim2(int dizi[], int uzunluk, int grafikNum) {
    float* diziF = floatdondurme2(dizi, uzunluk);

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


    karebirimler2(dizi, uzunluk);


}


void karebirimler2(int dizi[], int uzunluk) {
    int dizi2[50];
    memcpy(dizi2, dizi, sizeof(dizi));


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
    int n = maxy - miny;
    int m = maxx - minx;

    //int sabitmatris[64][] = { 1 };

    //int sabitmatris[n][m] = {1};

    int** sekilmatrisi = (int**)malloc(n * sizeof(int*));


    if (sekilmatrisi == NULL) {
        fprintf(stderr, "Bellek tahsis hatası\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        sekilmatrisi[i] = (int*)malloc(m * sizeof(int));
        if (sekilmatrisi[i] == NULL) {
            fprintf(stderr, "Bellek tahsis hatası\n");
            
            for (int j = 0; j < i; j++) {
                free(sekilmatrisi[j]);
            }
            free(sekilmatrisi);
            return;
        }
    }
    for (int a = 0; a < n; a++) {
        for (int b = 0; b < m; b++) {
            sekilmatrisi[a][b] = 1;
        }
    }


    int kacbirim = 0;

    for (int i = miny; i < maxy; i++) {
        int x = 0;
        for (int j = minx; j < maxx; j++) {
            int y = 0;
            //sabitmatris[x][y] = 1;
            float k = -1.0 + ((kare_sizeyeni)*j * 2) + (kare_sizeyeni);
            float l = 1.0 - ((kare_sizeyeni)*i * 2) - (kare_sizeyeni);
            //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            kare_ciz2(k, l, kare_sizeyeni, 0.0, 0.0, 0.7, 0.45);
            kacbirim++;
            y++;
        }
        x++;
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

                        glVertex2f(h - kare_sizeyeni, j - kare_sizeyeni);
                        glVertex2f(h + kare_sizeyeni, j - kare_sizeyeni);
                        glVertex2f(h + kare_sizeyeni, j + kare_sizeyeni);
                        glVertex2f(h - kare_sizeyeni, j + kare_sizeyeni);

                        glEnd();

                        glLineWidth(2.0);
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        kare_ciz(h, j, kare_sizeyeni, 0.9, 0.9, 0.9, 1.0);
                        sekilmatrisi[t + v - miny][r + c - minx] = 0;
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

                        glVertex2f(h - kare_sizeyeni, j - kare_sizeyeni);
                        glVertex2f(h + kare_sizeyeni, j - kare_sizeyeni);
                        glVertex2f(h + kare_sizeyeni, j + kare_sizeyeni);
                        glVertex2f(h - kare_sizeyeni, j + kare_sizeyeni);

                        glEnd();

                        glLineWidth(2.0);
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        kare_ciz(h, j, kare_sizeyeni, 0.9, 0.9, 0.9, 1.0);
                        sekilmatrisi[u + v - miny][r + c - minx] = 0;
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

                        glVertex2f(h - kare_sizeyeni, j - kare_sizeyeni);
                        glVertex2f(h + kare_sizeyeni, j - kare_sizeyeni);
                        glVertex2f(h + kare_sizeyeni, j + kare_sizeyeni);
                        glVertex2f(h - kare_sizeyeni, j + kare_sizeyeni);

                        glEnd();

                        glLineWidth(2.0);
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        kare_ciz(h, j, kare_sizeyeni, 0.9, 0.9, 0.9, 1.0);
                        sekilmatrisi[v + t - miny][y + c - minx] = 0;
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

                        glVertex2f(h - kare_sizeyeni, j - kare_sizeyeni);
                        glVertex2f(h + kare_sizeyeni, j - kare_sizeyeni);
                        glVertex2f(h + kare_sizeyeni, j + kare_sizeyeni);
                        glVertex2f(h - kare_sizeyeni, j + kare_sizeyeni);

                        glEnd();

                        glLineWidth(2.0);
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        kare_ciz(h, j, kare_sizeyeni, 0.9, 0.9, 0.9, 1.0);
                        sekilmatrisi[v + u - miny][c + y - minx] = 0;
                        kacbirim--;
                    }

                }
            }

        }

        a += 2;


    }
    
    karebirim16x16(sekilmatrisi, dizi, uzunluk);
    karebirim8x8(sekilmatrisi, dizi, uzunluk);
    karebirim4x4(sekilmatrisi, dizi, uzunluk);
    karebirim2x2(sekilmatrisi, dizi, uzunluk);

    hesapyap(sekilmatrisi, dizi2, minx, maxy, n, m, kacbirim);

    

    for (int i = 0; i < n; i++) {
        free(sekilmatrisi[i]);
    }
    free(sekilmatrisi);




}

void hesapyap(int** matris, int* dizi, int minx, int miny, int n, int m, int kacbirim) {
    int bir = 0;
    int iki = 0;
    int dort = 0;
    int sekiz = 0;
    int onalti = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matris[i][j] != 0) {
                switch (matris[i][j]) {
                case 1:
                    bir++;
                    break;
                case 2:
                    iki++;
                    break;
                case 4:
                    dort++;
                    break;
                case 8:
                    sekiz++;
                    break;
                case 16:
                    onalti++;
                    break;
                }
            }
        }
    }

    int ikisayisi = iki / 2;
    int dortsayisi = dort / 4;
    int sekizsayisi = sekiz / 8;
    int onaltisayisi = onalti / 16;

    int sondajmaaliyeti = kacbirim * birimsondaj3;
    int depolamamaaliyeti = (bir + ikisayisi + dortsayisi + sekizsayisi + onaltisayisi) * birimplat3;
    int toplammaaliyet = sondajmaaliyeti + depolamamaaliyeti;
    int rezerv_alani = kacbirim * 10;
    int karzarar = rezerv_alani - toplammaaliyet;

    glColor4f(0.0, 0.0, 0.0, 1.0);
    glRasterPos2f(-1.0 + (float)(minx) * 0.03125f + 0.015625f, 1.0 - (float)(miny) * 0.03125f - 0.015625f);

    //char sondajmaaliyetiyazi[] = "Toplam sondaj maaliyeti : ";
    char sondajmaaliyetii[10];
    snprintf(sondajmaaliyetii, sizeof(sondajmaaliyetii), "%d", sondajmaaliyeti);

    //char sondajsayisiyazi[] = "Toplam sondaj sayisi : ";
    char sondajsayisi[10];
    snprintf(sondajsayisi, sizeof(sondajsayisi), "%d", kacbirim);

    //char platformmaaliyetiyazi[] = "Toplam platform maaliyeti : ";
    char platformmaaliyeti[10];
    snprintf(platformmaaliyeti, sizeof(platformmaaliyeti), "%d", depolamamaaliyeti);

    //char platformmsayisiyazi[] = "Toplam platform sayisi : ";
    char platformmsayisi[10];
    snprintf(platformmsayisi, sizeof(platformmsayisi), "%d", depolamamaaliyeti / birimplat3);

    char toplammaliyett[10];
    snprintf(toplammaliyett, sizeof(toplammaliyett), "%d", toplammaaliyet);
    char karzararr[10];
    snprintf(karzararr, sizeof(karzararr), "%d", karzarar);

    char* metinler[] = {
    "Toplam sondaj maaliyeti : ",
    "Toplam sondaj sayisi : ",
    "Toplam platform maaliyeti : ",
    "Toplam platform sayisi : ",
    "Toplam maaliyet : ",
    "Toplam kar zarar durumu : "
    };

    int degerler[] = {
        sondajmaaliyeti,
        kacbirim,
        depolamamaaliyeti,
        depolamamaaliyeti / birimplat3,
        toplammaaliyet,
        karzarar
    };

    for (int i = 0; i < 6; i++) {
        glRasterPos2f(-1.0 + (float)(minx) * 0.03125f + 0.015625f, 1.0 - (float)(miny) * 0.03125f - 0.015625f * i * 2);

        for (int j = 0; metinler[i][j] != '\0'; j++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, metinler[i][j]);
        }

        char degerMetni[10];
        snprintf(degerMetni, sizeof(degerMetni), "%d", degerler[i]);

        for (int j = 0; degerMetni[j] != '\0'; j++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, degerMetni[j]);
        }
    }

    glRasterPos2f(0.0f, 0.0f);

}




int olurmu(int** matris, int i, int j, int kac, int n, int m) {
    int a = i + kac;
    int b = j + kac;
    if (a > n) {
        a = n;
    }
    if (b > m) {
        b = m;
    }

    for (int x = i; x < a; x++) {
        for (int y = j; y < b; y++) {
            if (matris[x][y] != 1) {
                return 0;
            }
        }
    }

    for (int x = i; x < a; x++) {
        for (int y = j; y < b; y++) {
            matris[x][y] = kac;
        }
    }

    return 1;
}

void karebirim2x2(int** matris, int dizi[], int uzunluk) {
    int minx = dizi[0];
    int miny = dizi[1];
    int maxx = dizi[0];
    int maxy = dizi[1];

    for (int i = 2; i < uzunluk; i += 2) {
        if (dizi[i] != 0) {
            if (dizi[i] < minx) {
                minx = dizi[i];
            }
            if (dizi[i] > maxx) {
                maxx = dizi[i];
            }
        }
    }

    for (int i = 3; i < uzunluk; i += 2) {
        if (dizi[i] != 0) {
            if (dizi[i] < miny) {
                miny = dizi[i];
            }
            if (dizi[i] > maxy) {
                maxy = dizi[i];
            }
        }
    }
    int n = maxy - miny;
    int m = maxx - minx;

    for (int i = 0; i < n; i++) {
        if (i + 2 <= n) {
            for (int j = 0; j < m; j++) {
                if (j + 2 <= m) {
                    if (matris[i][j] == 1) {
                        if (olurmu(matris, i, j, 2, n, m) == 1) {
                            float x = -1.0 + (0.03125f * (minx + j + 1));
                            float y = 1.0 - (0.03125f * (miny + i + 1));
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            kare_ciz3(x, y, kare_sizeyeni * 2, 1.0, 0.0, 0.0, 0.5);


                        }
                    }

                }

            }

        }

    }
}



void karebirim4x4(int** matris, int dizi[], int uzunluk) {
    int minx = dizi[0];
    int miny = dizi[1];
    int maxx = dizi[0];
    int maxy = dizi[1];

    for (int i = 2; i < uzunluk; i += 2) {
        if (dizi[i] != 0) {
            if (dizi[i] < minx) {
                minx = dizi[i];
            }
            if (dizi[i] > maxx) {
                maxx = dizi[i];
            }
        }
    }

    for (int i = 3; i < uzunluk; i += 2) {
        if (dizi[i] != 0) {
            if (dizi[i] < miny) {
                miny = dizi[i];
            }
            if (dizi[i] > maxy) {
                maxy = dizi[i];
            }
        }
    }
    int n = maxy - miny;
    int m = maxx - minx;

    for (int i = 0; i < n; i++) {
        if (i + 4 <= n) {
            for (int j = 0; j < m; j++) {
                if (j + 4 <= m) {
                    if (matris[i][j] == 1) {
                        if (olurmu(matris, i, j, 4, n, m) == 1) {
                            float x = -1.0 + (0.03125f * (minx + j + 2));
                            float y = 1.0 - (0.03125f * (miny + i + 2));
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            kare_ciz3(x, y, kare_sizeyeni * 4, 0.0, 0.0, 1.0, 0.5);


                        }
                    }

                }

            }

        }

    }
}

void karebirim8x8(int** matris, int dizi[], int uzunluk) {
    int minx = dizi[0];
    int miny = dizi[1];
    int maxx = dizi[0];
    int maxy = dizi[1];

    for (int i = 2; i < uzunluk; i += 2) {
        if (dizi[i] != 0) {
            if (dizi[i] < minx) {
                minx = dizi[i];
            }
            if (dizi[i] > maxx) {
                maxx = dizi[i];
            }
        }
    }

    for (int i = 3; i < uzunluk; i += 2) {
        if (dizi[i] != 0) {
            if (dizi[i] < miny) {
                miny = dizi[i];
            }
            if (dizi[i] > maxy) {
                maxy = dizi[i];
            }
        }
    }
    int n = maxy - miny;
    int m = maxx - minx;

    for (int i = 0; i < n; i++) {
        if (i + 8 <= n) {
            for (int j = 0; j < m; j++) {
                if (j + 8 <= m) {
                    if (matris[i][j] == 1) {
                        if (olurmu(matris, i, j, 8, n, m) == 1) {
                            float x = -1.0 + (0.03125f * (minx + j + 4));
                            float y = 1.0 - (0.03125f * (miny + i + 4));
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            kare_ciz3(x, y, kare_sizeyeni * 8, 0.0, 1.0, 0.0, 0.5);


                        }
                    }

                }

            }

        }

    }
}

void karebirim16x16(int** matris, int dizi[], int uzunluk) {
    int minx = dizi[0];
    int miny = dizi[1];
    int maxx = dizi[0];
    int maxy = dizi[1];

    for (int i = 2; i < uzunluk; i += 2) {
        if (dizi[i] != 0) {
            if (dizi[i] < minx) {
                minx = dizi[i];
            }
            if (dizi[i] > maxx) {
                maxx = dizi[i];
            }
        }
    }

    for (int i = 3; i < uzunluk; i += 2) {
        if (dizi[i] != 0) {
            if (dizi[i] < miny) {
                miny = dizi[i];
            }
            if (dizi[i] > maxy) {
                maxy = dizi[i];
            }
        }
    }
    int n = maxy - miny;
    int m = maxx - minx;

    for (int i = 0; i < n; i++) {
        if (i + 16 <= n) {
            for (int j = 0; j < m; j++) {
                if (j + 16 <= m) {
                    if (matris[i][j] == 1) {
                        if (olurmu(matris, i, j, 16, n, m) == 1) {
                            float x = -1.0 + (0.03125f * (minx + j + 8));
                            float y = 1.0 - (0.03125f * (miny + i + 8));
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            kare_ciz3(x, y, kare_sizeyeni * 16, 1.0, 0.0, 1.0, 0.5);


                        }
                    }

                }


            }

        }

    }
}