#include <libc.h>

int ft_strlen(char *str)
{
    int i = 0;
    while(str[i])
        i++;
    return (i);
}

int ft_max(int a, int b)
{
    return (a > b ? a : b);
}

int ft_min (int a, int b)
{
    return (a < b ? a : b);
}

void ft_init(char buf[20])
{
    int i = 0;
    while (i < 20)
    {
        buf[i] = 0;
        i++;
    }
}

void ft_itoa(unsigned long nb, int i, int pos,char buf[20])
{
    nb >= i ? ft_itoa(nb / i, i, pos + 1, buf) : 0;
    buf[pos] = (i == 10 ? "0123456789"[nb % i] : "0123456789abcdef"[nb % i]);
}

void ft_switch(char buf[20])
{
    int i = 0;
    char copy[20];
    int len = ft_strlen(buf);
    
    while (i < 20)
    {
        copy[i] = buf[i];
        i++;
    }
    i = 0;
    while (i < 20)
    {
        buf[i] = copy[len - i - 1];
        i++;
    }
}

int ft_printf(char *str, ...)
{
    va_list va;
    int ret = 0;
    
    va_start(va, str);
    while (*str)
    {
        if (*str == '%')
        {
            str++;
            int width = 0;
            int precision = -1;
            int zeros = 0;
            int spaces = 0;
            char buf[20];
            ft_init(buf);
            while (*str >= '0' && *str <= '9')
            {
                width *= 10;
                width += *str - '0';
                str++;
            }
            if (*str == '.')
            {
                precision = 0;
                str++;
                while (*str >= '0' && *str <= '9')
                {
                    precision *= 10;
                    precision += *str - '0';
                    str++;
                }
            }
            if (*str == 'd')
            {
                int neg = 0;
                int d = va_arg(va, int);
                neg= (d < 0 ? 1 : 0);
                d= (d < 0 ? -d : d);
                ft_itoa(d, 10, 0, buf);
                ft_switch(buf);
                zeros = ft_max(precision - ft_strlen(buf), 0);
                spaces = ft_max(width - zeros - ft_strlen(buf) - neg, 0);
                while (spaces-- && ret++)
                    write(1, " ", 1);
                if (neg == 1)
                    write(1, "-", 1);
                while (zeros-- && ret++)
                    write(1, "0", 1);
                write(1, buf, ft_strlen(buf));
                ret +=ft_strlen(buf);
                str++;
            }
            else if (*str == 'x')
            {
                unsigned int x = va_arg(va, unsigned int);
                ft_itoa(x, 16, 0, buf);
                ft_switch(buf);
                zeros = ft_max(precision - ft_strlen(buf), 0);
                spaces = ft_max(width - zeros - ft_strlen(buf), 0);
                while (spaces-- && ret++)
                    write(1, " ", 1);
                while (zeros-- && ret++)
                    write(1, "0", 1);
                write(1, buf, ft_strlen(buf));
                ret += ft_strlen(buf);
                str++;
            }
            else if (*str == 's')
            {
                char *s = va_arg(va, char *);
                int taille = (precision != -1 ? ft_min(precision, ft_strlen(s)) : ft_strlen(s));
                spaces = ft_max(width - taille, 0);
                while (spaces-- && ret++)
                    write(1, " ", 1);
                write (1, s, taille);
                ret += taille;
                str++;
            }
        }
        write(1, str++, 1);
        ret++;
    }
    va_end(va);
    return (ret);
}

int main(int ac, char **av)
{
    //char buf[20];
    //ft_init(buf);
    //printf("la valeur min entre 2 et 5 est %d\n", ft_min(2, 5));
    //printf("la valeur max entre 2 et 5 est %d\n", ft_max(2, 5));
    //ft_itoa(123456789, 10, 0, buf);
    //printf("ft_itoa de 123456789 donne %s en base 10\n", buf);
    //ft_switch(buf);
    //printf("ft_switch de buf donne %s\n", buf);
    //ft_init(buf);
    //ft_itoa(16, 16, 0, buf);
    //printf("ft_itoa de 16 donne %s en base 16\n", buf);
    //ft_switch(buf);
    //printf("ft_switch de buf donne %s\n", buf);
    int count = ft_printf("testing %3.2s\n", NULL);
    int count2 = printf("testing %3.2s\n", NULL);
    printf("%d\t%d\n", count, count2);
    count = ft_printf("testing %10.6d\n", -1234);
    count2 = printf("testing %10.6d\n", -1234);
    printf("%d\t%d\n", count, count2);
    count = ft_printf("testing %10.6x\n", -1234);
    count2 = printf("testing %10.6x\n", -1234);
    printf("%d\t%d\n", count, count2);
    
}

