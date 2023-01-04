// CapyCity_MC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
enum BuildingType {
    EMPTY = 0, WATER = 1, WIND = 2, SOLAR = 3
};
BuildingType buildArea[50][50];
int width;
int height;
bool running = true;

void declareConstructionSite();
int inputHeight();
int inputWidth();
void menu();

void build();
BuildingType chooseBuildingType();
int inputBuildingWidth(int xCoordinate);
int inputBuildingLength(int yCoordinate);
int inputBuildingXCoordinate();
int inputBuildingYCoordinate();
bool checkBuilding(int xCoordinate, int yCoordinate, int buildingLength, int buildingHeight);
void setBuilding(BuildingType buildingType, int xCoordinate, int yCoordinate, int buildingLength, int buildingWidth);

void destroy();
void showBuildArea();

int main()
{
    declareConstructionSite();
    while (running) {
        menu();
    }
    
}

void declareConstructionSite() {
    height = inputHeight();
    width = inputWidth();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            buildArea[j][i] = EMPTY;
        }
    }
}
int inputHeight() {
    int input;
    cout << "Laenge der Bauflaeche eingeben (max 50): ";
    cin >> input;
    if (input <= 50 && input >= 0) {
        return input;
    }
    else {
        cout << "Eingabe ist ungültig\n";
        inputHeight();
    }
    return 0;
}
int inputWidth() {
    int input;
    cout << "Breite der Bauflaeche eingeben (max 50): ";
    cin >> input;
    if (input <= 50 && input >= 0) {
        return input;
    }
    else {
        cout << "Eingabe ist ungültig\n";
        inputHeight();
    }
}

void menu() {
    int input;
    cout << "*********** MENU ***********" << endl;
    cout << "Gebäude bauen (1)" << endl;
    cout << "Gebäude abreissen (2)" << endl;
    cout << "Bauplan ausgeben (3)" << endl;
    cout << "Programm beenden (4)" << endl;
    cout << "Eingabe: ";
    cin >> input;
    cout << "****************************" << endl;

    switch (input) {
    case 1:
        build();
        break;
    case 2:
        destroy();
        break;
    case 3: 
        showBuildArea();
        break;
    case 4:
        exit(0);
        running = false;
        break;
    default:
        cout << "Ungültige Eingabe\n";
        menu();
    }
}

void build() {
    BuildingType buildingType = chooseBuildingType();
    int xCoordinate = inputBuildingXCoordinate();
    int yCoordinate = inputBuildingYCoordinate();
    int buildingWidth = inputBuildingWidth(xCoordinate);
    int buildingLength = inputBuildingLength(yCoordinate);
    bool buildSpaceAlreadyInUse = checkBuilding(xCoordinate, yCoordinate, buildingLength, buildingWidth);
    if (buildSpaceAlreadyInUse) {
        cout << "Du kannst hier nicht Bauen. Der Platz ist schon belegt.";
    }
    else {
        setBuilding(buildingType, xCoordinate, yCoordinate, buildingLength, buildingWidth);
    }
}

BuildingType chooseBuildingType() {
    int input;
    cout << "1 - Wasserkraft\n";
    cout << "2 - Windkraft\n";
    cout << "3 - Solarkraft\n";
    cout << "Gebaeudetyp waehlen: ";
    cin >> input;
    
    switch (input) {
    case 1:
        return WATER;
        break;
    case 2:
        return WIND;
        break;
    case 3:
        return SOLAR;
        break;
    default:
        cout << "Ungueltige Eingabe!\n";
        chooseBuildingType();
    }
}
int inputBuildingXCoordinate() {
    int input;
    cout << "x-Koordinate fuer Gebaeude eingeben: ";
    cin >> input;

    if (input >= 0 && input <= width) {
        return input;
    }
    else {
        cout << "Eingabe ungültig" << endl;
        inputBuildingXCoordinate();
    }
}
int inputBuildingYCoordinate() {
    int input;
    cout << "y-Koordinate fuer Gebaeude eingeben: ";
    cin >> input;

    if (input >= 0 && input <= height) {
        return input;
    }
    else {
        cout << "Eingabe ungültig" << endl;
        inputBuildingYCoordinate();
    }
}
int inputBuildingWidth(int xCoordinate) {
    int input;
    cout << "Gebaeudebreite eingeben: ";
    cin >> input;

    if ((xCoordinate + input - 1) <= width) {
        return input;
    }
    else {
        cout << "Gebaeude zu gross" << endl;
        inputBuildingWidth(xCoordinate);
    }
}
int inputBuildingLength(int yCoordinate) {
    int input;
    cout << "Gebaeudelaenge eingeben: ";
    cin >> input;

    if ((yCoordinate + input - 1) <= height) {
        return input;
    }
    else {
        cout << "Gebaeude zu gross" << endl;
        inputBuildingLength(yCoordinate);
    }
}
bool checkBuilding(int xCoordinate, int yCoordinate, int buildingLength, int buildingWidth) {
    bool alreadyBuilt = false;
    for (int i = yCoordinate; i < buildingWidth + yCoordinate; i++) {
        for (int j = yCoordinate; j < buildingLength + yCoordinate; j++) {
            if (buildArea[j][i] == WATER || buildArea[j][i] == WIND || buildArea[j][i] == SOLAR) {
                alreadyBuilt = true;
            }
        }
    }
    return alreadyBuilt;
}
void setBuilding(BuildingType buildingType, int xCoordinate, int yCoordinate, int buildingLength, int buildingWidth) {
    for (int i = yCoordinate; i < buildingWidth + yCoordinate; i++) {
        for (int j = yCoordinate; j < buildingLength + yCoordinate; j++) {
            buildArea[j][i] = buildingType;
        }
    }
}


void destroy() {
    int xCoordinate = inputBuildingXCoordinate();
    int yCoordinate = inputBuildingYCoordinate();
    buildArea[xCoordinate][yCoordinate] = EMPTY;
    cout << "Gebaeude an den Koordinaten x=" << xCoordinate << " y=" << yCoordinate << " wurde abgerissen\n\n";
}

void showBuildArea() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            BuildingType type = buildArea[j][i];
            if (type == EMPTY) {
                cout << ".";
            } 
            else if(type == WATER) {
                cout << "A";
            }
            else if (type == WIND) {
                cout << "W";
            }
            else if (type == SOLAR) {
                cout << "S";
            }
        }
        cout << "\n";
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
