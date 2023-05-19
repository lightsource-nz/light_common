add_executable(light_common_demo)

target_sources(light_common_demo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/main.c)

target_link_libraries(
        light_common_demo PUBLIC
        light_common
)
if(LIGHT_SYSTEM EQUAL PICO_SDK)
        if(NOT PICO_NO_HARDWARE)
                pico_enable_stdio_semihosting(light_common_demo 1)
                target_link_libraries(light_common_demo PUBLIC pico_stdlib)
        endif()
        pico_add_extra_outputs(light_common_demo)
endif()
