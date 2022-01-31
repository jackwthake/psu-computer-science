#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int main(int argc, char **argv) {
    uint32_t i, a, b, result;
    char *end;

    if (argc != 3) { /* ensure correct amount of input */
        assert(printf("Error: please provide two hexadecimal numbers as arguments to the program.\n") > 0);
        return -1;
    }

    /* convert arguments to a workable format */
    a = strtol(argv[1], &end, 16);
    assert(end != argv[1]);
    b = strtol(argv[2], &end, 16);
    assert(end != argv[2]);

    /* compare the two numbers, the result will have their shared bits */
    result = a & b;
    assert(printf("Bits ") > 0);
    for (i = 0; i < 32; ++i) { /* iterate to identify which bits are in common */
        if (result >> i & 0x1) {
            assert(printf("%d,", i) > 0);
        }
    }

    assert(printf(" in common. Hexadecimal: %x, Signed: %d, Unsigned: %u.\n", result, result, result) > 0);

    return 0;
}
