#include "main.h"
/****************** PRINT POINTER ******************/
int print_pointer(va_list types, char buffer[], int flags) {
    char extra_char = 0;
    int ind = BUFF_SIZE - 2; /* length=2, for '0x' */
    unsigned long num_addrs;
    void *addrs = va_arg(types, void *);

    if (addrs == NULL) {
        return write(1, "(nil)", 5);
    }

    buffer[BUFF_SIZE - 1] = '\0';
    num_addrs = (unsigned long)addrs;

    while (num_addrs > 0) {
        buffer[ind--] = "0123456789abcdef"[num_addrs % 16];
        num_addrs /= 16;
    }

    if ((flags & F_ZERO) && !(flags & F_MINUS)) {
        extra_char = '+';
    }

    ind++;

    return write_pointer(buffer, ind, ind + 2, flags, extra_char);
}

/************************* PRINT NON PRINTABLE **************************/
int print_non_printable(va_list types, char buffer[], int flags) {
    int i = 0, offset = 0;
    char *str = va_arg(types, char *);

    if (str == NULL) {
        return write(1, "(null)", 6);
    }

    while (str[i] != '\0') {
        if (is_printable(str[i])) {
            buffer[i + offset] = str[i];
        } else {
            offset += append_hexa_code(str[i], buffer, i + offset);
        }
        i++;
    }

    buffer[i + offset] = '\0';

    return write(1, buffer, i + offset);
}

/************************* PRINT REVERSE **************************/
int print_reverse(va_list types) {
    char *str;
    int i, count = 0;

    str = va_arg(types, char *);

    if (str == NULL) {
        str = ")Null(";
    }

    for (i = 0; str[i]; i++) {}

    for (i = i - 1; i >= 0; i--) {
        char z = str[i];
        write(1, &z, 1);
        count++;
    }

    return count;
}

/************************* PRINT A STRING IN ROT13 *************************/
int print_rot13string(va_list types) {
    char x;
    char *str;
    unsigned int i, j;
    int count = 0;
    char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

    str = va_arg(types, char *);

    if (str == NULL) {
        str = "(AHYY)";
    }

    for (i = 0; str[i]; i++) {
        for (j = 0; in[j]; j++) {
            if (in[j] == str[i]) {
                x = out[j];
                write(1, &x, 1);
                count++;
                break;
            }
        }
        if (!in[j]) {
            x = str[i];
            write(1, &x, 1);
            count++;
        }
    }

    return count;
}
