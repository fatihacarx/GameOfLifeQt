/*
    Fatih (6251581), Javi (), Lesik (6081100), Kelvin Tsang (5428328)

    Milestone 1

*/
#include <iostream>
#include <cstdlib>
#include "CAbase.h"

using namespace std;

/*
 * Constructor – set
 */
CAbase::CAbase() {}
CAbase::CAbase(int x, int y) { worldWidth = x; worldHeight = y; createWorld(); populate_test(); }

/*
 * Empty deconstructor
 */
CAbase::~CAbase() {}

// gibt Position des Elementes im Array zurück
int CAbase::getIndexByCoord(int x, int y) {return x + worldHeight * y;}

void CAbase::createWorld()      // Erstellt leere Welt
{
    currentworld = new int[worldWidth * worldHeight];
    nextgenworld = new int[worldWidth * worldHeight];
    for (int x = 0; x < worldWidth; x++) {
        for (int y = 0; y < worldHeight; y++) {
                currentworld[getIndexByCoord(x, y)] = 0;
                nextgenworld[getIndexByCoord(x, y)] = 0;
        }
    }
}

void CAbase::populateRandomly()     // Fühlt die Welt mit Random lebenden Zellen
{
    for (int x = 0; x < worldWidth; x++) {
        for (int y = 0; y < worldHeight; y++) {
                currentworld[getIndexByCoord(x, y)] = rand() % 2;
        }
    }
}

void CAbase::populate_test()        // Testwelt
{
    for (int x = 0; x < worldWidth; x++) {
        for (int y = 0; y < worldHeight; y++) {
                currentworld[getIndexByCoord(x, y)] = 0;
        }
    }
    currentworld[getIndexByCoord(0, 0)] = 1;
    currentworld[getIndexByCoord(29, 29)] = 1;
    currentworld[getIndexByCoord(0, 3)] = 1;
    currentworld[getIndexByCoord(0, 4)] = 1;
    currentworld[getIndexByCoord(0, 5)] = 1;
    // blinker
    currentworld[getIndexByCoord(4, 4)] = 1;
    currentworld[getIndexByCoord(5, 4)] = 1;
    currentworld[getIndexByCoord(6, 4)] = 1;
    //rechteck
    currentworld[getIndexByCoord(12, 12)] = 1;
    currentworld[getIndexByCoord(12, 13)] = 1;
    currentworld[getIndexByCoord(13, 12)] = 1;
    currentworld[getIndexByCoord(13, 13)] = 1;
}

void CAbase::setSize(int x, int y) // Erstellt die Größe des Feldes
{
    worldWidth = x;
    worldHeight = y;
    currentworld = new int[x * y];
    nextgenworld = new int[x * y];
    for (int x = 0; x < worldWidth; x++) {
        for (int y = 0; y < worldHeight; y++) {
                currentworld[getIndexByCoord(x, y)] = 0;
                nextgenworld[getIndexByCoord(x, y)] = 0;
        }
    }
}

// Setzt wert auf Zelle (x,y)
void CAbase::setCell(int x, int y, int wert) {currentworld[x + worldHeight * y] = wert;}
void CAbase::setCell_next(int x, int y, int wert) {nextgenworld[x + worldHeight * y] = wert;}

// Definition der Getter
int CAbase::getCell(int x, int y) {return currentworld[x + worldHeight * y];}
int CAbase::getNx() {return worldWidth;}
int CAbase::getNy() {return worldHeight;}
int* CAbase::getCurrentWorld() {return currentworld;}
int* CAbase::getNextGenWorld() {return nextgenworld;}

int CAbase::nachbar(int x, int y) // Zählt die Anzahl der Nachbarn vom Feld (x,y)
{
    if (x == 0 && y == 0) {
        return (getCell(0, 1) + getCell(1, 1) + getCell(1, 0) + getCell(1, getNy() - 1)
                + getCell(0, getNy() - 1) + getCell(getNx() - 1, 0) + getCell(getNx() - 1, 1)
                + getCell(getNx() - 1, getNy() - 1));
    }
    //rechts oben
    else if (x == getNx() - 1 && y == 0) {
        return (getCell(x, 1) + getCell(x - 1, 1) + getCell(x - 1, 0) + getCell(x - 1, getNy() - 1)
                + getCell(x, getNy() - 1) + getCell(0, getNy() - 1) + getCell(0, 0) + getCell(0, 1));
    }
    //links unten
    else if (x == 0 && y == getNy() - 1) {
        return (getCell(0, y - 1) + getCell(1, y - 1) + getCell(1, y)
                + getCell(1, 0) + getCell(0, 0) + getCell(getNx() - 1, 0) + getCell(getNx() - 1, y)
                + getCell(getNx() - 1, y - 1));
    }
    //rechts unten
    else if (x == getNx() - 1 && y == getNy() - 1) {
        return (getCell(x, y - 1) + getCell(x - 1, y - 1) + getCell(x - 1, y) + getCell(x - 1, 0) + getCell(x, 0)
                + getCell(0, 0) + getCell(0, y) + getCell(0, y - 1));
    }
    //erste reihe
    else if (y == 0) {
        return (getCell(x - 1, 0) + getCell(x - 1,  1) + getCell(x, 1) + getCell(x + 1, 1)
               + getCell(x + 1, 0) + getCell(x - 1, getNy() - 1) + getCell(x, getNy() - 1) + getCell(x + 1, getNy() - 1));
    }
    //letzte reihe
    else if (y == getNy() - 1) {
        return (getCell(x - 1, y - 1) + getCell(x, y - 1) + getCell(x + 1, y - 1) + getCell(x - 1, y)
               + getCell(x + 1, y) + getCell(x - 1, 0) + getCell(x, 0) + getCell(x + 1, 0));
    }
    //erste spalte
    else if (x == 0) {
        return (getCell(0, y - 1) + getCell(0, y + 1) + getCell(1, y - 1) + getCell(1, y)
               + getCell(1, y + 1) + getCell(getNx() - 1, y - 1) + getCell(getNx() - 1, y) + getCell(getNx() - 1, y + 1));
    }
    //letzte spalte
    else if (x == getNx() - 1) {
        return (getCell(x, y - 1) + getCell(x, y + 1) + getCell(x - 1, y - 1) + getCell(x - 1,  y)
               + getCell(x - 1, y + 1) + getCell(0, y - 1) + getCell(0, y) + getCell(0, y + 1));
    }
    //rest
    else {
        return (getCell(x - 1, y - 1) + getCell(x - 1, y) + getCell(x - 1, y + 1) + getCell(x, y - 1)
               + getCell(x, y + 1) + getCell(x + 1, y - 1) + getCell(x + 1, y) + getCell(x + 1, y + 1));
    }
}

// Gibt die aktuelle Welt im Terminal an
void CAbase::print() {
    cout << ". ";
    for (int j = 0; j < worldWidth; j++) {
        cout << " . ";
    }
    cout << " .";
    cout << endl;
    for (int i = 0; i < worldHeight; i++) {
        cout << ". ";
        for (int k = 0; k < worldWidth; k++) {
            if (currentworld[getIndexByCoord(k, i)] == 1) {
                cout << " * ";
            }
            else {
                cout << "   ";
            }
        }
        cout << " .";
        cout << endl;
    }
    cout << ". ";
    for (int j = 0; j < worldWidth; j++) {
        cout << " . ";
    }
    cout << " .";
    cout << endl;
}

// Regel des Spiels
void CAbase::regel(int x, int y)
{
    if (getCell(x, y) == 1) {
        switch (nachbar(x, y)) {
            case 2:
                setCell_next(x, y, 1);
                break;
            case 3:
                setCell_next(x, y, 1);
                break;
            default:
                setCell_next(x, y, 0);
        }
    }
     else {
        if (nachbar(x, y) == 3) setCell_next(x, y, 1);
    }
}

void CAbase::evolve()           // Evolutionsstufe wird um 1 erhöht
{
    for (int y = 0; y < worldHeight; y++)       // Alle Felder werden die Regel getestet
        for (int x = 0; x < worldWidth; x++)
            regel(x, y);

    for (int y = 0; y < worldHeight; y++)       // Überschreiben
        for (int x = 0; x < worldWidth; x++)
            currentworld[getIndexByCoord(x, y)] = nextgenworld[getIndexByCoord(x, y)];
}
