# TicTacToe

### Descriere

- X si O pe matrice de dimensiuni variate (ex: 3x3, 5x5, 7x7), maximul este 9.
- Pentru dimeniunea 3, se pastreaza regulile clasice.
- Pentru dimensiuni mai mari, se aplica regula de la Connect 4 pentru a adauga complexitate (se castiga daca se formeaza o linie de lungime 4).
- Se poate alege intre CvC (Computer vs Computer), PvC/PvE (Player vs Computer/Environment) si PvP (Player vs Player).
- La PvE, se poate alege dificultatea AI-ului (Easy, Hard, Impossible).
- La CvC, dificultatile sunt alese random.
- Cele 3 dificultati au fost implementate folosind Minimax cu Alpha-Beta Pruning.
- Pe Easy, AI-ul alege intotdeauna una din cele mai slabe mutari posibile (i. e. Minimax score = -10).
- Pe Hard, AI-ul are un stil balansat, stiind sa faca mutarea castigatoare sau sa blocheze mutarea castigatoare a adversarului, in rest alegand una dintre mutarile care duc catre remiza sau uneori catre pierdere (i.e. Minimax score = 0 sau 75% sansa Minimax score = -10).
- Pe Impossible, AI-ul alege intotdeauna una din cele mai bune mutari posibile (i. e. Minimax score = 10).

|  Size | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| ----- | - | - | - | - | - | - | - |
| Depth | 9 | 8 | 6 | 5 | 4 | 4 | 4 |

## Tema 0

- [x] Nume proiect (poate fi schimbat ulterior)
- [x] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [x] definirea a minim 3-4 clase folosind compunere
- [x] constructori de inițializare
- [x] pentru o clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [x] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [x] cât mai multe `const` (unde este cazul)
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese
- [x] scenariu de utilizare a claselor definite:
  - crearea de obiecte și apelarea funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` exemple de date de intrare de la tastatură (dacă există)
- [x] tag de `git`: de exemplu `v0.1`
- [x] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Tema 2

#### Cerințe
- [x] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [x] moșteniri
  - [x] clasă cu atribut de tip pointer la o clasă de bază cu derivate
  - [x] funcții virtuale (pure) apelate prin pointeri de bază din clasa de mai sus, constructori virtuali (clone)
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
  - [x] apelarea constructorului din clasa de bază din constructori din derivate
  - [x] smart pointers
  - [x] `dynamic_cast`
- [x] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
- [x] excepții
  - [x] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim 2 clase pentru erori specifice
  - [x] utilizare cu sens: de exemplu, `throw` în constructor, `try`/`catch` în `main`
- [x] funcții și atribute `static`
- [x] STL
- [x] cât mai multe `const`
- [x] la sfârșit: commit separat cu adăugarea unei noi derivate fără a modifica restul codului : [6f94cf0](https://github.com/Andrei137/Tic-Tac-Toe/commit/77c9c2e2e686bd244d37e7f3958e0195d34f5d1e)
- [x] tag de `git`: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [x] 2 șabloane de proiectare (design patterns)
     - Singleton: Heart, Interface, Minimax, Scoreboard
     - Factory: AIFactory
     - Strategy: baza Difficulty cu derivatele Easy, Hard, Impossible; clasa Player are un atribut de tip Difficulty
- [x] o funcție șablon (template) cu sens; minim 2 instanțieri
     - Functia start_game din Interface, instantierile se fac in play_tictactoe
     - Permite schimbarea size-ului in timp real
- [x] o clasă șablon cu sens; minim 2 instanțieri
     - Clasa Game, instantierile se fac in Interface
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [x] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Compilare
##### Windows
```bash
build.bat
```

##### Linux
```bash
./build.sh
```

## Rulare
##### Windows
```bash
cd bin
TicTacToe.exe
```

##### Linux
```bash
cd bin
./TicTacToe
```

## Resurse

- [Heart Model](https://github.com/liuyubobobo/heart-curve-cplusplus)
- [Rlutil](https://github.com/tapio/rlutil)
- [Tabulate](https://github.com/p-ranav/tabulate)
- [TicTacToe Logo](https://github.com/umutambyi-gad/Tic-Tac-Toe)
