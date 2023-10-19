#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

int _printf(const char *format, ...)
{
    int i, total_printed_chars = 0;
    int flags, width, precision, size, buff_index = 0;
    va_list args;
    char output_buffer[BUFF_SIZE];

    if (format == NULL)
        return -1;

    va_start(args, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            output_buffer[buff_index++] = format[i];
            if (buff_index == BUFF_SIZE)
                print_buffer(output_buffer, &buff_index);
            total_printed_chars++;
        }
        else
        {
            print_buffer(output_buffer, &buff_index);
            flags = get_flags(format, &i);
            width = get_width(format, &i, args);
            precision = get_precision(format, &i, args);
            size = get_size(format, &i);
            ++i;
            int chars_printed = handle_print(format, &i, args, output_buffer,
                flags, width, precision, size);
            if (chars_printed == -1)
                return -1;
            total_printed_chars += chars_printed;
        }
    }

    print_buffer(output_buffer, &buff_index);

    va_end(args);

    return total_printed_chars;
}


/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
