// Problem: CF 2027 E1 - Bit Game (Easy Version)
// https://codeforces.com/contest/2027/problem/E1

/*
Algorithm/Techniques: Game Theory, Bit Manipulation, Nim Game
Time Complexity: O(n * log(max(a_i))) where n is the number of piles
Space Complexity: O(1) excluding input storage

This code determines the winner of a game where two players take turns removing stones from piles.
Each move must satisfy: 1 <= d <= a_i and x & d = d, where x is current stones and a_i is the pile's associated value.
The game follows the rules of Nim, where the XOR of all pile states determines the outcome.
The code uses bit manipulation to analyze each pile and compute the Grundy number for each.
*/
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <unordered_map>

#define fastio                                                                 \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(nullptr)
#define i64 long long
#define u64 unsigned long long
#define ld long double
#define F first
#define S second
#define MOD 1'000'000'007
#define INF 1'000'000'000
#define INFL 10'000'000'000'000'000ll
#define pi pair<int, int>
#define pi64 pair<i64, i64>
#define pb push_back
#define eb emplace_back
#ifdef ONLINE_JUDGE
#define endl '\n'
#endif
#define matrix vector<vector<int>>
#define vi vector<int>
#define vi64 vector<i64>
#define uset unordered_set
#define umap unordered_map
#define mpr make_pair
#define ALL(x) x.begin(), x.end()
#define RALL(data) data.rbegin(), data.rend()
#define TYPEMAX(type) std::numeric_limits<type>::max()
#define TYPEMIN(type) std::numeric_limits<type>::min()
#define null nullptr
using namespace std;
#ifdef ONLINE_JUDGE
class NullBuffer : public std::streambuf {
public:
  int overflow(int c) { return c; }
};
ostream logger(new NullBuffer());
#else
ostream &logger = cout;
#endif
umap<int, int> ln2;
void setup() {
  for (int i = 1, j = 0; j < 32; i <<= 1, j++) {
    ln2[i] = j;
  }
}
int ln(int x) {
  for (int i = 1; i <= 16; i <<= 1) {
    x |= x >> i;
  }
  return ln2[(x >> 1) + 1];
}
void solveMain() {
  int n;
  cin >> n;
  int ar[n], xr[n];
  for (int i = 0; i < n; i++) {
    cin >> ar[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> xr[i];
  }
  int sum = 0;
  for (int i = 0; i < n; i++) {
    int a = ar[i], x = xr[i];
    int la = ln(a);
    x = x & ((1 << (la + 1)) - 1);
    if (x <= a) {
      // If x is less than or equal to a, we can directly compute the nim value
      sum ^= __builtin_popcount(x);
      continue;
    }
    // If x > a, we need to compute complex nim value
    int y = x;
    int lft = 0, rgt = 0, ttl = 0;
    int flag = 0;
    for (int i = la; i >= 0; i--) {
      bool ab = (a & (1 << i)) != 0, xb = (x & (1 << i)) != 0;
      if (!flag and ab and xb) {
        // Both a and x have bit set, count towards left (lft)
        lft++;
      } else if (!flag and !ab and xb) {
        // Only x has bit set, this is the first change point, set flag to 1
        flag = 1, ttl++;
      } else if (flag == 1 and !ab and xb) {
        // Only x has bit set, continuing the pattern after flag
        ttl++;
      } else if (flag == 1 and ab) {
        // Switch from x to a, set flag to 2 and increment rgt if necessary
        flag = 2, rgt += xb;
      } else if (flag == 2 and xb) {
        // Count right bits after flag is set to 2
        rgt++;
      }
    }
    // Calculate the nim value based on complex logic
    int c = ttl == 1 and !rgt                 ? 0
            : (ttl & 1) and lft == 1 and !rgt ? ttl - 1
                                              : ttl + lft + rgt;
    sum ^= c;
  }
  cout << (sum ? "Alice" : "Bob") << endl;
}
int main() {
#ifndef ONLINE_JUDGE
  clock_t tStart = clock();
#endif
  fastio;
  int t = 1;
  cin >> t;
  setup();
  while (t--) {
    solveMain();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/