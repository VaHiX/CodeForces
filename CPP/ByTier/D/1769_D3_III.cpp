// Problem: CF 1769 D3 - Game of Nine III
// https://codeforces.com/contest/1769/problem/D3

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (n); ++i)

const int N = 9, T = 4;
const char *SUITS = "CDSH";
const char *VALS = "6789TJQKA";

vector<long long> masks = {
    67515452935, 67515454987, 67515456011, 67515456013, 67515456523,
    67515456525, 67515456526, 67517553677, 67517553678, 67517558284,
    67518604813, 67521752588, 19592278700, 34336059520, 32688256024,
    10934253124, 21497764062, 953865822,   54567319559, 26364203238,
    20511443181, 67643379720, 67642331145, 67642331148, 67634991116,
    67626602508,
};

string card(int k) { return {VALS[k % N], SUITS[k / N]}; }

void print(long long mask) {
  forn(j, T * N) {
    if ((mask >> j) & 1) {
      cout << card(j) << " ";
    }
  }
  cout << "\n";
}

int main() {
  int k;
  cin >> k;
  long long full = (1ll << (T * N)) - 1;
  forn(i, k) {
    print(masks[i]);
    print(full - masks[i]);
    cout << "\n";
  }

  return 0;
}

// https://github.com/VaHiX/CodeForces/