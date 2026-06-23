#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "bibliocomplet.h"

/*
================================================================
INTIALISTIONS
================================================================
*/

void initialiser_paquet(Paquet *p)
{
    int carte_num=0;
    for (int i=1; i<=NB_COULEURS; i++)
    {
        for (int j=1; j<=TAILLE_MAX_MAIN; j++)
        {
           p->carte[carte_num].couleur=i;
           p->carte[carte_num].chiffre=j;
           p->carte[carte_num].utilisee_tri=0;
           carte_num++;
        }
    }
}

void initialisation_seuil_victoire(Partie *partie, int choix_partie)
{
    switch (choix_partie)
    {
        case 1:
            strcpy(partie->nom_mode_de_jeu, "Partie standard");
            partie->seuil_victoire = 15;
            break;

        case 2:
            strcpy(partie->nom_mode_de_jeu, "Partie courte");
            partie->seuil_victoire = 10;
            break;

        case 3:
            strcpy(partie->nom_mode_de_jeu, "Partie longue");
            partie->seuil_victoire = 20;
            break;

        case 4:
            strcpy(partie->nom_mode_de_jeu, "Partie express");
            partie->seuil_victoire = 1;
            break;
    }

}

//CALCULS

int calcul_num_pose(Partie *partie)  //tri a bulle
{
    Carte temp;
    Carte copie[TAILLE_MAX_MAIN];
    int valeur=0;
    for (int k=0; k<partie->pile_milieu.nb_carte_milieu; k++)
    {
        copie[k]=partie->pile_milieu.carte_posee[k];               //faire copie sinon on modofie l'ordre des anciennes cartes du milieu avant meme jouer_partie
    }
    for (int i=0; i<partie->pile_milieu.nb_carte_milieu; i++)
    {
        for (int j=0; j<partie->pile_milieu.nb_carte_milieu-i-1; j++)
        {
            if (partie->pile_milieu.carte_posee[j].chiffre<partie->pile_milieu.carte_posee[j+1].chiffre)
            {
                temp=copie[j];
                copie[j]=copie[j+1];
                copie[j+1]=temp;
            }
        }
    }
     for (int l=0; l<partie->pile_milieu.nb_carte_milieu; l++)
     {
         valeur=valeur*10+copie[l].chiffre;    //valeur*10 pour le nombre des dizaine puis pour les unités (ex: 27.  valeur=0*10+2; valeur=2*10+7)
     }
     return valeur;
}

int calcul_num_choisi(Partie *partie, int m)
{
    Carte temp;
    int valeur=0;
    for (int i=0; i<partie->joueur[m].nb_cartes_jouees; i++)
    {
        for (int j=0; j<partie->joueur[m].nb_cartes_jouees-i-1; j++)
        {
            if (partie->joueur[m].main[partie->joueur[m].choix[j]-1].chiffre<partie->joueur[m].main[partie->joueur[m].choix[j+1]-1].chiffre)
            {
                temp=partie->joueur[m].main[partie->joueur[m].choix[j]-1];
                partie->joueur[m].main[partie->joueur[m].choix[j]-1]=partie->joueur[m].main[partie->joueur[m].choix[j+1]-1];
                partie->joueur[m].main[partie->joueur[m].choix[j+1]-1]=temp;
            }
        }
    }
     for (int k=0; k<partie->joueur[m].nb_cartes_jouees; k++)
     {
         valeur=valeur*10+ partie->joueur[m].main[partie->joueur[m].choix[k]-1].chiffre;    //valeur*10 pour le nombre des dizaine puis pour les unités (ex: 27.  valeur=0*10+2; valeur=2*10+7)
     }
     return valeur;
}

void calculer_scores_manche(Partie *partie)  //fait par nolan
{
    for(int i = 0; i < partie->nb_joueur; i++)
    {
        partie->joueur[i].score_manche = partie->joueur[i].nb_cartes;//1pt = 1carte
        partie->joueur[i].score_total = partie->joueur[i].score_total + partie->joueur[i].score_manche;
    }
}

// TRIS

void trier_joueurs_par_score(Partie *partie)
{
    // Algorithme : tri à bulles
    Joueur temp;
    for (int i = 0; i < partie->nb_joueur - 1; i++)
    {
        for (int j = 0; j < partie->nb_joueur - i - 1; j++)
        {
            if (partie->joueur[j].score_total> partie->joueur[j+1].score_total)
            {
                temp = partie->joueur[j];
                partie->joueur[j] = partie->joueur[j+1];
                partie->joueur[j+1] = temp;
            }
        }
    }
}



