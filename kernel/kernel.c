void kernel_main()
{
    asm volatile (
        "mov $0x0E, %%ah\n\t"
        "mov $'K', %%al\n\t"
        "int $0x10\n\t"

        "mov $'e', %%al\n\t"
        "int $0x10\n\t"

        "mov $'r', %%al\n\t"
        "int $0x10\n\t"

        "mov $'n', %%al\n\t"
        "int $0x10\n\t"

        "mov $'e', %%al\n\t"
        "int $0x10\n\t"

        "mov $'l', %%al\n\t"
        "int $0x10\n\t"

        "mov $'!', %%al\n\t"
        "int $0x10\n\t"

        :
        :
        : "ax"
    );

    for (;;)
    {
    }
}