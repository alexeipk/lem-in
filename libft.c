
#include <unistd.h> // To write function



void	ft_putnbr(int n)
{
	char num;

	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else {
		if (n < 0) {
			write(1, "-", 1);
			n = n * -1;
		}
		if (n > 9) {
			ft_putnbr(n / 10);
			ft_putnbr(n % 10);
		}
		else {
			num = n + '0';
			write(1, &num, 1);
		}
	}
}


int		ft_isdigit(int c) {
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}


int	ft_atoi(const char *str) {
	int	index;
	int	sign;
	int	res;

	index = 0;
	sign = 1;
	res = 0;
	while (str[index] == ' ' || (str[index] >= '\t' && str[index] <= '\r'))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			sign = -1;
		index++;
	}
	while (str[index] >= '0' && str[index] <= '9')
	{
		res = (str[index] - '0') + (res * 10);
		index++;
	}
	return (res * sign);
}