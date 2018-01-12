make clean all;
export AFL_USE_ASAN=1; afl-fuzz -i ../input -o ../output -m none -- ./sint;

