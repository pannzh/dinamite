LLVM_SOURCE=/home/pan/project/LLVM/llvm-src/llvm-3.5.0.src
LLVM_BUILD=/home/pan/project/LLVM/llvm-src/llvm-3.5.0.build
DIN_ROOT=/home/pan/project/LLVM/llvm-pass/dinamite

DIN_BUILD=$DIN_ROOT/build
DIN_CC="clang -g -Xclang -load -Xclang $DIN_BUILD/pass/libAccessInstrument.so"
DIN_CXX="clang++ -g -Xclang -load -Xclang $DIN_BUILD/pass/libAccessInstrument.so"
DIN_LDFLAGS="-L$DIN_ROOT/library -linstrumentation -lpthread"
export INST_LIB=$DIN_ROOT/library
export DIN_MAPS=maps
#export DIN_FILTERS=$DIN_ROOT/function_filter.json
#export ALLOC_IN=$DIN_ROOT/alloc.in

PATH=$LLVM_BUILD/bin:$PATH
LD_LIBRARY_PATH=$INST_LIB
PS1="(dinamite)$PS1"
