Simulation of flying drones on Mars in gnuplot
-

**Build**: 
```
mkdir build
cmake -S . -B build
cmake --build build -t Executable
```

**run**: `./build/Executable` 

**example**: 
```
./build/Executable
c
Twoj wybor? (m - menu): u
Podaj numer elementu: 5

Twoj wybor? (m - menu): d
Podaj numer typu elementu: 3
Podaj wymiary elementu wzgledem kolejnych osi OX,OY,OZ: 100 40 30
Podaj wspolrzedne srodka podstawy(x,y): 100 -105
Podaj kat obrotu figury wzgledem osi OZ: 45

Twoj wybor? (m - menu): a
Wprowadz numer aktywnego drona: 2

Twoj wybor? (m - menu): p
Podaj kierunek lotu (kat w stopniach): 180
Podaj dlugosc lotu: 50

Twoj wybor? (m - menu): k
```

Ten program mozna uruchomic tylko w srodowisku sytemu Linux lub Unix.
Wymaga wczesniejszej instalacji programu gnuplot.
Program gnuplot dostepny jest w standardowych pakietach kazdej
dystrybucji Linuksa.
