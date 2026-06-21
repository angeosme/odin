#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "biblio.h"
#include <conio.h>
//version du 21/06/2026  14h01

/*
===================================================================
TEST AFFICHAGE MAIN JOUEUR (ALÉATOIRE)
===================================================================
*/


/*int main()
{
    plein_ecran();

    srand(time(NULL));

    int couleur_carte, valeur_carte;

    int tab[] = {BLEU, ROUGE, ROSE, VERT, MARRON, JAUNE};

    for(int i = 1; i<10; i++)
    {
        couleur_carte = tab[rand() % 5 + 0];
        valeur_carte = rand() % 9 + 1;
        dessiner_carte_du_jeu(1, 5+PAS_ENTRE_CARTES*i, couleur_carte, valeur_carte);
    }



    positionner_curseur(15,6);
    return 0;
}
*/



/*
===================================================================
TEST MENU PRINCIPAL AVEC CERTAINES ENTRÉES ET MODE DE JEU
===================================================================
*/


int main()
{
    plein_ecran();
    menu_principal();



   // dessiner_logo_odin(1,70);
   // positionner_curseur(90,6);
    return 0;
}




/*
===================================================================
TEST DIFFERENTES TRANSITIONS
===================================================================
*/

/*
int main ()
{
    plein_ecran();
    transition_la_partie_va_commencer();
    transition_joueur_suivant("Dany Hulot");
    transition_manche_suivante();
    transition_retour_au_menu_principal();



    return 0;
}
*/

/*
===================================================================
TEST ENTRÉES NOM JOUEURS
===================================================================
*/
/*int main ()
{
    Joueur *ensemble_des_joueurs;
    int nb_joueurs;
    plein_ecran();

    nb_joueurs=entree_du_nombre_de_joueurs();

    ensemble_des_joueurs = malloc(nb_joueurs*sizeof(Joueur));

    entree_des_informations_des_joueurs(ensemble_des_joueurs, nb_joueurs);

    transition_la_partie_va_commencer();
    printf("Il y a %d joueurs, les voici :\n",nb_joueurs);
    for(int i = 0; i < nb_joueurs; i++)
    {
        printf("%s\n",ensemble_des_joueurs[i].nom);
    }
}
*/


/*
===================================================================
TEST d'ANTONIN
===================================================================
*/
/*
int main ()
{
    plein_ecran();
    Partie partie;
    partie.nb_joueur=1;
    //menu_complet();
    tour_de_jeu(&partie);
}
*/


