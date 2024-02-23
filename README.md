# Projet BlackJack en C - BlackJack_TP

## Description du Projet

Le projet BlackJack_TP est une implémentation du jeu de cartes BlackJack en langage C. Le jeu permet à un joueur ou plusieurs joueurs de jouer contre un croupier automatisé selon les règles classiques du BlackJack.

## Fonctionnalités

- Le joueur peut effectuer les actions suivantes :
  - Recevoir une main initiale de deux cartes.
  - Tenter de s'approcher de la valeur de 21 sans la dépasser.
  - Tirer une nouvelle carte, rester avec la main actuelle ou doubler la mise de base.

- Le croupier automatisé suit les règles standard du BlackJack :
  - Tirer des cartes jusqu'à ce qu'il atteigne une main d'au moins 17 points.
  - Ne pas tirer de nouvelle carte s'il atteint ou dépasse 17 points.

- Affichage simple et lisible du jeu dans la console.

## Comment jouer

1. Assurez-vous que vous avez un compilateur C installé sur votre système.

2. Clonez ce dépôt sur votre machine locale.

3. Ouvrez un terminal ou une invite de commande.

4. Déplacez-vous dans le répertoire racine du projet.

5. Compilez le code source à l'aide de la commande suivante du Makefile:

    ```bash
    make
    ```

   - Assurez-vous que l'exécutable sera généré dans le répertoire `bin`.

6. Une fois la compilation terminée, vous pouvez lancer le jeu à l'aide de la commande suivante :

   ```bash
   ./bin/BlackJack nb_joueur
   ```

   - Remplacez `nb_joueur` par le nombre de joueurs souhaité pour la partie (y compris le joueur principal).

7. Le jeu devrait se lancer avec le nombre de joueurs spécifié, et vous pourrez commencer à jouer en suivant les instructions affichées à l'écran.

## Documentation

La documentation a été générer via Doxygen.

```bash
# Générer la documentation 
doxygen -g
doxygen Doxyfile
```

## Reste à faire

- cas : le split (séparer les cartes si double en main de départ)  

## Remarques

- Ce projet a été réalisé dans le cadre d'un travail pratique ou d'un projet académique.

**Amusez-vous bien en jouant au BlackJack !**