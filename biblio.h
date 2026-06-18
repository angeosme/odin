#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#endif // BIBLIO_H_INCLUDED

// DEFINES

// position du centre pour le menu
#define MILLIEU_MENU 90
#define CENTRE_MENU 50

#define PAS_ENTRE_CARTES 16

#define BLEU 1
#define ROUGE 4
#define ROSE 13
#define VERT 2
#define MARRON 6
#define JAUNE 14

// STRUCTURES

typedef struct {



} Paquet;

/*
======================================================================
AFFICHAGE ET INTERFACE
======================================================================
*/

// SOUS PROGRAMMES ELEMENT CONCEPTUELS DE L'AFFICHAGE AVEC CARTE JEU BASIQUE

void positionner_curseur(int ligne, int colonne);

void plein_ecran();

void dessiner_formes(int ligne,int colonne,int c,int lg, int la);

void dessiner_pointilles(int ligne,int colonne,int c,int lg, int la);

void dessiner_fond_carte(int ligne, int colonne);

void dessiner_carte_du_jeu(int ligne,int colonne, int couleur, int valeur_carte);


// SOUS PROGRAMMES MENU

void dessiner_logo_odin(int ligne, int colonne);

void menu_principal();

void menu_jouer();

void todo(char *s);

// SOUS PROGRAMMES TRANSITION

void transition_la_partie_va_commencer();

void transition_retour_au_menu_principal();

void transition_joueur_suivant(char nom_joueur[]);
