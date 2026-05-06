cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)
# symbols (macros)
set(GD32_DEFINES
    GD32F10X_MD
    USE_FREERTOS
    $<$<CONFIG:Debug>:DEBUG>
)

# include paths
set(GD32_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/Core/Inc
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/include
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/GD/GD32F10x/Include
    ${CMAKE_SOURCE_DIR}/Drivers/GD32F10x_standard_peripheral/Include
)

# application sources
set(GD32_APPLICATION_SOURCES
    ${CMAKE_SOURCE_DIR}/Core/Src/main.c
    ${CMAKE_SOURCE_DIR}/Core/Src/freertos.c
    ${CMAKE_SOURCE_DIR}/Core/Src/gd32f10x_it.c
    ${CMAKE_SOURCE_DIR}/Core/Src/systick.c
    ${CMAKE_SOURCE_DIR}/startup_gd32f10x_md.s
)

# driver sources
set(GD32_DRIVER_SOURCES
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/GD/GD32F10x/Source/system_gd32f10x.c
    ${CMAKE_SOURCE_DIR}/Drivers/GD32F10x_standard_peripheral/Source/gd32f10x_gpio.c
    ${CMAKE_SOURCE_DIR}/Drivers/GD32F10x_standard_peripheral/Source/gd32f10x_misc.c
    ${CMAKE_SOURCE_DIR}/Drivers/GD32F10x_standard_peripheral/Source/gd32f10x_rcu.c
)

# Drivers Midllewares
set(FREERTOS_SOURCES
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/list.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/queue.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/timers.c
    # ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    ${CMAKE_SOURCE_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3/port.c
)


# Link directories setup
set(GD_LINK_DIRS

)
# Project static libraries
set(GD_LINK_LIBS 
    GD32_Drivers
    FreeRTOS
    
)
# Interface library for includes and symbols
add_library(gd32 INTERFACE)
target_include_directories(gd32 INTERFACE ${GD32_INCLUDE_DIRS})
target_compile_definitions(gd32 INTERFACE ${GD32_DEFINES})

# Create GD32_Drivers static library
add_library(GD32_Drivers OBJECT)
target_sources(GD32_Drivers PRIVATE ${GD32_DRIVER_SOURCES})
target_link_libraries(GD32_Drivers PUBLIC gd32)

# Create FreeRTOS static library
add_library(FreeRTOS OBJECT)
target_sources(FreeRTOS PRIVATE ${FREERTOS_SOURCES})
target_link_libraries(FreeRTOS PUBLIC gd32)

# Add application sources to the project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${GD32_APPLICATION_SOURCES})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${GD_LINK_DIRS})

# Add libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} ${GD_LINK_LIBS})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate thatcode is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()