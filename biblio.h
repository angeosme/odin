#ifndef BIBLIO_H
#define BIBLIO_H
//version du 21/06/2026  14h01

/*
======================================================================
DEFINES
======================================================================
*/

#define TAILLE_MAX_MAIN 9
#define NB_COULEURS 6
#define NB_JOUEUR_MAX 6
#define NB_CARTES_MAX 54
// position du centre pour le menu :
#define MILLIEU_MENU 90
#define CENTRE_MENU 50

#define PAS_ENTRE_CARTES 16

// valeur des couleurs de cartes, précisées aussi dans la fonction color, mais rappelée pour plus de lisibilité dans le code
#define BLEU 1
#define ROUGE 4
#define ROSE 13
#define VERT 2
#define MARRON 6
#define JAUNE 14

/*
======================================================================
STRUCTURES
======================================================================
*/

typedef struct
{
    int couleur;
    int chiffre;
    int utilisee_tri; //0 pas utilsée et 1 utilisée
}Carte;

typedef struct
{
    Carte carte[NB_CARTES_MAX];
}Paquet;

typedef struct
{
    char nom[50];
    int numero_joueur;
    int nb_cartes;
    Carte main[TAILLE_MAX_MAIN+1]; //a cause de la recup de la carte au milieu
    int nb_cartes_jouees;
    int choix[TAILLE_MAX_MAIN];    //passe par choix
    Carte carte_jouee[TAILLE_MAX_MAIN];  //puis devient carte_jouee
}Joueur;

typedef struct
{
    Carte carte_posee[TAILLE_MAX_MAIN];
    int nb_carte_milieu;
    int num_final[TAILLE_MAX_MAIN];
}Pile_milieu;

typedef struct
{
    Joueur joueur[NB_JOUEUR_MAX];
    int nb_joueur;
    Paquet paquet;
    Pile_milieu pile_milieu;
    int conditions_fin_tour;
    int conditions_fin_manche;
}Partie;

/*
======================================================================
PARTIE ET INITIALISATIONS
======================================================================
*/

// SOUS PROGRAMMES PARTIE

void initialiser_cartes(Carte carte[TAILLE_MAX_MAIN][NB_COULEURS]);

void distribuer_carte_depart(Partie *partie);

void demande_carte_a_jouer();

void  jouer_cartes( Partie *partie);

void poser_au_millieu(Partie *partie, int nb_cartes_jouees, Carte carte_jouee[TAILLE_MAX_MAIN]);

int verif_conditions_de_jeu(int nb_cartes_jouees, Partie partie);

void calcul_num_pose(Partie partie);

// BOUCLE PRINCIPALE
void tour_de_jeu(Partie *partie);


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

void menu_des_regles();

void menu_des_credits();

void menu_complet();

void todo(char *s);


// SOUS PROGRAMMES TRANSITION

void transition_la_partie_va_commencer();

void transition_retour_au_menu_principal();

void transition_joueur_suivant(char nom_joueur[]);

void transition_manche_suivante();

// SOUS PROGRAMMES ENTREE INITIALES

int validation_du_mode_de_jeu_chosi(char nom_mode_de_jeu[], int choix);

void application_du_choix_du_mode_de_jeu(char nom_mode_de_jeu[], int choix);

int entree_du_nombre_de_joueurs();

void demander_prenom();

void entree_des_informations_des_joueurs(Joueur *ensemble_des_joueurs, int nb_joueurs);





#endif
