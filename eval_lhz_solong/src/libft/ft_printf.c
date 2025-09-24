/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regillio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 10:02:41 by regillio          #+#    #+#             */
/*   Updated: 2025/07/14 20:13:02 by regillio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	format_type(char c, va_list *ap)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_putchar((char)va_arg(*ap, int));
	else if (c == 's')
		count += ft_putstr(va_arg(*ap, char *));
	else if (c == 'i' || c == 'd')
		count += ft_putnbr(va_arg(*ap, int));
	else if (c == 'u')
		count += ft_putnbr_unsigned(va_arg(*ap, unsigned int));
	else if (c == 'X')
		count += ft_putnbr_hex(va_arg(*ap, unsigned int));
	else if (c == 'x')
		count += ft_putnbr_hex_lowercase(va_arg(*ap, unsigned int));
	else if (c == 'p')
		count += ft_putnbr_ptr(va_arg(*ap, void *));
	else if (c == '%')
		count += ft_putchar('%');
	else
		return (-1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		i;
	int		count;

	va_start(ap, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += format_type(format[i + 1], &ap);
			i++;
		}
		else
		{
			ft_putchar(format[i]);
			count++;
		}
		i++;
	}
	va_end(ap);
	return (count);
}
/*
int	main()
{
	int ft;
	int pf;
	char s[] = "bonjour";
	char c = 'c';
	int d = -1;
	int i = -2;
	int *ptr = &d;
	unsigned int u = 0;
	unsigned int hex_up= 1234;
	unsigned int hex_low= 98678;
	char *dup = strdup("bonjour");

	ft = ft_printf("FT_PRINTF:\nchar:%c\n\
	string:%s\ndecimal:%d\ninteger:%i\nsigned int:%u\n\
	pourcentage:%%\nHexadecimal Uppercase:%X\nhexadecimal lowercase:%x\n\
	pointer address:%p\nheap-allocated pointer address:%p\n\
	",c,s,d,i, u, hex_up, hex_low, ptr, dup);
	printf("-----------------------------------\n");
	pf = printf("CS_PRINTF:\nchar:%c\nstring:%s\ndecimal:%d\n\
	integer:%i\nsigned int:%u\npourcentage:%%\n\
	Hexadecimal Uppercase:%X\nhexadecimal lowercase:%x\n\
	pointer address:%p\nheap-allocated pointer address:%p\n\
	",c,s,d,i, u, hex_up, hex_low, ptr, dup);
	ft_printf("RETURN FT_PF():%d\nRETURN PF():%d\n",ft,pf);
	ft_printf("---------------------------------\n");
	unsigned int u2 = 10000000;
	int a =  ft_printf("%u\n", u2);
	ft_printf("%d\n",a);
	int b = printf("%d\n",u);
	printf("%d\n",b);
	char *sn = NULL;
	printf("%s",s);
	printf(" NULL %s NULL", sn);
	printf("%p %p", NULL, NULL);
	ft_printf("%p %p", NULL, NULL);
	char *s = NULL;
	int a = printf("%s", s);
//	printf("%k");
	int b = ft_printf("%k");
	b = ft_printf("%k",b, a);	
	printf("%d",b);	
	return (0);
}
*/
