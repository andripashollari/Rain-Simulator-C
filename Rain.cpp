#include <graphics.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

unsigned long int count = 0;
time_t t;
FILE *fptr;
struct pika_shiu {
    int x;
    int y;
};
struct pika_shiu vektori[500];
int temperatura, era, drejtimi;

void shiu(int, int, int, int);
void levizshiun();
void nrpikave_nefile();

int main() {
    srand(time(NULL));
    printf("Ju lutem jepni temperaturen ne grade Celcius: ");
    scanf("%d", &temperatura);
    printf("\nJu lutem jepni eren (kendi me boshtin vertikal): ");
    scanf("%d", &era);
    printf("\nJu lutem jepni drejtimin (0 per majtas dhe 1 per djathtas): ");
    scanf("%d", &drejtimi);

    initwindow(getmaxwidth(), 700, "Raindrop Simulation", true, true);
    levizshiun();
    nrpikave_nefile();
    closegraph();
    getch();
}

void shiu(int x, int y, int kendi, int drejtimi) {
    if (kendi == 0) {
        line(x, y, x, y + 15);
    } else {
        double rad = (double)kendi * M_PI / 180;
        if (drejtimi){
            line(x, y, x - 15 * cos(rad), y - 15 * sin(rad));
        } else {
            line(x, y, x + 15 * cos(rad), y - 15 * sin(rad));
        }
    }
}

void nrpikave_nefile() {
    fptr = fopen("nripikave_teshiut.txt", "w");
    fprintf(fptr, "Numri i pikave te shiut/bores eshte:%lu", count);
    fclose(fptr);
}

void levizshiun() {
    while (1) {
        for (int j = 0; j < 500; j++) {
            vektori[j].x = rand() % getmaxx();
            vektori[j].y = rand() % getmaxy();
             if (temperatura > 0) {
                    shiu(vektori[j].x, vektori[j].y, era, drejtimi);
                    count++;
                } else {
                    circle(vektori[j].x, vektori[j].y, 3.5);
                    count++;
                }
        }

        while (!kbhit()) {
            cleardevice();

            for (int j = 0; j < 500; j++) {
                vektori[j].y += 30;

                if (temperatura > 0) {
                    shiu(vektori[j].x, vektori[j].y, era, drejtimi);
                } else {
                    circle(vektori[j].x, vektori[j].y, 3.5);
                }

                if (vektori[j].y > getmaxy()) {
                    vektori[j].y = 0;
                    vektori[j].x = rand() % getmaxx();
                    count++;
                }
            }
            nrpikave_nefile();
            delay(10);
        }

        char key = getch();
        if (key == 't' || key == 'T') {
            printf("\nJu lutem jepni temperaturen ne grade Celcius: ");
            scanf("%d", &temperatura);
        } else if (key == 'e' || key == 'E') {
            printf("\nJu lutem jepni eren (kendi me boshtin vertikal): ");
            scanf("%d", &era);
        } else if (key == 'd' || key == 'D') {
            printf("\nJu lutem jepni drejtimin (0 per majtas dhe 1 per djathtas): ");
            scanf("%d", &drejtimi);
        } else if (key == 'c' || key == 'C') {
            return;
        }
    }
}
