/*!
* \file main.c
* \author Tarchaud
* \version 0.1
* \date 19/12/2021
* \brief Fonction principal du programme 
* \remarks None
*/


/*! Inclusion des entetes de librairies */
#include "BlackJack.h"


/*!
* \fn int main(int argc, char** argv)
* \author Tarchaud
* \version 0.1
* \date 19/12/2021
* \brief Fonction principal du programme 
* \remarks None
* \param argc nombre d'arguments en entree
* \param argv valeur des arguments en entree
* \return 0 si tout c'est bien passe
*/
int main(int argc, char** argv){
    //Déclaration des variables et Initialisation
    int nb_Joueur;
    nb_Joueur=atoi(argv[1]);
    //Teste s'il y a trop d'argument 
    if (argv[2]==0)
    {
        //Teste si le nombre de joueurs entré est bon
        if (nb_Joueur>=1 && nb_Joueur<=5)
        {
            //Lance le jeu en appelant la fonction BlackJack
            BlackJack(nb_Joueur);
        }
        else
        {
            //affiche un message
            printf("Soit il y a trop de joueur ou pas assez, il faut au moins 1 joueur et maximun 5 joueurs.\n");
        }
    }
    else
    {
        //Affiche un message
        printf("Il y a trop d'argument, il faut 1 seule argument qui correspond au nombre de joueur.\n");
    }
    //Renvoie 0 si tout c'est bien passé
    return(0);
}

