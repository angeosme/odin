#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "biblio.h"
#include <conio.h>
//version du 21/06/2026  14h01

void initialiser_paquet(Paquet *p)
{
    int carte_num=0;
    for (int i=0; i<NB_COULEURS; i++)
    {
        for (int j=0; j<TAILLE_MAX_MAIN; j++)
        {
           p->carte[carte_num].couleur=i;
           p->carte[carte_num].chiffre=j;
           p->carte[carte_num].utilisee_tri=0;
           carte_num++;
        }
    }
}

void distribuer_carte_depart(Partie *partie)
{
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

void demande_carte_a_jouer(Partie *partie)
{
    int saisie_valide=0;
    Pile_milieu pile;
    pile.nb_carte_milieu=0;
    int i;
    while (1)
    {
         positionner_curseur(120,0);
         printf("combien de cartes veux tu jouer ? (si tu es le 1er a jouer, joue une seule carte)");
         scanf("%d",&partie->joueur->nb_cartes_jouees);
         if (partie->joueur->nb_cartes_jouees>=0 && partie->joueur->nb_cartes_jouees<=TAILLE_MAX_MAIN && partie->joueur->nb_cartes_jouees>=pile.nb_carte_milieu && partie->joueur->nb_cartes_jouees<=pile.nb_carte_milieu+1)
            {
               break;
            }

    }
    while (saisie_valide==0)
    {
        for (i=0; i<partie->joueur->nb_cartes_jouees; i++)
        {
            printf("carte numero %d ?",i);  //demande quelles cartes ?
            scanf("%d",&partie->joueur->choix[i]);

            if (partie->joueur->choix[i]-1>=0 && partie->joueur->choix[i]-1<=partie->joueur->nb_cartes) //verif que la saisie est bonne
            {
               saisie_valide=1;
            }
        }
    }
}

void jouer_cartes( Partie *partie)
{
    int choix_carte_recuperee;
    if (partie->pile_milieu.nb_carte_milieu>=1)
    {
        printf("quelle carte veux tu prendre dans la pile du milieu (position de la carte et non pas sa valeur)");
        scanf("%d",&choix_carte_recuperee);
        partie->joueur->main[TAILLE_MAX_MAIN+1]=partie->pile_milieu.carte_posee[choix_carte_recuperee];
    }
    //--------------------------------------------------
    int a_joue[TAILLE_MAX_MAIN]={0};  //utile pour faire la nouvelle main après avoir jouer
    for (int i=0; i<partie->joueur->nb_cartes_jouees; i++)
    {
        a_joue[partie->joueur->choix[i]-1]=1;
        partie->joueur->carte_jouee[i]=partie->joueur->main[partie->joueur->choix[i]-1];
        partie->pile_milieu.nb_carte_milieu++;
        partie->pile_milieu.carte_posee[i]=partie->joueur->main[partie->joueur->choix[i]-1];
    }
    //------------------------------------------
     int nouvelle_taille_main=0;
     for (int j = 0; j < partie->joueur->nb_cartes; j++)
    {
        if(a_joue[j]==0)    //si la carte est pas jouée alors... si elle est jouée, pas d'action donc nouvelle taille main se decale de j, donc réordonne la main
        {
            partie->joueur->main[nouvelle_taille_main]=partie->joueur->main[j];
            nouvelle_taille_main++;
        }
    }
    partie->joueur->nb_cartes=nouvelle_taille_main +1; // +1 car il choisit une carte deja dans la pile

//-------------------------------------------------------affichage milieu
    int ecartement_milieu=10;
    for (int c=0; c<partie->joueur->nb_cartes_jouees; c++)
    {
        dessiner_carte_du_jeu( 15,ecartement_milieu, partie->pile_milieu.carte_posee[c].couleur, partie->pile_milieu.carte_posee[c].chiffre);
        ecartement_milieu=ecartement_milieu+PAS_ENTRE_CARTES;
    }



}

void poser_au_millieu(Partie *partie, int nb_cartes_jouees, Carte carte_jouee[TAILLE_MAX_MAIN])
{
    partie->pile_milieu.nb_carte_milieu=nb_cartes_jouees;
    //----------------------------------
    for (int i=0; i<nb_cartes_jouees; i++)
    {
        partie->pile_milieu.carte_posee[i]=carte_jouee[i];
    }
}

int verif_conditions_de_jeu(int nb_cartes_jouees, Partie partie)
{
    if (nb_cartes_jouees<partie.pile_milieu.nb_carte_milieu || nb_cartes_jouees>partie.pile_milieu.nb_carte_milieu+1 )
    {
        return 1;    //utile pour la verif dans le main
    }
    return 0;
}

void calcul_num_pose(Partie partie)
{
    int temp;
    for (int i=0; i<partie.pile_milieu.nb_carte_milieu; i++)
    {
        for (int j=0; j<partie.pile_milieu.nb_carte_milieu-i-1; j++)
        {
            if (partie.pile_milieu.carte_posee[j].chiffre<partie.pile_milieu.carte_posee[j+1].chiffre)
            {
                temp=partie.pile_milieu.carte_posee[j].chiffre;
                partie.pile_milieu.carte_posee[j].chiffre=partie.pile_milieu.carte_posee[j+1].chiffre;
                partie.pile_milieu.carte_posee[j].chiffre=temp;
            }
        }
    }
}

//------------------------------------------------------------------------------------------------
//-------------------------menu d'entrée
void menu_complet()
{
    plein_ecran();
    menu_principal();

    dessiner_logo_odin(1,70);
    positionner_curseur(90,6);

}
//-----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

void demander_prenom()
{
    Joueur *ensemble_des_joueurs;
    int nb_joueurs;
    plein_ecran();

    nb_joueurs=entree_du_nombre_de_joueurs();

    ensemble_des_joueurs = malloc(nb_joueurs*sizeof(Joueur));

    entree_des_informations_des_joueurs(ensemble_des_joueurs, nb_joueurs);

    /*transition_la_partie_va_commencer();
    printf("Il y a %d joueurs, les voici :\n",nb_joueurs);
    for(int i = 0; i < nb_joueurs; i++)
    {
        printf("%s\n",ensemble_des_joueurs[i].nom);
    }*/


}

void tour_de_jeu(Partie *partie)
{
    int ecartement=0;
    int j;
    int c;
    int nb_cartes_jouees;
    Paquet p;
    initialiser_paquet(&partie->paquet);
    distribuer_carte_depart(partie);

        for ( j=0; j< partie->nb_joueur; j++)
        {
            for (c=0; c<9; c++) //ecartement des cartes
            {

                dessiner_carte_du_jeu( 34, ecartement, partie->joueur[j].main[c].couleur, partie->joueur[j].main[c].chiffre);
                ecartement=ecartement+PAS_ENTRE_CARTES;
            }
            demande_carte_a_jouer(partie);
            jouer_cartes(partie);
        }

}
