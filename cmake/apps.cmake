# --------------------------------------------------
# Applications
# --------------------------------------------------

file(
    GLOB_RECURSE
    APP_SOURCES
    CONFIGURE_DEPENDS
    ${MYOS_ROOT}/apps/*.c
)

set(APP_INCLUDE_DIRS)

foreach(APP_SOURCE ${APP_SOURCES})
    get_filename_component(APP_DIR ${APP_SOURCE} DIRECTORY)

    list(APPEND APP_INCLUDE_DIRS
        ${APP_DIR}
    )
endforeach()

list(REMOVE_DUPLICATES APP_INCLUDE_DIRS)

add_library(app_objects OBJECT
    ${APP_SOURCES}
)

target_include_directories(app_objects
    PRIVATE
    ${APP_INCLUDE_DIRS}
)

target_compile_options(
    app_objects
    PRIVATE
    -m32
    -ffreestanding
    -fno-stack-protector
    -fno-pie
)