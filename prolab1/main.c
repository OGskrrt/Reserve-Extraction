#include "freeglut.h"
#include "glut.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "opengl.h"
#include "opengl2.h"
#include <GL/glut.h>


size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    FILE* fp = (FILE*)userp;
    return fwrite(contents, size, nmemb, fp);
}
FILE* dataFile;
float kare_size;
void grafikciz(int dizi[], int uzunluk, int grafikNum);
void Curl(void);
void keyboard(unsigned char key);
int grafiknumarasi;
int birimsondaj;
int birimplat;


int main(int argc, char** argv) {

    printf("İstenilen satır numarasını giriniz. \n");

    scanf("%d", &grafiknumarasi);
    printf("Birim sondaj maaliyetini girniz. \n");
    scanf("%d", &birimsondaj);

    printf("Birim platform maaliyetini girniz. \n");

    scanf("%d", &birimplat);

    aktar(grafiknumarasi, birimsondaj, birimplat);

    Curl();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1500, 1500);
    glutCreateWindow("woahhh");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}


void Curl() {
    CURL* curl;
    CURLcode res;

    FILE* fp;
    char* url = "https://bilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt";
    char outfilename[] = "prolab1.txt";
    char outfilename2[] = "dafuck.txt";
    char outfilename3[] = "prolab2.txt";

    curl = curl_easy_init();

    if (curl) {
        fp = fopen(outfilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);

        if (res != CURLE_OK) {
            fprintf(stderr, "İndirme hatası: %s\n", curl_easy_strerror(res));
            return 1;
        }
    }
    else {
        fprintf(stderr, "CURL başlatma hatası\n");
        return 1;
    }

    printf("Veriler başarıyla indirildi ve '%s' dosyasına kaydedildi.\n", outfilename);

    

    //Curl_Devam();
}

void keyboard(unsigned char key) {
    switch (key)
        case 'w':
            ikinciasama();


}
