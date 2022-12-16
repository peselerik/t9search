# t9search
T9search funguje podobne jako vyhledavac kontaktu z tlacitkovych telefonu. Zadany vyraz je vyhledavan pomoci prevedeni vsech pismen na odpovidajici cislo a nasledne porovnavan. Pokud se s nejakym (pripadne vice) kontaktem(y) shoduje, vypise jej na standardni vystup. Pokud neni zadan zadny argument, vypise cely seznam.

## Spousteni programu
./t9search [search for] <[text file]

### Priklady spusteni programu:
- ./t9search 778 <in.txt
- ./t9search <in.txt

## Beh programu
1. Nacte do struktury "cotnactList_t list" jmeno a cislo kontaktu
2. Preformatuje kazde pismenko ze jmena na odpovidajici cislo
3. Tato cisla ulozi do "cotnactList_t numList" misto jmena; tel. cislo zustava stejne
4. Porovnava argument argv[1] s kazdym jmenem a kazdym cislem
5. Vypise vyhovujici kontakty
