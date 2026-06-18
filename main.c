#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "biblio.h"


// TEST AFFICHAGE MAIN D'UN JOUEUR
/*
int main()
{
    plein_ecran();

    srand(time(NULL));

    int couleur_carte, valeur_carte;

    int tab[] = {BLEU, ROUGE, ROSE, VERT, MARRON, JAUNE};

    for(int i = 1; i<10; i++)
    {
        couleur_carte = tab[rand() % 5 + 0];
        valeur_carte = rand() % 9 + 1;
        dessiner_carte_du_jeu(1, 5+PAS_ENTRE_CARTES*i, couleur_carte, valeur_carte);
    }



    positionner_curseur(15,6);
    return 0;
}
*/

int main()
{
    plein_ecran();
    dessiner_logo_odin(1,70);

    positionner_curseur(90,6);
    return 0;
}
