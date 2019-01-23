#include <utility>

//
// Created by koncord on 20.01.19.
//

#pragma once

#include <clang-c/Index.h>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

struct TArg
{
    TArg() = default;
    TArg(CXType &type, std::string name): type(type), name(std::move(name)) {}
    CXType type{};
    std::string name;
};

struct CDeclTokens
{
    CXType retType;
    std::string declName;
    std::vector<TArg> args;
};

class Parser
{
private:
    friend class IConverter;
public:

    explicit Parser(const char *inputFile, const char *ns, const char *module, const std::vector<const char *> &clangArgs);
    ~Parser();

    CXType GetTypeDef(const std::string &typeName) const;
    std::string GetModule() const { return module; }
    std::string GetFullFilePath() const { return file; }
    std::string GetNamespace() const { return ns; }
    const std::vector<CDeclTokens> &GetTokens() const { return tokens; }
    const std::set<std::string> &GetDefinesInUse() const { return defsInUse; }
private:
    CXIndex index;
    CXTranslationUnit unit;

    std::vector<CDeclTokens> tokens;
    std::map<std::string, CXType> typedefs;
    std::set<std::string> defsInUse;
    std::map<std::string, std::string> docstrings;

    std::string module;
    std::string file;
    std::string ns;
};