#include <stdio.h>
#include <stdarg.h>

/**
 * _printf - custom printf implementation
 * @format: format string
 *
 * Return: number of characters printed (excluding null byte)
 */
int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;
	char c;
	const char *s;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
				case 'c':
					c = (char) va_arg(args, int);
					putchar(c);
					count++;
					break;
				case 's':
					s = va_arg(args, const char *);
					while (*s)
					{
						putchar(*s);
						s++;
						count++;
					}
					break;
				case '%':
					putchar('%');
					count++;
					break;
				default:
					/* unsupported conversion specifier */
					break;
			}
		}
		else
		{
			putchar(*format);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}

