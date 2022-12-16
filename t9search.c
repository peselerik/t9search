/*  Projekt 1 - T9search 
---------------------------
    Erik Pesel
    xpesel00
    rijen 2022
---------------------------
    Beh programu:
    1. Nacte do struktury "cotnactList_t list" jmeno a cislo kontaktu
    2. Preformatuje kazde pismenko ze jmena na odpovidajici cislo
    3. Tato cisla ulozi do "cotnactList_t numList" misto jmena; tel. cislo zustava stejne
    4. Porovnava argument argv[1] s kazdym jmenem a kazdym cislem
    5. Vypise vyhovujici kontakty
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct contactList_t
{
    struct contact_t
    {
        char name[100];
        char number[100];
    } contact;
};

struct t9map_t
{
    char map[10][5];
};

void structLoad(struct contactList_t *list, int * rows);
void numLoad(struct contactList_t *list, struct contactList_t *numList, int rows);
void find(struct contactList_t *numList, char *needle, struct contactList_t *list, int rows);

int main(int argc, char **argv)
{
    struct contactList_t list[20]; //podporuje 20 kontaktu
    struct contactList_t numList[20];
    int rows = 0;

    structLoad(list, &rows);
    numLoad(list, numList, rows);

    if(argc < 2)
    {
        for(int i = 0; i < rows; i++)
        {
            fprintf(stdout, "%s, %s\n", list[i].contact.name, list[i].contact.number);
        }
        return 0;
    }

    if(argc > 2)
    {
        printf("Prilis mnoho argumentu\n");
        return 1;
    }

    find(numList, argv[1], list, rows);

    return 0;
}

/// @brief Nacte do struktury jmeno a cislo kontaktu
void structLoad(struct contactList_t *list, int * rows)
{
    char c = '1';
    int listCount = 0, nameCount = 0, numCount = 0, alt = 0;

    while(c != EOF)
    {
        c = getchar();

        // osetri maximalni delku radku
        if(nameCount >= 100 || numCount >= 100)
        {
            fprintf(stderr, "Prekrocena maximalni delka radku\n");
            return;
        }

        if(c == 10) // '/n'
        {
            alt++;
            nameCount = 0;
            numCount = 0;

            if(alt%2 == 0)
            {
                listCount++;
            }
        }
        else if(alt%2 == 0)  // osetruje co je jmeno a co cislo
        {
            list[listCount].contact.name[nameCount] = c;
            nameCount++;
        }
        else if(c < 0){} // nechtene znaky
        else
        {
            list[listCount].contact.number[numCount] = c;
            numCount++;
        }
    }

    *rows = (alt+1)/2;
}

/// @brief Funkce premenuje znaky ve jmene na cisla podle zadani
void numLoad(struct contactList_t *list, struct contactList_t *numList, int rows)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            if((list[i].contact.name[j] >= 65 && list[i].contact.name[j] <= 67) || (list[i].contact.name[j] >= 97 && list[i].contact.name[j] <= 99))
            {
                numList[i].contact.name[j] = '2';
            }
            else if((list[i].contact.name[j] >= 68 && list[i].contact.name[j] <= 70) || (list[i].contact.name[j] >= 100 && list[i].contact.name[j] <= 102))
            {
                numList[i].contact.name[j] = '3';
            }
            else if((list[i].contact.name[j] >= 71 && list[i].contact.name[j] <= 73) || (list[i].contact.name[j] >= 103 && list[i].contact.name[j] <= 105))
            {
                numList[i].contact.name[j] = '4';
            }
            else if((list[i].contact.name[j] >= 74 && list[i].contact.name[j] <= 76) || (list[i].contact.name[j] >= 106 && list[i].contact.name[j] <= 108))
            {
                numList[i].contact.name[j] = '5';
            }
            else if((list[i].contact.name[j] >= 77 && list[i].contact.name[j] <= 79) || (list[i].contact.name[j] >= 109 && list[i].contact.name[j] <= 111))
            {
                numList[i].contact.name[j] = '6';
            }
            else if((list[i].contact.name[j] >= 80 && list[i].contact.name[j] <= 83) || (list[i].contact.name[j] >= 112 && list[i].contact.name[j] <= 115))
            {
                numList[i].contact.name[j] = '7';
            }
            else if((list[i].contact.name[j] >= 84 && list[i].contact.name[j] <= 86) || (list[i].contact.name[j] >= 116 && list[i].contact.name[j] <= 118))
            {
                numList[i].contact.name[j] = '8';
            }
            else if((list[i].contact.name[j] >= 87 && list[i].contact.name[j] <= 90) || (list[i].contact.name[j] >= 119 && list[i].contact.name[j] <= 122))
            {
                numList[i].contact.name[j] = '9';
            }
            else if(list[i].contact.name[j] == 32)
            {
                numList[i].contact.name[j] = 32;
            }
            else{}

            if(list[i].contact.number[j] == 43)
            {
                numList[i].contact.number[j] = '1';
            }
            else
            {
                numList[i].contact.number[j] = list[i].contact.number[j];
            }
        }
    }
}

/// @brief hleda v seznamu prislusny kontakt
void find(struct contactList_t *numList, char *needle, struct contactList_t *list, int rows)
{
    char * haystackName = NULL;
    char * haystackNumber = NULL;
    int found = 0;

    for(int i = 0; i < rows; i++)
    {
        haystackName = numList[i].contact.name;
        haystackNumber = numList[i].contact.number;

        if((strstr(haystackName, needle) != NULL) || strstr(haystackNumber,needle) != NULL)
        {
            found = 1;
            fprintf(stdout, "%s, %s\n", list[i].contact.name, list[i].contact.number);
        }
    }

    if(found == 0)
        fprintf(stderr, "Not found\n");
}