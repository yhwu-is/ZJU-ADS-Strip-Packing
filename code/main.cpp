#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
// #include "block.h"
using namespace std;

typedef pair<int, int> block;
typedef vector<block>::iterator it_b;

int n; // number of blocks
int W_b; // weight & height of the bin

int NF(vector<block> &backet) {
    // Init
    int h_b = 0;
    int h_level = 0;
    int width_left = W_b;

    // For each block in basket
    for(it_b b = backet.begin(); b != backet.end(); b++) {
        // Note first as _width_ & second as _height_
        
        if(b->first <= width_left) {
            // This block can be inserted into this level
            width_left -= b->first;
            if(b->second > h_level) h_level = b->second;

            cout << b->first << " ";
        } else {
            // Need to open new level
            h_b += h_level; // add height of this level to the result
            width_left = W_b - b->first;
            cout << ": " << h_level << endl << b->first << " ";

            h_level = b->second;
        }
    }
    h_b += h_level; // For the top level
    cout << endl;
    return h_b;
}

int main(void) {
    #ifndef SIMPLE_TEST
        freopen("in", "r", stdin);
        // freopen("out", "w", stdout);
    #endif

    vector<block> backet;

    // Input
    cin >> W_b >> n;
    for(int i = 0; i < n; i++) {
        int w, h;
        cin >> w >> h;
        backet.push_back(block(w, h));
    }

    // for(int i = 0; i < n; i++) cout << backet[i].first << " " << backet[i].second << endl;

    cout << NF(backet) << endl;
    cout << "NF Done" << endl;

    return 0;
}