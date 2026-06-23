#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "bibliocomplet.h"

/*
================================================================
VERIFICATIONS
================================================================
*/

int coup_le_plus_grand(Partie *partie, int m)
 {
     int valeur_joueur;
     int valeur_milieu;

     valeur_milieu= calcul_num_pose(partie);
     valeur_joueur= calcul_num_choisi(partie, m);

     return valeur_joueur > valeur_milieu;
 }

int verif_conditions_de_jeu(int nb_cartes_jouees, Partie partie)
{
    if (nb_cartes_jouees<partie.pile_milieu.nb_carte_milieu || nb_cartes_jouees>partie.pile_milieu.nb_carte_milieu+1 )
    {
        return 1;    //utile pour la verif dans le main
    }
    return 0;
}

int verif_meme_couleur(Partie *partie, int m)
{
    int couleur_differente=0;
    int carte_meme_valeur=1;
    if (partie->joueur[m].nb_cartes_jouees>=2)
    {
        for (int a=0; a<partie->joueur[m].nb_cartes_jouees-1; a++)     //-1 sinon on depasse le tableau
        {
            if(partie->joueur[m].main[partie->joueur[m].choix[a]-1].chiffre!=partie->joueur[m].main[partie->joueur[m].choix[a+1 ]-1].chiffre)
            {
                carte_meme_valeur=0;
            }
        }
        if (carte_meme_valeur==0)
        {
           for (int i=0; i<partie->joueur[m].nb_cartes_jouees-1; i++)
            {
                if(partie->joueur[m].main[partie->joueur[m].choix[i]-1].couleur!=partie->joueur[m].main[partie->joueur[m].choix[i+1 ]-1].couleur)
                {
                    couleur_differente=1;
                }
            }
        }
    }
    return  couleur_differente;

}

int verifier_seuil_victoire(Partie *partie)
{
     for(int i = 0; i < partie->nb_joueur; i++)
    {
        if (partie->joueur[i].score_total >= partie->seuil_victoire)
        {
            return 1;
        }
    }

    return 0; // 0 = personne n'a atteint la limite
}

