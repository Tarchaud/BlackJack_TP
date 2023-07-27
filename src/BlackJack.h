/*!
 \file BlackJack.h
 \author Tarchaud
 \version 0.1
 \date 11/12/2021
 \brief Prototypes des fonction pour le blackJack
 \remarks None
*/


#ifndef __BlackJack_H_
#define __BlackJack_H_


/*! Inclusion des entetes de librairies */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*! \enum eCouleur
 * Enumération pour les couleurs des cartes
*/
enum eCouleur
{
    Carreau, /*!< Couleur Carreau */
    Coeur, /*!< Couleur Coeur */
    Pique, /*!< Couleur Pique*/
    Trefle /*!< Couleur Trefle */
};

/*! \enum aGagner
 * Enumération pour les résulats possibles
*/
enum aGagner
{
    perdu, /*!< Résultat : Perdu */
    egalite, /*!< Résultat : Egalité */
    gagne, /*!< Résultat : Gagné */
    blackJack /*!< Résultat : BlackJack */
};

/*! \struct sCarte
 * Structure pour la manipulation d'une carte
 * \remark une carte a une valeur est une couleur
*/
struct sCarte
{
    enum eCouleur couleur; /*!< Couleur de la carte */
    int valeur; /*!< valeur de la carte */
};

/*! \struct Joueur 
 * Structure pour la manipulation d'un joueur
 * \remark un joueur a un nom, une somme d'argent, une mise et sa main 
*/
struct Joueur
{
    char nom[20]; /*!< Nom du joueur */
    double argent; /*!< l'argent du joueur */
    double mise; /*!< la mise du joueur  */
    double assurance; /*!< l'assurance du joueur s'il en a besoin */
    struct sCarte carte[10]; /*!< La main du joueur */
    int sommecarte; /*!< La somme des cartes du joueur */
    int nbCarte; /*!< Nombre de carte que le joueur a */
    enum aGagner resultat; /*!< Résultat du joueur */
};

/*! \struct Croupier 
 * Structure pour la manipulation du croupier
 * \remark le croupier a sa main, la somme de ses cartes et le nombre de cartes qu'il a 
*/
struct Croupier
{
    struct sCarte carte[10]; /*!< La main du croupier */
    int sommecarte; /*!< La somme des cartes du croupier */
    int nbCarte; /*!< Nombre de carte du croupier */
};


/*!
* \fn void InitPaquet(struct sCarte* Paquet)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Crée le paquet de cartes
* \remarks None
* \param Paquet tableau de struct sCarte
*/ 
void InitPaquet(struct sCarte* Paquet);

/*!
* \fn void melangePaquet(struct sCarte* Paquet)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Mélange le paquet de cartes aléatoirement
* \remarks None
* \param Paquet tableau de struct sCarte
*/
void melangePaquet(struct sCarte* Paquet);

/*!
* \fn void creationJoueur(struct Joueur* participant,int nb_joueur)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Crée les joueurs en demandant leur nom et leur argent qui est pret à jouer
* \remarks None
* \param participant tableau de struct Joueur
* \param nb_joueur le nombre de joueurs qu'il y a 
*/
void creationJoueur(struct Joueur* participant, int nb_joueur);

/*!
* \fn void demandeMise(struct Joueur* participant,int nb_joueur)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Demande la mise de chaque joueur
* \remarks None
* \param participant tableau de struct Joueur
* \param nb_joueur le nombre de joueurs qu'il y a 
*/
void demandeMise(struct Joueur* participant,int nb_joueur);

/*!
* \fn void tiragePCarte(struct Joueur* participant, struct Croupier* Croupier,struct sCarte* Paquet, int nb_joueur,int posPaquet)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Tirage des 2 premières cartes de chaque joueur et du croupier
* \remarks None
* \param participant tableau de struct Joueur
* \param Croupier struct du Croupier
* \param Paquet tableau de struct sCarte
* \param nb_joueur le nombre de joueurs qu'il y a 
* \param posPaquet la position de la carte qu'il faut tirer
*/
void tiragePCarte(struct Joueur* participant, struct Croupier* Croupier,struct sCarte* Paquet, int nb_joueur,int posPaquet);

/*!
* \fn void affichagetourJoueur(struct Joueur* participant, int joueur, struct Croupier* Croupier)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Affiche la main du croupier avec sa deuxième carte face cachée et affiche la main du joueur qui doit jouer
* \remarks None
* \param participant tableau de struct Joueur
* \param joueur indice du joueur à qui c'est son tour
* \param Croupier struct du Croupier
*/
void affichagetourJoueur(struct Joueur* participant, int joueur, struct Croupier* Croupier);

/*!
* \fn void demandeAssurance(struct Joueur* participant, int nb_joueur, struct Croupier* Croupier)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Demande si les joueurs veulent une assurance si la première carte du croupier est un As
* \remarks None
* \param participant tableau de struct Joueur
* \param nb_joueur nombre de joueur qui jouent 
* \param Croupier struct du Croupier
*/
void demandeAssurance(struct Joueur* participant, int nb_joueur, struct Croupier* Croupier);

/*!
* \fn void tourDuJoueur(struct Joueur* participant, int joueur, int posPaquet,struct sCarte* Paquet,struct Croupier* Croupier)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Fait jouer un joueur 
* \remarks None
* \param participant tableau de struct Joueur
* \param joueur indice du joueur à qui c'est son tour
* \param posPaquet la position de la carte qu'il faut tirer
* \param Paquet tableau de struct sCarte
* \param Croupier struct du Croupier
*/
void tourDuJoueur(struct Joueur* participant, int joueur, int posPaquet,struct sCarte* Paquet,struct Croupier* Croupier);

/*!
* \fn void tourDuCroupier(int posPaquet,struct sCarte* Paquet,struct Croupier* Croupier)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Fait jouer le Croupier 
* \remarks None
* \param posPaquet la position de la carte qu'il faut tirer
* \param Paquet tableau de struct sCarte
* \param Croupier struct du Croupier
*/
void tourDuCroupier(int posPaquet,struct sCarte* Paquet,struct Croupier* Croupier);

/*!
* \fn void resultat(struct Joueur* participant,struct Croupier* Croupier,int nb_joueur )
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Compare le score de chaque joueur avec celui du Croupier et dit si gagné, perdu, égalité, BlackJack
* \remarks None
* \param participant tableau de struct Joueur
* \param Croupier struct du Croupier
* \param nb_joueur nombre de joueur qui jouent
*/
void resultat(struct Joueur* participant,struct Croupier* Croupier,int nb_joueur );

/*!
* \fn int gains(struct Joueur* participant,int nb_joueur,struct Croupier* Croupier)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Distribue les gains aux joueurs
* \remarks None
* \param participant tableau de struct Joueur
* \param nb_joueur nombre de joueur qui jouent
* \param Croupier struct du Croupier
* \return 1 s'il y a un joueur à plus d'argent sinon 0
*/
int gains(struct Joueur* participant,int nb_joueur,struct Croupier* Croupier);

/*!
* \fn void afficheFinTour(struct Joueur* participant,int nb_joueur,struct Croupier* Croupier)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Affiche la main du Croupier et les mains de tous les joueurs avec leur résultat
* \remarks None
* \param participant tableau de struct Joueur
* \param nb_joueur nombre de joueur qui jouent
* \param Croupier struct du Croupier
*/
void afficheFinTour(struct Joueur* participant,int nb_joueur,struct Croupier* Croupier);

/*!
* \fn int demandeArret(struct Joueur* participant,int nb_joueur)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Demande si les joueurs veulent continuer ou bien arrêter
* \remarks None
* \param participant tableau de struct Joueur
* \param nb_joueur nombre de joueur qui jouent
* \return 2 s'il y a un joueur veut arrêter ou sinon 1
*/
int demandeArret(struct Joueur* participant,int nb_joueur);

/*!
* \fn void reinitJoueur(struct Joueur* participant,int nb_joueur)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Réinitialise tous les joueurs 
* \remarks None
* \param participant tableau de struct Joueur
* \param nb_joueur nombre de joueur qui jouent
*/
void reinitJoueur(struct Joueur* participant,int nb_joueur);

/*!
* \fn void reinitCroupier(struct Croupier* Croupier)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Réinitialise le Croupier
* \remarks None
* \param Croupier struct du Croupier
*/
void reinitCroupier(struct Croupier* Croupier);

/*!
* \fn void BlackJack(int nb_joueur)
* \author Tarchaud
* \version 0.1
* \date  19/12/2021
* \brief Fait tourné le jeu
* \remarks None
* \param nb_joueur nombre de joueur qui jouent
*/
void BlackJack(int nb_joueur);

#endif