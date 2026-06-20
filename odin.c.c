#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "biblio.h"
#include <conio.h>

void initialiser_paquet(Paquet *p)
{
    int carte_num=0;
    for (int i=0; i<NB_COULEURS; i++)
    {
        for (int j=0; j<TAILLE_MAX_MAIN; j++)
        {
           p->carte[carte_num].couleur=i;
           p->carte[carte_num].chiffre=j;
           p->carte[carte_num].utilisee_tri=0;
           carte_num++;
        }
    }
}


void distribuer_carte_depart(Partie *partie)
{
    int j=0;
    for (int k=0; k<partie->nb_joueur; k++)  //defini le nb de cartes des joueurs a 0
    {
        partie->joueur[k].nb_cartes=0;
    }
    while (j<partie->nb_joueur)
    {
        int c=0;
        while (c<TAILLE_MAX_MAIN || partie->joueur[j].nb_cartes<9) //tant que le joueur a pas 9 cartes
        {
            int position;
            while(1) //boucle infinie pour vérifier que la carte n'est pas deja utilisée
            {
                position=rand()% NB_CARTES_MAX;
                if (partie->paquet.carte[position].utilisee_tri==0)
                    break;
            }
            partie->paquet.carte[position].utilisee_tri=1;     //marque la carte tirée
            partie->joueur[j].main[c]=partie->paquet.carte[position];  //donne la carte au joueur
            partie->joueur[j].nb_cartes++;
            c++;
        }
        partie->joueur[j].nb_cartes=TAILLE_MAX_MAIN;
        j++;
    }
}

void demande_carte_a_jouer(Partie *partie)
{
    int saisie_valide=0;
    Pile_milieu pile;
    pile.nb_carte_milieu=0;
    int i;
    while (1)
    {
         positionner_curseur(120,0);
         printf("combien de cartes veux tu jouer ? (si tu es le 1er a jouer, joue une seule carte)");
         scanf("%d",&partie->joueur->nb_cartes_jouees);
         if (partie->joueur->nb_cartes_jouees>=0 && partie->joueur->nb_cartes_jouees<=TAILLE_MAX_MAIN && partie->joueur->nb_cartes_jouees>=pile.nb_carte_milieu && partie->joueur->nb_cartes_jouees<=pile.nb_carte_milieu+1)
            {
               break;
            }

    }
    while (saisie_valide==0)
    {
        for (i=0; i<partie->joueur->nb_cartes_jouees; i++)
        {
            printf("carte numero %d ?",i);  //demande quelles cartes ?
            scanf("%d",&partie->joueur->choix[i]);

            if (partie->joueur->choix[i]-1>=0 && partie->joueur->choix[i]-1<=partie->joueur->nb_cartes) //verif que la saisie est bonne
            {
               saisie_valide=1;
            }
        }
    }
}

void jouer_cartes( Partie *partie)
{
    int choix_carte_recuperee;
    if (partie->pile_milieu.nb_carte_milieu>=1)
    {
        printf("quelle carte veux tu prendre dans la pile du milieu (position de la carte et non pas sa valeur)");
        scanf("%d",&choix_carte_recuperee);
        partie->joueur->main[TAILLE_MAX_MAIN+1]=partie->pile_milieu.carte_posee[choix_carte_recuperee];
    }
    //--------------------------------------------------
    int a_joue[TAILLE_MAX_MAIN]={0};  //utile pour faire la nouvelle main après avoir jouer
    for (int i=0; i<partie->joueur->nb_cartes_jouees; i++)
    {
        a_joue[partie->joueur->choix[i]-1]=1;
        partie->joueur->carte_jouee[i]=partie->joueur->main[partie->joueur->choix[i]-1];
        partie->pile_milieu.nb_carte_milieu++;
        partie->pile_milieu.carte_posee[i]=partie->joueur->main[partie->joueur->choix[i]-1];
    }
    //------------------------------------------
     int nouvelle_taille_main=0;
     for (int j = 0; j < partie->joueur->nb_cartes; j++)
    {
        if(a_joue[j]==0)    //si la carte est pas jouée alors... si elle est jouée, pas d'action donc nouvelle taille main se decale de j, donc réordonne la main
        {
            partie->joueur->main[nouvelle_taille_main]=partie->joueur->main[j];
            nouvelle_taille_main++;
        }
    }
    partie->joueur->nb_cartes=nouvelle_taille_main +1; // +1 car il choisit une carte deja dans la pile

//-------------------------------------------------------affichage milieu
    int ecartement_milieu=10;
    for (int c=0; c<partie->joueur->nb_cartes_jouees; c++)
    {
        dessiner_carte_du_jeu( 15,ecartement_milieu, partie->pile_milieu.carte_posee[c].couleur, partie->pile_milieu.carte_posee[c].chiffre);
        ecartement_milieu=ecartement_milieu+PAS_ENTRE_CARTES;
    }



}

void poser_au_millieu(Partie *partie, int nb_cartes_jouees, Carte carte_jouee[TAILLE_MAX_MAIN])
{
    partie->pile_milieu.nb_carte_milieu=nb_cartes_jouees;
    //----------------------------------
    for (int i=0; i<nb_cartes_jouees; i++)
    {
        partie->pile_milieu.carte_posee[i]=carte_jouee[i];
    }
}

int verif_conditions_de_jeu(int nb_cartes_jouees, Partie partie)
{
    if (nb_cartes_jouees<partie.pile_milieu.nb_carte_milieu || nb_cartes_jouees>partie.pile_milieu.nb_carte_milieu+1 )
    {
        return 1;    //utile pour la verif dans le main
    }
    return 0;
}

void calcul_num_pose(Partie partie)
{
    int temp;
    for (int i=0; i<partie.pile_milieu.nb_carte_milieu; i++)
    {
        for (int j=0; j<partie.pile_milieu.nb_carte_milieu-i-1; j++)
        {
            if (partie.pile_milieu.carte_posee[j].chiffre<partie.pile_milieu.carte_posee[j+1].chiffre)
            {
                temp=partie.pile_milieu.carte_posee[j].chiffre;
                partie.pile_milieu.carte_posee[j].chiffre=partie.pile_milieu.carte_posee[j+1].chiffre;
                partie.pile_milieu.carte_posee[j].chiffre=temp;
            }
        }
    }
}

/*
======================================================================
DESSIN GENERAL
======================================================================
*/
void positionner_curseur(int ligne, int colonne) //fonction récupérée du TP jeu d'echec, car très pratique pour notre jeu
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);//permet de déclarer la variable "hstdout" qui fait référénce à la console
    COORD pos; // COORD est un type structuré défini dans la bibliothèque windows.h
    pos.X=colonne;// numéro de la colonne
    pos.Y=ligne;// numéro de la ligne
    SetConsoleCursorPosition(hStdout, pos);
}

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

/*
======================================================================
DESSIN CARTE
======================================================================
*/

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
            validation_du_mode_de_jeu_chosi("Partie standard");

            break;

        case 2 :
            validation_du_mode_de_jeu_chosi("Partie courte");
            break;
        case 3:
            validation_du_mode_de_jeu_chosi("Partie longue");
            break;

        case 4:
            validation_du_mode_de_jeu_chosi("Partie express");
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
ENTRÉE DES INFORMATION DE PARTIE
======================================================================
*/

void validation_du_mode_de_jeu_chosi(char nom_mode_de_jeu[])
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
        printf(" Vous avez choisi le mode %s, continuer ?\n", nom_mode_de_jeu);
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
            demander_prenom();
             break;

        case 2 :
            menu_jouer();
            break;

        default :
            printf("Choix invalide ! merci de taper une valeur entre 1 et 12 ! \n");
            system("PAUSE");
            break;
    }
}

int entree_du_nombre_de_joueurs()  //mettre structure joueur ici
{
    int nb_joueurs;
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
        scanf("%d",&nb_joueurs);             //entrée du nombre de joueurs souhaité, la boucle permet de ne pas entrer des valeurs invalides
        }
        while(nb_joueurs>6 || nb_joueurs<2);

    return nb_joueurs;

}

void entree_des_informations_des_joueurs(Joueur *ensemble_des_joueurs, int nb_joueurs)
{
    int a;
    a=CENTRE_MENU-17;
    for(int i = 0; i<nb_joueurs; i ++)
    {
        positionner_curseur(a,MILLIEU_MENU);
        color(0,15);
        printf(" ____________  Entrez le nom du joueur %d  _____________\n",(i+1));
        color(15,0);
        positionner_curseur(a+1,MILLIEU_MENU);
        printf(" |->                                                  |\n");
        positionner_curseur(a+1,MILLIEU_MENU+5);
        scanf("%s",&ensemble_des_joueurs[i].nom[50]);
        ensemble_des_joueurs[i].numero_joueur=i+1;
        a=a+2;
    }
    plein_ecran();
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
        color(0,0);
        system("PAUSE");
        positionner_curseur(5+CENTRE_MENU,MILLIEU_MENU);
        color(15,0);
        system("cls");
}
//-----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
void menu_complet()
{//-------------------------menu d'entrée
    plein_ecran();
    menu_principal();

    dessiner_logo_odin(1,70);
    positionner_curseur(90,6);

}
//-----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

void demander_prenom()
{
    Joueur *ensemble_des_joueurs;
    int nb_joueurs;
    plein_ecran();

    nb_joueurs=entree_du_nombre_de_joueurs();

    ensemble_des_joueurs = malloc(nb_joueurs*sizeof(Joueur));

    entree_des_informations_des_joueurs(ensemble_des_joueurs, nb_joueurs);

    /*transition_la_partie_va_commencer();
    printf("Il y a %d joueurs, les voici :\n",nb_joueurs);
    for(int i = 0; i < nb_joueurs; i++)
    {
        printf("%s\n",ensemble_des_joueurs[i].nom);
    }*/


}
void tour_de_jeu(Partie *partie)
{
    int ecartement=0;
    int j;
    int c;
    int nb_cartes_jouees;
    Paquet p;
    initialiser_paquet(&partie->paquet);
    distribuer_carte_depart(partie);

        for ( j=0; j< partie->nb_joueur; j++)
        {
            for (c=0; c<9; c++) //ecartement des cartes
            {

                dessiner_carte_du_jeu( 34, ecartement, partie->joueur[j].main[c].couleur, partie->joueur[j].main[c].chiffre);
                ecartement=ecartement+PAS_ENTRE_CARTES;
            }
            demande_carte_a_jouer(partie);
            jouer_cartes(partie);
        }

}
