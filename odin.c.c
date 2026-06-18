#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "odin.h"

void initialiser_paquet(Paquet p)
{
    int carte_num=0;
    for (int i=0; i<NB_COULEURS; i++)
    {
        for (int j=0; j<TAILLE_MAX_MAIN; j++)
        {
           p.carte[carte_num].couleur=i;
           p.carte[carte_num].chiffre=j;
           p.carte[carte_num].utilisee_tri=0;
           carte_num++;
        }
    }
}


void distribuer_carte(Partie *partie)
{
    int j=0;
    while (j<partie->nb_joueur)
    {
        int c=0;
        while (c<TAILLE_MAX_MAIN)
        {
            int position;
            while(1) //boucle infinie pour vérifier que la carte n'est pas deja utilisée
            {
                position=rand()% NB_CARTES_MAX;
                if (partie->paquet.carte[position].utilisee_tri==0)
                    break;
            }
            partie->paquet.carte[position].utilisee_tri=1;
            partie->joueur[j].main[c]=partie->paquet.carte[position];  //donne la carte au joueur
            c++;
        }
        partie->joueur[j].nb_cartes=TAILLE_MAX_MAIN;
        j++;
    }
}

void demande_carte_a_jouer(Joueur joueur)
{
    Pile_millieu pile;
    pile.nb_carte_millieu=0;
    int i;
    int choix[TAILLE_MAX_MAIN];
    int nb_cartes_jouees;
    while (1)
    {
         printf("combien de cartes veux tu jouer ?");
         scanf("%d",&nb_cartes_jouees);
         if (nb_cartes_jouees>=0 && nb_cartes_jouees<=TAILLE_MAX_MAIN && nb_cartes_jouees>=pile.nb_carte_millieu && nb_cartes_jouees<=pile.nb_carte_millieu+1)
            {
               break;
            }

    }
    while (1)
    {
        for (i=0; i<nb_cartes_jouees; i++)
        {
            printf("carte numero %d ?",i);
            scanf("%d",&choix[i]);
        }
        for (i=0; i<nb_cartes_jouees; i++)
        {
            if (choix[i]-1>=0 && choix[i]-1<=joueur.nb_cartes)
                break;
        }

    }
}

int jouer_cartes(int choix[TAILLE_MAX_MAIN], int nb_cartes_jouees, Joueur *joueur, Carte carte_jouee[TAILLE_MAX_MAIN], int nb_carte_millieu)
{
    int a_joue[TAILLE_MAX_MAIN]={0};
    for (int i=0; i<nb_cartes_jouees; i++)
    {
        a_joue[choix[i]-1]=1;
        carte_jouee[i]=joueur->main[choix[i]-1];
    }
     int nouvelle_taille_main=0;
     for (int j = 0; j < joueur->nb_cartes; j++)
    {
        if(a_joue[j]==0)    //si la carte est pas jouée alors... si elle est jouée, pas d'action donc nouvelle taille main se decale de j, donc réordonne la main
        {
            joueur->main[nouvelle_taille_main]=joueur->main[j];
            nouvelle_taille_main++;
        }
    }
    joueur->nb_cartes=nouvelle_taille_main;
    return 1;
}
