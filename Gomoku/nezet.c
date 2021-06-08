#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "nezet.h"
#include "mentes.h"
#include "memoriakezeles.h"
#include "debugmalloc.h"



void kezdo_nezet(Jatek *amoba) {
    while(1) {
        int static switch1;
    int sor, oszlop;
    printf("------------------------------ \n"
           "|                             |\n"
           "| 1. Korabbi jatekok betoltese|\n"
           "| 2.        Uj jatek          |\n"
           "|        (9) Kilepes          |\n"
           "|                             |\n"
           "------------------------------ \n");

    scanf("%d", &switch1);

    switch(switch1)
    {
        case 1 :

            if(betolt_mentes(amoba))
                printf("Sikeres betöltés");
            else
                printf("Sikertelen betöltés");
            break;
        case 2 :
            printf("------------------------------ \n"
                   "|                             |\n"
                   "|  Adja meg a palya meretet!  |\n"
                   "|         Sor  Oszlop         |\n"
                   "|                             |\n"
                   "------------------------------ \n"
            );
            scanf("%d %d", &sor, &oszlop);
            amoba->sor = sor;
            amoba->oszlop = oszlop;
            amoba->palya = (Babuk**) malloc((amoba->sor+1) * sizeof(Babuk*));
            if(amoba->palya == NULL) {
                printf("Nem sikerült memóriát foglalni!\n");
                exit(0);
            }
            for (int y = 0; y <= amoba->sor; ++y) {
                amoba->palya[y] = (Babuk*) malloc(amoba->oszlop * sizeof(Babuk));
                if(amoba->palya[y] == NULL) {
                    printf("Nem sikerült memóriát foglalni!\n");
                    exit(0);
                }
    }
            jatek_nezet(amoba);
            break;
        case 9 :
            exit(0);
            break;
        default: ;
            printf("------------------------------ \n"
                   "|                             |\n"
                   "|  Adja meg a palya meretet!  |\n"
                   "|         Sor   Oszlop        |\n"
                   "|                             |\n"
                   "------------------------------ \n"
            );
            scanf("%d %d", &sor, &oszlop);
            amoba->sor = sor;
            amoba->oszlop = oszlop;
            amoba->palya = (Babuk**) malloc((amoba->sor+1) * sizeof(Babuk*));
            if(amoba->palya == NULL) {
                printf("Nem sikerült memóriát foglalni!\n");
                exit(0);
            }
            for (int y = 0; y <= amoba->sor; ++y) {
                amoba->palya[y] = (Babuk*) malloc(amoba->oszlop * sizeof(Babuk));
                if(amoba->palya[y] == NULL) {
                    printf("Nem sikerült memóriát foglalni!\n");
                    exit(0);
                }
            }
            jatek_nezet(amoba);
            break;
    }
    }

}

void jatek_nezet(Jatek *amoba) {
    int switch2;
    char nev[32+1];
    printf("Hogy hivnak?\n");
    scanf("%s", nev);
    printf("------------------------------ \n"
           "|                             |\n"
           "|  Melyik Babuval szeretnel   |\n"
           "|     jatszani %s?        |\n"
           "|         (1)X /(2)O          |\n"
           "|        (9) Kilepes          |\n"
           "------------------------------ \n", nev);

    scanf("%d", &switch2);
    switch(switch2)
    {
        case 1:
            amoba->gep = 1;
            amoba->jatekos = 2;
            amoba->ki_kezd = amoba->gep;
            amoba->suly = 4;
            strcpy(amoba->kor_nev, "Gep");
            strcpy(amoba->iksz_nev, nev);
            break;
        case 2:
            amoba->gep = 2;
            amoba->jatekos = 1;
            amoba->ki_kezd = amoba->jatekos;
            amoba->suly = 0;
            strcpy(amoba->kor_nev, nev);
            strcpy(amoba->iksz_nev, "Gep");
            break;
        case 9:
            felszabaditas(amoba);
            exit(0);
            break;
        default:
            amoba->gep = 2;
            amoba->ki_kezd = amoba->jatekos;
            amoba->jatekos = 1;
            amoba->suly = 0;
            strcpy(amoba->kor_nev, nev);
            strcpy(amoba->iksz_nev, "Gep");
    }
    kezdes(amoba);
    jatek(amoba);

}
