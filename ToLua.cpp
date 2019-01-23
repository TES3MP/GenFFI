//
// Created by koncord on 19.01.19.
//

#include "Parser.hpp"
#include "Utils.hpp"
#include "ToLua.hpp"

#include <regex>

static std::regex reFFIDefined(R"([u]?int[\d]+_t|bool|[u]?intptr_t|ptrdiff_t|size_t|wchar_t|va_list|__builtin_va_list|__gnuc_va_list)");

std::ostream &ToLua::Serialize(std::ostream &out) const
{
    out << "local ffi = require(\"ffi\")\n\nffi.cdef [[\n";
    const auto &defsInUse = parser.GetDefinesInUse();
    if (!defsInUse.empty())
    {
        for (const auto &tdefName : defsInUse)
        {
            if (std::regex_match(tdefName, reFFIDefined))
                continue;
            out << "    typedef ";
            out << clang_getTypeSpelling(parser.GetTypeDef(tdefName)) << " " << tdefName << ";\n";
        }
        out << "\n";
    }

    for (const auto &decl : parser.GetTokens())
    {
        out << "    " << clang_getTypeSpelling(decl.retType);
        if (decl.retType.kind != CXType_Pointer)
            out << " ";
        out << decl.declName << "(";
        auto endIt = decl.args.end();
        for (auto it = decl.args.begin(); it != endIt; ++it)
        {
            out << clang_getTypeSpelling(it->type);
            if (it->type.kind != CXType_Pointer)
                out << " ";
            out << it->name;
            if (std::next(it) != endIt)
                out << ", ";
        }
        out << ");\n";
    }

    out << "]]\n\n";
    out << "local M = {}\n";
    out << "M.C = ffi.C\n\n";

    for (const auto &decl : parser.GetTokens())
    {
//        if (const auto it = docstrings.find(decl.declName); it != docstrings.end())
//        {
//            std::string luaComment = it->second;
//            //luaComment.replace(luaComment.begin(), luaComment.end() -1 , "/**", "--!");
//            //luaComment.replace(luaComment.begin(), luaComment.end() , "*/", "--!");
//            luaComment.replace(luaComment.begin(), luaComment.end() , "*", "--!");
//            out << luaComment;
//        }

        std::string func = "M.";
        std::string args;
        auto endIt = decl.args.end();
        for (auto it = decl.args.begin(); it != endIt; ++it)
        {
            args += it->name;
            if (std::next(it) != endIt)
                args += ", ";
        }

        func += decl.declName;
        func += " = function(" + args + ")\n";
        std::string cfunc = "M.C.";
        cfunc += decl.declName;
        cfunc += "(" + args + ")";
        if (decl.retType.kind == CXType_Pointer)
        {
            CXType popinteeType = clang_getPointeeType(decl.retType);
            //bool isConst = clang_isConstQualifiedType(popinteeType);
            if (popinteeType.kind == CXType_Char_S || popinteeType.kind == CXType_SChar)
            {
                func += "    local result = " + cfunc + "\n";
                func += "    return ffi.string(result)\n";
            }
            else
            {
                throw std::runtime_error("Unsupported pointee return type: "
                                             + GetCXXString(clang_getTypeKindSpelling(popinteeType.kind)));
            }
        }
        else
        {
            func += "    ";
            if (decl.retType.kind != CXType_Void)
                func += "return ";
            func += cfunc + "\n";
        }
        func += "end\n";
        out << func << "\n";
    }
    out << "\nreturn M\n";
    return out;
}
