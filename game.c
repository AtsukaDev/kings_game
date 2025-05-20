#include <stdio.h>
#include "board.h"

/**
 * \file game.c
 *
 * \brief Affichage des jeux de la SAE.
 *
 * \author Brillant Lukas
 *
 */

void print_cell(board game, int lig, int col)
{
    /* Fonction permettant d'afficher le contenu d'une cellule */

    cell contenu = get_content(game, lig, col);

    if (contenu == 0)
    { // Case Vide
        printf("   ");
    }
    else if (contenu == 1)
    { // Case du joueur Nord
        printf(" \033[36;01m♚\033[00m ");
    }
    else if (contenu == 2)
    { // Case du joueur Sud
        printf(" \033[31;01m♚\033[00m ");
    }
    else if (contenu == 3)
    {
        // Case Retirée
        printf("███");
    }
    printf("|");
}

void affiche_jeu(board game)
{
    /* Fonction permettant d'afficher la grille du jeu en prenant en compte :
        - Le plateau de jeu
        - Les joueurs
        - Les cases retirées
        */
    for (int l = 0; l < NB_LINES * 2 + 1; l++)
    {
        if (l == 0)
        {
            printf("\n     1   2   3   4   5   6   7");
        }
        if (l % 2 == 0)
        {
            printf("\n   +");
        }
        else
        {
            printf("\n %d |", (l + 1) / 2);
        }

        for (int c = 0; c < NB_COLS; c++)
        {
            if (l % 2 == 0)
            {
                printf("---+");
            }

            else
            {
                // Gère l'affichage des joueurs et des cases cassées
                print_cell(game, (l - 1) / 2, c);
            }
        }
    }
    printf("\n\n");
}
void print_joueur(player joueur, char j1[], char j2[])
{
    /* Fonction affichant le jour dont c'est le tour de manière colorée afin de distinguer plus facilement*/
    if (joueur == 1)
    {
        printf("\033[36;01m%s - \033[00m", j1);
    }
    else if (joueur == 2)
    {
        printf("\033[31;01m%s - \033[00m", j2);
    }
}

void get_case_joueur(board game, player joueur, int *ligne, int *col)
{
    /* Fonction permettant de récupérer les coordonnées du roi du joueur actuel */
    for (int l = 0; l < NB_LINES; l++)
    {
        for (int c = 0; c < NB_COLS; c++)
        {
            cell content = get_content(game, l, c);
            if (joueur == 1 && content == 1)
            {
                *ligne = l;
                *col = c;
                return;
            }
            else if (joueur == 2 && content == 2)
            {
                *ligne = l;
                *col = c;
                return;
            }
        }
    }
}
void affiche_cases_possibles(board game, player joueur, char j1[], char j2[])
{
    /* Permet d'afficher au joueur toutes les possibilités de mouvement dont il dispose */
    int ligne;
    int colonne;
    get_case_joueur(game, joueur, &ligne, &colonne);

    if (joueur == 1)
    {
        printf("\033[36;01m%s -\033[00m Vos choix de déplacement\033[36;01m", j1);
    }

    else
    {
        printf("\033[31;01m%s -\033[00m Vos choix de déplacement\033[31;01m", j2);
    }

    printf("\n ");

    if (get_content(game, ligne - 1, colonne - 1) == 0)
    {
        printf("1 ");
    }
    else
    {
        printf("X ");
    }

    if (get_content(game, ligne - 1, colonne) == 0)
    {
        printf("2 ");
    }
    else
    {
        printf("X ");
    }

    if (get_content(game, ligne - 1, colonne + 1) == 0)
    {
        printf("3 ");
    }
    else
    {
        printf("X");
    }

    printf("\n ");

    if (get_content(game, ligne, colonne - 1) == 0)
    {
        printf("8 ");
    }
    else
    {
        printf("X ");
    }

    printf("  ");

    if (get_content(game, ligne, colonne + 1) == 0)
    {
        printf("4 ");
    }
    else
    {
        printf("X ");
    }
    printf("\n ");

    if (get_content(game, ligne + 1, colonne - 1) == 0)
    {
        printf("7 ");
    }
    else
    {
        printf("X ");
    }

    if (get_content(game, ligne + 1, colonne) == 0)
    {
        printf("6 ");
    }
    else
    {
        printf("X ");
    }

    if (get_content(game, ligne + 1, colonne + 1) == 0)
    {
        printf("5 ");
    }
    else
    {
        printf("X ");
    }

    printf("\033[00m\n");
}

direction convert_choix(int choix)
{
    /* Permet d'afficher une roue des choix plus logique à l'utilisateur */
    direction dir;
    switch (choix)
    {
    case 1:
        dir = 5;
        break;
    case 2:
        dir = 6;
        break;
    case 3:
        dir = 7;
        break;
    case 4:
        dir = 4;
        break;
    case 5:
        dir = 2;
        break;
    case 6:
        dir = 1;
        break;
    case 7:
        dir = 0;
        break;
    case 8:
        dir = 3;
        break;
    default:
        break;
    }
    return dir;
}

void print_erreur_break(enum return_code code)
{
    /* Convertit les codes d'erreur en affichage pour l'utilisateur */
    if (code == 0)
    {
        return;
    }
    else if (code == 1)
    {
        printf("\033[90;01mLa case est en dehors du jeu !\033[00m\n");
    }
    else if (code == 2)
    {
        printf("\033[90;01mLa case est occupée ou déjà cassée !\033[00m\n");
    }
    else if (code == 3)
    {
        printf("\033[90;01mTu n'as pas la portée nécessaire !\033[00m\n");
    }
}

void move_joueur(board game, player joueur, char j1[], char j2[])
{
    /* Fonction affichant les différentes possibilités à l'utilisateur de mouvement puis son choix. */

    affiche_cases_possibles(game, joueur, j1, j2);
    int choix;
    direction direct;
    while (1) // Gère les problèmes de type
    {
        print_joueur(joueur, j1, j2);
        printf("Saisissez la case où vous souhaitez vous déplacer : ");
        if (scanf("%d", &choix) == 1)
        {
            break;
        }
        printf("\033[90;01mTu dois entrer un nombre valide !\033[00m\n");
        while (getchar() != '\n')
            ;
    }
    direct = convert_choix(choix);
    enum return_code code = move_toward(game, direct);
    while (code != 0)
    {
        print_erreur_break(code);
        print_joueur(joueur, j1, j2);
        printf("Saisissez la case où vous souhaitez vous déplacer : ");
        scanf("%d", &choix);
        direct = convert_choix(choix);
        code = move_toward(game, direct);
    }
}

void break_case_joueur(board game, player joueur, char j1[], char j2[])
{
    /* Fonction affichant les différentes possibilités à l'utilisateur de mouvement puis son choix. */

    int col_r, lig_r;
    while (1) // Les while permettent de gérer le cas où du texte est entré à la place des chiffres
    {
        print_joueur(joueur, j1, j2);
        printf("Saisissez la colonne de la case à retirer : ");
        if (scanf("%d", &col_r) == 1)
        {
            break;
        }
        printf("\033[90;01mTu dois entrer un nombre valide !\033[00m\n");
        while (getchar() != '\n')
            ;
    }
    while (1)
    {
        print_joueur(joueur, j1, j2);
        printf("Saisissez la ligne de la case à retirer : ");
        if (scanf("%d", &lig_r) == 1)
        {
            break;
        }
        printf("\033[90;01mTu dois entrer un nombre valide !\033[00m\n");
        while (getchar() != '\n')
            ;
    }

    enum return_code code = kill_cell(game, lig_r - 1, col_r - 1);

    while (code != 0)
    {

        print_erreur_break(code);
        while (1)
        {
            print_joueur(joueur, j1, j2);
            printf("Saisissez la colonne de la case à retirer : ");
            if (scanf("%d", &col_r) == 1)
            {
                break;
            }
            printf("\033[90;01mTu dois entrer un nombre valide !\033[00m\n");
            while (getchar() != '\n')
                ;
        }
        while (1)
        {
            print_joueur(joueur, j1, j2);
            printf("Saisissez la ligne de la case à retirer : ");
            if (scanf("%d", &lig_r) == 1)
            {
                break;
            }
            printf("\033[90;01mTu dois entrer un nombre valide !\033[00m\n");
            while (getchar() != '\n')
                ;
        }
        code = kill_cell(game, lig_r - 1, col_r - 1);
    }
}

void tour(board game, player joueur, int portee, char j1[], char j2[])
{
    /* Fonction effectuant un tour du jeu */
    move_joueur(game, joueur, j1, j2);
    affiche_jeu(game);
    break_case_joueur(game, joueur, j1, j2);
}

void afficher_gagnant(player j, char j1[], char j2[])
{
    /* Affiche le gagnant */
    if (j == 0)
    {
        // Egalité
        printf("\033[2J\033[H\e[236;5;1m\n ███████  ██████   █████  ██      ██ ████████ ███████     ██  \n ██      ██       ██   ██ ██      ██    ██    ██          ██  \n █████   ██   ███ ███████ ██      ██    ██    █████       ██  \n ██      ██    ██ ██   ██ ██      ██    ██    ██              \n ███████  ██████  ██   ██ ███████ ██    ██    ███████     ██ \n\e[0m\n");
    }
    else if (j == 1)
    {
        // J1 Gagne
        printf("\033[2J\033[H\e[36;5;1m\n%s a gagné !\e[0m\n", j1);
    }
    else if (j == 2)
    {
        // J2 Gagne
        printf("\033[2J\033[H\e[31;5;1m\n%s a gagné !\e[0m\n", j2);
    }
}
void jeu(char j1[], char j2[])
{
    /* Permet de faire une partie */
    board jeu = new_game();
    player joueur = current_player(jeu);
    while (!get_winner(jeu))
    {
        affiche_jeu(jeu);
        tour(jeu, joueur, 0, j1, j2);
        joueur = current_player(jeu);
    };
    player gagnant = get_winner(jeu);
    afficher_gagnant(gagnant, j1, j2);
}

void jeu_portee(char j1[], char j2[])
{
    /* Permet de faire une partie avec de la portée*/
    board jeu = new_special_game(0, 1);
    player joueur = current_player(jeu);
    while (!get_winner(jeu))
    {
        affiche_jeu(jeu);
        tour(jeu, joueur, 1, j1, j2);
        joueur = current_player(jeu);
    };
    player gagnant = get_winner(jeu);
    afficher_gagnant(gagnant, j1, j2);
}
void lireProtegee(char chaine[], int taille)
{
    /* Fonction permettant de récupérer une chaîne de caractères de manière sécurisée */

    char chain[21];
    scanf("%s", chain);
    int i = 0;
    while (i < taille - 1 && chain[i] != '\n')
    {
        chaine[i] = chain[i];
        i++;
    }
    chaine[i] = '\0';
}
int choix_mode(char j1[], char j2[])
{
    /* Permet à l'utilisateur de choisir le mode tout en gérant les erreurs de type */
    int choix = 0;
    printf("Entrez le pseudo du joueur 1 (20 caractères max) : ");
    lireProtegee(j1, 21);
    printf("Entrez le pseudo du joueur 2 (20 caractères max) : ");
    lireProtegee(j2, 21);
    while (1)
    {
        printf("\e[0mEntrez le mode de jeu que vous souhaitez lancer : ");
        if (scanf("%d", &choix) == 1)
        {
            break;
        }
        printf("\033[90;01mTu dois entrer un nombre valide !\033[00m\n");
        while (getchar() != '\n');
    }
    return choix;
}
int main(int args, char **argv)
{
    printf("\033[2J\033[H\e[1mBienvenue !\n");
    char j1[21];
    char j2[21];
    int choix = choix_mode(j1, j2); // 1 = Basique; 2 = Basique avec portée; 3 = Hexagonal; 4 = Hexagonal avec portée
    printf("\033[2J\033[H");
    if (choix == 1 || choix > 4 || choix < 1)
    {
        jeu(j1, j2);
    }
    else if (choix == 2)
    {
        jeu_portee(j1, j2);
    }
    return 0;
}