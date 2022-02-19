#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (0);
	while(str[i])
		i ++;
	return (i);
}

int	ft_nbrlen(long nbr, int base)
{
	int	i;

	i = 1;
	while (nbr >= base)
	{
		nbr = nbr / base;
		i ++;
	}
	return (i);
}

void	ft_putnbr(long nbr, char *base, int baselen)
{
	if (nbr >= baselen)
		ft_putnbr(nbr / baselen, base, baselen);
	write(1, &base[nbr % baselen], 1);
}

int	ft_printf(const char *str, ...)
{
	va_list arg;
	int	i;
	int ret;
	int	with;
	int prec;
	int	len;
	char *string;
	int	num;
	unsigned int	unum;
	int	neg;

	i = 0;
	ret = 0;
	va_start(arg, str);
	while(str[i])
	{
		with = 0;
		num = 0;
		unum = 0;
		prec = -1;
		neg = 0;
		if (str[i] == '%')
		{
			i ++;
			while (str[i] >= '0' && str[i] <= '9')
			{
				with = with * 10 + str[i] - '0';
				i ++;
			}
			// printf("with = %d\n",with);
			if (str[i] == '.')
			{
				i ++;
				prec = 0;
				while (str[i] >= '0' && str[i] <= '9')
				{
					prec = prec * 10 + str[i] - '0';
					i ++;
				}
			}
			// printf("prec = %d\n",prec);
			if (str[i] == 's')
			{	
				// printf("\n ZALUPA \n");
				string = va_arg(arg, char *);
				len = ft_strlen(string);
				if (len > prec && prec != -1 && string)
					len = prec;
				if (!string && (prec == -1 || prec > 5))
				{
					string = "(null)";
					len = ft_strlen(string);
				}
				while (with -- > len)
					ret += write(1, " ", 1);
				ret += write(1, string, len);
			}
			if (str[i] == 'd')
			{
				num = va_arg(arg, int);
				if (num == -2147483648)
				{
					len = 10;
					neg = 1;
				}
				else
				{
					if (num < 0)
					{
						num = -num;
						neg = 1;
					}
					if (num == 0 && prec == 0)
						len = 0;
					else
						len = ft_nbrlen(num, 10);
				}
				if (prec > len)
					prec = prec - len;
				else 
					prec = 0;
				while (with -- > len + neg + prec)
					ret += write (1, " ", 1);
				if (neg)
					ret += write (1, "-", 1);
				while (prec --)
					ret += write (1, "0", 1);
				if (num == -2147483648)
					write(1, "2147483648", 10);
				else if (len)
					ft_putnbr(num, "0123456789", 10);
				ret += len;
			}
			if (str[i] == 'x')
			{
				unum = va_arg(arg, unsigned int);
				if (unum == 0 && prec == 0)
					len = 0;
				else
					len = ft_nbrlen(unum, 16);
				if (prec > len)
					prec = prec - len;
				else 
					prec = 0;
				while (with -- > len + prec)
					ret += write (1, " ", 1);
				while (prec --)
					ret += write (1, "0", 1);
				if (len)	
					ft_putnbr(unum, "0123456789abcdef", 16);
				ret += len;
			}
			i ++;
		}
		else
		{
			ret += write(1, &str[i], 1);
			i ++;
		}
	}
	va_end(arg);
	return (ret);
}

// int main()
// {	int a;
// 	int b;
// 	char *str = 0;
// 	a = ft_printf("%.6s\n", str);
// 	b = printf("%.6s\n", str);
// 	printf("A=%d\t B=%d\n",a ,b);
// }