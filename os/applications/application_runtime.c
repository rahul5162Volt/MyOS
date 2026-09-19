#include "application_runtime.h"

static int application_exit_requested;

void application_exit(void)
{
    application_exit_requested = 1;
}

int application_should_exit(void)
{
    return application_exit_requested;
}

void application_clear_exit(void)
{
    application_exit_requested = 0;
}
