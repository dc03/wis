#pragma once

/* Copyright (C) 2020  Dhruv Chawla */
/* See LICENSE at project root for license details */

#ifndef TYPE_RESOLVER_HPP
#define TYPE_RESOLVER_HPP

#include "../AST.hpp"
#include "../Module.hpp"

#include <string_view>
#include <unordered_map>
#include <vector>

class TypeResolver final : Visitor {
    struct Value {
        std::string_view lexeme{};
        QualifiedTypeInfo info{};
        std::size_t scope_depth{};
        ClassStmt *class_{nullptr};
    };

    Module &current_module;
    const std::unordered_map<std::string_view, ClassStmt *> &classes;
    const std::unordered_map<std::string_view, FunctionStmt *> &functions;
    std::vector<TypeNode> type_scratch_space{};
    std::vector<Value> values{};

    bool in_ctor{false};
    bool in_dtor{false};
    bool in_class{false};
    bool in_function{false};
    bool in_loop{false};
    bool in_switch{false};
    ClassStmt *current_class{nullptr};
    FunctionStmt *current_function{nullptr};
    std::size_t scope_depth{0};

    template <typename T, typename... Args>
    BaseType *make_new_type(Type type, bool is_const, bool is_ref, Args &&... args);
    ExprTypeInfo resolve_class_access(ExprVisitorType &object, const Token &name);
    ExprVisitorType check_inbuilt(VariableExpr *function, const Token &oper, std::vector<ExprNode> &args);
    ClassStmt *find_class(const std::string &class_name);
    FunctionStmt *find_function(const std::string &function_name);

  public:
    TypeResolver(Module &module);

    void check(std::vector<StmtNode> &program);
    void begin_scope();
    void end_scope();

    ExprVisitorType resolve(Expr *expr);
    StmtVisitorType resolve(Stmt *stmt);
    BaseTypeVisitorType resolve(BaseType *type);

    ExprVisitorType visit(AssignExpr &expr) override final;
    ExprVisitorType visit(BinaryExpr &expr) override final;
    ExprVisitorType visit(CallExpr &expr) override final;
    ExprVisitorType visit(CommaExpr &expr) override final;
    ExprVisitorType visit(GetExpr &expr) override final;
    ExprVisitorType visit(GroupingExpr &expr) override final;
    ExprVisitorType visit(IndexExpr &expr) override final;
    ExprVisitorType visit(LiteralExpr &expr) override final;
    ExprVisitorType visit(LogicalExpr &expr) override final;
    ExprVisitorType visit(ScopeAccessExpr &expr) override final;
    ExprVisitorType visit(ScopeNameExpr &expr) override final;
    ExprVisitorType visit(SetExpr &expr) override final;
    ExprVisitorType visit(SuperExpr &expr) override final;
    ExprVisitorType visit(TernaryExpr &expr) override final;
    ExprVisitorType visit(ThisExpr &expr) override final;
    ExprVisitorType visit(UnaryExpr &expr) override final;
    ExprVisitorType visit(VariableExpr &expr) override final;

    StmtVisitorType visit(BlockStmt &stmt) override final;
    StmtVisitorType visit(BreakStmt &stmt) override final;
    StmtVisitorType visit(ClassStmt &stmt) override final;
    StmtVisitorType visit(ContinueStmt &stmt) override final;
    StmtVisitorType visit(ExpressionStmt &stmt) override final;
    StmtVisitorType visit(FunctionStmt &stmt) override final;
    StmtVisitorType visit(IfStmt &stmt) override final;
    StmtVisitorType visit(ReturnStmt &stmt) override final;
    StmtVisitorType visit(SwitchStmt &stmt) override final;
    StmtVisitorType visit(TypeStmt &stmt) override final;
    StmtVisitorType visit(VarStmt &stmt) override final;
    StmtVisitorType visit(WhileStmt &stmt) override final;

    BaseTypeVisitorType visit(PrimitiveType &type) override final;
    BaseTypeVisitorType visit(UserDefinedType &type) override final;
    BaseTypeVisitorType visit(ListType &type) override final;
    BaseTypeVisitorType visit(TypeofType &type) override final;
};

#endif