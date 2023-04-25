#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * print_char - Prints a char
 * @listofargs: List a of arguments
 * @buffer: Buffer array to handle print
 * @aflags:  Calculates active aflags
 * @width: Width
 * @pspec: pspec specification
 * @sspec: sspec specifier
 * Return: Number of chars printed
 */
int print_char(va_list listofargs, char buffer[],
	int aflags, int width, int pspec, int sspec)
{
	char c = va_arg(listofargs, int);

	return (handle_write_char(c, buffer, aflags, width, pspec, sspec));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @listofargs: List a of arguments
 * @buffer: Buffer array to handle print
 * @aflags:  Calculates active aflags
 * @width: get width.
 * @pspec: pspec specification
 * @sspec: sspec specifier
 * Return: Number of chars printed
 */
int print_string(va_list listofargs, char buffer[],
	int aflags, int width, int pspec, int sspec)
{
	int length = 0, i;
	char *str = va_arg(listofargs, char *);

	UNUSED(buffer);
	UNUSED(aflags);
	UNUSED(width);
	UNUSED(pspec);
	UNUSED(sspec);
	if (str == NULL)
	{
		str = "(null)";
		if (pspec >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (pspec >= 0 && pspec < length)
		length = pspec;

	if (width > length)
	{
		if (aflags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @listofargs: Lista of arguments
 * @buffer: Buffer array to handle print
 * @aflags:  Calculates active aflags
 * @width: get width.
 * @pspec: pspec specification
 * @sspec: sspec specifier
 * Return: Number of chars printed
 */
int print_percent(va_list listofargs, char buffer[],
	int aflags, int width, int pspec, int sspec)
{
	UNUSED(listofargs);
	UNUSED(buffer);
	UNUSED(aflags);
	UNUSED(width);
	UNUSED(pspec);
	UNUSED(sspec);
	return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @listofargs: Lista of arguments
 * @buffer: Buffer array to handle print
 * @aflags:  Calculates active aflags
 * @width: get width.
 * @pspec: pspec specification
 * @sspec: sspec specifier
 * Return: Number of chars printed
 */
int print_int(va_list listofargs, char buffer[],
	int aflags, int width, int pspec, int sspec)
{
	int i = BUFF_sspec - 2;
	int is_negative = 0;
	long int n = va_arg(listofargs, long int);
	unsigned long int num;

	n = convert_sspec_number(n, sspec);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_sspec - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, aflags, width, pspec, sspec));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @listofargs: Lista of arguments
 * @buffer: Buffer array to handle print
 * @aflags:  Calculates active aflags
 * @width: get width.
 * @pspec: pspec specification
 * @sspec: sspec specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list listofargs, char buffer[],
	int aflags, int width, int pspec, int sspec)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(aflags);
	UNUSED(width);
	UNUSED(pspec);
	UNUSED(sspec);

	n = va_arg(listofargs, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
