#include <libc.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
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

void ft_init(char buf[20])
{
	int i = 0;
	while (i < 20)
	{
		buf[i] = 0;
		i++;
	}
}

void ft_itoa(unsigned long nb, int i, int pos, char buf[20])
{
	nb >= i ? ft_itoa(nb / i, i, pos + 1, buf) : 0;
	buf[pos] = (i == 10 ? "0123456789"[nb % i] : "0123456789abcdef"[nb % i]);
}

void ft_switch(char buf[20])
{
	int i = 0;
	char copy[20];
	while(buf[i])
	{
		copy[i] = buf[i];
		i++;
	}
	int size = ft_strlen(buf);
	i = 0;
	while(buf[i])
	{
		buf[i] = copy[size - 1 - i];
		i++;
	}
}

int ft_printf(char *str, ...)
{
	int ret = 0;
	va_list va;
	va_start(va, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			int width = 0;
			int precision = -1;
			char buf[20];
			ft_init(buf);
			int zeros = 0;
			int spaces = 0;
			while(*str >= '0' && *str <= '9')
			{
				width *= 10;
				width += *str - '0';
				str++;
			}
			if (*str == '.')
			{
				str++;
				precision = 0;
				while(*str >= '0' && *str <= '9')
				{
					precision *= 10;
					precision += *str - '0';
					str++;
				}
			}
			if (*str == 'd')
			{
				int neg = 0;
				int nb = va_arg(va, int);
				neg = (nb < 0 ? 1 : 0);
				nb = (nb < 0 ? -nb : nb);
				ft_itoa(nb, 10, 0, buf);
				ft_switch(buf);
				zeros = ft_max(precision - ft_strlen(buf), 0);
				spaces = ft_max(width - zeros - neg - ft_strlen(buf), 0);
				while (spaces-- && ret++)
					write(1, " ", 1);
				if (neg == 1 && ret++)
					write(1, "-", 1);
				while (zeros-- && ret++)
					write(1, "0", 1);
				write(1, buf, ft_strlen(buf));
				ret += ft_strlen(buf);
				str++; 
			}
			if (*str == 'x')
			{
				unsigned long nb = va_arg(va, unsigned long);
				ft_itoa(nb, 16, 0, buf);
				ft_switch (buf);
				zeros = ft_max(precision - ft_strlen(buf), 0);
				spaces = ft_max(width - zeros -ft_strlen(buf), 0);
				while(spaces-- && ret++)
					write(1, " ", 1);
				while (zeros-- && ret++)
					write(1, "0", 1);
				write(1, buf, ft_strlen(buf));
				ret += ft_strlen(buf);
				str++;
			}
			if (*str == 's')
			{
				char *s = va_arg(va, char *);
				s = (s == NULL? "(null)" : s);
				int taille = (precision != -1 ? ft_min(ft_strlen(s), precision) : ft_strlen(s));
				spaces = ft_max(width - taille, 0);
				while (spaces-- && ret++)
					write(1, " ", 1);
				write(1, s, taille);
				ret += taille;
				str++;
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
	int count = ft_printf("testing %10.2s\n", NULL);
	int count2 = printf("testing %10.2s\n", NULL);
	printf("%d\t%d\n", count, count2);
	count = ft_printf("testing %10.6d\n", 123);
	count2 = printf("testing %10.6d\n", 123);
	printf("%d\t%d\n", count, count2);
	count = ft_printf("testing %10.6x\n", 123);
	count2 = printf("testing %10.6x\n", 123);
	printf("%d\t%d\n", count, count2);
	//ft_itoa(16, 16, 0, buf);
	//printf("%s\n", buf);
	//ft_switch(buf);
	//printf("%s\n", buf);
}
