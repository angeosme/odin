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
// MENUS

void plein_ecran() //fonction récupérée du TP jeu d'echec, car très pratique pour l'affichage et l'ergonomie
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

void menu_principal( Partie *partie)
{
    char menu[4][58]= {"   Jouer !                                            ","   Regles                                             ","   Credits                                            ",
                        "   Quitter                                            ",};
    int choix=0; // numéro de l'option choisie dans le menu
    int frappe=0; //permet de stocker le code de la touche clavier

    int i;


        choix=0;frappe=0;
        system("cls");
        dessiner_logo_odin(4, MILLIEU_MENU-12);
        positionner_curseur(CENTRE_MENU,MILLIEU_MENU);
        printf(" ___________    Bienvenue dans le jeu ODIN   __________\n");
        positionner_curseur(1+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(2+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        for(i=0; i<4; i++)
        {
            //color(2,0);
            positionner_curseur(3+i+CENTRE_MENU,MILLIEU_MENU);
            printf("|%s|\n",menu[i]);
            //color(15,0);

        }
        positionner_curseur(7+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(8+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(9+CENTRE_MENU,MILLIEU_MENU);
        printf("|______________________________________________________|\n");

        positionner_curseur(3+CENTRE_MENU,MILLIEU_MENU);
        color(0,15);
        printf("|%s|\n",menu[0]);
        color(15,0);
        positionner_curseur(19+CENTRE_MENU,MILLIEU_MENU);
        printf("\n");

        while(frappe!=13) // tant qu'on a pas appuyer sur la touche ECHAP
        {
            //printf("e");
            if (kbhit()) //si on a appuyer sur une touche du clavier
            {


                frappe=getch(); // on récupère le code de la touche sur laquelle on a appuyée


                if(frappe==72) //75 est le code de la flèche directionnelle vers le haut
                {

                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU); // positionne le curseur au choix courant
                    color(15,0); // met la couleur du texte en blanc et celle du fond en noir
                    printf("|%s|",menu[choix]); // On réaffiche le choix courant avec les couleurs préalablement choisies, une manière de le désélectionner
                    choix--; // on décrémebte le numéro de l'option
                    if (choix ==-1) choix =3; // les options sont numérotées de 0 à 11
                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU);// positionne le curseur au choix juste dessus du précédent
                    color(0,15);// met la couleur du texte en noir et celle du fond en blanc
                    printf("|%s|\n",menu[choix]);// On réaffiche le nouveau choix  avec les couleurs préalablement choisies, une manière de le séléctionner
                    color(15,0);
                }
                if(frappe==80) //80 est le code de la flèche directionnelle vers le bas
                {

                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU);
                    color(15,0);
                    printf("|%s|",menu[choix]);
                    choix++;
                    if (choix ==4) choix =0;
                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU);
                    color(0,15);
                    printf("|%s|",menu[choix]);
                    color(15,0);
                }

            }
            positionner_curseur(19+CENTRE_MENU,MILLIEU_MENU);

        }

        choix++;
        switch (choix)
        {
        case 1 :
            menu_jouer(partie);
            break;

        case 2 :
            menu_des_regles(partie);
            break;
        case 3:
            menu_des_credits(partie);
            break;

        case 4:
            positionner_curseur(CENTRE_MENU+12, MILLIEU_MENU);
            printf("******************    Au revoir    ******************");
            positionner_curseur(CENTRE_MENU+14, MILLIEU_MENU);
            Sleep(100);
            system("PAUSE");
            break;

        default :

            system("PAUSE");
            break;
    }

}

void menu_jouer(Partie *partie)
{
    char menu[5][58]= {"   Partie standard                                    ","   Partie courte                                      ","   Partie longue                                      ",
                       "   Partie express                                     ","   Retour                                             ",};
    int choix=0; // numéro de l'option choisie dans le menu
    int frappe=0; //permet de stocker le code de la touche clavier

    int i;


        choix=0;frappe=0;
        system("cls");
        dessiner_logo_odin(4, MILLIEU_MENU-12);
        positionner_curseur(CENTRE_MENU,MILLIEU_MENU);
        printf(" ______________    Choix du mode de jeu   _____________\n");
        positionner_curseur(1+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(2+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        for(i=0; i<5; i++)
        {
            //color(2,0);
            positionner_curseur(3+i+CENTRE_MENU,MILLIEU_MENU);
            printf("|%s|\n",menu[i]);
            //color(15,0);

        }
        positionner_curseur(8+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(9+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(10+CENTRE_MENU,MILLIEU_MENU);
        printf("|______________________________________________________|\n");

        positionner_curseur(3+CENTRE_MENU,MILLIEU_MENU);
        color(0,15);
        printf("|%s|\n",menu[0]);
        color(15,0);
        positionner_curseur(19+CENTRE_MENU,MILLIEU_MENU);
        printf("\n");

        while(frappe!=13) // tant qu'on a pas appuyer sur la touche ECHAP
        {
            //printf("e");
            if (kbhit()) //si on a appuyer sur une touche du clavier
            {


                frappe=getch(); // on récupère le code de la touche sur laquelle on a appuyée


                if(frappe==72) //75 est le code de la flèche directionnelle vers le haut
                {

                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU); // positionne le curseur au choix courant
                    color(15,0); // met la couleur du texte en blanc et celle du fond en noir
                    printf("|%s|",menu[choix]); // On réaffiche le choix courant avec les couleurs préalablement choisies, une manière de le désélectionner
                    choix--; // on décrémebte le numéro de l'option
                    if (choix ==-1) choix =4; // les options sont numérotées de 0 à 11
                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU);// positionne le curseur au choix juste dessus du précédent
                    color(0,15);// met la couleur du texte en noir et celle du fond en blanc
                    printf("|%s|\n",menu[choix]);// On réaffiche le nouveau choix  avec les couleurs préalablement choisies, une manière de le séléctionner
                    color(15,0);
                }
                if(frappe==80) //80 est le code de la flèche directionnelle vers le bas
                {

                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU);
                    color(15,0);
                    printf("|%s|",menu[choix]);
                    choix++;
                    if (choix ==5) choix =0;
                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU);
                    color(0,15);
                    printf("|%s|",menu[choix]);
                    color(15,0);
                }

            }
            positionner_curseur(19+CENTRE_MENU,MILLIEU_MENU);

        }

        choix++;
        switch (choix)
        {
        case 1 :
            validation_du_mode_de_jeu_chosi(1, partie);

            break;

        case 2 :
            validation_du_mode_de_jeu_chosi(2, partie);
            break;
        case 3:
            validation_du_mode_de_jeu_chosi(3, partie);
            break;

        case 4:
            validation_du_mode_de_jeu_chosi(4, partie);
            break;

        case 5:
            menu_principal(partie);
            break;

        default :

            system("PAUSE");
            break;
    }

}

void menu_complet(Partie *partie)
{
    menu_principal(partie);
    system("PAUSE");
}

void menu_des_regles( Partie *partie)
{
system("cls");


color(6,0);
printf("========================================\n");
printf("          REGLES DU JEU ODIN\n");
printf("========================================\n\n");
color(15,0);

printf("COMMENT JOUER A ODIN\n\n");

printf("Le jeu en bref :\n");
printf(" - But du jeu : Etre le premier a vider sa main afin de marquer\n");
printf("   le moins de points possible.\n");
printf(" - Mecanique principale : Poser des cartes de valeur superieure\n");
printf("   a celles du centre en combinant astucieusement couleurs et\n");
printf("   chiffres.\n");
printf(" - Condition de victoire : Le joueur ayant le moins de points\n");
printf("   lorsque quelqu'un atteint 15 points remporte la partie.\n\n");

printf("Salut ! Odin est un jeu de cartes inspire de la mythologie\n");
printf("viking melangeant bluff, timing et strategie. Chaque carte\n");
printf("jouee vous oblige a en recuperer une autre. Les parties sont\n");
printf("rapides, tendues et pleines de retournements de situation.\n\n");

color(6,0);
printf("========================================\n");
printf("MATERIEL\n");
printf("========================================\n\n");
color(15,0);

printf("Le jeu se compose de 54 cartes numerotees de 1 a 9,\n");
printf("reparties en 6 couleurs differentes.\n");
printf("Il se joue de 2 a 6 joueurs, a partir de 7 ans,\n");
printf("pour des parties d'environ 15 minutes.\n\n");

color(6,0);
printf("========================================\n");
printf("MISE EN PLACE\n");
printf("========================================\n\n");
color(15,0);

printf("1. Melangez les 54 cartes.\n");
printf("2. Distribuez 9 cartes face cachee a chaque joueur.\n");
printf("3. Chaque joueur regarde ses cartes sans les montrer.\n");
printf("4. Designez un premier joueur au hasard.\n");
printf("5. Les cartes restantes sont mises de cote.\n\n");

color(6,0);
printf("========================================\n");
printf("DEROULEMENT D'UNE MANCHE\n");
printf("========================================\n\n");
color(15,0);


printf("Le premier joueur pose obligatoirement une carte au centre.\n");
printf("Cette carte devient la carte de reference.\n");
printf("Ensuite, chaque joueur peut soit jouer, soit passer.\n\n");

printf("JOUER UNE OU PLUSIEURS CARTES\n\n");

printf("Pour jouer, il faut respecter trois regles :\n");
printf(" - La valeur doit etre strictement superieure a celle du centre.\n");
printf(" - Vous pouvez poser le meme nombre de cartes ou une de plus.\n");
printf(" - Plusieurs cartes doivent etre de meme valeur OU de meme\n");
printf("   couleur.\n\n");

printf("La valeur d'une combinaison correspond au plus grand nombre\n");
printf("possible obtenu en accolant les chiffres dans l'ordre\n");
printf("decroissant.\n");
printf("Exemple : 2 et 8 donnent 82.\n");
printf("Exemple : 2, 4 et 9 donnent 942.\n\n");

printf("Apres avoir joue, vous devez recuperer une carte parmi celles\n");
printf("qui etaient precedemment au centre.\n");
printf("Les autres cartes sont defaussees.\n\n");

printf("Astuce : essayez de recuperer des cartes qui completeront vos\n");
printf("combinaisons futures.\n\n");

printf("PASSER\n\n");

printf("Vous pouvez choisir de passer votre tour.\n");
printf("Vous pourrez rejouer au prochain tour de jeu du meme tour.\n\n");

printf("FIN D'UN TOUR\n\n");

printf("Le tour se termine lorsque tous les joueurs sauf un ont passe.\n");
printf("Les cartes restantes sont defaussees.\n");
printf("Le dernier joueur ayant joue commence alors un nouveau tour.\n\n");

color(6,0);
printf("========================================\n");
printf("FIN DE MANCHE\n");
printf("========================================\n\n");
color(15,0);

printf("La manche se termine :\n");
printf(" - lorsque vous videz votre main ;\n");
printf(" - ou lorsque vous pouvez jouer toutes vos cartes restantes\n");
printf("   d'un seul coup au debut d'un nouveau tour (meme valeur ou\n");
printf("   meme couleur).\n\n");

printf("Dans le cas d'une main vide, aucune carte du centre n'est\n");
printf("recuperee.\n\n");

color(6,0);
printf("========================================\n");
printf("COMPTAGE DES POINTS\n");
printf("========================================\n\n");
color(15,0);

printf("A la fin de chaque manche, chaque joueur marque autant de\n");
printf("points de penalite que de cartes restantes dans sa main.\n");
printf("Le joueur ayant vide sa main marque 0 point.\n\n");

printf("Une nouvelle manche commence avec une nouvelle distribution\n");
printf("de 9 cartes.\n\n");

color(6,0);
printf("========================================\n");
printf("FIN DE LA PARTIE\n");
printf("========================================\n\n");
color(15,0);

printf("La partie s'arrete lorsqu'un joueur atteint ou depasse\n");
printf("15 points.\n");
printf("Le joueur ayant le moins de points remporte la victoire.\n\n");

printf("Variantes :\n");
printf(" - Partie courte : 10 points.\n");
printf(" - Partie standard : 15 points.\n");
printf(" - Partie longue : 20 points ou plus.\n");
printf(" - Partie express : une seule manche.\n\n");

printf("Conseil : ne gardez pas vos grosses cartes trop longtemps,\n");
printf("car chaque carte restante vaut un point de penalite.\n\n");

printf("Bon jeu et que le meilleur Viking l'emporte !\n\n");


color(6,0);
system("PAUSE");
color(15,0);
menu_principal(partie);

}

void menu_des_credits( Partie *partie)
{

system("cls");

color(13,0);

positionner_curseur(CENTRE_MENU - 25, MILLIEU_MENU);
printf("========================================");

positionner_curseur(CENTRE_MENU - 25 + 1, MILLIEU_MENU);
printf("           A PROPOS DU PROJET");

positionner_curseur(CENTRE_MENU - 25 + 2, MILLIEU_MENU);
printf("========================================");

color(15,0);

positionner_curseur(CENTRE_MENU - 25 + 3, MILLIEU_MENU);
printf("Ce jeu a ete cree par Nel HOPPE,");

positionner_curseur(CENTRE_MENU - 25 + 4, MILLIEU_MENU);
printf("Antonin DUMONT et Nolan BENOIT dans le cadre");

positionner_curseur(CENTRE_MENU - 25 + 5, MILLIEU_MENU);
printf("des rattrapages du projet d'algorithmique de");

positionner_curseur(CENTRE_MENU - 25 + 6, MILLIEU_MENU);
printf("l'ESTACA en premiere annee.");

positionner_curseur(CENTRE_MENU - 25 + 7, MILLIEU_MENU);
printf(" ");

positionner_curseur(CENTRE_MENU - 25 + 8, MILLIEU_MENU);
printf("Notre mission etait de recreer le jeu \"Odin\"");

positionner_curseur(CENTRE_MENU - 25 + 9, MILLIEU_MENU);
printf("en langage C.");

positionner_curseur(CENTRE_MENU - 25 + 10, MILLIEU_MENU);
printf(" ");

positionner_curseur(CENTRE_MENU - 25 + 11, MILLIEU_MENU);
printf("Nous disposions d'une semaine pour mener ce");

positionner_curseur(CENTRE_MENU - 25 + 12, MILLIEU_MENU);
printf("projet a bien.");

positionner_curseur(CENTRE_MENU - 25 + 13, MILLIEU_MENU);
printf(" ");

positionner_curseur(CENTRE_MENU - 25 + 14, MILLIEU_MENU);
printf("Vous pouvez retrouver, en annexe de ce projet,");

positionner_curseur(CENTRE_MENU - 25 + 15, MILLIEU_MENU);
printf("un poster presentant notre travail ainsi que");

positionner_curseur(CENTRE_MENU - 25 + 16, MILLIEU_MENU);
printf("les differentes phases de conception.");

positionner_curseur(CENTRE_MENU - 25 + 17, MILLIEU_MENU);
printf(" ");

positionner_curseur(CENTRE_MENU - 25 + 18, MILLIEU_MENU);
printf("Nous vous attendons avec plaisir lors de la");

positionner_curseur(CENTRE_MENU - 25 + 19, MILLIEU_MENU);
printf("soutenance afin de vous rencontrer en personne.");

positionner_curseur(CENTRE_MENU - 25 + 20, MILLIEU_MENU);
printf("Nous serons ravis de vous presenter le projet !");

positionner_curseur(CENTRE_MENU - 25 + 21, MILLIEU_MENU);
color(13,0);
system("PAUSE");
color(15,0);
menu_principal(partie);

}

void todo(char *s)  // onction récupérée au cas où, du TP n°2
{
    system("cls");
    positionner_curseur(CENTRE_MENU+12, MILLIEU_MENU);
    printf("fonctionnalité pas encore programmée, %s",s);
    positionner_curseur(CENTRE_MENU+14, MILLIEU_MENU);

    system("PAUSE");
}

// ENTRÉES

int validation_du_mode_de_jeu_chosi( int choix_de_partie,  Partie *partie)
{
    char menu[5][58]= {"   Continuer                                          ","   Retour                                             "};
    int choix=0; // numéro de l'option choisie dans le menu
    int frappe=0; //permet de stocker le code de la touche clavier

    int i;


        choix=0;frappe=0;
        system("cls");
        //dessiner_logo_odin(4, MILLIEU_MENU-12);
        positionner_curseur(CENTRE_MENU,MILLIEU_MENU);
        color(1,0);
        printf(" Vous avez choisi le mode %s, continuer ?\n", partie->nom_mode_de_jeu);
        color(15,0);
        positionner_curseur(1+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(2+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        for(i=0; i<2; i++)
        {

            positionner_curseur(3+i+CENTRE_MENU,MILLIEU_MENU);
            printf("|%s|\n",menu[i]);


        }
        positionner_curseur(5+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(6+CENTRE_MENU,MILLIEU_MENU);
        printf("|                                                      |\n");
        positionner_curseur(7+CENTRE_MENU,MILLIEU_MENU);
        printf("|______________________________________________________|\n");

        positionner_curseur(3+CENTRE_MENU,MILLIEU_MENU);
        color(15,2);
        printf("|%s|\n",menu[0]);
        color(15,0);
        positionner_curseur(19+CENTRE_MENU,MILLIEU_MENU);
        printf("\n");

        while(frappe!=13) // tant qu'on a pas appuyer sur la touche ECHAP
        {
            //printf("e");
            if (kbhit()) //si on a appuyer sur une touche du clavier
            {


                frappe=getch(); // on récupère le code de la touche sur laquelle on a appuyée


                if(frappe==72) //75 est le code de la flèche directionnelle vers le haut
                {

                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU); // positionne le curseur au choix courant
                    color(15,0); // met la couleur du texte en blanc et celle du fond en noir
                    printf("|%s|",menu[choix]); // On réaffiche le choix courant avec les couleurs préalablement choisies, une manière de le désélectionner
                    choix--; // on décrémebte le numéro de l'option
                    if (choix ==-1) choix =1; // les options sont numérotées de 0 à 11
                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU);// positionne le curseur au choix juste dessus du précédent
                    color(15,2);// met la couleur du texte en noir et celle du fond en blanc
                    printf("|%s|\n",menu[choix]);// On réaffiche le nouveau choix  avec les couleurs préalablement choisies, une manière de le séléctionner
                    color(15,0);
                }
                if(frappe==80) //80 est le code de la flèche directionnelle vers le bas
                {

                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU);
                    color(15,0);
                    printf("|%s|",menu[choix]);
                    choix++;
                    if (choix ==2) choix =0;
                    positionner_curseur(choix+3+CENTRE_MENU,MILLIEU_MENU);
                    color(15,2);
                    printf("|%s|",menu[choix]);
                    color(15,0);
                }

            }
            positionner_curseur(19+CENTRE_MENU,MILLIEU_MENU);

        }

        choix++;
        switch (choix)
        {
        case 1 :
            application_du_choix_du_mode_de_jeu( choix_de_partie, partie);
            break;

        case 2 :
            menu_jouer(partie);
            break;

        default :

            system("PAUSE");
            break;
    }
    return 0;
}

int entree_du_nombre_de_joueurs(Partie *partie)  //mettre structure joueur ici
{
    system("cls");
    positionner_curseur(CENTRE_MENU-20,MILLIEU_MENU);
    color(0,15);
    printf(" ____________  Entrez le nombre de joueurs ____________\n");
    color(15,0);
    positionner_curseur(CENTRE_MENU-19,MILLIEU_MENU);
    printf(" |                (Minimum 2, Maximum 6)              |\n");
    positionner_curseur(CENTRE_MENU-18,MILLIEU_MENU);
    printf(" |->                                                  |\n");
        do
        {
        positionner_curseur(CENTRE_MENU-18,MILLIEU_MENU+5);
        scanf("%d",&partie->nb_joueur);             //entrée du nombre de joueurs souhaité, la boucle permet de ne pas entrer des valeurs invalides
        }
        while(partie->nb_joueur>6 || partie->nb_joueur<2);

    return partie->nb_joueur;

}

void demander_prenom(Partie *partie)
{

    partie->nb_joueur=entree_du_nombre_de_joueurs(partie);

    entree_des_informations_des_joueurs(partie);



    /*transition_la_partie_va_commencer();
    printf("Il y a %d joueurs, les voici :\n",nb_joueurs);
    for(int i = 0; i < nb_joueurs; i++)
    {
        printf("%s\n",ensemble_des_joueurs[i].nom);
    }*/


}

void application_du_choix_du_mode_de_jeu(int choix_partie, Partie *partie)
{
    system("cls");
    switch(choix_partie)
    {
    case 1 :
        printf("Nous allons lancer le mode 1 : %s",partie->nom_mode_de_jeu);  //à completer avec les sous programme lancer_partie_...
        initialisation_seuil_victoire(partie, choix_partie);
        demander_prenom(partie);
        break;
    case 2 :
        printf("Nous allons lancer le mode 2 : %s",partie->nom_mode_de_jeu);
        initialisation_seuil_victoire(partie, choix_partie);
        demander_prenom(partie);
        break;
    case 3 :
        printf("Nous allons lancer le mode 3 : %s",partie->nom_mode_de_jeu);
        initialisation_seuil_victoire(partie, choix_partie);
        demander_prenom(partie);
        break;
    case 4 :
        printf("Nous allons lancer le mode 4 : %s",partie->nom_mode_de_jeu);
        initialisation_seuil_victoire(partie, choix_partie);
        demander_prenom(partie);
        break;
    }
}

void entree_des_informations_des_joueurs(Partie *partie)
{
    int a;
    a=CENTRE_MENU-17;
    for(int i = 0; i<partie->nb_joueur; i ++)
    {
        positionner_curseur(a,MILLIEU_MENU);
        color(0,15);
        printf(" ____________  Entrez le nom du joueur %d  _____________\n",(i+1));
        color(15,0);
        positionner_curseur(a+1,MILLIEU_MENU);
        printf(" |->                                                  |\n");
        positionner_curseur(a+1,MILLIEU_MENU+5);
        scanf("%s",&partie->joueur[i].nom);
        partie->joueur[i].numero_joueur=i;
        a=a+2;
    }

}



