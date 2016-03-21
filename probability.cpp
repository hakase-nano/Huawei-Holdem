//
//  probability.cpp
//  HW_Holdem
//
//  Created by simon on 15/5/11.
//  Copyright (c) 2015年 simon. All rights reserved.
//

#include "probability.h"

string Probability::showCard(int hash) {
    string res;
    res += sym[hash%4];
    int digit = hash/4+1;
    if (digit == 1) res += num10[0];
    else if (digit == 10) res += "10";
    else if (digit < 10) res += digit + '0';
    else res += num10[digit - 10];
    return res;
}

void Probability::makeHighCard(int* holds, int* bestHolds) {
    for (int i = 6, j = 0; i >= 2; i--, j++) {
        bestHolds[j] = holds[i];
    }
    return;
}

bool Probability::is_8_Pair(int* holds, int* bestHolds) {
    for (int i = 6; i >= 1; i--) {
        if (IS_PAIR(holds[i], holds[i-1])) {
            bestHolds[0] = holds[i-1];
            bestHolds[1] = holds[i];
            int count = 2;
            int j;
            for (j = 6; count < 5 && j != i && j != i-1; j--) {
                bestHolds[count++] = holds[j];
            }
            if (count < 5) {
                for (j = i-2; count < 5 && j >= 0; j--) {
                    bestHolds[count++] = holds[j];
                }
            }
            return true;
        }
    }
    return false;
}

bool Probability::is_7_TwoPair(int* holds, int* bestHolds) {
    for (int i0 = 6; i0 >= 3; i0--) {
        if (IS_PAIR(holds[i0], holds[i0-1])) {
            for (int i1 = i0-2; i1 >= 1; i1--) {
                if (IS_PAIR(holds[i1], holds[i1-1])) {
                    bestHolds[0] = holds[i0-1];
                    bestHolds[1] = holds[i0];
                    bestHolds[2] = holds[i1-1];
                    bestHolds[3] = holds[i1];
                    int j = 6;
                    while ((j == i0 || j == i0-1 || j == i1 || j == i1-1) && (j >= 0)) j--;
                    //assert(j >= 0);
                    bestHolds[4] = holds[j];
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}

bool Probability::is_6_Three(int* holds, int* bestHolds) {
    for (int i = 6; i >= 2;) {
        if (IS_PAIR(holds[i], holds[i-1])) {
            if (IS_PAIR(holds[i-1], holds[i-2])) {
                bestHolds[0] = holds[i-2];
                bestHolds[1] = holds[i-1];
                bestHolds[2] = holds[i];
                int count = 3;
                for (int j = 6; count < 5 && j >= 0; j--) {
                    if (j != i && j != i-1 && j != i-2) {
                        bestHolds[count++] = holds[j];
                    }
                }
                return true;
            }
            else i -= 2;
        }
        else i -= 1;
    }
    return false;
}

//v1.3.1
bool Probability::is_5_Straight(int* holds, int* bestHolds) {
    int head = 6;
    while (head >= 4) {
        int next = head-1, cnt = head;
        int count = 0;
        bestHolds[count++] = holds[cnt];
        while (next >= 0 && count < 5) {
            if (IS_STRAIGHT(holds[cnt], holds[next])) {
                cnt = next;
                bestHolds[count++] = holds[cnt];
            }
            next--;
        }
        if (count == 5) return true;
        head--;
    }
    return false;
}

//v1.3.1
bool Probability::is_4_Flush(int* holds, int* bestHolds) {
    int flush_color = 0, nTimes, i;
    for (i = nTimes = 0; i < 7; i++) {
        if (nTimes == 0) {
            flush_color = COLOR(holds[i]), nTimes = 1;
        }
        else {
            if (flush_color == COLOR(holds[i]))
                nTimes++;
            else
                nTimes--;
        }
    }
    int count = 0;
    for (i = 6; i >= 0; i--) {
        if (flush_color == COLOR(holds[i])) {
            bestHolds[count++] = holds[i];
        }
        if (count == 5) break;
    }
    return count == 5;
}

bool Probability::is_3_FullHouse(int* holds, int* bestHolds) {
    for (int i = 6; i >= 2;) {
        if (IS_PAIR(holds[i], holds[i-1])) {
            if (IS_PAIR(holds[i-1], holds[i-2])) {
                for (int j = 6; j >= 1; j--) {
                    if ((j-1 > i || j < i-2) && IS_PAIR(holds[j], holds[j-1])) {
                        bestHolds[0] = holds[i-2];
                        bestHolds[1] = holds[i-1];
                        bestHolds[2] = holds[i];
                        bestHolds[3] = holds[j-1];
                        bestHolds[4] = holds[j];
                        return true;
                    }
                }
                return false;
            }
            else i -= 2;
        }
        else i -= 1;
    }
    return false;
    
}

bool Probability::is_2_Four(int* holds, int* bestHolds) {
    for (int i = 6; i >= 3;) {
        if (IS_PAIR(holds[i], holds[i-1])) {
            if (IS_PAIR(holds[i-1], holds[i-2])) {
                if (IS_PAIR(holds[i-2], holds[i-3])) {
                    for (int j = 0; j < 4; j++)
                        bestHolds[j] = holds[i-j];
                    if (i != 6) bestHolds[4] = holds[6];
                    else bestHolds[4] = holds[2];
                    return true;
                }
                else i -= 3;
            }
            else i -= 2;
        }
        else i -= 1;
    }
    return false;
}

//v1.3.1
bool Probability::is_1_StraightFlush(int* holds, int* bestHolds) {
    int head = 6;
    while (head >= 4) {
        int next = head-1, cnt = head;
        int count = 0;
        bestHolds[count++] = holds[cnt];
        while (next >= 0 && count < 5) {
            if (IS_STRAIGHT(holds[cnt], holds[next]) && IS_FLUSH(holds[cnt], holds[next])) {
                cnt = next;
                bestHolds[count++] = holds[cnt];
            }
            next--;
        }
        if (count == 5) {
            return true;
        }
        head--;
    }
    return false;
}

int Probability::bestPokerHand(int* holds, int* bestHolds) {
    if (is_1_StraightFlush(holds, bestHolds)) {
        if (IS_ACE(bestHolds[0]))               return 0;
        else                                    return 1;
    }
    
    if (is_2_Four(holds, bestHolds))            return 2;
    if (is_3_FullHouse(holds, bestHolds))       return 3;
    if (is_4_Flush(holds, bestHolds))           return 4;
    if (is_5_Straight(holds, bestHolds))        return 5;
    if (is_6_Three(holds, bestHolds))           return 6;
    if (is_7_TwoPair(holds, bestHolds))         return 7;
    if (is_8_Pair(holds, bestHolds))            return 8;
    
    makeHighCard(holds, bestHolds);             return 9;
}

//v1.1
int Probability::cmpPokerHand(int level, int* bestHolds, int* bestRival) {
    if (level == 5 || level <= 1) { // Straight*
        if (IS_ACE(bestHolds[0]) && !IS_ACE(bestRival[0])) return 2;
        else if (IS_ACE(bestRival[0]) && !IS_ACE(bestHolds[0])) return 0;
    }
    for (int i = 0; i < 5; i++) {
        int c = CMP(bestHolds[i], bestRival[i]);
        if (c != 1) return c;
    }
    return 1;
}

void Probability::moveAceToHigh(int* holds) { // 将Ace移到高位
    if (!IS_ACE(holds[0])) return;
    int i = 0, j = 0;
    int tmp[4];
    while (IS_ACE(holds[i])) {
        tmp[i] = holds[i];
        i++;
    }
    for (j = 0; j < 7-i; j++) {
        holds[j] = holds[i+j];
    }
    for (j = 7-i; j < 7; j++) {
        holds[j] = tmp[j+i-7];
    }
}

int Probability::bet() {
    int holds[7], bestHolds[5];
    int rival[7], bestRival[5];
    for (int i = 0; i < 5; i++) {
        holds[i] = communityCard[i];
        rival[i] = communityCard[i];
    }
    holds[5] = holdCards[0], holds[6] = holdCards[1];
    rival[5] = rivalHoldCards[0], rival[6] = rivalHoldCards[1];
    sort(holds, holds+7); moveAceToHigh(holds);
    sort(rival, rival+7); moveAceToHigh(rival);
    int level0 = bestPokerHand(holds, bestHolds); //level越小牌面越高
    int level1 = bestPokerHand(rival, bestRival);
    
    
    if (0) {
     cout << "Holds: ";
     for (int i = 0; i < 7; i++) cout << showCard(holds[i]) << " ";
     cout << endl;
     cout << "bestHolds: ";
     for (int i = 0; i < 5; i++) cout << showCard(bestHolds[i]) << " ";
     cout << levelName[level0] << endl;
     cout << "----------------------------------------------\n";
     cout << "Rival: ";
     for (int i = 0; i < 7; i++) cout << showCard(rival[i]) << " ";
     cout << endl;
     cout << "bestRival: ";
     for (int i = 0; i < 5; i++) cout << showCard(bestRival[i]) << " ";
     cout << levelName[level1] << endl;
     cout << "----------------------------------------------\n";
     cout << "----------------------------------------------\n";
    }

    
    if (level0 == level1) {
        return cmpPokerHand(level0, bestHolds, bestRival);
    }
    else if (level0 < level1) return 0;
    else return 2;
}

void Probability::dfs(int* a, int nr, int pos, int maxNr, int& win, int& tie, int& total, int restCardNum) {
    if (pos == restCardNum) return;
    if (nr == maxNr) {
        
        //tricky 不要动
        const int alpha[6][4] = {
            {0, 1, 2, 3}, {0, 2, 1, 3},
            {1, 2, 0, 3}, {0, 3, 1, 2},
            {1, 3, 0, 2}, {2, 3, 0, 1}
        };
        const int beta[3] = {6, 3, 1};
        //assert(4-maxNr >= 0);
        total += beta[4-maxNr];
        for (int i = 0; i < beta[4-maxNr]; i++) {
            for (int j = 0; j < maxNr; j++) {
                if (j < 2) rivalHoldCards[j] = a[alpha[i][j]];
                else {
                    //assert(j+5-maxNr >= 0);
                    communityCard[j+5-maxNr] = a[alpha[i][j]];
                }
            }
            
            int betRes = bet();
            if (betRes == 0) {
                win++;
            }
            else if(betRes == 1) {
                tie++;
            }
            
            else {
//                if (maxNr == 2) {
//                    cout << showCard(rivalHoldCards[0]) << " " << showCard(rivalHoldCards[1]) << endl;
//                }
            }
        }
        
        return;
    }
    else {
        poolRestBool[pos] = true;
        a[nr] = poolRest[pos];
        dfs(a, nr+1, pos+1, maxNr, win, tie, total, restCardNum);
        poolRestBool[pos] = false;
        dfs(a, nr, pos+1, maxNr, win, tie, total, restCardNum);
    }
}

//v1.1
void Probability::dfsForTypes(int* a, int nr, int pos, int maxNr, int count[], int& total) {
    if (pos == CARDNUM) return;
    if (nr == maxNr) {
        total++;
        for (int i = 0; i < maxNr; i++) communityCard[i+3] = a[i];
        
        int holds[7], bestHolds[5];
        for (int i = 0; i < 5; i++) {
            holds[i] = communityCard[i];
        }
        holds[5] = holdCards[0], holds[6] = holdCards[1];
        sort(holds, holds+7); moveAceToHigh(holds);
        int level = bestPokerHand(holds, bestHolds); //level越小牌面越高
        count[level]++;
    }
    else {
        poolRestBool[pos] = true;
        a[nr] = poolRest[pos];
        dfsForTypes(a, nr+1, pos+1, maxNr, count, total);
        poolRestBool[pos] = false;
        dfsForTypes(a, nr, pos+1, maxNr, count, total);
    }
}

//计算胜率
//v1.2
void Probability::calculateProb(int currentRound, double& winProb, double& tieProb, bool sample) {
    int numCommunityCards = currentRound + 1;
    int restCardNum = 0;
    for (int i = 0; i < CARDNUM; i++) {
        if (!pool[i]) poolRest[restCardNum++] = i;
    }
    memset(poolRestBool, 0, sizeof(poolRestBool));
    int a[4];
    int win = 0, tie = 0, total = 0;
    
    if (sample == true) {
        samplingDFS(7 - numCommunityCards, win, tie, restCardNum);
        total = SAMPLINGCOUNT;
    }
    else
        dfs(a, 0, 0, 7 - numCommunityCards, win, tie, total, restCardNum);
    winProb = (double)win / total;
    tieProb = (double)tie / total;
//    cout << "total " << total << endl;
}

//计算获得每种牌型的概率 v1.1
void Probability::calculateProbForTypes(int currentRound, double probs[]) {
    int numCommunityCards = currentRound + 1;
    for (int i = 0, j = 0; i < CARDNUM; i++) {
        if (!pool[i]) poolRest[j++] = i;
    }
    memset(poolRestBool, 0, sizeof(poolRestBool));
    int a[2], count[TYPENUM] = {0};
    int total = 0;
    dfsForTypes(a, 0, 0, 5 - numCommunityCards, count, total);
    for (int i = 0; i < TYPENUM; i++) {
        probs[i] = (double)count[i] / total;
    }
}

//v1.3
void Probability::getCard(int* a, int num, bool Pool[], int cardNum) {
    int i = 0;
    while (i < num) {
        int card;
        do {
            card = rand() % cardNum;
        } while (Pool[card]);
        a[i++] = card;
        Pool[card] = true;
    }
    return;
}

//v1.3
void Probability::getCardFromRest(int* a, int num, int cardNum) {
    int i = 0;
    while (i < num) {
        int card;
        do {
            card = rand() % cardNum;
        } while (poolRestBool[card]);
        a[i++] = poolRest[card];
        poolRestBool[card] = true;
    }
    return;
}

//v1.1
bool Probability::is_top10holds(int* holds) {
    // top10:
    // {A,A},{K,K},{A,K},{Q,Q},{J,J},{9,9},{8,8},{A,Q},{7,7},{10,10}
    
    int mx = MAX(holds[0], holds[1]);
    int mn = MIN(holds[0], holds[1]);

    if (mx/4 == mn/4 && (IS_ACE(mx) || mx/4 >= 9)) return true;
    else if (IS_ACE(mn) && mx/4 >= 11) return true;
    else return false;
}

void Probability::getHoldCard2() { //获取底牌
    /*
    do {
        memset(pool, 0, sizeof(pool));
        getCard(holdCards, 2, pool, CARDNUM);
    } while (false);
     */
//    } while (is_top10holds(holdCards) == false);

    setCard(1, 13, holdCards[0]);
    setCard(3, 1, holdCards[1]);
}

void Probability::getCommunityCard3() { //获取三张公共牌
//    getCard(communityCard, 3, pool, CARDNUM);
    
    setCard(3, 13, communityCard[0]);
    setCard(3, 2, communityCard[1]);
    setCard(0, 7, communityCard[2]);
    currentRound = 2;
}

void Probability::getTurnCard1() { //获取第4张公共牌
//    getCard(communityCard+3, 1, pool, CARDNUM);

    setCard(3, 7, communityCard[3]);
    currentRound = 3;
}

void Probability::getRiverCard1() { //获取第5张公共牌
//    getCard(communityCard+4, 1, pool, CARDNUM);

    setCard(1, 5, communityCard[4]);
    currentRound = 4;
}

void Probability::showCards(int currentRound) { //输出当前场上的公共牌及底牌
    int numCommunityCards = currentRound + 1;
    cout << "----------------------------------------------\n";
    cout << "Hold: ";
    for (int i = 0; i < 2; i++) {
        cout << showCard(holdCards[i]) << " ";
    }
    cout << " Community: ";
    for (int i = 0; i < numCommunityCards; i++) {
        cout << showCard(communityCard[i]) << " ";
    }
    cout << endl;
}

//v1.2
void Probability::samplingDFS(int maxNr, int& win, int& tie, int restCardNum) {
    set<int> hashPool;
    int a[4];
    int commCardNum = maxNr - 2;
    int tot = 0;
    while (tot < SAMPLINGCOUNT) {
        tot++;
        int hash;
        do {
            getCardFromRest(a, maxNr, restCardNum);
            hash = calHash(a, commCardNum);
            for (int i = 0; i < maxNr; i++) {
                for (int j = 0; j < restCardNum; j++) {
                    if (a[i] == poolRest[j]) {
                        poolRestBool[j] = false;
                        break;
                    }
                }
            }
        } while (hashPool.count(hash) == 1);
        
        hashPool.insert(hash);

        for (int i = 0; i < commCardNum; i++)   communityCard[i+5-commCardNum] = a[i];
        for (int i = 0; i < 2; i++)             rivalHoldCards[i] = a[i+commCardNum];
        
        int betRes = bet();
        if (betRes == 0) {
            win++;
        }
        else if(betRes == 1) {
            tie++;
        }

    }
}

//v1.2
int Probability::calHash(int* a, int commCardNum) {
    int res = 0, tmp = 1;
    for (int i = 0; i < commCardNum; i++) tmp *= (a[i]+1);
    if (tmp != 1) res += tmp * 10000;
    res += (a[commCardNum]+1)*(a[commCardNum+1]+1);
    return res;
}



//v1.2.1
void Probability::setCard(int color, int digit, int& card) {
    int hash = color + (digit-1) * 4;
    pool[hash] = true;
    card = hash;
}