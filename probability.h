//
//  probability.h
//  HW_Holdem
//
//  Created by simon on 15/5/11.
//  Copyright (c) 2015年 simon. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

#ifndef HW_Holdem_probability_h
#define HW_Holdem_probability_h

#define SWAP(a, b) {int iii = a; a = b; b = iii;}
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define ABS(a) ((a) < 0 ? -(a) : (a))

#define IS_ACE(a)           ((a)/4 == 0)
#define IS_PAIR(a, b)       ((a)/4 == (b)/4 && ABS((a)-(b)) <= 3)
#define IS_FLUSH(a, b)      ((a)%4 == (b)%4)

//IS_STRAIGHT(a, b) 默认 a牌面值 >= b牌面值
#define IS_STRAIGHT(a, b)   (!IS_PAIR(a, b) && \
((a)/4 - (b)/4 == 1 || \
((b)/4 == 12 && IS_ACE(a)) \
) \
)
#define COLOR(card)         ((card)%4)

//CMP: 0, a>b; 1, a==b; 2, a<b
inline int CMP(int a, int b) {
    if (a/4 == b/4) return 1;
    else if (IS_ACE(a) || (a/4 > b/4 && !IS_ACE(b))) return 0;
    else return 2;
}

const int CARDNUM = 52;
const int TYPENUM = 10; //牌型的种类 v1.1
const double ESP  = 1e-6; // v1.1
//const string sym[4] = {"HeiTao_", "HongTao_", "MeiHua_", "FangKuai_"};
const string sym[4] = {"♠️", "❤️", "♣️", "♦️"};
const string num10[4] = {"A", "J", "Q", "K"};
const string levelName[TYPENUM] = {
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

const double levelRank[10] = {
    38.443359375,   25.62890625,    17.0859375, 11.390625,  7.59375,
    5.0625,         3.375,          2.25,       1.5,        1
};

const int SAMPLINGCOUNT = 1499400 * 0.01;

class Probability {
public:
    bool pool[CARDNUM];
    int communityCard[5];
    int holdCards[2];
    
    //计算概率接口函数
    void calculateProb(int currentRound, double& winProb, double& tieProb, bool sample);  //v1.2
    void calculateProbForTypes(int currentRound, double probs[]);                         //v1.1
    
    //模拟抽牌用
    void getCard(int* a, int num, bool Pool[], int cardNum);                              //v1.3
    void getHoldCard2();
    void getCommunityCard3();
    void getTurnCard1();
    void getRiverCard1();
    void showCards(int currentRound);
    string showCard(int hash);
    
private:
    int rivalHoldCards[2];
    int currentRound;
    int poolRest[CARDNUM];
    bool poolRestBool[CARDNUM];
    
    //判断属于哪种牌型
    void makeHighCard(int* holds, int* bestHolds);
    bool is_8_Pair(int* holds, int* bestHolds);
    bool is_7_TwoPair(int* holds, int* bestHolds);
    bool is_6_Three(int* holds, int* bestHolds);
    bool is_5_Straight(int* holds, int* bestHolds);
    bool is_4_Flush(int* holds, int* bestHolds);
    bool is_3_FullHouse(int* holds, int* bestHolds);
    bool is_2_Four(int* holds, int* bestHolds);
    bool is_1_StraightFlush(int* holds, int* bestHolds);
    
    int bestPokerHand(int* holds, int* bestHolds);
    int cmpPokerHand(int level, int* bestHolds, int* bestRival);
    
    void moveAceToHigh(int* holds);
    int bet();
    
    void dfs(int* a, int nr, int pos, int maxNr, int& win, int& tie, int& total, int restCardNum); //v1.3
    
    void dfsForTypes(int* a, int nr, int pos, int maxNr, int count[], int& total); //v1.1
    
    bool is_top10holds(int* holds); //v1.1
    
    //v1.2
    void samplingDFS(int maxNr, int& win, int& tie, int restCardNum); //v1.3
//    bool checkHashPool(set<int>& hashPool);
//    void recoverPoolRestBool(int* a, int maxNr, bool Pool[]);
    int calHash(int* a, int commCardNum);
    void setCard(int color, int digit, int& card);  //v1.2.1
    void getCardFromRest(int* a, int num, int cardNum); //v1.3
};

#endif
