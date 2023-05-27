cmake_minimum_required(VERSION 3.12)

project(light_common C CXX ASM)

add_subdirectory(demo)

add_library(light_common INTERFACE)

target_include_directories(
        light_common
        INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(
        light_common
        INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src/light_common.c
        ${CMAKE_CURRENT_LIST_DIR}/src/list.c
)

# mode defaults to production
if(NOT DEFINED LIGHT_RUN_MODE)
        message("LIGHT_RUN_MODE not set, defaulting to PRODUCTION")
        set(LIGHT_RUN_MODE PRODUCTION)
else()
        message("LIGHT_RUN_MODE is set to ${LIGHT_RUN_MODE}")
endif()

# system defaults to bare-metal
if(NOT DEFINED LIGHT_SYSTEM)
        message("LIGHT_SYSTEM not set, defaulting to NONE")
        set(LIGHT_SYSTEM NONE)
else()
        message("LIGHT_SYSTEM is set to ${LIGHT_SYSTEM}")
endif()

# platform defaults to on-device
if(NOT DEFINED LIGHT_PLATFORM)
        message("LIGHT_PLATFORM not set, defaulting to TARGET")
        set(LIGHT_PLATFORM TARGET)
else()
        message("LIGHT_PLATFORM is set to ${LIGHT_PLATFORM}")
endif()

set(LIGHT_RUN_MODE ${LIGHT_RUN_MODE} PARENT_SCOPE)
set(LIGHT_SYSTEM ${LIGHT_SYSTEM} PARENT_SCOPE)
set(LIGHT_PLATFORM ${LIGHT_PLATFORM} PARENT_SCOPE)

if(LIGHT_SYSTEM STREQUAL PICO_SDK)
        message("Loading pico-sdk support")

        if(LIGHT_PLATFORM STREQUAL TARGET)
                set(PICO_PLATFORM rp2040)
        elseif(LIGHT_PLATFORM STREQUAL HOST)
                set(PICO_PLATFORM host)
        endif()

        set(PICO_PLATFORM ${PICO_PLATFORM} PARENT_SCOPE)
        
        include(pico_sdk_import.cmake)
        pico_sdk_init()
        
        target_link_libraries(
                light_common
                INTERFACE
                pico_platform
        )
endif()

target_compile_definitions(
        light_common INTERFACE
        RUN_MODE=${LIGHT_RUN_MODE}
        SYSTEM=${LIGHT_SYSTEM}
        PLATFORM=${LIGHT_PLATFORM}
)
if(DEFINED COMPILE_LOG_LEVEL)
        message("COMPILE_LOG_LEVEL is set to ${COMPILE_LOG_LEVEL}")
        target_compile_definitions(
                light_common
                INTERFACE
                FILTER_LOG_LEVEL=${COMPILE_LOG_LEVEL}
        )
endif()

if(DEFINED LIGHT_API_TRACE)
        target_compile_definitions(
                light_common
                INTERFACE
                LIGHT_API_TRACE
        )
endif()
