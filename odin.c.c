#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include "biblio.h"
#include <conio.h>

void initialiser_paquet(Paquet *p)
{
    int carte_num=0;
    for (int i=1; i<=NB_COULEURS; i++)
    {
        for (int j=1; j<=TAILLE_MAX_MAIN; j++)
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
    srand(time(NULL));
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

int passage_au_joueur_suivant(Partie *partie,int m)
{

    partie->joueur[m].passer_au_joueur_suivant=0;

    positionner_curseur(118,0);
    printf("Veux-tu passer ton tour ? Tape 1 pour passer. 0 sinon, (LE PREMIER JOUEUR NE PEUX PAS PASSER)");

    do
    {
    positionner_curseur(119,0);
    scanf("%d",&partie->joueur[m].passer_au_joueur_suivant);
    positionner_curseur(119,0);
    }
    while(partie->joueur[m].passer_au_joueur_suivant < 0 || partie->joueur[m].passer_au_joueur_suivant > 1);

    return partie->joueur[m].passer_au_joueur_suivant;



}

void demande_carte_a_jouer(Partie *partie, int m)
{
    int saisie_valide=0;
    int i;

    while (1)
    {
         positionner_curseur(120,0);
         printf("combien de cartes veux tu jouer ? (si tu es le 1er a jouer, joue une seule carte)");
         scanf("%d",&partie->joueur[m].nb_cartes_jouees);
         if (partie->joueur[m].nb_cartes_jouees>=0 && partie->joueur[m].nb_cartes_jouees<=TAILLE_MAX_MAIN && partie->joueur[m].nb_cartes_jouees>=partie->pile_milieu.nb_carte_milieu && partie->joueur[m].nb_cartes_jouees<=partie->pile_milieu.nb_carte_milieu+1)
            {
               break;
            }

    }
    while (saisie_valide==0)
    {
        for (i=0; i<partie->joueur[m].nb_cartes_jouees; i++)
        {
            printf("carte numero %d ?(dans l'ordre décroissant des valeurs",i);  //demande quelles cartes ?
            scanf("%d",&partie->joueur[m].choix[i]);

            if (partie->joueur[m].choix[i]-1>=0 && partie->joueur[m].choix[i]-1<=partie->joueur[m].nb_cartes) //verif que la saisie est bonne
            {
               saisie_valide=1;
            }
        }
    }



}

void jouer_cartes( Partie *partie, int m)
{
    int choix_carte_recuperee;
    int nouvelle_taille_main=0;
    int a_recupere=0;
    if (partie->pile_milieu.nb_carte_milieu>0)
    {
        printf("quelle carte veux tu prendre dans la pile du milieu (position de la carte et non pas sa valeur)");
        scanf("%d",&choix_carte_recuperee);
        a_recupere=1;
    }
    //--------------------------------------------------
    int a_joue[TAILLE_MAX_MAIN]={0};  //utile pour faire la nouvelle main après avoir jouer
    partie->pile_milieu.nb_carte_milieu=0;
    for (int i=0; i<partie->joueur[m].nb_cartes_jouees; i++)
    {
        a_joue[partie->joueur[m].choix[i]-1]=1;
        partie->joueur[m].carte_jouee[i]=partie->joueur[m].main[partie->joueur[m].choix[i]-1];
        partie->pile_milieu.nb_carte_milieu++;
        partie->pile_milieu.carte_posee[i]=partie->joueur[m].main[partie->joueur[m].choix[i]-1];
    }

    //------------------------------------------
     for (int j = nouvelle_taille_main; j < partie->joueur[m].nb_cartes; j++)
    {
        if(a_joue[j]==0)    //si la carte est pas jouée alors... si elle est jouée, pas d'action donc nouvelle taille main se decale de j, donc réordonne la main
        {
            partie->joueur[m].main[nouvelle_taille_main]=partie->joueur[m].main[j];
            nouvelle_taille_main++;
        }
    }
    partie->joueur[m].nb_cartes=nouvelle_taille_main; // +1 car il choisit une carte deja dans la pile

    if ( a_recupere=1)
    {
        partie->joueur[m].main[nouvelle_taille_main]=partie->pile_milieu.carte_posee[choix_carte_recuperee-1];
        nouvelle_taille_main++;
        partie->joueur[m].nb_cartes++;
    }
}

void poser_au_millieu(Partie *partie)
{
    for (int i=0; i<partie->joueur[partie->joueur->numero_joueur].nb_cartes_jouees; i++)
    {
        partie->pile_milieu.carte_posee[i]=partie->joueur[partie->joueur->numero_joueur].carte_jouee[i];
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

int calcul_num_pose(Partie *partie)  //tri a bulle
{
    Carte temp;
    Carte copie[TAILLE_MAX_MAIN];
    int valeur=0;
    for (int k=0; k<partie->pile_milieu.nb_carte_milieu; k++)
    {
        copie[k]=partie->pile_milieu.carte_posee[k];               //faire copie sinon on modofie l'ordre des anciennes cartes du milieu avant meme jouer_partie
    }
    for (int i=0; i<partie->pile_milieu.nb_carte_milieu; i++)
    {
        for (int j=0; j<partie->pile_milieu.nb_carte_milieu-i-1; j++)
        {
            if (partie->pile_milieu.carte_posee[j].chiffre<partie->pile_milieu.carte_posee[j+1].chiffre)
            {
                temp=copie[j];
                copie[j]=copie[j+1];
                copie[j+1]=temp;
            }
        }
    }
     for (int l=0; l<partie->pile_milieu.nb_carte_milieu; l++)
     {
         valeur=valeur*10+copie[l].chiffre;    //valeur*10 pour le nombre des dizaine puis pour les unités (ex: 27.  valeur=0*10+2; valeur=2*10+7)
     }
     return valeur;
}

int calcul_num_choisi(Partie *partie, int m)
{
    Carte temp;
    int valeur=0;
    for (int i=0; i<partie->joueur[m].nb_cartes_jouees; i++)
    {
        for (int j=0; j<partie->joueur[m].nb_cartes_jouees-i-1; j++)
        {
            if (partie->joueur[m].main[partie->joueur[m].choix[j]-1].chiffre<partie->joueur[m].main[partie->joueur[m].choix[j+1]-1].chiffre)
            {
                temp=partie->joueur[m].main[partie->joueur[m].choix[j]-1];
                partie->joueur[m].main[partie->joueur[m].choix[j]-1]=partie->joueur[m].main[partie->joueur[m].choix[j+1]-1];
                partie->joueur[m].main[partie->joueur[m].choix[j+1]-1]=temp;
            }
        }
    }
     for (int k=0; k<partie->joueur[m].nb_cartes_jouees; k++)
     {
         valeur=valeur*10+ partie->joueur[m].main[partie->joueur[m].choix[k]-1].chiffre;    //valeur*10 pour le nombre des dizaine puis pour les unités (ex: 27.  valeur=0*10+2; valeur=2*10+7)
     }
     return valeur;
}

int verif_meme_couleur(Partie *partie, int m)
{
    int couleur_differente=0;
    for (int i=0; i<partie->joueur[m].nb_cartes_jouees; i++)
    {
        if(partie->joueur[m].main[partie->joueur[m].choix[i]-1].couleur!=partie->joueur[m].main[partie->joueur[m].choix[i+1 ]-1].couleur)
        {
             couleur_differente=1;
        }
    }
}


 int coup_le_plus_grand(Partie *partie, int m)
 {
     int valeur_joueur;
     int valeur_milieu;

     valeur_milieu= calcul_num_pose(partie);
     valeur_joueur= calcul_num_choisi(partie, m);

     return valeur_joueur > valeur_milieu;
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

void afficher_carte_milieu(Partie *partie, int m)
{
    int ecartement_milieu=10;
            for (int c=0; c<partie->pile_milieu.nb_carte_milieu; c++)
            {
                dessiner_carte_du_jeu( 20,ecartement_milieu, partie->pile_milieu.carte_posee[c].couleur, partie->pile_milieu.carte_posee[c].chiffre);
                ecartement_milieu=ecartement_milieu+PAS_ENTRE_CARTES;
            }
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
            printf("Choix invalide ! merci de taper une valeur entre 1 et 12 ! \n");
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
            validation_du_mode_de_jeu_chosi("Partie standard",1, partie);

            break;

        case 2 :
            validation_du_mode_de_jeu_chosi("Partie courte",2, partie);
            break;
        case 3:
            validation_du_mode_de_jeu_chosi("Partie longue",3, partie);
            break;

        case 4:
            validation_du_mode_de_jeu_chosi("Partie express",4, partie);
            break;

        case 5:
            menu_principal(partie);
            break;

        default :
            printf("Choix invalide ! merci de taper une valeur entre 1 et 12 ! \n");
            system("PAUSE");
            break;
    }

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

/*
Les fonctions menu_des_regles et menu_des_credits étant très répétitives, nous avons été assitées par l'IA pour rendre la tâche beaucoup plus rapide ! (saut de ligne par prtintf...),
    => c'est un simple gain de temps ici
*/


/*
======================================================================
ENTRÉE DES INFORMATION DE PARTIE
======================================================================
*/

int validation_du_mode_de_jeu_chosi(char nom_mode_de_jeu[], int choix_de_partie,  Partie *partie)
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
            application_du_choix_du_mode_de_jeu(nom_mode_de_jeu, choix_de_partie, partie);
            break;

        case 2 :
            menu_jouer(partie);
            break;

        default :
            printf("Choix invalide ! merci de taper une valeur entre 1 et 12 ! \n");
            system("PAUSE");
            break;
    }
    return 0;
}


//INSERER LES PROGRAMMES DE LANCEMENT DE PARTIE ICI !
//   |
//   |
//   v
void application_du_choix_du_mode_de_jeu(char nom_mode_de_jeu[], int choix_de_partie, Partie *partie)
{
    system("cls");
    switch(choix_de_partie)
    {
    case 1 :
        printf("Nous allons lancer le mode 1 : %s",nom_mode_de_jeu);  //à completer avec les sous programme lancer_partie_...
        demander_prenom(partie);
        break;
    case 2 :
        printf("Nous allons lancer le mode 2 : %s",nom_mode_de_jeu);
        demander_prenom(partie);
        break;
    case 3 :
        printf("Nous allons lancer le mode 3 : %s",nom_mode_de_jeu);
        demander_prenom(partie);
        break;
    case 4 :
        printf("Nous allons lancer le mode 4 : %s",nom_mode_de_jeu);
        demander_prenom(partie);
        break;
    }
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
void menu_complet(Partie *partie)
{//-------------------------menu d'entrée

    menu_principal(partie);

    dessiner_logo_odin(1,70);
    positionner_curseur(90,6);

}
//-----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

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
void tour_de_jeu(Partie *partie)
{
    int ecartement=0;
    int j;
    int c;
    int nb_cartes_jouees;
    int decalage=20;
    Paquet p;
    int tour;
    initialiser_paquet(&partie->paquet);
    distribuer_carte_depart(partie);
    partie->pile_milieu.nb_carte_milieu=0;
//-------------------------------------------------------------afficher main du joueur
    while (1)
    {
         for ( j=0; j<partie->nb_joueur; j++)
        {




            //positionner_curseur(decalage, 0);
            //decalage=decalage+ESPACE_ENTRE_TOURS;
            tour++;
            partie->joueur[j].nb_cartes_jouees=0;
            system("cls");
            ecartement=0;
            for (c=0; c<partie->joueur[j].nb_cartes; c++)
            {

                dessiner_carte_du_jeu( 50, ecartement, partie->joueur[j].main[c].couleur, partie->joueur[j].main[c].chiffre);
                ecartement=ecartement+PAS_ENTRE_CARTES;
            }
            if (j>=1)
            {
                afficher_carte_milieu(partie, j-1);
            }
            else
            {
                 afficher_carte_milieu(partie, j);
            }

            passage_au_joueur_suivant(partie, j);

            if (partie->joueur[j].passer_au_joueur_suivant==0)
            {

            do
            {
                demande_carte_a_jouer(partie, j);



            }while (!coup_le_plus_grand(partie, j));


            jouer_cartes(partie, j);

           // poser_au_millieu(partie);
            //---------------------------------------------------------affichage milieu
            afficher_carte_milieu(partie, j);


            }

        }




        }
        partie->nb_fois_joue++;
    }

