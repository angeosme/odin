#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "biblio.h"

//DESSIN GENERAL

void positionner_curseur(int ligne, int colonne)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);//permet de déclarer la variable "hstdout" qui fait référénce à la console
    COORD pos; // COORD est un type structuré défini dans la bibliothèque windows.h
    pos.X=colonne;// numéro de la colonne
    pos.Y=ligne;// numéro de la ligne
    SetConsoleCursorPosition(hStdout, pos);
}

void plein_ecran()
{
    // Basculer en plein écran
    keybd_event(VK_MENU, 0x38, 0, 0); // Appuie sur ALT
    keybd_event(VK_RETURN, 0x1C, 0, 0); // Appuie sur ENTREE
    keybd_event(VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0); // Relâche ENTREE
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0); // Relâche ALT

    // Attendre un court instant pour que le mode plein écran s'active
    Sleep(500);

    // Appliquer deux fois un dézoom (CTRL + '-')
    for (int i = 0; i < 2; i++)
    {
        keybd_event(VK_CONTROL, 0x1D, 0, 0); // Appuie sur CTRL
        keybd_event(VK_SUBTRACT, 0x4A, 0, 0); // Appuie sur '-'
        keybd_event(VK_SUBTRACT, 0x4A, KEYEVENTF_KEYUP, 0); // Relâche '-'
        keybd_event(VK_CONTROL, 0x1D, KEYEVENTF_KEYUP, 0); // Relâche CTRL

        Sleep(100); // Petite pause entre les actions
    }
}

void color (int couleurDuTexte, int couleurDuFond)
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

//DESSIN CARTE

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

//DESSIN MENU

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

