# TicTacToe

### Descriere

- X si O pe matrice de dimensiuni variate (ex: 3x3, 5x5, 7x7).
- Pentru dimeniunea 3, se pastreaza regulile clasice.
- Pentru dimensiuni mai mari, se aplica regula de la Connect 4 pentru a adauga complexitate (se castiga daca se formeaza o linie de lungime 4).
- Se poate juca intre 2 jucatori sau impotriva unui AI.
- Se poate alege dificultatea AI-ului (Easy, Normal, Impossible).
- Pe Easy, AI-ul cauta pozitiile ocupate de adversar si incearca sa se plaseze pe pozitii libere din jurul lor, in ordinea sus, stanga, jos, dreapta. La prima mutare cu X se plaseaza in coltul stanga sus.
- Pe Normal, AI-ul stie sa impedice victoria adversarului si sa completeze o linie pentru a castiga, insa in rest alege random pozitiile.
- Pe Impossible, AI-ul alege intotdeauna cea mai buna mutare posibila, algoritmul din spate fiind Minimax cu Alpha-Beta Pruning.

|  Size | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| ----- | - | - | - | - | - | - | - | -: |
| Depth | 9 | 8 | 6 | 5 | 4 | 4 | 4 |  3 |



### Tema 0

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
- [ ] la sfârșit: commit separat cu adăugarea unei noi derivate fără a modifica restul codului
- [ ] tag de `git`: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [ ] 2 șabloane de proiectare (design patterns)
- [ ] o funcție șablon (template) cu sens; minim 2 instanțieri
- [ ] o clasă șablon cu sens; minim 2 instanțieri
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [ ] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Resurse

- [Heart Model](https://github.com/liuyubobobo/heart-curve-cplusplus)
- [Rlutil](https://github.com/tapio/rlutil)
- [Tabulate](https://github.com/p-ranav/tabulate)
- [TicTacToe Logo](https://github.com/umutambyi-gad/Tic-Tac-Toe)
