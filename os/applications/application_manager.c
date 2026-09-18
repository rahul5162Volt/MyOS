#include "application_manager.h"

#include "application_runtime.h"

#include "editor/editor.h"
#include "calculator/calculator.h"

void os_application_manager_run_editor(void)
{
    application_clear_exit();

    editor_run();
}

void os_application_manager_run_calculator(void)
{
    application_clear_exit();

    calculator_run();
}
