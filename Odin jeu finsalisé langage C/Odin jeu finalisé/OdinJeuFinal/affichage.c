#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "bibliocomplet.h"

/*
================================================================
AFFICHAGE
================================================================
*/
// SOUS PROGRAMMES DESSIN

void positionner_curseur(int ligne, int colonne) //fonction récupérée du TP jeu d'echec, car très pratique pour notre jeu
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);//permet de déclarer la variable "hstdout" qui fait référénce à la console
    COORD pos; // COORD est un type structuré défini dans la bibliothèque windows.h
    pos.X=colonne;// numéro de la colonne
    pos.Y=ligne;// numéro de la ligne
    SetConsoleCursorPosition(hStdout, pos);
}

void color (int couleurDuTexte, int couleurDuFond) //fonction récupérée du TP jeu d'echec, car suffisante pour notre jeu
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDuFond*16+couleurDuTexte);

// 0.Noir
// 1.Bleu fonc
// 2.Vert fonc
// 3.Turquoise
// 4.Rouge fonc
// 5.Violet
// 6.Vert caca d'oie
// 7.Gris clair
// 8.Gris fonc
// 9.Bleu fluo
// 10.Vert fluo
// 11.Turquoise
// 12.Rouge fluo
// 13.Violet 2
// 14.Jaune
// 15.Blanc
}

void dessiner_formes(int ligne,int colonne,int c,int lg, int la)
{
    for (int i = 0; i < lg; i++)
    {
        positionner_curseur(ligne + i, colonne); // le but est de faire parcourir sur la longueur et largeur demandée un le curseur et de faire "prinft" un espace surligné de la couleur souhaité.
        for (int j = 0; j < la; j++)
        {
            color(0, c);
            printf(" ");
        }
    }
    color(15,0);   //réinitialisation de la couleur (texte blanc sur fond noir)
}

void dessiner_pointilles(int ligne,int colonne,int c,int lg, int la)
{

    for (int i = 0; i < lg; i++)
    {
        positionner_curseur(ligne + i, colonne); // le but est de faire parcourir sur la longueur et largeur demandée un le curseur et de faire "prinft" un espace surligné de la couleur souhaité.
        for (int j = 0; j < la; j++)
        {
            color(0, c);
            printf(":");
        }
    }
    color(15,0);   //réinitialisation de la couleur (texte blanc sur fond noir)
}

void dessiner_fond_carte(int ligne, int colonne)
{
    dessiner_formes(ligne, colonne, 15, 12, 14);
    dessiner_formes(ligne+1, colonne+1, 7, 10, 12);
}

void dessiner_carte_du_jeu(int ligne,int colonne, int couleur, int valeur_carte)
{


    dessiner_fond_carte(ligne, colonne);

    dessiner_formes(ligne+1, colonne+2, couleur, 3, 1);
    dessiner_formes(ligne+2, colonne+1, couleur, 1, 3);  // Dessin de l'"étoile" de gauche

    dessiner_formes(ligne+1, colonne+11, couleur, 3, 1);
    dessiner_formes(ligne+2, colonne+10, couleur, 1, 3);  // Dessin de l'"étoile" de droite

    positionner_curseur(ligne+2,colonne+2);
    color(15, couleur);
    printf("%d", valeur_carte);                         // Dessin du numero de la carte à gauche et à droite
    positionner_curseur(ligne+2,colonne+11);
    printf("%d", valeur_carte);

    dessiner_formes(ligne+4, colonne+5, couleur, 6, 4);  // Dessin du motif au centre

    color(15, 0);
}

void afficher_carte_milieu(Partie *partie, int m)
{
    int ecartement_milieu=10;
            for (int c=0; c<partie->pile_milieu.nb_carte_milieu; c++)
            {
                dessiner_carte_du_jeu( 20,ecartement_milieu, partie->pile_milieu.carte_posee[c].couleur, partie->pile_milieu.carte_posee[c].chiffre);
                ecartement_milieu=ecartement_milieu+PAS_ENTRE_CARTES;
            }
}

void dessiner_logo_odin(int ligne, int colonne)
{
    // =================================================

    for(int i = 0; i < 6; i++)
    dessiner_formes(ligne+5-i, colonne+i, 15, 5, 5);
    for(int i = 0; i < 6; i++)
    dessiner_formes(ligne+i, colonne+10+i, 15, 5, 5);

    dessiner_formes(ligne +10, colonne, 15, 5 ,5);
    dessiner_formes(ligne +10, colonne+15, 15, 5 ,5);       //Dessin du "O"

    for(int i = 0; i < 6; i++)
    dessiner_formes(ligne+i+15, colonne+i, 15, 5, 5);
    for(int i = 0; i < 6; i++)
    dessiner_formes(ligne+20-i, colonne+10+i, 15, 5, 5);

    // =================================================

    for(int i = 0; i < 6; i++)
    dessiner_formes(ligne+5-i, colonne+25+i, 15, 5, 1);
    for(int i = 0; i < 11; i++)
    dessiner_formes(ligne+i, colonne+31+i, 15, 5, 5);

    for(int i = 0; i < 6; i++)
    dessiner_formes(ligne+i+15, colonne+25+i, 15, 5, 1);       //Dessin du "D"
    for(int i = 0; i < 11; i++)
    dessiner_formes(ligne+20-i, colonne+31+i, 15, 5, 5);

    dessiner_formes(ligne +5, colonne+25, 15, 15 ,6);

    // =================================================

    for(int i = 0; i < 6; i++)
    dessiner_formes(ligne+5-i, colonne+50+i, 15, 5, 1);
    for(int i = 0; i < 6; i++)
    dessiner_formes(ligne+i+15, colonne+50+i, 15, 5, 1);        //Dessin du "I"

    dessiner_formes(ligne +5, colonne+50, 15, 15 ,6);

    // =================================================

    for(int i = 0; i < 15; i++)
    dessiner_formes(ligne+i, colonne+61+i, 15, 5, 2);
    for(int i = 0; i < 6; i++)
    dessiner_formes(ligne+i+15, colonne+61+i, 15, 5, 1);

    for(int i = 0; i < 6; i++)
    dessiner_formes(ligne+i, colonne+76+i, 15, 5, 1);           //Dessin du "N"
    for(int i = 0; i < 6; i++)
    dessiner_formes(ligne+20-i, colonne+76+i, 15, 5, 1);

    dessiner_formes(ligne +5, colonne+61, 15, 15 ,6);
    dessiner_formes(ligne +5, colonne+76, 15, 15 ,6);

    // =================================================
}

// SOUS PROGRAMMES TRANSITION

void transition_la_partie_va_commencer()
{
        system("cls");
        positionner_curseur(CENTRE_MENU,MILLIEU_MENU);
        color(2,0);
        printf(" ____________    LA PARTIE VA COMMENCER !  ____________\n");
        color(15,0);
        positionner_curseur(1+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(2+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(4+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(5+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(6+CENTRE_MENU,MILLIEU_MENU);
        color(2,0);
        printf("|______________________________________________________|\n");

        for(int i = 0; i<4; i++)
        {
            positionner_curseur(3+CENTRE_MENU,MILLIEU_MENU);
            printf("|                          %d                           |\n",3-i);
            Sleep(1000);
        }
        color(15,0);
        system("cls");
}

void transition_retour_au_menu_principal()
{
        system("cls");
        positionner_curseur(CENTRE_MENU,MILLIEU_MENU);
        color(4,0);
        printf(" ____________    RETOUR AU MENU PRINCIPAL  ____________\n");
        color(15,0);
        positionner_curseur(1+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(2+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(4+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(5+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(6+CENTRE_MENU,MILLIEU_MENU);
        color(4,0);
        printf("|______________________________________________________|\n");

        for(int i = 0; i<4; i++)
        {
            positionner_curseur(3+CENTRE_MENU,MILLIEU_MENU);
            printf("|                          %d                           |\n",3-i);
            Sleep(1000);
        }
        color(15,0);
        system("cls");
}

void transition_joueur_suivant(char nom_joueur[])
{
        system("cls");
        positionner_curseur(CENTRE_MENU,MILLIEU_MENU);
        printf(" Au tour de %s de jouer !\n",nom_joueur);
        positionner_curseur(1+CENTRE_MENU,MILLIEU_MENU);
        printf(" ______________________________________________________\n");
        color(15,0);
        positionner_curseur(2+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(3+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");

        color(1,0);
        positionner_curseur(4+CENTRE_MENU,MILLIEU_MENU);
        printf("|         *Appuyez sur une touche quelconque*          |\n");
        color(15,0);

        positionner_curseur(5+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(6+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(7+CENTRE_MENU,MILLIEU_MENU);

        printf("|______________________________________________________|\n");
        color(0,0);
        system("PAUSE");
        positionner_curseur(5+CENTRE_MENU,MILLIEU_MENU);
        color(15,0);
        system("cls");
}

void transition_manche_suivante()
{
        system("cls");
        positionner_curseur(CENTRE_MENU,MILLIEU_MENU);
        color(1,0);
        printf(" ________________    MACHE SUIVANTE !   ________________\n");
        color(15,0);
        positionner_curseur(1+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(2+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(4+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(5+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(6+CENTRE_MENU,MILLIEU_MENU);
        color(1,0);
        printf("|______________________________________________________|\n");

        for(int i = 0; i<4; i++)
        {
            positionner_curseur(3+CENTRE_MENU,MILLIEU_MENU);
            printf("|                          %d                           |\n",3-i);
            Sleep(1000);
        }
        color(15,0);
        system("cls");
}

// FINAL

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
    menu_principal(partie); // Retour au début du jeu
}

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

