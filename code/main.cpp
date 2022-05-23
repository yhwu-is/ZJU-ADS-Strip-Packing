#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
// #include "block.h"
using namespace std;

typedef pair<int, int> block;
typedef vector<block>::iterator it_b;

int n; // number of blocks
int W_b; // width & height of the bin

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

int FF(vector<block> &backet) {
    int cnt_level = 0;
    vector<int> h_level; // height for each closed level 
    vector<int> w_level; // width left for each closed level
    int h_b = 0; // As the sum of h_level and ending open level
    int h_level_open = 0;
    int width_left_open = W_b;
    bool fit_closed = false;
    for(it_b b = backet.begin(); b != backet.end(); b++) {
        fit_closed = false;
        int width = b->first;
        int height = b->second;
        // search for closed levels
        for(int i = 0; i < cnt_level; i++) {
            if(width <= w_level[i] && height <= h_level[i]) {
                // Fit this closed level
                // Insert this block into this level
                w_level[i] -= width;
                fit_closed = true;
                break;
            }
        }
        if(fit_closed) {
            // This block fits one of closed level, no need to get open level
            continue;
        }
        // Now we need to deal with the open level
        if(width <= width_left_open) {
            // This block can be inserted into this open level
            width_left_open -= width;
            if(height > h_level_open) h_level_open = height;
        } else {
            // Need to close the originally open level
            h_level.push_back(h_level_open);
            w_level.push_back(width_left_open);
            cnt_level++;
            h_b += h_level_open;
            width_left_open = W_b - width;
            h_level_open = height;
        }
    }
    if(fit_closed) // The last one not inserted into closed level
        h_b += h_level_open;
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

    cout << FF(backet) << endl;
    cout << "FF Done" << endl;

    return 0;
}