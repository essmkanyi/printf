#include <stdio.h>
#include <stdarg.h>

/**
 * print_char - prints a single character
 * @arg: character argument
 * @count: pointer to character count
 */
void print_char(va_list arg, int *count)
{
	char c = va_arg(arg, int);

	putchar(c);
	(*count)++;
}

/**
 * print_str - prints a string
 * @arg: string argument
 * @count: pointer to character count
 */
void print_str(va_list arg, int *count)
{
	const char *s = va_arg(arg, const char *);

	while (*s)
	{
		putchar(*s);
		s++;
		(*count)++;
	}
}

/**
 * print_percent - prints a percent character
 * @count: pointer to character count
 */
void print_percent(int *count)
{
	putchar('%');
	(*count)++;
}

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

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			switch (*format)
			{
				case 'c':
					print_char(args, &count);
					break;
				case 's':
					print_str(args, &count);
					break;
				case '%':
					print_percent(&count);
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

