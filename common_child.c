#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* FREE s1 & s2 */
static void    free_strings(char **ptr1, char **ptr2)
{
    if (*ptr1 != NULL)
    {
        free(*ptr1);
        *ptr1 = NULL;
    }
    if (*ptr2 != NULL)
    {
        free(*ptr2);
        *ptr2 = NULL;
    }
}

/* FREE tab */
static void    free_tab(int ***tab, size_t l1)
{
	int **t = *tab;
	size_t i = 0;
	if (t != NULL)
	{
		while (i < l1 + 1)
		{
			free(t[i]);
			t[i] = NULL;
			i++;
		}
		free(t);
		t = NULL;
	}
}


static int		common_suffix(int ***tab, int l1, int j)
{
	j--;
	int **t = *tab;
	int count = 1;
	while (j >= 0)
	{
		if (t[l1][j] > count - 1)
			count = t[l1][j] + 1;
		j--;
	}
	return (count);
}

static void     fill_tab(char *s1, char *s2, int ***tab)
{
	int **t = *tab;
	int i = 0;
	int j = 0;
	int l1 = (int)strlen(s1);
	int l2 = (int)strlen(s2);
	int max = 0;
	while (j < l2) //init last line ->stock suffix
	{
		t[l1][j] = 0;
		j++;
	}
	while (i < l1)
	{
		j = l2 - 1;
		while (j >= 0)
		{
			t[i][j] = 0;
			if (s1[i] == s2[j])
			{
				if (i == 0 || j == 0)
				{
					t[i][j] = 1;
					t[l1][j] = 1;
				}
				else
				{
					t[i][j] = common_suffix(tab, l1, j);
					t[l1][j] = t[i][j];
					if (max < t[i][j])
						 max = t[i][j];
				}
			}
			j--;
		}
		i++;
	}
	printf("%d", max);
}

/*
// ** FOR DEBUG
static void		debug_print_tab(char *s1, char *s2, int ***tab)
{
	int **t = *tab;
	int i = 0;
	int j = 0;
	int l1 = (int)strlen(s1);
	int l2 = (int)strlen(s2);
	printf("\n_____________\n");
	while (i < l1)
	{
		j = 0;
		while (j < l2)
		{
			printf(" %d ", t[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
*/


int main()
{
    char *s1 = NULL;
    char *s2 = NULL;
    int **tab = NULL;
    if ((s1 = (char *)malloc(sizeof(char) * 5001)) == NULL)
        return -1;
    if ((s2 = (char *)malloc(sizeof(char) * 5001)) == NULL)
    {
        free_strings(&s1, &s2);
        return -1;
    }
    scanf("%s %s",s1,s2);
    size_t len1 = strlen(s1);
    if ((tab = (int **)malloc(sizeof(int *) * (len1 + 1))) == NULL)
    {
        free_strings(&s1, &s2);
        return -1;
    }
    size_t i = 0;
    while (i < len1 + 1)
    {
        tab[i] = (int *)malloc(sizeof(int) * strlen(s2));
        i++;
    }
	fill_tab(s1, s2, &tab);
	// debug_print_tab(s1, s2, &tab);
	free_tab(&tab, len1);
    free_strings(&s1, &s2);
    return 0;
}
