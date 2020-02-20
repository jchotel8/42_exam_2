#include <libc.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_max(int a, int b)
{
	return (a > b ? a : b);
}

int ft_min(int a, int b)
{
	return (a < b ? a : b);
}

void ft_itoa(unsigned int nb, int i, int j, char buf[20])
{
	nb >= i ? ft_itoa(nb / i, i, j + 1, buf) : 0;
	buf[j] = (i == 10 ? "0123456789"[nb % i] : "0123456789abcdef"[nb % i]);
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

void ft_init(char buf[20])
{
	int i = 0;
	while (i < 20)
	{
		buf[i] = 0;
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
			int space = 0;
			int zero = 0;
            char buf[20];
            ft_init(buf);
	
			while(*str >= '0' && *str <= '9')
			{
				width *= 10;
				width += *str - '0';
				str++;
			}
			if(*str == '.')
			{
				precision = 0;
				str++;
				while(*str >= '0' && *str <= '9')
				{
					precision *= 10;
					precision += *str - '0';
					str++;
				}
			}
			if (*str == 's')
			{
				str++;
				char *s = va_arg(va, char *);
                int taille = (precision != -1 ? ft_min(precision, ft_strlen(s)) : ft_strlen(s));
				space = ft_max(width - taille, 0);
				while (space-- && ret++)
					write (1, " ", 1);
				write(1, s, taille);
				ret += ft_strlen(s);
			}
            if (*str == 'd')
            {
                str++;
                int neg = 0;
                int d = va_arg(va, int);
                if (d < 0)
                {
                    d = -d;
                    neg = 1;
                }
                ft_itoa(d, 10, 0, buf);
                ft_switch(buf);
                
                zero = ft_max(precision - ft_strlen(buf), 0);
                space = ft_max(width - zero - ft_strlen(buf) - neg, 0);
                while (space-- && ret++)
                    write (1, " ", 1);
                if (neg && ret++)
                    write (1, "-", 1);
                while (zero-- && ret++)
                    write (1, "0", 1);
                write(1, buf, ft_strlen(buf));
                ret += ft_strlen(buf);
            }
            if (*str == 'x')
            {
                str++;
                unsigned int x = va_arg(va, unsigned int);
                ft_itoa(x, 16, 0, buf);
                ft_switch(buf);
                
                zero = ft_max(precision - ft_strlen(buf), 0);
                space = ft_max(width - zero - ft_strlen(buf), 0);
                while (space-- && ret++)
                    write (1, " ", 1);
                while (zero-- && ret++)
                    write (1, "0", 1);
                write(1, buf, ft_strlen(buf));
                ret += ft_strlen(buf);
            }
		}
		write(1, str, 1);
		ret++;
		str++;
	}
	va_end(va);
	return (ret);
}

int main(int ac, char **av)
{
	//char buf[20];
	//ft_init(buf);
	//printf("la valeur max entre 2 et 10 est %d\n", ft_max(2, 10));
	//printf("la valeur min entre 2 et 10 est %d\n", ft_min(2, 10));
	//ft_itoa(123456789, 10, 0, buf);
	//ft_switch(buf); 
	//printf("itoa du de 123456789 donne %s", buf);
	int count = ft_printf("salut je fais un test, %.10s\n", "testing");
	int count2 = printf("salut je fais un test, %.10s\n", "testing");
    count = ft_printf("salut je fais un test, %8.5d\n", -20);
    count2 = printf("salut je fais un test, %8.5d\n", -20);
    count = ft_printf("salut je fais un test, %.10x\n", -20);
    count2 = printf("salut je fais un test, %.10x\n", -20);
	printf("%d\n", count);
	printf("%d\n", count2);
}
