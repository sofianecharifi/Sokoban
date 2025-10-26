#ifndef ___SOKOBAN_H__
#define __SOKOBAN_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Fonction pour créer le tableau de jeu
char** tableau(void);

// Fonction pour vérifier si le jeu est perdu (joueur sur cible)
int est_perdu(char **board);

// Fonction pour vérifier si le jeu est gagné (boîte sur cible)
int est_gagne(char **board);

// Fonction pour déplacer le joueur
int deplacer_joueur(char **board, char direction);

// Fonction pour trouver la position du joueur
void trouve_joueur(char **board, int *x, int *y);

// Fonction pour vérifier si le jeu est gagné
int est_gagne(char **board);

// Fonction pour déplacer le joueur et la boîte
int deplacer_joueur(char **board, char direction);





//fonction du personnage en mouvement 
void player_move(char **board, int move);




//fonction d'affichage du personnage 





#endif