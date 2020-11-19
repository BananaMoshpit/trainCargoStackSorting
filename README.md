# ed
A stack sorting cargo system written in c
refurbsihed from the final project for the Data Structure(2019/2) course at Universidade de Brasília.

There's a PDF explaining the system functionality (Trabalho_ED.pdf)

to run it with gcc in a terminal, execute the command:
gcc ED.c TRENS.a


As it is, the system won't fully load cargo because it assumes the max possible load'll be finished by the first exceding cargo in a sorted array instead of checking wether it may load successive smaller loads, wich will soon be fixed.
