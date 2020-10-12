#pragma once

/* See LICENSE at project root for license details */

#ifndef AST_TYPES_HPP
#  define AST_TYPES_HPP

#include <memory>
#include <string>
#include <variant>

#include "../Token.hpp"

enum class Type {
    BOOL,
    INT,
    FLOAT,
    STRING,
    CLASS,
    LIST,
    TYPEOF,
    NULL_
};

struct Expr;
struct BaseType;
struct ClassStmt
struct FunctionStmt;

using QualifiedTypeInfo = BaseType*;

struct ExprTypeInfo {
    QualifiedTypeInfo info{nullptr};
    FunctionStmt *func{nullptr};
    ClassStmt *class_{nullptr};
    Token lexeme{};

    ExprTypeInfo(QualifiedTypeInfo info, Token token);
    ExprTypeInfo(FunctionStmt *func, Token token);
    ExprTypeInfo(ClassStmt *class_, Token token);
};

struct LiteralValue {
    enum {
        INT,
        DOUBLE,
        STRING,
        BOOL,
        NULL_
    };
    std::variant<int, double, std::string, bool, std::nullptr_t> value;

    LiteralValue(int value);
    LiteralValue(double value);
    LiteralValue(std::string value);
    LiteralValue(bool value);
    LiteralValue(std::nullptr_t);
};

using StmtVisitorType = void;
using ExprVisitorType = ExprTypeInfo;
using BaseTypeVisitorType = QualifiedTypeInfo;

#endif