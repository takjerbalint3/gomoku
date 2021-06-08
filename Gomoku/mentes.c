#include <stdio.h>
#include <stdlib.h>
#include "mentes.h"
#include <dirent.h>
#include "jatek.h"
#include "memoriakezeles.h"
#include "debugmalloc.h"
#include "nezet.h"
#include <time.h>
//Az inspirációt az előadások anyagából vettem.
/**
 *  Felamoba->sorolja a mappában található fileok nevét, majd az egyik fájl nevét beírva meghívja a jatek_betolt függvényt.
 */
bool betolt_mentes(Jatek *amoba) {
    DIR *d = opendir(".//mentes");  /* melyik mappát */
    if (d == NULL) {
        return false;
        perror("Nem sikerült megnyitni");
    } else {
        struct dirent *dir;
        int szamlalo = 0;
        printf("Valasszon mentest a fajlnev beirasaval: \n");
        while ((dir = readdir(d)) != NULL) {
            ++szamlalo;
            printf("%d fajl: %s\n",szamlalo, dir->d_name);
        }
        closedir(d);
        char filenev[10];
        scanf("%s", filenev);
        return jatek_betolt(amoba,  filenev);

    }

}
/**
  *  Elmenti egy adott játékállás tulajdonságait fájlba, illetve mindig egy új fájlnevet hoz létre, tekintve hogy 100 nál nem játszunk többet, ekkor biztosan lesz két megegyező fájlnév
  *  @param amoba Dinamikus tömb aminek ztulajdonságait mentjük fájlba
  */
bool mentes(Jatek *amoba) {
    srand(time(0));
    int random = rand() % 99 + 1;
    char randomc[3];
    sprintf(randomc, "%d", random);
    char filenev[12];
    strcpy(filenev, "amoba");
    strcat(filenev, randomc);
    strcat(filenev, ".txt");
    printf("A mentett jatek fajlneve: %s\n", filenev);
    FILE *fp;
    chdir(".//mentes");
    fp = fopen(filenev, "wt");
    if (fp == NULL)
        return false;
    int sz;
    if(amoba->vege) {
        sz = 1;
    }
    else {
        sz = 0;
    }
    fprintf(fp, "%s\n", amoba->kor_nev);
    fprintf(fp, "%s\n", amoba->iksz_nev);
    fprintf(fp, "%d\n", sz);
    fprintf(fp, "%d\n", (int) amoba->kovetkezo);
    fprintf(fp, "%d\n", (int) amoba->gep);
    fprintf(fp, "%d\n", (int) amoba->jatekos);
    fprintf(fp, "%d\n", (int) amoba->suly);
    fprintf(fp, "%d\n", (int) amoba->ki_kezd);
    fprintf(fp, "%d\n", amoba->sor);
    fprintf(fp, "%d\n", amoba->oszlop);
    for (int y = 0; y < amoba->sor; ++y) {
        for (int x = 0; x < amoba->oszlop; ++x)
            fprintf(fp, "%d ", (int) amoba->palya[y][x]);
        fprintf(fp, "\n");
    }
    fclose(fp);
    chdir("..");
    felszabaditas(amoba);
    kezdo_nezet(amoba);
    return true;
}

/**
 *  Betölti az adott fájlból a korábbi játék tulajdonságait, majd bezárja a fájlt.
 *  @param amoba A játék struktúra amibe betöltjük az értékeket
 *  @param fajlnev A fájl neve amiből a beolvasás történik
 */
bool jatek_betolt(Jatek *amoba, char *fajlnev) {
    FILE *fp;
    chdir(".//mentes");
    char txt[15];
    sprintf(txt, "%s.txt", fajlnev);
    fp = fopen(txt, "rt");
    if (fp == NULL)
        return false;
    fscanf(fp, " %[^\n]", amoba->kor_nev);
    fscanf(fp, " %[^\n]", amoba->iksz_nev);

    int vege;
    int ki_jon;
    int sor;
    int oszlop;
    int gep;
    int jatekos;
    int suly;
    int ki_kezd;
    fscanf(fp, "%d", &vege);
    fscanf(fp, "%d", &ki_jon);
    fscanf(fp, "%d", &gep);
    fscanf(fp, "%d", &jatekos);
    fscanf(fp, "%d", &suly);
    fscanf(fp, "%d", &ki_kezd);
    fscanf(fp, "%d", &sor);
    fscanf(fp, "%d", &oszlop);

    amoba->sor = sor;
    amoba->oszlop = oszlop;
    if(vege == 1)
        amoba->vege = true;
    amoba->palya = (Babuk**) malloc((amoba->sor+1) * sizeof(Babuk*));
    if(amoba->palya == NULL) {
        printf("Nem sikerült memóriát foglalni!\n");
        return false;
    }
    for (int y = 0; y <= amoba->sor; ++y) {
        amoba->palya[y] = (Babuk*) malloc(amoba->oszlop * sizeof(Babuk));
        if(amoba->palya[y] == NULL) {
            printf("Nem sikerült memóriát foglalni!\n");
            return false;
        }
    }
    amoba->kovetkezo = (Babuk) ki_jon;
    for (int y = 0; y < amoba->sor; ++y) {
        for (int x = 0; x < amoba->oszlop; ++x) {
            int c;
            fscanf(fp, "%d", &c);
            amoba->palya[y][x] = (Babuk) c;
        }
    }
    fclose(fp);
    jatek(amoba);

    return true;
}
