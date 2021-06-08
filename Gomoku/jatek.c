#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "jatek.h"
#include "nezet.h"
#include "mentes.h"
#include "debugmalloc.h"
#include "memoriakezeles.h"



//Az inspirációt az előadások anyagából vettem.
/**
 * A pálya összes elemét üresre állítja, beállítja a kezdő játékost.
 */


void kezdes(Jatek *amoba) {
    amoba->kovetkezo = b_kor;

    for (int y = 0; y < amoba->sor; ++y)
        for (int x = 0; x < amoba->oszlop; ++x)
            amoba->palya[y][x] = b_ures;
}

/**
 * Megadja annak a játékosnak a nevét, aki a következõ lépést teszi majd.
 * @return A játékos neve.
 */
char const * jatek_kovetkezo_neve(Jatek const *amoba) {
    switch (amoba->kovetkezo) {
        case b_kor:
            return amoba->kor_nev;
        case b_iksz:
            return amoba->iksz_nev;
        default:
            assert(false);  // lehetetlen esemény
    }

}


/**
 * Megadja, ki a következõ játékos, ha most a megadott játékos lépett.
 */
Babuk kovetkezo(Babuk j) {
    switch (j) {
        case 1:
            return 2;
        case 2:
            return 1;
        default:
            assert(false);  // ilyen nem történhet
    }

}


/**
 * Megmondja, hogy egy adott pozícióból adott irányba indulva
 * az adott cella van-e mind az öt helyen.
 * @param p A pozició amiből kezdve vizsgáljuk a 4 irányt
 * @param c A bábu típusa amire a vizsgálat zajlik
 */

bool nyert_e(Jatek const *amoba, Pozicio p, Babuk c) {
    int db = 1;

    for(int i = 1; (p.y -i >= 0 && p.y -i < amoba->sor) && amoba->palya[p.y - i][p.x] == c;  i++) {
        if(amoba->palya[p.y - i][p.x] == c)
            db++;
    }
    for(int i = 1; (p.y +i >= 0 && p.y +i < amoba->sor) && amoba->palya[p.y + i][p.x] == c;  i++) {
        if(amoba->palya[p.y + i][p.x] == c)
            db++;
    }
    if(db == 5)
        return true;
    else
        db = 1;


    for(int i = 1; amoba->palya[p.y][p.x - i] == c && (p.x - i >= 0 && p.x -i < amoba->oszlop);  i++) {
        if(amoba->palya[p.y][p.x- i] == c)
            db++;
    }
    for(int i = 1; amoba->palya[p.y][p.x + i] == c && (p.x +i >= 0 && p.x +i < amoba->oszlop);  i++) {
        if(amoba->palya[p.y][p.x + i] == c)
            db++;
    }
    if(db == 5)
        return true;
    else
        db = 1;


    for(int i = 1;  (p.x - i >= 0 && p.x -i < amoba->oszlop) && (p.y -i >= 0 && p.y -i < amoba->sor)&&amoba->palya[p.y- i][p.x - i] == c;  i++) {
        if(amoba->palya[p.y- i][p.x- i] == c)
            db++;
    }
    for(int i = 1; (p.x +i >= 0 && p.x +i < amoba->oszlop) && (p.y +i >= 0 && p.y +i < amoba->sor) &&amoba->palya[p.y + i][p.x + i] == c;  i++) {
        if(amoba->palya[p.y + i][p.x + i] == c)
            db++;
    }
    if(db == 5)
        return true;
    else
        db = 1;


    for(int i = 1;  (p.x + i >= 0 && p.x +i < amoba->oszlop) && (p.y -i >= 0 && p.y -i < amoba->sor)&&amoba->palya[p.y- i][p.x + i] == c;  i++) {
        if(amoba->palya[p.y- i][p.x+ i] == c)
            db++;
    }
    for(int i = 1; (p.x -i >= 0 && p.x -i < amoba->oszlop) && (p.y +i >= 0 && p.y +i < amoba->sor) && amoba->palya[p.y + i][p.x - i] == c ;  i++) {
        if(amoba->palya[p.y + i][p.x - i] == c)
            db++;
    }
    if(db == 5)
        return true;
    else
        return false;

}



/**
 * Lép a megadott játékos a megadott pozícióra.
 * @return true, ha ezzel a lépésével megnyeri a játékot.
 */
bool jatek_lep(Jatek *amoba, Pozicio p) {
    bool nyert = false;
    if(amoba->palya[p.y][p.x] == b_ures) {
        amoba->palya[p.y][p.x] = amoba->kovetkezo;
        nyert = nyert_e(amoba, p, amoba->kovetkezo);
        if(nyert) {
            return nyert;
        } else {
            amoba->kovetkezo = kovetkezo(amoba->kovetkezo);
            return nyert;
        }
    } else {
        printf(
                "------------------------------ \n"
               "|                             |\n"
               "|     Ezen a helyen babu all  |\n"
               "|   adj meg egy uj lepest     |\n"
               "|                             |\n"
               "------------------------------ \n");
        Pozicio p =pozicio_beolvas(amoba);
        jatek_lep(amoba, p);
    }
    return nyert;

}

/**
 * Szabványos kimeneten megjeleníti a játékállást.
 */
void jatek_allas(Jatek const *amoba) {
    /* ebben a tömbben pont ugyanolyan amoba->sorrendben vannak, mint az enum értékei */
    static char const cella_kep[] = { '.', 'O', 'X' };

    printf("  \n");
    for(int i = 0; i <= amoba->oszlop; ++i)
        printf("%2d ", i);
    printf("\n");
    for (int y = 1; y <= amoba->sor; ++y) {
        printf("%2d ", y);
        for (int x = 0; x < amoba->oszlop; ++x) {
            printf("%2c ", cella_kep[amoba->palya[y-1][x]]);
        }
        printf("\n");
    }
}

/**
 * Beolvassa a koordínátákat a billentyűzetről
 * @return A beolvasott koordináták pozícióját adja vissza.
 */
Pozicio pozicio_beolvas(Jatek *amoba) {
    Pozicio p;
    p.y = 0;
    p.x = 0;
    scanf("%d %d", &p.y, &p.x);
    if(p.y > amoba->sor || p.x > amoba->oszlop) {
        printf("Hibas beolvasas, probald ujra\n");
        pozicio_beolvas(amoba);
    }
    p.y--;
    p.x--;
    return p;
}

void egymas_mellett_harom(Jatek*amoba, int**ertek ,int y, int x, int keresett) {

    if( ((x+3 < amoba->oszlop && x-1 > 0) && (y-3 > 0 && y+1 < amoba->sor)) && (amoba->palya[y-1][x+1] == keresett) && (amoba->palya[y-2][x+2] == keresett)) {
        ertek[y-3][x+3] +=75;
        ertek[y+1][x-1] +=75;
    }

    if( (y+3 < amoba->sor && y-1 >= 0) && (amoba->palya[y+1][x] == keresett) && (amoba->palya[y+2][x] == keresett))  {

        ertek[y+3][x] +=75;
        ertek[y-1][x] +=75;
    }
    if( ((x+3 < amoba->oszlop && x-1 > 0) && (y+3 < amoba->sor && y-1 > 0)) && (amoba->palya[y+1][x+1] == keresett) && (amoba->palya[y+2][x+2] == keresett)) {
        ertek[y+3][x+3] +=75;
        ertek[y-1][x-1] +=75;
    }
    if( (x+3 < amoba->oszlop && x-1 > 0) && (amoba->palya[y][x+1] == keresett) && (amoba->palya[y][x+2] == keresett)  ) {
        ertek[y][x+3] +=75;
        ertek[y][x-1] +=75;
    }
}

void egymas_mellett_ketto(Jatek*amoba, int**ertek ,int y, int x, int keresett) {

    if( ((x+2 < amoba->oszlop && x-1 > 0) && (y-2 > 0 && y+1 < amoba->sor)) && amoba->palya[y-1][x+1] == keresett) {
        ertek[y-2][x+2] +=20;
        ertek[y+1][x-1] +=20;
    }

    if( (y+2 < amoba->sor && y-1 >= 0) && amoba->palya[y+1][x] == keresett)  {

        ertek[y+2][x] +=20;
        ertek[y-1][x] +=20;
    }
    if( ((x+2 < amoba->oszlop && x-1 > 0) && (y+2 < amoba->sor && y-1 > 0)) && amoba->palya[y+1][x+1] == keresett) {
        ertek[y+2][x+2] +=20;
        ertek[y-1][x-1] +=20;
    }
    if( (x+2 < amoba->oszlop && x-1 > 0) && amoba->palya[y][x+1] == keresett ) {
        ertek[y][x+2] +=20;
        ertek[y][x-1] +=20;
    }
}

bool dontetlen_e(Jatek *amoba) {
    for (int y = 0; y < amoba->sor; ++y) {
        for (int x = 0; x < amoba->oszlop; ++x) {
            if(amoba->palya[y][x] == b_ures)
                return false;
        }
    }
    return true;
}


Pozicio legjobb_lepes(Jatek *amoba) {
    Pozicio legjobb;
    legjobb.x = 0;
    legjobb.y = 0;
    int **ertek;
    ertek = (int**) malloc((amoba->sor+1) * sizeof(int*));
    for (int y = 0; y <= amoba->sor; ++y)
        ertek[y] = (int*) malloc(amoba->oszlop * sizeof(int));

    for (int y = 0; y < amoba->sor; ++y)
        for (int x = 0; x < amoba->oszlop; ++x)
            ertek[y][x] = 0;

    if(amoba->ki_kezd == amoba->gep) {

        legjobb.y = amoba->sor / 2 - 1;
        legjobb.x = amoba->oszlop / 2 - 1;
        amoba->ki_kezd = 0;
    } else {
        for (int y = 0; y < amoba->sor; ++y) {
            for (int x = 0; x < amoba->oszlop; ++x) {

                if (amoba->palya[y][x] == amoba->gep) {
                    ertek[y][x] = -200;

                    egymas_mellett_harom(amoba, ertek, y ,x, amoba->gep);
                    egymas_mellett_ketto(amoba, ertek, y ,x, amoba->gep);

                    for (int i = 1; i <= 4; i++) {
                        if ((y - i >= 0 && y + i < amoba->sor) && (x + i < amoba->oszlop && x - i >= 0)) {
                            ertek[y + i][x + i] += 10 + amoba->suly- 2*i;
                            ertek[y + i][x - i] += 10 + amoba->suly - 2*i;
                            ertek[y + i][x] += 10 + amoba->suly - 2*i;
                            ertek[y - i][x + i] += 10 + amoba->suly - 2*i;
                            ertek[y - i][x - i] += 10  + amoba->suly - 2*i;
                            ertek[y - i][x] += 10 + amoba->suly - 2*i;
                            ertek[y][x + i] += 10 + amoba->suly - 2*i;
                            ertek[y][x - i] += 10 + amoba->suly - 2*i;
                        }
                    }
                }

                if (amoba->palya[y][x] == amoba->jatekos) {
                    ertek[y][x] = -200;

                    egymas_mellett_harom(amoba, ertek, y ,x, amoba->jatekos);
                    egymas_mellett_ketto(amoba, ertek, y ,x, amoba->jatekos);

                    for (int i = 1; i <= 4; i++) {
                        if ((y - i >= 0 && y + i < amoba->sor) && (x + i < amoba->oszlop && x - i >=0 )) {
                            ertek[y + i][x + i] += 10 - 2*i - amoba->suly;
                            ertek[y + i][x - i] += 10 - 2*i - amoba->suly;
                            ertek[y + i][x] += 10 - 2*i - amoba->suly;
                            ertek[y - i][x + i] += 10 - 2*i - amoba->suly;
                            ertek[y - i][x - i] += 10 - 2*i - amoba->suly;
                            ertek[y - i][x] += 10 - 2*i - amoba->suly;
                            ertek[y][x + i] += 10 - 2*i - amoba->suly;
                            ertek[y][x - i] += 10 - 2*i - amoba->suly;
                        }
                    }

                }
            }
        }

        int legnagyobb = 0;

        for (int y = 0; y < amoba->sor; ++y) {
            for (int x = 0; x < amoba->oszlop; ++x) {
                if(ertek[y][x] > legnagyobb) {
                    legnagyobb = ertek[y][x];
                    legjobb.y = y;
                    legjobb.x = x;
                }
            }
        }
    }

    for (int y = 0; y <= amoba->sor; ++y)
        free(ertek[y]);
    free(ertek);
    return legjobb;
}

bool gep_lep(Jatek *amoba) {
    bool nyert = false;
    Pozicio g = legjobb_lepes(amoba);
    amoba->palya[g.y][g.x] = amoba->kovetkezo;
    nyert = nyert_e(amoba, g, amoba->kovetkezo);
    if(nyert)
        return nyert;
    else {
        amoba->kovetkezo = kovetkezo(amoba->kovetkezo);
        return nyert;
    }
}



/**
  * A függvény a játék menetét viszi véghez a fentebbi részfüggvények segítségével
  *
  */

void jatek(Jatek *amoba) {
    int switch2;
    if(strcmp(jatek_kovetkezo_neve(amoba),"Gep") == 0) {
        if (gep_lep(amoba)) {
            amoba->jatek_vege = true;
            amoba->vege = true;
        }
        else if(dontetlen_e(amoba)) {
            jatek_allas(amoba);
            printf("Nincs tobb hely, a jatek dontetlen.\n");
            return;
        }
    } else {
        int szam;
        jatek_allas(amoba);
        printf("------------------------------------------------------------ \n"
               "|                             |    Hova szeretnel lepni?    |\n"
               "  Kovetkezo jatekos: %s            Sor Oszlop         \n"
               "|                             |                             |\n"
               "------------------------------ ------------------------------\n",
               jatek_kovetkezo_neve(amoba));
        Pozicio p = pozicio_beolvas(amoba);
        if(jatek_lep(amoba, p)){
            amoba->jatek_vege = true;
            amoba->vege = true;
        }
        else if(dontetlen_e(amoba)) {
            jatek_allas(amoba);
            printf("Nincs tobb hely, a jatek dontetlen.\n");
            return;
        }
        jatek_allas(amoba);
        printf("------------------------------ \n"
               "|        (1)Mentes            |\n"
               "|      (2)Kezdo menu          |\n"
               "| Folytatashoz barmi mas szam |\n"
               "------------------------------ \n");
        scanf("%d", &szam);
        switch(szam) {
        case 1:
            if(mentes(amoba))
                printf("Sikeres mentes.");
            else {
                printf("Nem sikerult a mentes");
                return;
            }
            break;
        case 2:
            felszabaditas(amoba);
            return;
            break;
        default:
            break;
        }


    }
    if(!amoba->jatek_vege) {
        jatek(amoba);
    }
    else {
        felszabaditas(amoba);
        printf("--------------------------------------------- \n"
               "|              Vege a jateknak               |\n"
               "|                 A gyoztes                  |\n"
               "|                  %s                      |\n"
               "| Szeretnel megint jatszani?(Igen(1)/Nem(2)) |\n"
               "|                 Kilepes(9)                 |\n"
               "--------------------------------------------- \n", jatek_kovetkezo_neve(amoba));
        scanf("%d", &switch2);
        int sor, oszlop;
        switch(switch2)
        {
            case 1:
                amoba->jatek_vege = false;
                amoba->vege = false;
                printf("------------------------------ \n"
                       "|                             |\n"
                       "|  Adja meg a palya meretet!  |\n"
                       "|         Sor  Oszlop         |\n"
                       "|                             |\n"
                       "------------------------------ \n");
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
                jatek_nezet( amoba);
                break;
            case 2:
                return;
                break;
            case 9:
                exit(0);

            default:
                amoba->jatek_vege = false;
                amoba->vege = false;
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
                jatek_nezet( amoba);
        }
    }


}
