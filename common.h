#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <cmath>
#include <map>
#include <vector>
#include <ctime>
#include <sstream>
using namespace std;

#define MAXSIZE 4096
#define PRINT 0
#define PRATIO 0.2
#define BIGBLINDBET 40

typedef struct {
    int pid;
    bool buttonFlag;
    bool sblindFlag; 
    bool bblindFlag;
    bool foldFlag;
    bool all_inFlag;
    int jetton;
    int money;
    int bet;
    int diff;
    string lastAction;
    string position;
} INFO;

const string color[4] = {"SPADES", "HEARTS", "CLUBS", "DIAMONDS"};
const double weight[10] = {38.443359375, 25.62890625, 17.0859375, 11.390625, 
                           7.59375, 5.0625, 3.375, 2.25, 1.5, 1};
const string cardName[10] = {
    "Royal Straight Flush",     // 0
    "Straight Flush",           // 1
    "Four of a kind",           // 2
    "Full house",               // 3
    "Flush",                    // 4
    "Straight",                 // 5
    "Three of a kind",          // 6
    "Two pair",                 // 7
    "One pair",                 // 8
    "High card"                 // 9
};


#endif