#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "odin.h"

void initialiser_cartes(Carte carte[TAILLE_MAX_MAIN][NB_COULEURS])
{
    for (int i=0; i<NB_COULEURS; i++)
    {
        for (int j=0; j<TAILLE_MAX_MAIN; j++)
        {
            carte[j][i].chiffre=j;
            carte[j][i].couleur=i;
        }
    }
}
