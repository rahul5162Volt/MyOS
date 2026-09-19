# --------------------------------------------------
# UI Tests
# --------------------------------------------------

file(
    GLOB_RECURSE
    UI_TEST_SOURCES
    CONFIGURE_DEPENDS
    ${MYOS_ROOT}/tests/integration/ui/*.c
)