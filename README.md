# WordShuffler
Shuffles the inside of words, 
so first and last char are kept as they are and everything is randomly shuffled


Example given:
> ./shuffleInWords -t "This is a very wounderful - but short sentence."

Can result in
> This is a very wenfuurdol - but sroht scnetnee.


For infinity mode, just run the executable, write your sentence and receive it shuffled back.
Interrupt with Ctrl + C.


## Compilation
This is standard c++ without any dependencies, so I'd propose:
1. git clone https://github.com/VxGrid/WordShuffler.git
2. cd WordShuffler
3. mkdir build && cd build
4. cmake -DCMAKE_BUILD_TYPE=Release ../src/
5. cmake --build . --config Release
