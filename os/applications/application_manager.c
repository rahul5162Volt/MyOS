#include "application_manager.h"

#include "application_runtime.h"

#include "editor/editor.h"
#include "calculator/calculator.h"

void application_manager_run_editor(void)
{
    application_clear_exit();

    editor_run();
}

void application_manager_run_calculator(void)
{
    application_clear_exit();

    calculator_run();
}
