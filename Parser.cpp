//
// Created by koncord on 20.01.19.
//

#include <iostream>
#include <regex>

#include "Parser.hpp"
#include "Utils.hpp"

Parser::Parser(const char *inputFile,
           const char *ns,
           const char *module,
           const std::vector<const char *> &clangArgs) : file(inputFile), module(module), ns(ns)
{
    index = clang_createIndex(0, 0);

    unit = clang_parseTranslationUnit(
        index,
        inputFile,
        clangArgs.data(), clangArgs.size(),
        nullptr, 0,
        CXTranslationUnit_None);
    if (unit == nullptr)
    {
        std::cerr << "Unable to parse translation unit. Quitting." << std::endl;
        exit(-1);
    }

    CXCursor cursor = clang_getTranslationUnitCursor(unit);
    clang_visitChildren(
        cursor,
        [](CXCursor c, CXCursor parent, CXClientData data)
        {
            CXSourceLocation loc = clang_getCursorLocation(c);
            if (clang_Location_isInSystemHeader(loc) != 0) // skip system headers
                return CXChildVisit_Continue;

            // since clang-c/Index.h is a C API we cannot capture anything in lambda.
            // Thankfully we can move any pointer in to last argument of clang_visitChildren
            Parser *_this = (Parser *) data;

            // Store all typedefs in to list, later we can use it to explicitly identify types in declarations
            if (c.kind == CXCursor_TypedefDecl)
            {
                CXCursor typeDefCursor = clang_getCursorReferenced(c);
                CXType type = clang_getTypedefDeclUnderlyingType(typeDefCursor);
                std::string typeName = GetCXXString(clang_getCursorDisplayName(c));
                _this->typedefs.emplace(typeName, type);
                return CXChildVisit_Continue;
            }
            else if (c.kind == CXCursor_FunctionDecl)
            {
                CDeclTokens token;
                token.retType = clang_getCursorResultType(c);
                token.declName = GetCXXString(clang_getCursorSpelling(c));

                auto comment = GetCXXString(clang_Cursor_getRawCommentText(c));
                if(!comment.empty())
                    _this->docstrings.emplace(token.declName, comment);

                for (unsigned i = 0; i < clang_Cursor_getNumArguments(c); ++i)
                {
                    CXCursor argumentCursor = clang_Cursor_getArgument(c, i);
                    if (argumentCursor.kind == CXCursor_ParmDecl)
                    {
                        CXType type = clang_getCursorType(argumentCursor);
                        std::string name = GetCXXString(clang_getCursorDisplayName(argumentCursor));
                        // Mark current type as used typedef
                        if (type.kind == CXType_Typedef)
                            _this->defsInUse.emplace(GetCXXString(clang_getTypeSpelling(type)));
                        token.args.emplace_back(type, name);
                    }
                    else
                    {
                        std::cerr << "Cursor '" << clang_getCursorSpelling(argumentCursor) << "' of kind '"
                                  << clang_getCursorKindSpelling(argumentCursor.kind) << "'\n";
                    }
                }
                _this->tokens.push_back(token);
                return CXChildVisit_Continue;
            }
            else if (c.kind >= CXCursor_FirstDecl && c.kind <= CXCursor_LastDecl)
            {
                CXFile file;
                unsigned line, column, offset;
                clang_getExpansionLocation(loc, &file, &line, &column, &offset);
                std::cerr << clang_getFileName(file) << ":" << line << ":" << column << ": warning: "
                          << "Unsupported declaration kind '" << clang_getCursorKindSpelling(c.kind) << "'\n";
            }
            return CXChildVisit_Recurse;
        },
        this
    );
}

Parser::~Parser()
{
    clang_disposeTranslationUnit(unit);
    clang_disposeIndex(index);
}

CXType Parser::GetTypeDef(const std::string &typeName) const
{
    auto it = typedefs.find(typeName);
    if (it == typedefs.end())
        throw std::runtime_error("Unknown type: " + typeName);
    return it->second;
}
