#ifndef BIBLIOCOMPLET_H_INCLUDED
#define BIBLIOCOMPLET_H_INCLUDED

/*
================================================================
DEFINES
================================================================
*/

#define TAILLE_MAX_MAIN 9
#define NB_COULEURS 6
#define NB_JOUEUR_MAX 6
#define NB_CARTES_MAX 54
// position du centre pour le menu :
#define MILLIEU_MENU 90
#define CENTRE_MENU 50

#define PAS_ENTRE_CARTES 16
#define ESPACE_ENTRE_TOURS 80

// valeur des couleurs de cartes, précisées aussi dans la fonction color, mais rappelée pour plus de lisibilité dans le code
#define BLEU 1
#define ROUGE 4
#define ROSE 13
#define VERT 2
#define MARRON 6
#define JAUNE 14

/*
================================================================
STRUCTURES
================================================================
*/
typedef struct
{
    int couleur;
    int chiffre;
    int utilisee_tri;//0 pas utilsée et 1 utilisée
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
    int score_manche;
    int score_total;
    int passer_au_joueur_suivant;
    int a_passe[1000]; //compte si le joueur a passé au tour tant
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
    char nom_mode_de_jeu[50];
    int seuil_victoire;
    int nb_tour;
}Partie;

/*
================================================================
AFFICHAGE
================================================================
*/
// SOUS PROGRAMMES DESSIN

void positionner_curseur(int ligne, int colonne);

void color (int couleurDuTexte, int couleurDuFond);

void dessiner_formes(int ligne,int colonne,int c,int lg, int la);

void dessiner_pointilles(int ligne,int colonne,int c,int lg, int la);

void dessiner_fond_carte(int ligne, int colonne);

void dessiner_carte_du_jeu(int ligne,int colonne, int couleur, int valeur_carte);

void afficher_carte_milieu(Partie *partie, int m);

void dessiner_logo_odin(int ligne, int colonne);

// SOUS PROGRAMMES TRANSITION

void transition_la_partie_va_commencer();

void transition_retour_au_menu_principal();

void transition_joueur_suivant(char nom_joueur[]);

void transition_manche_suivante();

//FINAL

void afficher_podium_final(Partie *partie);

void afficher_scores_manche(Partie *partie);

/*
================================================================
INTERFACE
================================================================
*/

// MENUS

void plein_ecran();

void menu_principal(Partie *partie);

void menu_jouer( Partie *partie);

void menu_complet(Partie *partie);

void menu_des_regles( Partie *partie);

void menu_des_credits( Partie *partie);

void todo(char *s);

// ENTRÉES

int validation_du_mode_de_jeu_chosi( int choix_de_partie,  Partie *partie);

int entree_du_nombre_de_joueurs();

void demander_prenom(Partie *partie);

void application_du_choix_du_mode_de_jeu( int choix_partie,  Partie *partie);

void entree_des_informations_des_joueurs(Partie *partie);


/*
================================================================
MECANIQUE
================================================================
*/

void distribuer_carte_depart(Partie *partie);

void demande_carte_a_jouer(Partie *partie, int m);

int passage_au_joueur_suivant(Partie *partie,int m);

void jouer_cartes( Partie *partie, int m);

void poser_au_millieu(Partie *partie);

int passe_consecutif(Partie *partie);

// Boucle principale

void tour_de_jeu(Partie *partie);

/*
================================================================
INITIALISATIONS
================================================================
*/

void initialiser_paquet(Paquet *p);

void initialisation_seuil_victoire(Partie *partie, int choix_partie);

void initialiser_cartes(Carte carte[TAILLE_MAX_MAIN][NB_COULEURS]);

//CALCULS

int calcul_num_pose(Partie *partie);

int calcul_num_choisi(Partie *partie, int m);

void calculer_scores_manche(Partie *partie);

//TRIS

void trier_joueurs_par_score(Partie *partie);

/*
================================================================
VERIFCATIONS
================================================================
*/

int coup_le_plus_grand(Partie *partie, int m);

int verif_conditions_de_jeu(int nb_cartes_jouees, Partie partie);

int verif_meme_couleur(Partie *partie, int m);

int verifier_seuil_victoire(Partie *partie);


// FIN

#endif // BIBLIOCOMPLET_H_INCLUDED
