# trainCargoStackSorting
A stack sorting cargo system written in c <br>
refurbsihed from my final project for the Data Structure(2019/2) course at Universidade de Brasília.

It's a system to receive multiple packages and arrenge them in trains, weightier first by the firsts train cars. <br>
Input is an amount cars per train, maximum weight by car, and an amount of weights(each belonging to a package). <br>
Output an amount of trains, each with heavier cars first, each car carrying a stack of packages with the heaviest by the bottom(first in stack).<br> 
There's a PDF with a thorough explanation inside: [Trabalho_ED.pdf](https://github.com/BananaMoshpit/ed/blob/master/Trabalho_ED.pdf)

to run it with gcc in a terminal, execute the commands:<br>
gcc -o ED ED.c TRENS.a <br>
./ED


