//
// Created by koncord on 20.01.19.
//

#include <sstream>
#include <iostream>
#include "Parser.hpp"
#include "Utils.hpp"
#include "ToMono.hpp"

static std::string CTypeToMono(const Parser &data, CXType type)
{
    switch(type.kind)
    {
        case CXType_Void:
            return "void";
        case CXType_Bool:
            return "bool";
        case CXType_Char_U:
        case CXType_UChar:
            return "byte";
        case CXType_Char_S:
        case CXType_SChar:
            return "sbyte";
        case CXType_Short:
            return "short";
        case CXType_UShort:
            return "ushort";
        case CXType_Int:
            return "int";
        case CXType_UInt:
            return "uint";
        case CXType_Long:
            return "long";
        case CXType_ULong:
            return "ulong";
        case CXType_Float:
            return "float";
        case CXType_Double:
            return "double";
        case CXType_Pointer:
        {
            CXType popinteeType = clang_getPointeeType(type);
            //bool isConst = clang_isConstQualifiedType(popinteeType);
            if(popinteeType.kind == CXType_Char_S || popinteeType.kind == CXType_SChar)
                return "string";
        }
        case CXType_Typedef: // todo: not the best way.
        {
            std::string typeName = GetCXXString(clang_getTypeSpelling(type));
            if(typeName == "bool") // since headers written on C, and bool type defined in C as uint_8, we need special handler for it
                return "bool";
            return CTypeToMono(data, data.GetTypeDef(typeName));
        }
        default:
            return "object";
    }
}

std::ostream &ToMono::Serialize(std::ostream &out) const
{
    out << "﻿using System.Runtime.InteropServices;\n\n"
        << "namespace " << parser.GetNamespace() << "\n{\n"
        << "    public static partial class " << parser.GetModule() << "\n    {\n";

    for (const auto &decl : parser.GetTokens())
    {
        std::stringstream ss;
        std::string retType = CTypeToMono(parser, decl.retType);
        bool haveStrings = retType == "string";
        ss << "public static extern " << retType << " " << decl.declName << "(";

        const auto endIt = decl.args.end();
        for (auto it = decl.args.begin(); it != endIt; ++it)
        {
            std::string type = CTypeToMono(parser, it->type);
            if (!haveStrings)
                haveStrings = type == "string";
            ss << type << " " << it->name;
            if (std::next(it) != endIt)
                ss << ", ";
        }
        ss << ");\n\n";

        if (haveStrings)
            out << "        [DllImport(\"__Internal\", CharSet = CharSet.Ansi)]\n";
        else
            out << "        [DllImport(\"__Internal\"]\n";
        out << "        " << ss.str();
    }
    out << "    }\n}";
    return out;
}
