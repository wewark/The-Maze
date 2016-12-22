#include "Room.h"

vector<vector<Room>> Room::room;
int Room::mapWidth;
int Room::mapHeight;

Room::Room()
{
    name = "";
    description = "";
    block = false;
    detected = false;

    // Linked to nothing
    north = NULL;
    south = NULL;
    east = NULL;
    west = NULL;
}

Room::Room(string name, string description) {

    this->name = name;
    this->description = description;
    type = "room";
    block = false;
    detected = false;

    // Linked to nothing
    north = NULL;
    south = NULL;
    east = NULL;
    west = NULL;
}

Room::Room(string name, string description, string type) {

    this->name = name;
    this->description = description;
    this->type = type;
    block = false;
    detected = false;

    // Linked to nothing
    north = NULL;
    south = NULL;
    east = NULL;
    west = NULL;
}

Room::~Room()
{
}

string Room::getName() const {
    return name;
}

string Room::getDescription() const {
    return description;
}

void Room::setNum(int n)
{
    roomNum = n;
}

int Room::getNum() const
{
    return roomNum;
}

void Room::printMap(Room** room)
{
    // Find the player room
    int player_i, player_j;
    for (int i = 0; i < MAP_SIZE; i++)
        for (int j = 0; j < MAP_SIZE; j++)
            if (room[i][j].occupantsSize > 0 &&
                room[i][j].occupants[0]->getName() == "Player1" ||
                room[i][j].occupantsSize > 1 &&
                room[i][j].occupants[1]->getName() == "Player1")
            {
                player_i = i, player_j = j;
                break;
            }

    // Detect all around it
    detectAround(room, player_i, player_j);

    // Print the map
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
            if (!room[i][j].isDetected())
                cout << '?';
            else if (room[i][j].isBlock())
                cout << '#';
            else if (room[i][j].occupantsSize == 0)
                cout << ' ';
            else if (room[i][j].occupants[0]->getName() == "Player1")
                cout << 'X';
            else
                cout << room[i][j].occupants[0]->nextMove();
        cout << endl;
    }
}

void Room::makeBlock()
{
    block = true;
}

void Room::unBlock()
{
    block = false;
}

bool Room::isBlock()
{
    return block;
}

// Link room to another room, one way
void Room::link(Room *r, string direction) {
    if (direction == "north")
        north = r;
    else if (direction == "south")
        south = r;
    else if (direction == "east")
        east = r;
    else if (direction == "west")
        west = r;
}

// Get room linked in a certain direction
Room *Room::getLinked(string direction) {
    if (direction == "north")
        return north;
    else if (direction == "south")
        return south;
    else if (direction == "east")
        return east;
    else if (direction == "west")
        return west;
    else return NULL;
}

// Print the name of the room linked in each direction
void Room::printLinked() {
    cout << "You can go:" << endl;
    if (north != NULL)
        cout << "North (n)" << endl;
    if (south != NULL)
        cout << "South (s)" << endl;
    if (east != NULL)
        cout << "East (e)" << endl;
    if (west != NULL)
        cout << "West (w)" << endl;
    cout << "Wait (wt)" << endl;
}

void Room::enter(Agent *a)
{
    occupants[occupantsSize++] = a;
}

void Room::leave(Agent *a)
{
    for (int i = 0; i < occupantsSize; i++)
        if (occupants[i]->getName() == a->getName())
        {
            for (int j = i + 1; j < occupantsSize; j++)
                occupants[j - 1] = occupants[j];
            break;
        }
    occupantsSize--;
}

int Room::getOccupantsSize()
{
    return occupantsSize;
}

void Room::detect()
{
    detected = true;
}

bool Room::isDetected()
{
    return detected;
}

void Room::detectAround(Room ** room, int player_i, int player_j)
{
    room[player_i][player_j].detect();
    // The 8 neighbors
    if (player_i > 0)
        room[player_i - 1][player_j].detect();
    if (player_i > 0 && player_j > 0)
        room[player_i - 1][player_j - 1].detect();
    if (player_i > 0 && player_j < MAP_SIZE - 1)
        room[player_i - 1][player_j + 1].detect();
    if (player_j > 0)
        room[player_i][player_j - 1].detect();
    if (player_j < MAP_SIZE - 1)
        room[player_i][player_j + 1].detect();
    if (player_i < MAP_SIZE - 1)
        room[player_i + 1][player_j].detect();
    if (player_i < MAP_SIZE - 1 && player_j > 0)
        room[player_i + 1][player_j - 1].detect();
    if (player_i < MAP_SIZE - 1 && player_j < MAP_SIZE - 1)
        room[player_i + 1][player_j + 1].detect();
}

void Room::initializeRooms(vector<string> map)
{
    mapHeight = map.size();
    mapWidth = map[0].size();
    room.assign(mapHeight, vector<Room>(mapWidth));

    for (int i = 0; i < mapHeight; i++)
        for (int j = 0; j < mapWidth; j++)
        {
            room[i][j].setNum(i * 11 + j);
            if (map[i][j] == '#')
                room[i][j].makeBlock();
            if (i > 0)
                room[i][j].link(&room[i - 1][j], "north");
            if (i < mapHeight - 1)
                room[i][j].link(&room[i + 1][j], "south");
            if (j > 0)
                room[i][j].link(&room[i][j - 1], "west");
            if (j < mapWidth - 1)
                room[i][j].link(&room[i][j + 1], "east");
        }
}
