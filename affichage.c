#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "biblio.h"
#include <conio.h>

/*
======================================================================
//DESSIN GENERAL
======================================================================
*/
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

/*
======================================================================
OPTION ET MENU
/!\ programmes empruntés, modifiés et adaptés du TP n°2
======================================================================
*/

void todo(char *s)
{
    system("cls");
    positionner_curseur(CENTRE_MENU+12, MILLIEU_MENU);
    printf("fonctionnalité pas encore programmée, %s",s);
    positionner_curseur(CENTRE_MENU+14, MILLIEU_MENU);

    system("PAUSE");
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


void menu_principal()
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
            menu_jouer();
            break;

        case 2 :
            //printf("implémenter et insérer la fonction : \n void afficher_list(S_Etudiant tab[], int nb) \n");
            todo(" vous devez implémenter et insérer la fonction : \n\n void afficher_list(S_Etudiant tab[], int nb) \n\n\n");
            break;
        case 3:
            todo(" vous devez implémenter et insérer les fonctions : \n\n int filtre_statut(int s,S_Etudiant Tab1[],int nb1,S_Etudiant Tab2[])\n\n void afficher_list(S_Etudiant tab[], int nb)  \n\n\n");
            break;

        case 4:
            positionner_curseur(CENTRE_MENU+12, MILLIEU_MENU);
            printf("******************    Au revoir    ******************");
            positionner_curseur(CENTRE_MENU+14, MILLIEU_MENU);
            Sleep(100);
            system("PAUSE");
            break;

        default :
            printf("Choix invalide ! merci de taper une valeur entre 1 et 12 ! \n");
            system("PAUSE");
            break;
    }

}


void menu_jouer()
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
        for(i=0; i<6; i++)
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
            todo(" vous devez implémenter et insérer la fonction : \n\n void afficher_list(S_Etudiant tab[], int nb) \n\n\n");
            break;

        case 2 :
            //printf("implémenter et insérer la fonction : \n void afficher_list(S_Etudiant tab[], int nb) \n");
            todo(" vous devez implémenter et insérer la fonction : \n\n void afficher_list(S_Etudiant tab[], int nb) \n\n\n");
            break;
        case 3:
            todo(" vous devez implémenter et insérer les fonctions : \n\n int filtre_statut(int s,S_Etudiant Tab1[],int nb1,S_Etudiant Tab2[])\n\n void afficher_list(S_Etudiant tab[], int nb)  \n\n\n");
            break;

        case 4:
            todo(" vous devez implémenter et insérer les fonctions : \n\n int filtre_statut(int s,S_Etudiant Tab1[],int nb1,S_Etudiant Tab2[])\n\n void afficher_list(S_Etudiant tab[], int nb)  \n\n\n");
            break;

        case 5:
            menu_principal();
            break;

        default :
            printf("Choix invalide ! merci de taper une valeur entre 1 et 12 ! \n");
            system("PAUSE");
            break;
    }

}

/*
======================================================================
TRANSITIONS
======================================================================
*/

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
        system("PAUSE");
        system("cls");
}

