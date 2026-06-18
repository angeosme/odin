#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#endif // BIBLIO_H_INCLUDED

// DEFINES

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




// SOUS PROGRAMMES ELEMENT CONCEPTUELS DE L'AFFICHAGE AVEC CARTE JEU BASIQUE

void positionner_curseur(int ligne, int colonne);

void plein_ecran();

void dessiner_formes(int ligne,int colonne,int c,int lg, int la);

void dessiner_pointilles(int ligne,int colonne,int c,int lg, int la);

void dessiner_fond_carte(int ligne, int colonne);

void dessiner_carte_du_jeu(int ligne,int colonne, int couleur, int valeur_carte);


// SOUS PROGRAMMES MENU

void dessiner_logo_odin(int ligne, int colonne);
