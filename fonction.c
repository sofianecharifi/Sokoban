#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "str_cpy.h"
#include "fonction.h"
#include "print_tab.h"

// Fonction pour vérifier si une position est valide pour la boîte
static int est_position_valide_boite(char **tab, int x, int y) {
    // Vérifier si la position est vide
    if(tab[x][y] != ' ') return 0;
    
    // Pour la boîte, vérifier qu'il y a de l'espace autour (pas collée au mur)
    if(tab[x-1][y] == '#' || tab[x+1][y] == '#' ||
       tab[x][y-1] == '#' || tab[x][y+1] == '#') {
        return 0;
    }
    return 1;
}

char** tableau(void)
{
    char **tab = malloc(11 * sizeof(*tab));
    tab[10] = NULL;

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Création du tableau avec les murs
    char *niveau[] = {
        "############",
        "#          #",
        "#          #",
        "#          #",
        "#          #",
        "#          #",
        "#          #",
        "#          #",
        "#          #",
        "############"
    };

    // Copie de chaque ligne dans le tableau
    for(int i = 0; i < 10; i++) {
        tab[i] = str_cpy((char*)niveau[i]);
    }

    // Placement aléatoire des éléments
    int placed = 0;
    while(placed < 3) { // 3 éléments à placer (P, B, X)
        // Générer des positions aléatoires (éviter les bords)
        int x = rand() % 8 + 1;  // Entre 1 et 8
        int y = rand() % 10 + 1; // Entre 1 et 10

        // Pour la boîte (placed == 1), utiliser la vérification spéciale
        if(placed == 1) {
            if(est_position_valide_boite(tab, x, y)) {
                tab[x][y] = 'B';
                placed++;
            }
        }
        // Pour P et X, vérifier juste si la case est libre
        else if(tab[x][y] == ' ') {
            switch(placed) {
                case 0:
                    tab[x][y] = 'P';
                    break;
                case 2:
                    tab[x][y] = 'X';
                    break;
            }
            placed++;
        }
    }

    return tab;
}


// Fonction pour trouver la position du joueur
void trouve_joueur(char **board, int *x, int *y) {
    for(int i = 0; board[i] != NULL; i++) {
        for(int j = 0; board[i][j] != '\0'; j++) {
            if(board[i][j] == 'P') {
                *x = i;
                *y = j;
                return;
            }
        }
    }
}

// Variables globales pour stocker la position initiale de X
static int cible_x = -1;
static int cible_y = -1;

// Fonction pour sauvegarder la position initiale de X
void sauvegarde_position_cible(char **board) {
    if(cible_x == -1) {  // Si pas encore sauvegardée
        for(int i = 0; board[i] != NULL; i++) {
            for(int j = 0; board[i][j] != '\0'; j++) {
                if(board[i][j] == 'X') {
                    cible_x = i;
                    cible_y = j;
                    return;
                }
            }
        }
    }
}

// Fonction pour vérifier si le jeu est perdu
int est_perdu(char **board) {
    // Si c'est le premier appel, sauvegarder la position de X
    if(cible_x == -1) {
        sauvegarde_position_cible(board);
    }

    // Chercher la position du joueur
    for(int i = 0; board[i] != NULL; i++) {
        for(int j = 0; board[i][j] != '\0'; j++) {
            if(board[i][j] == 'P') {
                // Vérifier si le joueur est sur la position initiale de X
                if(i == cible_x && j == cible_y) {
                    return 1;  // Perdu !
                }
            }
        }
    }
    return 0;  // Pas perdu
}

// Fonction pour vérifier si le jeu est gagné
int est_gagne(char **board) {
    // On cherche une boîte sur une cible (W)
    for(int i = 0; board[i] != NULL; i++) {
        for(int j = 0; board[i][j] != '\0'; j++) {
            if(board[i][j] == 'W') {  // W = boîte sur cible
                return 1;  // Gagné !
            }
        }
    }
    return 0;  // Pas encore gagné
}

// Fonction pour déplacer le joueur et la boîte
int deplacer_joueur(char **board, char direction) {
    int x, y;
    trouve_joueur(board, &x, &y);
    
    int new_x = x;
    int new_y = y;
    int box_x, box_y;
    
    // Calculer la nouvelle position selon la direction
    switch(direction) {
        case 'z': // Haut
            new_x = x - 1;
            box_x = new_x - 1;
            box_y = new_y;
            break;
        case 's': // Bas
            new_x = x + 1;
            box_x = new_x + 1;
            box_y = new_y;
            break;
        case 'q': // Gauche
            new_y = y - 1;
            box_x = new_x;
            box_y = new_y - 1;
            break;
        case 'd': // Droite
            new_y = y + 1;
            box_x = new_x;
            box_y = new_y + 1;
            break;
        default:
            return 0;
    }
    
    // Vérifier si le mouvement est valide (pas de mur)
    if(board[new_x][new_y] == '#') {
        return 0;
    }
    
    // Si on pousse une boîte
    if(board[new_x][new_y] == 'B') {
        // Vérifier si la boîte peut être poussée (pas de mur ou d'autre boîte)
        if(board[box_x][box_y] == '#' || board[box_x][box_y] == 'B') {
            return 0;
        }
        // Déplacer la boîte
        if(board[box_x][box_y] == 'X') {
            board[box_x][box_y] = 'W';  // W représente une boîte sur une cible
        } else {
            board[box_x][box_y] = 'B';
        }
    }
    
    // Effectuer le déplacement du joueur
    board[x][y] = ' ';      // Effacer l'ancienne position
    board[new_x][new_y] = 'P';  // Placer le joueur à la nouvelle position
    
    return 1;
}