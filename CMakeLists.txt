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
        set(LIGHT_RUN_MODE PRODUCTION PARENT_SCOPE)
else()
        message("LIGHT_RUN_MODE is set to ${LIGHT_RUN_MODE}")
endif()

# system defaults to bare-metal
if(NOT DEFINED LIGHT_SYSTEM)
        message("LIGHT_SYSTEM not set, defaulting to NONE")
        set(LIGHT_SYSTEM NONE PARENT_SCOPE)
else()
        message("LIGHT_SYSTEM is set to ${LIGHT_SYSTEM}")
endif()

# platform defaults to on-device
if(NOT DEFINED LIGHT_PLATFORM)
        message("LIGHT_PLATFORM not set, defaulting to TARGET")
        set(LIGHT_PLATFORM TARGET PARENT_SCOPE)
else()
        message("LIGHT_PLATFORM is set to ${LIGHT_PLATFORM}")
endif()

if(LIGHT_SYSTEM EQUAL PICO_SDK)
        include(pico_sdk_import.cmake)

        if(LIGHT_PLATFORM EQUAL TARGET)
                set(PICO_PLATFORM rp2040 PARENT_SCOPE)
        elseif(LIGHT_PLATFORM EQUAL HOST)
                set(PICO_PLATFORM host PARENT_SCOPE)
        endif()
        
        pico_sdk_init()
        
        # pico_platform must be linked to correctly define PICO_RP2040 in on-device builds
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
