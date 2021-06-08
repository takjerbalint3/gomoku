#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "nezet.h"
#include "jatek.h"
#include "debugmalloc.h"



int main(void)
{
    Jatek amoba;
    amoba.jatek_vege = false;
    kezdo_nezet(&amoba);
    return 0;
}
