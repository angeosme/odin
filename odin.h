#ifndef ODIN_H
#define ODIN_H

#define TAILLE_MAX_MAIN 9
#define NB_COULEURS 6
#define NB_JOUEUR_MAX 6
#define NB_CARTES_MAX 54
typedef struct
{
    int couleur;
    int chiffre;
    int utilisee; //0 pas utilsée et 1 utilisée
}Carte;

typedef struct
{
    Carte carte[NB_CARTES_MAX];
}Paquet;

typedef struct
{
    char nom[50];
    int nb_cartes;
    Carte main[TAILLE_MAX_MAIN];
}Joueur;

typedef struct
{
    Joueur joueur[NB_JOUEUR_MAX];
    int nb_joueur;
    Paquet paquet;
    int conditions_fin_tour;
    int conditions_fin_manche;
}Partie;
void initialiser_cartes(Carte carte[TAILLE_MAX_MAIN][NB_COULEURS]);
#endif
