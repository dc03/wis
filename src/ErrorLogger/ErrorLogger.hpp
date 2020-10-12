#pragma once

/* See LICENSE at project root for license details */

#ifndef ERROR_LOGGER_HPP
#  define ERROR_LOGGER_HPP

#include <string_view>

#include "../Token.hpp"

struct ErrorLogger {
    bool had_error{false};
    bool had_runtime_error{false};
    std::string_view source{};
    void set_source(std::string_view file_source);
};

extern ErrorLogger logger;

void warning(std::string_view message, const Token &where);
void error(std::string_view message, const Token &where);
void runtime_error(std::string_view message, const Token &where);
void note(std::string_view message);

#endif