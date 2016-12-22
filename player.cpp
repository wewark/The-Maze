#include "Player.h"

bool Player::won = false;

Player::Player(string name, Room * startingRoom) : Agent(name, startingRoom)
{
    won = false;
}

Player::~Player()
{
}

bool Player::act()
{
    currentRoom->printLinked();
    string response;
    cin >> response;

    // Convert abbreviations
    if (response == "n")
        response = "north";
    else if (response == "s")
        response = "south";
    else if (response == "e")
        response = "east";
    else if (response == "w")
        response = "west";
    else if (response == "wt")
        response = "wait";

    // While the choice is wrong, keep prompting
    while (
        !(response == "north" || response == "south" ||
            response == "east" || response == "west" ||
            response == "wait")
        || (response == "north" || response == "south" ||
            response == "east" || response == "west")
        && currentRoom->getLinked(response) == NULL)
    {
        cout << "Wrong choice! Try again" << endl;
        cin >> response;
        // Convert abbreviations
        if (response == "n")
            response = "north";
        else if (response == "s")
            response = "south";
        else if (response == "e")
            response = "east";
        else if (response == "w")
            response = "west";
        else if (response == "wt")
            response = "wait";
    }

    if (response == "north" || response == "south" ||
        response == "east" || response == "west")
    {
        currentRoom->leave(this);
        currentRoom = currentRoom->getLinked(response);
        currentRoom->enter(this);
    }
    if (currentRoom->getOccupantsSize() > 1)
        return false;
    if (currentRoom->getNum() == 5)
    {
        playerEscaped();
        return false;
    }
    return true;
}

void Player::playerEscaped() {
    won = true;
}

bool Player::playerWon() {
    return won;
}
