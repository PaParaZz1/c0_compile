chmod +x ./compile_test
./compile_test ./test/test_source_code.cpp > ans.txt 2>err.txt
cp mips.asm mips1.asm
