#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "biblio.h"

void initialiser_paquet(Paquet p)
{
    int carte_num=0;
    for (int i=0; i<NB_COULEURS; i++)
    {
        for (int j=0; j<TAILLE_MAX_MAIN; j++)
        {
           p.carte[carte_num].couleur=i;
           p.carte[carte_num].chiffre=j;
           p.carte[carte_num].utilisee=0;
           carte_num++;
        }
    }
}


void distribuer_carte(Partie partie)
{
    int j=0;
    while (j<partie.nb_joueur)
    {
        int c=0;
        while (c<TAILLE_MAX_MAIN)
        {
            int position;
            while(1) //boucle infinie pour vérifier que la carte n'est pas deja utilisée
            {
                position=rand()% NB_CARTES_MAX;
                if (partie.paquet.carte[position].utilisee==0)
                    break;
            }
            partie.paquet.carte[position].utilisee=1;
            partie.joueur[j].main[c]=partie.paquet.carte[position];  //donne la carte au joueur
            c++;
        }
        partie.joueur[j].nb_cartes=TAILLE_MAX_MAIN;
        j++;
    }
}
