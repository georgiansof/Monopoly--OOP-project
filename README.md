# MonOOPoly

Description:
  Bucharest Monopoly virtual replica with various changes.

  [Images](https://imgur.com/a/K7AwzwU)

<details>
  <summary>Images spoiler ( press here )</summary>

  <image src="https://imgur.com/heMeBIE.png"/> <br> -------------------------------------- <br>
  <image src="https://imgur.com/W29DvYZ.png"/> <br> -------------------------------------- <br>
  <image src="https://imgur.com/crdTDRw.png"/> <br> -------------------------------------- <br>
  <image src="https://imgur.com/QwCLu7z.png"/> <br> -------------------------------------- <br>
  <image src="https://imgur.com/pcYdf5C.png"/> <br> -------------------------------------- <br>
  <image src="https://imgur.com/S3RLILB.png"/> <br> -------------------------------------- <br>
  <image src="https://imgur.com/KS1wLGy.png"/> <br> -------------------------------------- <br>
  <image src="https://imgur.com/Oj9XAIX.png"/> <br> -------------------------------------- <br>

</details>

  
  BoardTile class hierarchy tree:

           -----------   BoardTile  ------------------
          /           /       |       \                \
         /           /        |        \                \
       Jail     Property   TaxTile   ParkTile          Chance
                  / | \             (GoToJail?)   (Chest or Surprise)
                 /  |  \                
                /   |   \            
               /    |    \
              /     |     \
    Neighborhood  Factory  TrainStation

### Tema 0

- [x] Nume proiect (poate fi schimbat ulterior)
- [x] Scurtă descriere a temei alese, ce v-ați propus să implementați

## Tema 1

#### Cerințe
- [x] definirea a minim **3-4 clase** folosind compunere
- [x] constructori de inițializare
- [x] pentru o clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [x] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [x] cât mai multe `const` (unde este cazul)
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese
- [x] scenariu de utilizare a claselor definite:
  - crearea de obiecte și apelarea tuturor funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` exemple de date de intrare de la tastatură (dacă există)
- [x] tag de `git`: de exemplu `v0.1`
- [x] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Tema 2

#### Cerințe
- [x] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [x] moșteniri:
  - minim o clasă de bază și **3 clase derivate**
  - ierarhia trebuie să fie cu bază proprie, nu derivată dintr-o clasă predefinită
  - [x] clasă cu atribut de tip pointer la o clasă de bază cu derivate (ChanceTile, Board - contin vectori de pointeri la clase de baza cu derivate)
  - [x] funcții virtuale (pure) apelate prin pointeri de bază din clasa care conține atributul de tip pointer de bază (ChanceCard::action())
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
    - constructori virtuali (clone): sunt necesari, dar nu se consideră funcții specifice temei
  - [x] apelarea constructorului din clasa de bază din constructori din derivate
  - [ ] smart pointers (recomandat, opțional)
  - [x] `dynamic_cast`/`std::dynamic_pointer_cast` pentru downcast cu sens (downcast exceptii resMan/SceneMan)
- [x] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap (clasa Player)
- [x] excepții
  - [x] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim 2 clase pentru erori specifice
  - [x] utilizare cu sens: de exemplu, `throw` în constructor, `try`/`catch` în `main`
- [x] funcții și atribute `static`
- [x] STL
- [x] cât mai multe `const`
- [x] la sfârșit: commit separat cu adăugarea unei noi clase derivate fără a modifica restul codului, pe lângă cele 3 derivate deja adăugate
  - noua derivată nu poate fi una existentă care a fost ștearsă și adăugată din nou
- [x] tag de `git`: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [x] 2 șabloane de proiectare (design patterns) *FACADE(Connection)* *Proxy(CircularList)* *iterator(CircularList/circular iterator)* *Observer(threaded network listening)*  
- [x] o clasă șablon cu sens; minim **2 instanțieri**  -> CircularList(Game::playersList, ChanceTile cards)
  - [x] preferabil și o funcție șablon (template) cu sens; minim 2 instanțieri -> Player::getTilesOfOwnedType
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [x] tag de `git`: de exemplu `v0.3` sau `v1.0`

## Resurse

- [SFML](https://github.com/SFML/SFML/tree/2.6.0) (Zlib)
- adăugați trimiteri către resursele externe care v-au ajutat sau pe care le-ați folosit -> used websites.txt
