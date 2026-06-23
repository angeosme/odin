#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "biblio.h"
#include <conio.h>

/*
===========================================
CALCUL Du SCORE
===========================================
*/

// Calculer les points a la fin d'une manche
void calculer_scores_manche(Partie *partie)
{
    for(int i = 0; i < partie->nb_joueur; i++)
    {
        partie->joueur[i].score_manche = partie->joueur[i].nb_cartes;//1pt = 1carte
        partie->joueur[i].score_total =  partie->joueur[i].score_total+partie->joueur[i].score_manche;
    }
}


int verifier_fin_partie(Partie *partie)
{
    int seuil_victoire = 15; // Partie standard


    if (strcmp(partie->mode_de_jeu, "Partie courte") == 0)
    {
        seuil_victoire = 10;
    }
    else if (strcmp(partie->mode_de_jeu, "Partie longue") == 0)
    {
        seuil_victoire = 20;
    }
    else if (strcmp(partie->mode_de_jeu,"Partie express") == 0)
    {
        return 1; // La partie express finit apres 1 manche
    }

    for(int i = 0; i < partie->nb_joueur; i++)
    {
        if (partie->joueur[i].score_total >= seuil_victoire)
        {
            return 1;
        }
    }

    return 0; // 0 = personne n'a atteint la limite

// Trier les joueurs (croissant)
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

/*
==============================
AFFICHAGE DES RESULTAT
==============================
*/

// Afficher le bilan entre les manches
void afficher_scores_manche(Partie *partie)
{
    system("cls");
    positionner_curseur(CENTRE_MENU - 15, MILLIEU_MENU - 5);
    color(14,0);
    printf(" ____________    FIN DE LA MANCHE !    ____________\n");
    color(15,0);

    positionner_curseur(CENTRE_MENU - 14, MILLIEU_MENU - 5);
    printf("|                                                  |\n");
    positionner_curseur(CENTRE_MENU - 13, MILLIEU_MENU - 5);
    printf("|         Repertoire des penalites recues :        |\n");
    positionner_curseur(CENTRE_MENU - 12, MILLIEU_MENU - 5);
    printf("|                                                  |\n");

    int ligne_actuelle = CENTRE_MENU - 11;

    for(int i = 0; i < partie->nb_joueur; i++)
    {
        positionner_curseur(ligne_actuelle, MILLIEU_MENU- 5);
        if(partie->joueur[i].score_manche == 0)
        {
            color(10,0); //vert
            printf("|  %s : BRAVO (0 point) -> Total : %d pts", partie->joueur[i].nom, partie->joueur[i].score_total);
            color(15,0);
        }
        else
        {
            color(4,0); // Rouge, penalité
            printf("|  %s : +%d point(s) -> Total : %d pts", partie->joueur[i].nom, partie->joueur[i].score_manche, partie->joueur[i].score_total);
            color(15,0);
        }

        positionner_curseur(ligne_actuelle, MILLIEU_MENU + 46);
        printf("|\n");

        ligne_actuelle++;
    }

    positionner_curseur(ligne_actuelle, MILLIEU_MENU - 5);
    printf("|                                                  |\n");
    positionner_curseur(ligne_actuelle + 1, MILLIEU_MENU - 5);
    printf("|__________________________________________________|\n");

    positionner_curseur(ligne_actuelle + 3, MILLIEU_MENU - 5);
    color(1,0);
    printf("       *Appuyez sur une touche pour continuer* \n");
    color(15,0);

    color(0,0);
    system("PAUSE");
    color(15,0);
}




void afficher_podium_final(Partie *partie)
{
    // trie des joueurs avant podium
    trier_joueurs_par_score(partie);

    system("cls");
    positionner_curseur(CENTRE_MENU - 20, MILLIEU_MENU - 10);

    color(14,0); // Jaune pour l'or
    printf(" ========================================================\n");
    positionner_curseur(CENTRE_MENU- 19, MILLIEU_MENU - 10);
    printf(" ||               FIN DE LA PARTIE                     ||\n");
    positionner_curseur(CENTRE_MENU - 18, MILLIEU_MENU - 10);
    printf(" ========================================================\n");
    color(15,0);

    positionner_curseur(CENTRE_MENU - 16, MILLIEU_MENU - 10);
    printf("   Le vainqueur est : ");
    color(10,0);
    printf("%s", partie->joueur[0].nom);
    color(15,0);
    printf(" avec %d points \n", partie->joueur[0].score_total);

    positionner_curseur(CENTRE_MENU - 14, MILLIEU_MENU - 10);
    printf("   --- CLASSEMENT COMPLET ---   \n");

    int ligne_actuelle = CENTRE_MENU - 12;

    for (int i = 0; i < partie->nb_joueur; i++)
    {
        positionner_curseur(ligne_actuelle, MILLIEU_MENU - 8);

        if(i == 0) color(14,0); // 1er
        else if (i == 1) color(7,0); // 2eme
        else if (i == 2) color(6,0); // 3eme
        else color(15,0); // Reste (Blanc)

        printf("%d. %s - Score final : %d points", i + 1, partie->joueur[i].nom, partie->joueur[i].score_total);
        color(15,0);

        ligne_actuelle += 2;
    }

    positionner_curseur(ligne_actuelle + 2, MILLIEU_MENU - 10);
    color(4,0);
    printf(" ========================================================\n");
    color(15,0);

    positionner_curseur(ligne_actuelle + 4, MILLIEU_MENU - 10);
    system("PAUSE");

    transition_retour_au_menu_principal();
    menu_principal(); // Retour au début du jeu
}
}
