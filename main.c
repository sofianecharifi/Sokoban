#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "fonction.h"
#include "print_tab.h"

int main()
{
    char * prenom = malloc(100 * sizeof(char));
    printf("Quel est ton prénom ?\n");
    scanf("%s", prenom);
    printf("Bonjour %s ! \nPour prouver que tu es bon dans un domaine (potentiellement le seul),\n", prenom);
    printf("nous te proposons de réussir ce niveau de Sokoban !\n\n");
    sleep(5);
    printf("Les touches sont les suivantes :\n [Z] pour monter d'une case\n [Q] pour aller à Gauche\n [S] pour aller en bas\n [D] pour aller à droite\n\n");
    printf("Pour rappel, pour gagner tu dois mettre la boite [B] sur la cible [X] !\n");
    printf("BONUS ! Attention à ne pas marcher sur la cible, sinon c'est ciao ! ");
    printf("Bon jeu à toi !\n\n");
    sleep(8);
    
    char **game_board = tableau();  // Création du tableau de jeu
    print_tab(game_board);          // Affichage du tableau

    // Fonction locale pour sauvegarder le plateau dans end.txt
    void save_board(char **board) {
        FILE *f = fopen("end.txt", "w");
        if (!f) {
            perror("Erreur lors de l'ouverture de end.txt");
            return;
        }
        for (int i = 0; board[i] != NULL; i++) {
            fprintf(f, "%s\n", board[i]);
        }
        fclose(f);
    }
    
    char mouvement;
    int finished = 0; // flag indiquant que la partie s'est terminée
    while(1) {
        // Lire le caractère sans appuyer sur Entrée
        system("stty raw");
        mouvement = getchar();
        system("stty cooked");
        
        // Quitter si on appuie sur 'x'
        if(mouvement == 'x') {
            break;
        }
        
        // Si le mouvement est valide (zqsd), déplacer le joueur
        if(mouvement == 'z' || mouvement == 'q' || mouvement == 's' || mouvement == 'd') {
            if(deplacer_joueur(game_board, mouvement)) {
                system("clear");  // Effacer l'écran
                print_tab(game_board);  // Réafficher le tableau
                
                // Vérifier si le joueur a perdu (P est sur X)
                if(est_perdu(game_board)) {
                    printf("\nC'est pas pro ça %s ! T'as été sur la cible ! Fallait lire les règles 🤡\n", prenom);
                    finished = 1;
                    break; // sortir de la boucle proprement pour sauvegarder et libérer
                }
                
                // Vérifier si le joueur a gagné
                if(est_gagne(game_board)) {
                    printf("\nFélicitations %s ! Tu n'es pas si nul que ça finalement...\n", prenom);
                    finished = 1;
                    break;
                }
            }
        }
    }
    // Sauvegarder l'état final du plateau (écrase end.txt)
    save_board(game_board);

    // Libération de la mémoire à la fin
    int i = 0;
    while(game_board[i] != NULL) {
        free(game_board[i]);
        i++;
    }
    free(game_board);
    (void)finished; // variable présente si besoin d'extensions futures
}