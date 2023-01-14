/*
 *  light_object.c
 *  core definitions for the light object model
 * 
 *  authored by Alex Fulton
 *  created january 2023
 * 
 */

#include "light_util.h"

#include <stdio.h>
#include <string.h>

static uint8_t log_buffer[LIGHT_LOG_BUFFER_SIZE];

void light_util_init()
{

}
const uint8_t *light_log_level_to_string(uint8_t level)
{
        switch (level) {
        case LOG_TRACE:
                return "TRACE";
        case LOG_DEBUG:
                return "DEBUG";
        case LOG_INFO:
                return "INFO";
        case LOG_WARN:
                return "WARNING";
        case LOG_ERROR:
                return "ERROR";
        }
}

void light_log_internal(const uint8_t level, const uint8_t *format, ...)
{
        snprintf(log_buffer, LIGHT_LOG_BUFFER_SIZE, "[%7s]: ", light_log_level_to_string(level));
        printf(log_buffer);

        va_list args;
        va_start(args, format);
        vsnprintf(log_buffer, LIGHT_LOG_BUFFER_SIZE, format, args);
        va_end(args);
        printf(log_buffer);
        putc('\n', stdout);
}