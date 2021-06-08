
#include "jatek.h"
#include "debugmalloc.h"

void felszabaditas(Jatek *amoba) {
    for (int y = 0; y <= amoba->sor; ++y)
        free(amoba->palya[y]);
    free(amoba->palya);
}
