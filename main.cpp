#include <iostream>
#include <fstream>
#include "Parser.hpp"
#include "ToMono.hpp"
#include "ToLua.hpp"
#include "Version.hpp"

std::string GetFileName(std::string file)
{
    file.erase(0, file.find_last_of("/\\") + 1);
    auto pos = file.rfind('.');
    if (pos != std::string::npos)
        file.erase(pos);
    return std::move(file);
}

int main(int argc, char **argv)
{
    if (argc < 5)
    {
        std::cout << argv[0] << " inputFile outFile nameSpace moduleName [clang options...]\n"
                  << "genffi, version " << GENFFI_MAJOR << "." << GENFFI_MINOR << "." << GENFFI_PATCH << std::endl
                  << "Copyright (C) 2019 TES3MP Team\n"
                  << "This is free software; see the source for copying conditions.  There is NO\n"
                  << "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE." << std::endl;
        return 1;
    }

    const char *inputFile = argv[1];
    std::string outFile = argv[2];
    const char *nameSpace = argv[3];
    const char *module = argv[4];
    std::string version = "-D__GENFFI_VERSION=" + std::to_string(GENFFI_VERSION);
    std::vector<const char *> args{
        "-D__genffi__",
        version.c_str()
    };

    if (!std::ifstream(inputFile).is_open())
    {
        std::cerr << inputFile << " not found." << std::endl;
        return 1;
    }

    if (argc > 5)
    {
        args.reserve(argc - 5);
        for (int i = 0; i < argc - 5; ++i)
            args.push_back(argv[i + 5]);
    }

    Parser parser(inputFile, nameSpace, module, args);
    std::ofstream out(outFile);

    std::string ext = outFile.substr(outFile.find_last_of('.') + 1);
    if (ext == "lua")
        out << ToLua(parser);
    else if (ext == "cs")
        out << ToMono(parser);
    else
    {
        std::cerr << "Unknown output format '" << ext << "\'." << std::endl;
        return 1;
    }

    return 0;
}
