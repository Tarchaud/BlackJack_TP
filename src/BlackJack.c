#include "BlackJack.h"

//Partie : Initialisation et Mélange du paquet

void InitPaquet(struct sCarte* Paquet){
    //Déclaration des variables et Initialisation
    int int_i;
    int int_j;
    int_i=0;
    int c;
    c =0;
    //Boucle tant que, initialisation du paquet
    while (int_i<13)
    {
        //Boucle pour, associer la valeur de la carte et la couleur
        for (int_j = 0; int_j < 4; int_j++)
        {
            //Teste si la carte est supérieur a un 9
            if (int_i>=9)
            {
                Paquet[4*int_i+int_j].valeur=10;
                Paquet[4*int_i+int_j].couleur=c;
            }
            else if (int_i==0)//Initialisation des as
            {
                Paquet[4*int_i+int_j].valeur=int_i+11;
                Paquet[4*int_i+int_j].couleur=c;
            }
            else
            {
                Paquet[4*int_i+int_j].valeur=int_i+1;
                Paquet[4*int_i+int_j].couleur=c;
            }
            c =c+1;
        }
        int_i =int_i+1;
        c=0;
    }
}

void melangePaquet(struct sCarte* Paquet){
    //Déclaration des variables et Initialisation
    struct sCarte melangeur[52];
    int histo[52];
    int pos;
    int i;
    int placer;
    //Création de l'aléatoire
    srand(time(NULL));
    //Boucle pour, initialisation de l'histogramme 
    for (i = 0; i < 52 ; i++)
    {
        histo[i]=-1;
    }
    //Boucle pour, mélanger le paquet dans le mélangeur 
    for ( i = 0; i < 52; i++)
    {
        placer =0;
        //Boucle tant que, placer une carte 
        while (placer==0)
        {
            pos=rand()%52;
            if (histo[pos]==-1)
            {
                placer=1;
                melangeur[i]=*(Paquet+pos);
                histo[pos]=0;
            }   
        }
    }
    //Boucle pour, mettre le melangeur dans le paquet 
    for ( i = 0; i < 52; i++)
    {
        *(Paquet+i)=melangeur[i];
    }   
}

//Partie : Création des joueur 

void creationJoueur(struct Joueur* participant,int nb_joueur){
    //Déclaration des variables et Initialisation
    int i; 
    int int_retour;
    //Boucle pour, initialiser les joueur
    for (i = 0; i < nb_joueur; i++)
    {
        //Affiche le nom du joueur 
        printf("Quel est le nom de joueur %d : ",i+1);
        scanf("%s",participant[i].nom);
        //initialisation de l'argent du joueur
        participant[i].argent=0;
        //Boucle tant que, demande l'argent du joueur
        while (participant[i].argent<=0)
        {
            //demande l'argent du joueur
            printf("Quel est la somme d'argent que joueur %d veut jouer : ",i+1);
            int_retour=scanf("%lf",&participant[i].argent);
            //Evite le probleme de buffer 
            scanf("%*[^\n]");
            getchar();
            //Boucle tant que, demande l'argent du joueur tant que la saisie est fausse
            while (int_retour!=1)
            {
                //demande l'argent du joueur
                fprintf(stderr,"Saisie incorrecte.\n");
                printf("Quel est la somme d'argent que joueur %d veut jouer : ",i+1);
                int_retour=scanf("%lf",&participant[i].argent);
                //Evite le probleme de buffer
                scanf("%*[^\n]");
                getchar();
            }
            //teste de la saisie
            if (participant[i].argent<=0)
            {
                printf("Vous devez entrer un chiffre supérieur à 0.\n");
            }
            
        }
        //initialisation du nombre de carte et de la somme des carte du joueur   
        participant[i].nbCarte=0;
        participant[i].sommecarte=0;
    }
}

//Partie : demande des mises

void demandeMise(struct Joueur* participant,int nb_joueur){
    //Déclaration des variables et Initialisation
    int i;
    int int_retour;
    //Boucle pour, demande la mise de chaque joueur
    for ( i = 0; i < nb_joueur; i++)
    {
        participant[i].mise=-1;
        //Boucle tant que, la mise est pas bonne
        while (participant[i].mise<0)
        {
            //Demande la mise
            printf("\n%s, mettez votre mise (argent : %lf): ",participant[i].nom,participant[i].argent);
            int_retour=scanf("%lf",&participant[i].mise);
            //Evite le probleme de buffer
            scanf("%*[^\n]");
            getchar();
            //boucle tant que, la saisie n'est pas correcte
            while (int_retour!=1)
            {
                //Demande la mise
                fprintf(stderr,"Saisie incorrecte.\n");
                printf("\n%s, mettez votre mise (argent : %lf): ",participant[i].nom,participant[i].argent);
                int_retour=scanf("%lf",&participant[i].mise);
                //Evite le probleme de buffer
                scanf("%*[^\n]");
                getchar();
            }
            //Teste si le joueur a assez de sous
            if (participant[i].mise>participant[i].argent)
            {
                printf("Vous avez pas assez\n");
                //Demande la mise 
                while (participant[i].mise>participant[i].argent)
                {
                    printf("\n%s, mettez votre mise (argent : %lf): ",participant[i].nom,participant[i].argent);
                    int_retour=scanf("%lf",&participant[i].mise);
                    //Evite le probleme de buffer
                    scanf("%*[^\n]");
                    getchar();
                    //boucle tant que, la saisie n'est pas correcte
                    while (int_retour!=1)
                    {
                        //Demande la mise
                        fprintf(stderr,"Saisie incorrecte.\n");
                        printf("\n%s, mettez votre mise (argent : %lf): ",participant[i].nom,participant[i].argent);
                        int_retour=scanf("%lf",&participant[i].mise);
                        //Evite le probleme de buffer
                        scanf("%*[^\n]");
                        getchar();
                    }
                }
            }
            else if (participant[i].mise<0)
            {
                printf("Vous devez entrer une mise qui supérieure ou égale à 0.\n");
            }
            
        }
        participant[i].argent=participant[i].argent-participant[i].mise;
    }
}

//Partie : tirage des premiere cartes

void tiragePCarte(struct Joueur* participant, struct Croupier* Croupier,struct sCarte* Paquet, int nb_joueur,int posPaquet){
    //Déclaration des variables et Initialisation
    int i;

    //Boucle pour, tirage de la 1er carte des joueurs
    for ( i = 0; i < nb_joueur; i++)//tirage 1er carte des joueurs
    {
        if (participant[i].mise!=0)
        {
            participant[i].carte[participant[i].nbCarte]=Paquet[posPaquet];
            posPaquet=posPaquet+1;
            participant[i].sommecarte=participant[i].sommecarte+participant[i].carte[participant[i].nbCarte].valeur;
            participant[i].nbCarte=participant[i].nbCarte+1;
        }
    }

    //tirage 1er carte du croupier
    Croupier->carte[Croupier->nbCarte]=Paquet[posPaquet];
    Croupier->sommecarte=Croupier->sommecarte+Croupier->carte[Croupier->nbCarte].valeur;
    Croupier->nbCarte=Croupier->nbCarte+1;
    posPaquet=posPaquet+1;

    //Boucle pour, tirage de la 2eme carte des joueurs
    for ( i = 0; i < nb_joueur; i++)
    {
        if (participant[i].mise!=0)
        {
            participant[i].carte[participant[i].nbCarte]=Paquet[posPaquet];
            posPaquet=posPaquet+1;
            participant[i].sommecarte=participant[i].sommecarte+participant[i].carte[participant[i].nbCarte].valeur;
            participant[i].nbCarte=participant[i].nbCarte+1;
        }
    }

    //tirage 2e carte des joueur
    Croupier->carte[Croupier->nbCarte]=Paquet[posPaquet];
    Croupier->sommecarte=Croupier->sommecarte+Croupier->carte[Croupier->nbCarte].valeur;
    Croupier->nbCarte=Croupier->nbCarte+1;
    posPaquet=posPaquet+1;
}

//Partie : affichage lors des tours des joueurs

void affichagetourJoueur(struct Joueur* participant, int joueur, struct Croupier* Croupier){
    //Déclaration des variables et Initialisation
    int i; 
    int j;
    //Affichage du jeu du croupier
    printf("\n\nCroupier :\n");
    for ( i = 0; i <3; i++)
    {
        if (i==0)
        {
            for (j= 0; j<Croupier->nbCarte; j++)
            {
                if (j==Croupier->nbCarte-1)
                {
                    printf("+-----+\n");
                }
                else
                {
                    if (Croupier->carte[j].valeur>=10)
                    {
                        printf("+-----+ ");
                    }
                    else
                    {
                        printf("+----+ ");
                    }
                }
            }
        }
        else if (i==1)
        {
            for (j= 0; j<Croupier->nbCarte; j++)
            {
                if (j==Croupier->nbCarte-1)
                {
                    printf("|  ?  |\n");
                }
                else
                {
                    switch (Croupier->carte[j].couleur)
                    {
                    case 0:
                        printf("|\x1B[31;01m♦\033[00m %d | ",Croupier->carte[j].valeur);
                        break;
                    case 1:
                        printf("|\x1B[31;01m♥\033[00m %d | ",Croupier->carte[j].valeur);
                        break;
                    case 2:
                        printf("|\x1B[32;01m♠\033[00m %d | ",Croupier->carte[j].valeur);
                        break;
                    default:
                        printf("|\x1B[32;01m♣\033[00m %d | ",Croupier->carte[j].valeur);
                        break;
                    }
                }
            }
        }
        else
        {
            for (j= 0; j<Croupier->nbCarte; j++)
            {
                if (j==Croupier->nbCarte-1)
                {
                    printf("+-----+\n\n");
                }
                else
                {
                    if (Croupier->carte[j].valeur>=10)
                    {
                        printf("+-----+ ");
                    }
                    else
                    {
                        printf("+----+ ");
                    }
                }
            }
        }
        

        
    }
    //Affichage du jeu du joueur
    printf("%s, score %d :\n",participant[joueur].nom,participant[joueur].sommecarte);
    for ( i = 0; i < 3; i++)
    {
        if (i==0)
        {
            for (j= 0; j<participant[joueur].nbCarte; j++)
            {
                if (j==participant[joueur].nbCarte-1)
                {
                    if (participant[joueur].carte[j].valeur>=10)
                    {
                        printf("+-----+\n");
                    }
                    else
                    {
                        printf("+----+\n");
                    }
                }
                else
                {
                    if (participant[joueur].carte[j].valeur>=10)
                    {
                        printf("+-----+ ");
                    }
                    else
                    {
                        printf("+----+ ");
                    }
                }
            }
        }
        else if (i==1)
        {
            for (j= 0; j<participant[joueur].nbCarte; j++)
            {
                if (j==participant[joueur].nbCarte-1)
                {
                    switch (participant[joueur].carte[j].couleur)
                    {
                    case 0:
                        printf("|\x1B[31;01m♦\033[00m %d |\n",participant[joueur].carte[j].valeur);
                        break;
                    case 1:
                        printf("|\x1B[31;01m♥\033[00m %d |\n",participant[joueur].carte[j].valeur);
                        break;
                    case 2:
                        printf("|\x1B[32;01m♠\033[00m %d |\n",participant[joueur].carte[j].valeur);
                        break;
                    default:
                        printf("|\x1B[32;01m♣\033[00m %d |\n",participant[joueur].carte[j].valeur);
                        break;
                    }
                }
                else
                {
                    switch (participant[joueur].carte[j].couleur)
                    {
                    case 0:
                        printf("|\x1B[31;01m♦\033[00m %d | ",participant[joueur].carte[j].valeur);
                        break;
                    case 1:
                        printf("|\x1B[31;01m♥\033[00m %d | ",participant[joueur].carte[j].valeur);
                        break;
                    case 2:
                        printf("|\x1B[32;01m♠\033[00m %d | ",participant[joueur].carte[j].valeur);
                        break;
                    default:
                        printf("|\x1B[32;01m♣\033[00m %d | ",participant[joueur].carte[j].valeur);
                        break;
                    }
                }
            }
        }
        else
        {
            for (j= 0; j<participant[joueur].nbCarte; j++)
            {
                if (j==participant[joueur].nbCarte-1)
                {
                    if (participant[joueur].carte[j].valeur>=10)
                    {
                        printf("+-----+\n\n");
                    }
                    else
                    {
                        printf("+----+\n\n");
                    }
                }
                else
                {
                    if (participant[joueur].carte[j].valeur>=10)
                    {
                        printf("+-----+ ");
                    }
                    else
                    {
                        printf("+----+ ");
                    }
                }
            }
        }
    }
}

//Partie : demande assurance

void demandeAssurance(struct Joueur* participant, int nb_joueur, struct Croupier* Croupier){
    //Déclaration des variables et Initialisation
    int i;
    int choix;
    int int_retour;
    //Boucle pour, demande si les joueur veulent prendre une assurance
    for ( i = 0; i < nb_joueur; i++)
    {
        //Teste si le joueur a assez de sous et qu'il a misé
        if (participant[i].argent>=participant[i].mise/2 && participant[i].mise !=0)
        {
            //Demande si il veut prendre une assurance
            affichagetourJoueur(participant,i,Croupier);
            printf("Voulez vous prendre l'assurance ?\n[1] OUI.\n[2] NON.\nEntrez votre choix : ");
            int_retour=scanf("%d",&choix);
            //Evite le probleme de buffer
            scanf("%*[^\n]");
            getchar();
            //Boucle tant que, la saisie est fausse ou que le choix ne correspond pas au choix possible
            while ((choix!=1 && choix!=2) || int_retour!=1)
            {
                //Demande s'il veut une assurance
                printf("Erreur de saisie.\n");
                printf("Voulez vous prendre l'assurance ?\n[1] OUI.\n[2] NON.\nEntrez votre choix : ");
                int_retour=scanf("%d",&choix);
                //Evite le probleme de buffer
                scanf("%*[^\n]");
                getchar();
            }
            //Teste si le joueur a pris une assurance
            if (choix==1)
            {
                //Initialisation de l'assurance
                participant[i].assurance=participant[i].mise/2;
                participant[i].argent=participant[i].argent-participant[i].assurance;
            }
        }
    }
}

//Partie : tour du joueur

void tourDuJoueur(struct Joueur* participant, int joueur, int posPaquet,struct sCarte* Paquet,struct Croupier* Croupier){
    //Déclaration des variables et Initialisation
    int choix;
    choix=0;
    int j;
    j=0;
    int int_retour;
    int doubler;
    doubler=0;
    //Boucle tant que, le joueur n'a pas choisi de rester et de doubler et la somme des carte est inférieur à 21
    while (choix!=2 && participant[joueur].sommecarte<21 && doubler!=1)
    {
        //Teste si le joueur ne peut pas doubler
        if (participant[joueur].nbCarte==2 && doubler!=2)
        {
            //Affiche les choix possibles
            printf("[1] Carte !\n[2] Je reste.\n[3] Doubler.\nFaite votre jeu :");
            int_retour=scanf("%d",&choix);
        }
        else
        {
            //Affiche les choix possibles
            printf("[1] Carte !\n[2] Je reste.\nFaite votre jeu :");
            int_retour=scanf("%d",&choix);
        }
        //Evite le probleme de buffer
        scanf("%*[^\n]");
        getchar();
        //Boucle tant que, la saisie est fausse
        while ((choix!=1 && choix!=2 && choix!=3) || int_retour!=1)
        {
            if (participant[joueur].nbCarte==2 && doubler!=2)
            {
                //Affiche les choix possibles
                printf("[1] Carte !\n[2] Je reste.\n[3] Doubler.\nFaite votre jeu :");
                int_retour=scanf("%d",&choix);
            }
            else
            {
                //Affiche les choix possibles
                printf("[1] Carte !\n[2] Je reste.\nFaite votre jeu :");
                int_retour=scanf("%d",&choix);
            }
            //Evite le probleme de buffer
            scanf("%*[^\n]");
            getchar();
        }
        //Teste si le joueur veut une carte
        if (choix==1)
        {
            //Tirage de la carte
            participant[joueur].carte[participant[joueur].nbCarte]=Paquet[posPaquet];
            participant[joueur].sommecarte=participant[joueur].sommecarte+participant[joueur].carte[participant[joueur].nbCarte].valeur;
            participant[joueur].nbCarte=participant[joueur].nbCarte+1;
            posPaquet=posPaquet+1;
            j=0;
            //Boucle tant que, si la somme est supérieur à 21 regarde s'il y a un as et le compte en 1 au lieu de 11
            while (participant[joueur].sommecarte>21 && j<participant[joueur].nbCarte)
            {
                //Teste si la carte est un as
                if (participant[joueur].carte[j].valeur==11)
                {
                    participant[joueur].carte[j].valeur=1;
                    participant[joueur].sommecarte=participant[joueur].sommecarte-10;
                }
                j=j+1;
            }
            //Appel de la procédure affichagetourJoueur
            affichagetourJoueur(participant,joueur,Croupier);
        }
        //Teste si le joueur veut doubler
        else if (choix==3)
        {
            //teste si le joueur peut doubler
            if (participant[joueur].argent>=participant[joueur].mise)
            {
                //Tirage de la carte
                participant[joueur].argent=participant[joueur].argent-participant[joueur].mise;
                participant[joueur].mise=participant[joueur].mise*2;
                participant[joueur].carte[participant[joueur].nbCarte]=Paquet[posPaquet];
                participant[joueur].sommecarte=participant[joueur].sommecarte+participant[joueur].carte[participant[joueur].nbCarte].valeur;
                participant[joueur].nbCarte=participant[joueur].nbCarte+1;
                posPaquet=posPaquet+1;
                j=0;
                //Boucle tant que, si la somme est supérieur à 21 regarde s'il y a un as et le compte en 1 au lieu de 11
                while (participant[joueur].sommecarte>21 && j<participant[joueur].nbCarte)
                {
                    //teste si la carte est un as
                    if (participant[joueur].carte[j].valeur==11)
                    {
                        participant[joueur].carte[j].valeur=1;
                        participant[joueur].sommecarte=participant[joueur].sommecarte-10;
                    }
                    j=j+1;
                }
                doubler=1;
            }
            else
            {
                //Affiche un message
                printf("Vous avez pas assez pour doubler.\n");
                doubler=2;
            }
            //Appel de la procédure affichagetourJoueur
            affichagetourJoueur(participant,joueur,Croupier);
        }
    }
}

//Partie : tour du Croupier

void tourDuCroupier(int posPaquet,struct sCarte* Paquet,struct Croupier* Croupier){
    //Déclaration des variables
    int i;
    //Teste si le croupier a 2 as
    if (Croupier->sommecarte==22)
    {
        Croupier->carte[0].valeur=1;
        Croupier->sommecarte=Croupier->sommecarte-10;
    }
    //Boucle tant que, le croupier tire une carte jusqu'à que sa somme soit supérieur ou égale à 17
    while (Croupier->sommecarte<17)
    {
        //tirage de la carte
        Croupier->carte[Croupier->nbCarte]=Paquet[posPaquet];
        Croupier->sommecarte=Croupier->sommecarte+Croupier->carte[Croupier->nbCarte].valeur;
        Croupier->nbCarte=Croupier->nbCarte+1;
        posPaquet=posPaquet+1;
        //teste si la somme est supérieur ou égale à 17
        if (Croupier->sommecarte>=17)
        {
            //Boucle pour, regarde s'il y a un as est le compte en 1 au lieu de 11
            for ( i = 0; i < Croupier->nbCarte; i++)
            {
                //teste si la carte est un as
                if (Croupier->carte[i].valeur==11)
                {
                    Croupier->carte[i].valeur=1;
                    Croupier->sommecarte=Croupier->sommecarte-10;
                }
            }
        }
    }
}

//Partie : verification des résultat

void resultat(struct Joueur* participant,struct Croupier* Croupier,int nb_joueur ){
    //Déclaration des variables 
    int i;
    //Boucle pour, attriburt le résultat des joueur
    for ( i = 0; i < nb_joueur; i++)
    {
        //Teste si le joueur a misé
        if (participant[i].mise!=0)
        {
            //Teste si la somme est supérieur à 21
            if (participant[i].sommecarte>21)
            {
                participant[i].resultat=0;
            }
            //Teste si la somme est égale à 21
            else if (participant[i].sommecarte==21)
            {
                //Teste le nombre de carte du joueur
                if (participant[i].nbCarte==2)
                {
                    //Teste si le croupier a fait BlackJack
                    if (Croupier->nbCarte==2 && Croupier->sommecarte==21)
                    {
                        participant[i].resultat=1;
                    }
                    else
                    {
                        participant[i].resultat=3;
                    }
                }
                else
                {
                    //Teste si le joueur a fait BlackJack
                    if (Croupier->sommecarte==21 && Croupier->nbCarte==2)
                    {
                        participant[i].resultat=0;
                    }
                    else
                    {
                        participant[i].resultat=2;
                    }
                }
            }
            else
            {
                //Teste la somme du croupier
                if (Croupier->sommecarte>21 || Croupier->sommecarte<participant[i].sommecarte)
                {
                    participant[i].resultat=2;              
                }
                else if (Croupier->sommecarte>participant[i].sommecarte)
                {
                    participant[i].resultat=0;
                }
                else
                {
                    participant[i].resultat=1;
                }
            }
        }
    }
}

//Partie : restitution des gains

int gains(struct Joueur* participant,int nb_joueur,struct Croupier* Croupier){
    //Déclaration des variables et Initialisation
    int i; 
    int zero;
    zero=0;
    //Boucle pour, attribuer les gains au joueur 
    for ( i = 0; i < nb_joueur; i++)
    {
        //Teste si la joueur a miser
        if (participant[i].mise!=0)
        {
            //Teste du résultat du joueur
            switch (participant[i].resultat)
            {
            case 3://Cas BlackJack
                participant[i].argent=participant[i].argent+3*participant[i].mise;
                break;
            case 2://Cas gagné
                participant[i].argent=participant[i].argent+2*participant[i].mise;
                break;
            case 1://Cas égalité
                participant[i].argent=participant[i].argent+participant[i].mise;
                break;
            default://Cas perdu
                //Teste si le joueur avait pris une assurance 
                if (participant[i].assurance!=0 && Croupier->sommecarte==21 && Croupier->nbCarte==2)
                {
                    participant[i].argent=participant[i].argent+3*participant[i].assurance;
                }
                //rien a faire cas perdu
                break;
            }
            //Teste le joueur n'a plus d'argent
            if (participant[i].argent==0)
            {
                zero=1;
            }
        }
    }
    //renvoie si un joueur n'a plus d'argent
    return(zero);
}

//Partie : affichage de fin de tour

void afficheFinTour(struct Joueur* participant,int nb_joueur,struct Croupier* Croupier){
    //Déclaration des variables
    int i;
    int j;
    int p;
    //Affcihe un message
    printf("\n\nVoici les résultats de la manche :");
    printf("\n\nCroupier, scrore : %d\n",Croupier->sommecarte);
    //Boucle pour, affiche le jeu du croupier
    for ( i = 0; i < 3; i++)
    {
        if (i==0)
        {
            for (j= 0; j<Croupier->nbCarte; j++)
            {
                if (j==Croupier->nbCarte-1)
                {
                    if (Croupier->carte[j].valeur>=10)
                    {
                        printf("+-----+\n");
                    }
                    else
                    {
                        printf("+----+\n");
                    }
                }
                else
                {
                    if (Croupier->carte[j].valeur>=10)
                    {
                        printf("+-----+ ");
                    }
                    else
                    {
                        printf("+----+ ");
                    }
                }
            }
        }
        else if (i==1)
        {
            for (j= 0; j<Croupier->nbCarte; j++)
            {
                if (j==Croupier->nbCarte-1)
                {
                    switch (Croupier->carte[j].couleur)
                    {
                    case 0:
                        printf("|\x1B[31;01m♦\033[00m %d |\n",Croupier->carte[j].valeur);
                        break;
                    case 1:
                        printf("|\x1B[31;01m♥\033[00m %d |\n",Croupier->carte[j].valeur);
                        break;
                    case 2:
                        printf("|\x1B[32;01m♠\033[00m %d |\n",Croupier->carte[j].valeur);
                        break;
                    default:
                        printf("|\x1B[32;01m♣\033[00m %d |\n",Croupier->carte[j].valeur);
                        break;
                    }
                }
                else
                {
                    switch (Croupier->carte[j].couleur)
                    {
                    case 0:
                        printf("|\x1B[31;01m♦\033[00m %d | ",Croupier->carte[j].valeur);
                        break;
                    case 1:
                        printf("|\x1B[31;01m♥\033[00m %d | ",Croupier->carte[j].valeur);
                        break;
                    case 2:
                        printf("|\x1B[32;01m♠\033[00m %d | ",Croupier->carte[j].valeur);
                        break;
                    default:
                        printf("|\x1B[32;01m♣\033[00m %d | ",Croupier->carte[j].valeur);
                        break;
                    }
                }
            }
        }
        else
        {
            for (j= 0; j<Croupier->nbCarte; j++)
            {
                if (j==Croupier->nbCarte-1)
                {
                    if (Croupier->carte[j].valeur>=10)
                    {
                        printf("+-----+\n\n ");
                    }
                    else
                    {
                        printf("+----+\n\n ");
                    }
                }
                else
                {
                    if (Croupier->carte[j].valeur>=10)
                    {
                        printf("+-----+ ");
                    }
                    else
                    {
                        printf("+----+ ");
                    }
                }
            }
        }
    }
    //Boucle pour, affiche le jeu des joueurs
    for ( i = 0; i < nb_joueur; i++)
    {
        //Teste le résultat du joueur et affiche un message 
        switch (participant[i].resultat)
        {
        case 3:
            printf("%s , mise %lf, scrore %d : BlackJack\n",participant[i].nom,participant[i].mise,participant[i].sommecarte);
            break;
        case 2:
            printf("%s , mise %lf, score %d : Gagné\n",participant[i].nom,participant[i].mise,participant[i].sommecarte);
            break;
        case 1:
            printf("%s , mise %lf, score %d : éalite\n",participant[i].nom,participant[i].mise,participant[i].sommecarte);
            break;
        default:
            printf("%s , mise %lf, score %d : Perdu\n",participant[i].nom,participant[i].mise,participant[i].sommecarte);
            break;
        }
        //Boucle pour, affcihe le jeu du joueur
        for ( p = 0; p < 3; p++)
        {
            if (p==0)
            {
                for (j= 0; j<participant[i].nbCarte; j++)
                {
                    if (j==participant[i].nbCarte-1)
                    {
                        if (participant[i].carte[j].valeur>=10)
                        {
                            printf("+-----+\n");
                        }
                        else
                        {
                            printf("+----+\n");
                        }
                    }
                    else
                    {
                        if (participant[i].carte[j].valeur>=10)
                        {
                            printf("+-----+ ");
                        }
                        else
                        {
                            printf("+----+ ");
                        }
                    }
                }
            }
            else if (p==1)
            {
                for (j= 0; j<participant[i].nbCarte; j++)
                {
                    if (j==participant[i].nbCarte-1)
                    {
                        switch (participant[i].carte[j].couleur)
                        {
                        case 0:
                            printf("|\x1B[31;01m♦\033[00m %d |\n",participant[i].carte[j].valeur);
                            break;
                        case 1:
                            printf("|\x1B[31;01m♥\033[00m %d |\n",participant[i].carte[j].valeur);
                            break;
                        case 2:
                            printf("|\x1B[32;01m♠\033[00m %d |\n",participant[i].carte[j].valeur);
                            break;
                        default:
                            printf("|\x1B[32;01m♣\033[00m %d |\n",participant[i].carte[j].valeur);
                            break;
                        }
                    }
                    else
                    {
                        switch (participant[i].carte[j].couleur)
                        {
                        case 0:
                            printf("|\x1B[31;01m♦\033[00m %d | ",participant[i].carte[j].valeur);
                            break;
                        case 1:
                            printf("|\x1B[31;01m♥\033[00m %d | ",participant[i].carte[j].valeur);
                            break;
                        case 2:
                            printf("|\x1B[32;01m♠\033[00m %d | ",participant[i].carte[j].valeur);
                            break;
                        default:
                            printf("|\x1B[32;01m♣\033[00m %d | ",participant[i].carte[j].valeur);
                            break;
                        }
                    }
                }
            }
            else
            {
                for (j= 0; j<participant[i].nbCarte; j++)
                {
                    if (j==participant[i].nbCarte-1)
                    {
                        if (participant[i].carte[j].valeur>=10)
                        {
                            printf("+-----+\n\n");
                        }
                        else
                        {
                            printf("+----+\n\n");
                        }
                    }
                    else
                    {
                        if (participant[i].carte[j].valeur>=10)
                        {
                            printf("+-----+ ");
                        }
                        else
                        {
                            printf("+----+ ");
                        }
                    }
                }
            }
        }
    }
}

//Partie ; demande si un joueur veut arreter

int demandeArret(struct Joueur* participant,int nb_joueur){
    //Déclaration des varaibles et Initialisation
    int i;
    i=0;
    int reponse;
    reponse=1;
    int int_retour;
    //Boucle tant que, la réponse est égale a 1 et tout le monde a répondu
    while (reponse==1 && i<nb_joueur)
    {
        //Demande si le joueur veut arreter
        printf("\n[1] Je continue\n[2] J'arrête \n%s entrez votre choix : ",participant[i].nom);
        int_retour=scanf("%d",&reponse);
        //Evite le probleme de buffer
        scanf("%*[^\n]");
        getchar();
        //Boucle tant que, la saisie est fausse ou que la choix n'est pas correcte
        while ((reponse != 1 && reponse!=2)||int_retour!=1)
        {
            //Demande si le jouer veut arreter
            printf("\nErreur de saisie\n");
            printf("[1] Je continue\n[2] J'arrête \n%s entrez votre choix : ",participant[i].nom);
            int_retour=scanf("%d",&reponse);
            //Evite le probleme de buffer
            scanf("%*[^\n]");
            getchar();
        }
        i=i+1;
    }
    //Renvoie s'il y un joueur qui veut arreter ou non
    return(reponse);
}

//Partie : réinitialisation des cartes, du nombre de carte et de la somme des cartes des joueurs

void reinitJoueur(struct Joueur* participant,int nb_joueur){
    //Déclarattion des variables 
    int i;
    int j;
    //Boucle pour, réinitialisation des cartes, du nombre de carte et de la somme des joueurs
    for ( i = 0; i < nb_joueur; i++)
    {
        for (j = 0; j < participant[i].nbCarte; j++)
        {
            participant[i].carte[i].valeur=0;
        }
        participant[i].nbCarte=0;
        participant[i].sommecarte=0;
    }
}

//Partie : réinitialisation du Croupier

void reinitCroupier(struct Croupier* Croupier){
    //Déclaration des variables
    int i;
    //Boucle pour, réinitailise les cartes du croupier
    for ( i = 0; i < Croupier->nbCarte; i++)
    {
        Croupier->carte[i].valeur=0;
    }
    //réinitialisation du nombre de carte et de la somme du croupier 
    Croupier->nbCarte=0;
    Croupier->sommecarte=0;
}

//Parite : la fonction principale

void BlackJack(int nb_joueur){
    //Déclaration des variables et Initialisation
    int i ;
    int j;
    j=0;
    int posPaquet;
    posPaquet=0;
    int zero;
    zero=0;
    int demandearret;
    demandearret=1;

    //Création du Croupier
    struct Croupier Croupier;
    struct Croupier* p_Croupier;
    p_Croupier=&Croupier;
    Croupier.nbCarte=0;
    Croupier.sommecarte=0;

    //Création des joueurs
    struct Joueur participant[nb_joueur];
    creationJoueur(participant,nb_joueur); 

    //Init et mélange du paquet
    struct sCarte Paquet[52];
    struct sCarte* p_Paquet;
    p_Paquet=&Paquet[0];
    
    //Boucle tant que, fait tourner le jeu
    while (zero==0 && demandearret==1)
    {
        //Création du paquet de carte mélanger
        InitPaquet(Paquet);
        melangePaquet(p_Paquet);

        //Mise des joueurs
        demandeMise(participant,nb_joueur);
        //Tirage des Cartes
        tiragePCarte(participant,p_Croupier,Paquet,nb_joueur,posPaquet);

        //teste si on demande les assurances
        if(Croupier.carte[0].valeur==11){     
            demandeAssurance(participant,nb_joueur,p_Croupier);
        }

        //Boucle pour, fait jouer les joueur
        for ( i = 0; i < nb_joueur; i++)
        {
            //Teste si le joueur a misé
            if (participant[i].mise!=0)
            {
                printf("\nC'est le tour de %s :",participant[i].nom);
                j=0;
                //Boucle tant que, la somme du joueur est supérieur a 21 et compte 1 un as
                while (participant[i].sommecarte>21)
                {
                    //teste si la carte est un as
                    if (participant[i].carte[j].valeur==11)
                    {
                        participant[i].carte[j].valeur=1;
                        participant[i].sommecarte=participant[j].sommecarte-10;
                    }
                    j=j+1;
                }
                //Fait jouer le joueur
                affichagetourJoueur(participant,i,p_Croupier);
                tourDuJoueur(participant,i,posPaquet,Paquet,p_Croupier);
            }        
        }

        //Fait jouer le croupier 
        tourDuCroupier(posPaquet,Paquet,p_Croupier);
        
        //savoir les resultats des joueurs
        resultat(participant,p_Croupier,nb_joueur);

        //Distribut les gains et regarde si il y a un joueur n'a plus de sous
        zero=gains(participant,nb_joueur,p_Croupier);

        //Affiche les jeu de tout le monde 
        afficheFinTour(participant,nb_joueur,p_Croupier);

        //Teste si il y a personne qui n'a plus de sous
        if (zero==0)
        {
            //Demande s'il y a une personne qui veut arreter
            demandearret=demandeArret(participant, nb_joueur);
        }
        //Réinitialise les joueurs et le croupier
        reinitCroupier(p_Croupier);
        reinitJoueur(participant,nb_joueur);
        posPaquet=0;
    }
    //Teste s'il y a une personne qui a voulu a arreter
    if (demandearret==2)
    {
        //Affiche un message
        printf("\nLe jeu est terminé car un joueur a arreté.\n");    
    }
    //Teste s'il y a une personne qui n'a plus de sous
    else if (zero==1)
    {
        //Affiche une message 
        printf("\nLe jeu est terminé car un joueur n'a plus de sous.\n");
    }
}
