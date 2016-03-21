//
//  main.cpp
//  HW_Holdem
//
//  Created by simon on 15/5/9.
//  Copyright (c) 2015年 simon. All rights reserved.
//

#include "probability.h"

int main(int argc, const char * argv[]) {
    srand ((unsigned int)time(NULL));
    time_t t;
    Probability p = Probability();
    while(1) {
        double winProb, tieProb;
        
        memset(p.pool, 0, sizeof(p.pool));
        p.getHoldCard2();
       
        //------------------flop------------------
        p.getCommunityCard3();
        p.showCards(2);
        t = clock();
        p.calculateProb(2, winProb, tieProb, true);
        printf("sample:: win: %.2f%%  tie: %.2f%%\n", winProb*100, tieProb*100);
        
        /*
        double probs[10];
        p.calculateProbForTypes(2, probs);
        for (int i = 0; i < TYPENUM; i++) {
            if (probs[i] > ESP)
                printf("%9.4f  :", probs[i]);
            else
                printf("     NULL  :");
            cout << levelName[i] << endl;
        }
        double rank = 0;
        for (int i = 0; i < 10; i++) {
            rank += levelRank[i] * probs[i];
        }
        cout << "rank = " << rank << endl;
        p.calculateProb(2, winProb, tieProb);
        printf("win: %.4f  tie: %.4f\n", winProb, tieProb);
        */
         
        printf("exec time = %fs\n", (double)(clock() - t) / CLOCKS_PER_SEC);

        double winProb0 = winProb, tieProb0 = tieProb;
        
        t = clock();
        p.calculateProb(2, winProb, tieProb, false);
        printf("non-sample:: win: %.2f%%  tie: %.2f%%\n", winProb*100, tieProb*100);
        printf("exec time = %fs\n", (double)(clock() - t) / CLOCKS_PER_SEC);
        
        
        printf("\nDIFFERENCE: win: %.2f%%  tie: %.2f%%\n\n", (winProb0 - winProb)*100, (tieProb0 - tieProb)*100);
        
        
        //------------------turn------------------
        p.getTurnCard1();
        p.showCards(3);
        t = clock();
        p.calculateProb(3, winProb, tieProb, false);
        printf("win: %.2f%%  tie: %.2f%%\n", winProb*100, tieProb*100);
        printf("exec time = %fs\n", (double)(clock() - t) / CLOCKS_PER_SEC);
        
        //------------------river------------------
        p.getRiverCard1();
        p.showCards(4);
        t = clock();
        p.calculateProb(4, winProb, tieProb, false);
        printf("win: %.2f%%  tie: %.2f%%\n", winProb*100, tieProb*100);
        printf("exec time = %fs\n", (double)(clock() - t) / CLOCKS_PER_SEC);
        getchar();
    }
    return 0;
}
