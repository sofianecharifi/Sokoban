# 📦 Sokoban - Random Edition

Une version revisitée du célèbre jeu de puzzle japonais, développée en C.
Contrairement au jeu classique, ici **les niveaux sont générés aléatoirement** à chaque partie !

### Les Règles
1.  **Pousser la caisse :** Amenez la caisse `[B]` sur la cible `[X]`.
2.  **Victoire :** Une fois la caisse sur la cible, vous gagnez !
3.  **⚠️ Danger (Règle Spéciale) :** Si **VOUS** (le joueur) marchez sur la cible `[X]`, vous perdez immédiatement la partie.
4.  **Murs :** Vous ne pouvez pas traverser les murs `[#]`.

## 🛠️ Prérequis

Ce jeu utilise des commandes système UNIX. Il est conçu pour fonctionner sur :
* **Linux**
* **macOS**
* *(Non compatible nativement avec Windows sans WSL)*

## 🚀 Installation et Compilation

### 1. Télécharger
Clonez ce dépôt ou téléchargez les fichiers.

### 2. Compiler
Comme le projet est composé de plusieurs fichiers `.c`, compilez-le avec `gcc` ou avec le makefile :

```bash
gcc main.c fonction.c print_tab.c str_cpy.c str_len.c -o sokoban
Makefile :
make all
