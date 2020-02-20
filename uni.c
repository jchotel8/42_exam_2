#include <libc.h>

void    ft_union(char *s1, char *s2)
{
    int    tab[256];
    int    a;
    
    a = 0;
    while (s1[a])
    {
        if (tab[(int)s1[a]] == 0)
        {
            tab[(int)s1[a]] = 1;
            write(1, &s1[a], 1);
        }
        a++;
    }
    a = 0;
    while (s2[a])
    {
        if (tab[(int)s2[a]] == 0)
        {
            tab[(int)s2[a]] = 1;
            write(1, &s2[a], 1);
        }
        a++;
    }
}

void ft_inter(char *s1, char *s2)
{
    int    tab[256];
    int    a;
    
    a = 0;
    while (s1[a])
    {
        if (tab[(int)s1[a]] == 0)
        {
            tab[(int)s1[a]] = 1;
        }
        a++;
    }
    a = 0;
    while (s2[a])
    {
        if (tab[(int)s2[a]] == 1)
        {
            tab[(int)s2[a]] = 0;
            write(1, &s2[a], 1);
        }
        a++;
    }
}

int main(int ac, char **av)
{
    ft_union(av[1], av[2]);
    //printf("\n");
    ft_inter(av[1], av[2]);
}
