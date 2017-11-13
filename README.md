# DINAMITE LLVM Pass

Main release repo for DINAMITE's compiler pass.
For more info and a quickstart guide, go to https://dinamite-toolkit.github.io/

# build


## build pass (libAccessInstrument.so)

first set your `LLVM_DIR` path in CMakeLists.txt

```bash
mkdir build && cd build
cmake ..
make
```

## build runtime

first set your `LLVM_DIR` in bashrc and then
```
source bashrc
```

### build libinstrumentation.so

```
cd library
make hotarea
```

### build target

```bash
cd tests
mkdir maps
DIN_MAPS=maps $DIN_CC $DIN_LDFLAGS main.c -o a.out
```

# run

## run target

```
cd tests && ./a.out
```
This would generate `basic_block.trace` and `access.trace` file.
to analysis the trace file, we prepared a script in `utils/trace_parser.py`.
for example (assume we're in tests directory where we compiled the main.c previously):

1. to get per basic block access counts (to identify hot area):

```bash
../utils/trace_parser.py -a block -t basic_block.trace -m maps
```

outputs example:

```json
{
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:23 abc().return": 250, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:18 abc().if.then": 100, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:45 main().for.body": 50, 
    "n/a:-1 abc().entry": 250, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:46 main().for.cond1": 300, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:44 main().for.cond": 51, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:44 main().for.inc24": 50, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:46 main().for.inc": 250, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:47 main().for.body3": 250, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:20 abc().if.else": 150, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:65 main().for.end": 50, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:66 main().for.end26": 1
}
```

2. get value range of variables (for value profiling):

```
../utils/trace_parser.py -a value -t access.trace -m maps
```

output example:
```json
{
    "n/a:-1 main().retval": {
        "max": 0, 
        "w": 1, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:49 simplestruct.a": {
        "max": 4, 
        "w": 250, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:48 main().a": {
        "max": 500, 
        "r": 250, 
        "w": 250, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:51 simplestruct.a": {
        "max": 500, 
        "w": 250, 
        "min": 2
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:51 main().a": {
        "max": 500, 
        "r": 250, 
        "min": 2
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:37 main().a": {
        "max": 0, 
        "w": 1, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:49 main().i": {
        "max": 4, 
        "r": 250, 
        "min": 0
    }, 
    "n/a:-1 abc().i": {
        "max": 4, 
        "w": 250, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:44 main().j": {
        "max": 50, 
        "r": 101, 
        "w": 51, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:55 main().i": {
        "max": 4, 
        "r": 250, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:18 abc().retval": {
        "max": 4, 
        "w": 100, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:17 abc().i": {
        "max": 4, 
        "r": 250, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:38 s_compositestruct.e": {
        "max": 0.0, 
        "w": 1, 
        "min": 0.0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:54 simplestruct.a": {
        "max": 503, 
        "r": 250, 
        "w": 250, 
        "min": 4
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:60 s_compositestruct.e": {
        "max": 785.002441, 
        "r": 250, 
        "w": 250, 
        "min": 3.14
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:53 simplestruct.a": {
        "max": 502, 
        "r": 250, 
        "w": 250, 
        "min": 3
    }, 
    "n/a:-1 main().argc": {
        "max": 1, 
        "w": 1, 
        "min": 1
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:20 abc().retval": {
        "max": 1, 
        "w": 150, 
        "min": 1
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:40 anon.NA": {
        "max": 0, 
        "w": 1, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:55 simplestruct.b": {
        "max": 4, 
        "w": 250, 
        "min": 4
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:52 simplestruct.a": {
        "max": 501, 
        "r": 250, 
        "w": 250, 
        "min": 2
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:23 abc().retval": {
        "max": 4, 
        "r": 250, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:46 main().i": {
        "max": 5, 
        "r": 550, 
        "w": 300, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:61 s_compositestruct.c": {
        "max": 3, 
        "w": 250, 
        "min": 3
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:47 main().i": {
        "max": 4, 
        "r": 500, 
        "min": 0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:50 s_compositestruct.e": {
        "max": 785.002441, 
        "r": 250, 
        "w": 250, 
        "min": 0.0
    }, 
    "/home/pan/project/LLVM/llvm-pass/dinamite/tests/main.c:62 s_compositestruct.c": {
        "max": 4, 
        "r": 250, 
        "w": 250, 
        "min": 3
    }
}
```
