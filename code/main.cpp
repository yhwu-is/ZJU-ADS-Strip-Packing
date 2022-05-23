#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
// #include "block.h"
using namespace std;

#define SETTING_BIN_WIDTH 20

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

            // cout << b->first << " ";
        } else {
            // Need to open new level
            h_b += h_level; // add height of this level to the result
            width_left = W_b - b->first;
            // cout << ": " << h_level << endl << b->first << " ";

            h_level = b->second;
        }
    }
    h_b += h_level; // For the top level
    // cout << endl;
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
                // cout << i << endl;
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

int BWF(vector<block> &backet) {
    // It's changed based on FF that I copy most of the code of FF()
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
        int W_left_min = W_b;
        int idx_min = -1;
        // search for closed levels
        for(int i = 0; i < cnt_level; i++) {
            if(width <= w_level[i] && height <= h_level[i]) {
                // Fit this closed level
                // Updated W_left_min & idx_min if the left width is less than other before
                fit_closed = true;
                if(w_level[i] < W_left_min) {
                    idx_min = i;
                    W_left_min = w_level[i];
                }
            }
        }
        if(fit_closed) {
            // This block fits one of closed level, no need to get open level
            w_level[idx_min] -= width;
            // cout << idx_min << endl;
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
#define _TEST_
#ifndef _TEST_
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

    cout << BWF(backet) << endl;
    cout << "BWF Done" << endl;

    return 0;
}
#else 
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define FILE_NOT_OPEN 1
#define FILE_NOT_CLOSE 2
#define TIME ((double)(end-start)/CLOCKS_PER_SEC)
#define TIME_BEGIN start=clock()
#define TIME_END end=clock()

void generate_data(int max_width, int max_height) {
    ofstream out;
    out.open("in", ios::out);
    if(!out.is_open()) {
        exit(FILE_NOT_OPEN);
    }
    out << W_b << " " << n << endl;
    for(int i = 0; i < n; i++) {
        out << rand() % max_width + 1 << " " << rand() % max_height + 1 << endl;
    }

    out.close();
    if(out.is_open()) {
        exit(FILE_NOT_CLOSE);
    }
}

int main() {
    srand(time(NULL));
    time_t start;
    time_t end;
    // Reopen the stdin & stdout
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);

    vector<block> backet;

    W_b = SETTING_BIN_WIDTH;

    int test_n[] = {10, 50, 100, 500, 1000, 3000, 5000, 8000, 10000};
    const int test_repeat = 5;

    for(int test_n_i = 0; test_n_i < sizeof(test_n)/sizeof(int); test_n_i++) {
        n = test_n[test_n_i];
        for(int i = 0; i < test_repeat; i++) {
            generate_data(SETTING_BIN_WIDTH, 10);
            vector<block> backet;

            // Input
            cin >> W_b >> n;
            for(int i = 0; i < n; i++) {
                int w, h;
                cin >> w >> h;
                backet.push_back(block(w, h));
            }
            // cout << NF(backet) << " " << FF(backet) << " " << BWF(backet) << endl;
            cout << n << " ";

            TIME_BEGIN;
            cout << NF(backet) << " ";
            TIME_END;
            cout << TIME << " ";

            TIME_BEGIN;
            cout << FF(backet) << " ";
            TIME_END;
            cout << TIME << " ";

            TIME_BEGIN;
            cout << BWF(backet) << " ";
            TIME_END;
            cout << TIME << endl;
        }
    }
}
#endif