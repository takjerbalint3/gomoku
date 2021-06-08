#ifndef JATEKALLAS_H
#define JATEKALLAS_H
#include <stdbool.h>


//Az inspirációt az előadások anyagából vettem.

/** A pálya egy cellája, vagy játékos. */
typedef enum Babuk {
    b_ures = 0, b_kor = 1, b_iksz=  2
} Babuk;

/** A pályán egy pozíció, x és y koordináta. */
typedef struct Pozicio {
    int x, y;
} Pozicio;

/** A játékállásról minden információ. */
typedef struct Jatek {
    int oszlop;
    int sor;
    int gep;
    int jatekos;
    int ki_kezd;
    int suly;
    bool jatek_vege;
    Babuk **palya;
    Babuk kovetkezo;
    bool vege;
    char kor_nev[30];
    char iksz_nev[30];
} Jatek;

void kezdes(Jatek *amoba);
char const * jatek_kovetkezo_neve(Jatek const *amoba);
bool jatek_lep(Jatek *amoba, Pozicio p);

void egymas_mellett_ketto(Jatek*amoba, int**ertek ,int y, int x, int keresett);
bool dontetlen_e(Jatek *amoba);
bool gep_lep(Jatek *amoba);
void jatek_kirajzol(Jatek const *amoba);
Pozicio pozicio_beolvas(Jatek *amoba);
void jatek(Jatek *amoba);



#endif
