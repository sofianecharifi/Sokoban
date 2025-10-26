#include <stdio.h>

int print_tab(char **tab)
{
    int i = 0;

    while(tab[i] != NULL)
    {
        int j = 0;

        while(tab[i][j] != '\0')
        {
            printf("%c", tab[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    return 0;
}