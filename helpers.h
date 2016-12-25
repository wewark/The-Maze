#pragma once
#include<iostream>
#include <fstream>
#include "player.h"
#include "grue.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
inline string tolowerStr(string &x)
{
    for (unsigned int i=0; i<x.size(); i++)
    {
        x[i]=tolower(x[i]);
    }
    return x;
}
inline string getDirections()
{
   string x;
   cin >> x;
   x=tolowerStr(x);
   if(x=="north" || x=="south" || x=="east" || x=="west" || x=="quit" || x=="attack")
   {
       return x;
   }
   else return "invalid";

}
inline void printMap(vector<vector<room>> &x,player* y,int length, int width)
{
    for(int i=0; i<length; i++)
    {
        cout << "          |";
      for(int j=0; j<width; j++)
        {
            if(&x[i][j]==y->getPos())
                    cout << "O";
            else if(x[i][j].fog)
            {
                if(x[i][j].getType())
                {
                    if(x[i][j].getSize()>0)
                    {
                     cout << x[i][j].getSize();
                    }
                    else cout <<" ";
                }
                else cout << "#";
            }
            else cout << "?";
        }
        cout<<"|";
        cout << endl;
    }
    cout << endl;
}
inline void loadCords(int &length, int &width)
{
    fstream cords;
    cords.open("cords.txt", ios::in);
    cords >> length;
    cords >> width;
    cords.close();
}
inline void moveMobs(vector<grue> &mobs)
{
    for(int i=0; i<mobs.size(); i++)
    {
                mobs[i].act();
    }
}
inline void linkMap(vector<vector<room>> &x)
{
    int length,width;
    loadCords(length,width);
    fstream roomData;
    fstream roomName;
    /////File value holder (ba-cin fehom)/////
    string name;
    string desc="Description: later to be added";
    int type; //ROOM TYPE
    /////////////////////////////////////////
    roomData.open("roomData.txt", ios::in);
    roomName.open("roomName.txt", ios::in);
    for(int i=0; i<length; i++)
    {
      for(int j=0; j<width; j++)
        {
            roomName >> name;
            roomData >> type;
            x[i][j] = room(name,desc,type);
        }
    }
    //LINKINK
    for(int i=0; i<length; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(i==0&&j==0)
            {
                x[0][0].link(&x[1][0],"south");
                x[0][0].link(&x[0][1],"east");
            }
            if(i!=0&&j!=0)
            {
                x[i][j].link(&x[i-1][j],"north");
                x[i][j].link(&x[i][j-1],"west");
            }
            if(i==0&&j!=0)
            {
                x[i][j].link(&x[i][j-1],"west");
            }
            if(i!=0&&j==0)
            {
                x[i][j].link(&x[i-1][j],"north");
            }
        }
    }
    roomData.close();
    roomName.close();
    return;
}

inline void spawnLoadMobs(vector<vector<room>> &x, vector<grue> &mobs)
{
    int n,mobLevel; //Number of mobs,level
    int ix,jx; //Monster coordinates
    string mobName;
    fstream mobData;
    mobData.open("mobData.txt", ios::in);
    mobData>>n; //ba5od el N mn el file
    for(int i=0; i<n; i++)
    {
            mobData >> mobName;
            mobData >> mobLevel;
            mobData >> ix;
            mobData >> jx;
            mobs.emplace_back(grue(mobName,&x[ix][jx],mobLevel));
    }
    mobData.close();
    return;
}


