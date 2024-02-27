#include <stdio.h>

void print()
{
    printf("-------------------------------------------------\n");
    printf("Selectable function code\n");
    printf("1. Read Coil (0x01)\n");
    printf("2. Read Discrete Input (0x02)\n");
    printf("3. Read Holding Registers (0x03)\n");
    printf("4. Read Input Registers (0x04)\n");
    printf("5. Write Single Coil (0x05)\n");
    printf("6. Write Single Holding Register (0x06)\n");
    printf("7. Write Multiple Coils (0xf)\n");
    printf("8. Write Multiple Holding Registers (0x10)\n");
    printf("9. escape\n");
    printf("-------------------------------------------------\n");
    printf("Select function code: ");
}