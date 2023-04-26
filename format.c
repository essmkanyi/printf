#include <stdio.h>
#include <stdarg.h>
#include <main.h>
/**
 * _printf - Prints formatted output to stdout.
 *
 * @format: Format string.
 *
 * Return: Number of characters printed (excluding null byte).
 */
int _printf(const char *format, ...)
{
	va_list args;
	int checker = 0;

	va_start(args, format);

	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c')
			{
				int c = va_arg(args, int);

				putchar(c);
				checker++;
			}
			else if (*format == 's')
			{
				char *s = va_arg(args, char *);

				while (*s != '\0')
				{
					putchar(*s);
					s++;
					checker++;
				}
			}
			else if (*format == '%')
			{
				putchar('%');
				checker++;
			}
		}
		else
		{
			putchar(*format);
			checker++;
		}

		format++;
	}

	va_end(args);

	return (checker);
}

