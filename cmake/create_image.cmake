if(NOT DEFINED BOOT)
    message(FATAL_ERROR "BOOT is not defined")
endif()

if(NOT DEFINED STAGE2)
    message(FATAL_ERROR "STAGE2 is not defined")
endif()

if(NOT DEFINED KERNEL)
    message(FATAL_ERROR "KERNEL is not defined")
endif()

if(NOT DEFINED OUTPUT)
    message(FATAL_ERROR "OUTPUT is not defined")
endif()

set(TARGET_SIZE 1474560)

# Concatenate the three binary files as raw bytes.
execute_process(
    COMMAND powershell
        -NoProfile
        -Command
        "[IO.File]::WriteAllBytes('${OUTPUT}', ([IO.File]::ReadAllBytes('${BOOT}') + [IO.File]::ReadAllBytes('${STAGE2}') + [IO.File]::ReadAllBytes('${KERNEL}')))"
    RESULT_VARIABLE RESULT
)

if(RESULT)
    message(FATAL_ERROR "Failed to create OS image")
endif()

file(SIZE "${OUTPUT}" IMAGE_SIZE)

if(IMAGE_SIZE GREATER TARGET_SIZE)
    message(
        FATAL_ERROR
        "OS image is too large: ${IMAGE_SIZE} bytes"
    )
endif()

# Pad the image with zero bytes to 1.44 MiB.
math(EXPR PADDING "${TARGET_SIZE} - ${IMAGE_SIZE}")

if(PADDING GREATER 0)
    execute_process(
        COMMAND powershell
            -NoProfile
            -Command
            "[IO.File]::OpenWrite('${OUTPUT}').SetLength(${TARGET_SIZE})"
        RESULT_VARIABLE RESULT
    )

    if(RESULT)
        message(FATAL_ERROR "Failed to pad OS image")
    endif()
endif()

message(
    STATUS
    "Created OS image: ${OUTPUT} (${TARGET_SIZE} bytes)"
)