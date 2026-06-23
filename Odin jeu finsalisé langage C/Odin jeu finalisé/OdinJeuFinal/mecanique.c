#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "bibliocomplet.h"

/*
================================================================
MECANIQUE
================================================================
*/


void distribuer_carte_depart(Partie *partie)
{
    srand(time(NULL));
    int j=0;
    for (int k=0; k<partie->nb_joueur; k++)  //defini le nb de cartes des joueurs a 0
    {
        partie->joueur[k].nb_cartes=0;
    }
    while (j<partie->nb_joueur)
    {
        int c=0;
        while (c<TAILLE_MAX_MAIN || partie->joueur[j].nb_cartes<9) //tant que le joueur a pas 9 cartes
        {
            int position;
            while(1) //boucle infinie pour vérifier que la carte n'est pas deja utilisée
            {
                position=rand()% NB_CARTES_MAX;
                if (partie->paquet.carte[position].utilisee_tri==0)
                    break;
            }
            partie->paquet.carte[position].utilisee_tri=1;     //marque la carte tirée
            partie->joueur[j].main[c]=partie->paquet.carte[position];  //donne la carte au joueur
            partie->joueur[j].nb_cartes++;
            c++;
        }
        partie->joueur[j].nb_cartes=TAILLE_MAX_MAIN;
        j++;
    }
}

void demande_carte_a_jouer(Partie *partie, int m)
{
    int saisie_valide=0;
    int i;
    while (1)
    {
         positionner_curseur(120,0);
         printf("combien de cartes veux tu jouer ? (si tu es le 1er a jouer, joue une seule carte)");
         scanf("%d",&partie->joueur[m].nb_cartes_jouees);
         if (partie->joueur[m].nb_cartes_jouees>=0 && partie->joueur[m].nb_cartes_jouees<=TAILLE_MAX_MAIN && partie->joueur[m].nb_cartes_jouees>=partie->pile_milieu.nb_carte_milieu && partie->joueur[m].nb_cartes_jouees<=partie->pile_milieu.nb_carte_milieu+1)
            {
               break;
            }

    }
    while (saisie_valide==0)
    {
        for (i=0; i<partie->joueur[m].nb_cartes_jouees; i++)
        {
            printf("carte numero %d ?(dans l'ordre décroissant des valeurs",i);  //demande quelles cartes ?
            scanf("%d",&partie->joueur[m].choix[i]);

            if (partie->joueur[m].choix[i]-1>=0 && partie->joueur[m].choix[i]-1<=partie->joueur[m].nb_cartes) //verif que la saisie est bonne
            {
               saisie_valide=1;
            }
        }
    }
}

int passage_au_joueur_suivant(Partie *partie,int m)
{

    partie->joueur[m].passer_au_joueur_suivant=0;

    positionner_curseur(118,0);
    printf("Veux-tu passer ton tour ? Tape 1 pour passer. 0 sinon, (LE PREMIER JOUEUR NE PEUX PAS PASSER)");

    do
    {
    positionner_curseur(119,0);
    scanf("%d",&partie->joueur[m].passer_au_joueur_suivant);
    positionner_curseur(119,0);
    }
    while(partie->joueur[m].passer_au_joueur_suivant < 0 || partie->joueur[m].passer_au_joueur_suivant > 1);

    return partie->joueur[m].passer_au_joueur_suivant;



}

void jouer_cartes( Partie *partie, int m)
{
    int choix_carte_recuperee;
    int nouvelle_taille_main=0;
    int a_recupere=0;
    Carte carte_recuperee;
    if (partie->pile_milieu.nb_carte_milieu>0)
    {
        printf("quelle carte veux tu prendre dans la pile du milieu (position de la carte et non pas sa valeur)");
        scanf("%d",&choix_carte_recuperee);
        carte_recuperee=partie->pile_milieu.carte_posee[choix_carte_recuperee-1]; //evite d'ecraser par les cartes jouées apres ca
        a_recupere=1;
    }
    //--------------------------------------------------
    int a_joue[TAILLE_MAX_MAIN]={0};  //utile pour faire la nouvelle main après avoir jouer
    partie->pile_milieu.nb_carte_milieu=0;
    for (int i=0; i<partie->joueur[m].nb_cartes_jouees; i++)
    {
        a_joue[partie->joueur[m].choix[i]-1]=1;
        partie->joueur[m].carte_jouee[i]=partie->joueur[m].main[partie->joueur[m].choix[i]-1];
        partie->pile_milieu.nb_carte_milieu++;
        partie->pile_milieu.carte_posee[i]=partie->joueur[m].main[partie->joueur[m].choix[i]-1];
    }

    //------------------------------------------
     for (int j = nouvelle_taille_main; j < partie->joueur[m].nb_cartes; j++)
    {
        if(a_joue[j]==0)    //si la carte est pas jouée alors... si elle est jouée, pas d'action donc nouvelle taille main se decale de j, donc réordonne la main
        {
            partie->joueur[m].main[nouvelle_taille_main]=partie->joueur[m].main[j];
            nouvelle_taille_main++;
        }
    }
    partie->joueur[m].nb_cartes=nouvelle_taille_main; // +1 car il choisit une carte deja dans la pile

    if ( a_recupere==1)
    {
        partie->joueur[m].main[nouvelle_taille_main]=carte_recuperee;
        nouvelle_taille_main++;
        partie->joueur[m].nb_cartes++;
    }
}

void poser_au_millieu(Partie *partie)
{
    for (int i=0; i<partie->joueur[partie->joueur->numero_joueur].nb_cartes_jouees; i++)
    {
        partie->pile_milieu.carte_posee[i]=partie->joueur[partie->joueur->numero_joueur].carte_jouee[i];
    }
}

int passe_consecutif(Partie *partie)
{
    int nb_de_passe=0;
    for (int i=0; i<partie->nb_joueur; i++)
    {
        if (partie->joueur[i].a_passe[partie->nb_tour]==1)
        {
            nb_de_passe++;
        }
    }
    return nb_de_passe;

}

//BOUCLE PRINCIPALE

void tour_de_jeu(Partie *partie)
{
    int ecartement=0;
    int fin_manche=0;
    int j;
    int c;
    int nb_cartes_jouees;
    partie->nb_tour=0;
    int decalage=20;
    Paquet p;
    int tour;
    initialiser_paquet(&partie->paquet);
    distribuer_carte_depart(partie);
    partie->pile_milieu.nb_carte_milieu=0;
//-------------------------------------------------------------afficher main du joueur
    while (1)
    {
        for ( j=0; j<partie->nb_joueur; j++)
        {
            //positionner_curseur(decalage, 0);
            //decalage=decalage+ESPACE_ENTRE_TOURS;
            tour++;
            partie->joueur[j].nb_cartes_jouees=0;
            system("cls");
            ecartement=0;
            transition_joueur_suivant(partie->joueur[j].nom);
            for (c=0; c<partie->joueur[j].nb_cartes; c++)
            {

                dessiner_carte_du_jeu( 50, ecartement, partie->joueur[j].main[c].couleur, partie->joueur[j].main[c].chiffre);
                ecartement=ecartement+PAS_ENTRE_CARTES;
            }
            if (j>=1)
            {
                afficher_carte_milieu(partie, j-1);
            }
            else
            {
                 afficher_carte_milieu(partie, j);
            }


            passage_au_joueur_suivant(partie, j);

            if (partie->joueur[j].passer_au_joueur_suivant==0)
            {
            do
            {
                demande_carte_a_jouer(partie, j);
            }while (!coup_le_plus_grand(partie, j) || (verif_meme_couleur(partie, j)!=0));

            jouer_cartes(partie, j);

           // poser_au_millieu(partie);
            //---------------------------------------------------------affichage milieu
            afficher_carte_milieu(partie, j);
            }
            else
            {
                partie->joueur[j].a_passe[partie->nb_tour]=1;
                if (passe_consecutif(partie)>=partie->nb_joueur-1)
                {
                    partie->pile_milieu.nb_carte_milieu=0;
                }
            }

            if (partie->joueur[j].nb_cartes==0)
            {
                fin_manche=1;
            }

        }

        partie->nb_tour++;

        if(fin_manche==1)
        {
            break;
        }

    }
    calculer_scores_manche(partie);
    afficher_scores_manche(partie);

    if (partie->seuil_victoire != 1)
    transition_manche_suivante();
}
