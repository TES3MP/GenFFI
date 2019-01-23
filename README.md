GenFFI
======

GenFFI - is an FFI generator that takes the C Headers and converts them to the target language.

Supported languages:
* Lua
* Mono

Usage:
```
genffi inputFile outFile nameSpace moduleName [clang options...]
```

Example of usage:
```
genffi test/Functions/Server.h Server.lua tes3mpApi tes3mp
```

Builtin macros:
* ``__genffi__`` - can be used to detect genffi
* ``__GENFFI_VERSION`` - current version of the genffi (10000 for example)