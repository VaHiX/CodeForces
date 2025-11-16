// Problem: CF 1869 D2 - Candy Party (Hard Version)
// https://codeforces.com/contest/1869/problem/D2

/*
Algorithm/Technique:
- This problem involves determining if a set of people can redistribute candies such that:
  1. Everyone ends up with the same number of candies (Tom's condition).
  2. Each person gives candies to at most one person and receives from at most one person (Daniel's condition).
- The core idea is to analyze how many candies each person needs to give or receive, and use bit manipulation to efficiently check if a valid redistribution exists.
- Key steps:
  1. Check if the total number of candies can be evenly divided among all people.
  2. For each person, compute the delta (difference from average).
  3. Classify deltas into powers of two (special case) or general cases.
  4. For the general case, try all possible ways to form a power of 2 and update delta accordingly.
  5. Use a greedy-like approach to validate the flow of candies, ensuring no imbalance in giving/ receiving.
- Time Complexity: O(n * log(max_value)) where `n` is the number of people and `max_value` is the maximum number of candies.
- Space Complexity: O(1) since we use fixed-size arrays and vectors.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define ll long long
using namespace std;
const int N = 2e5 + 5;
const int M = 31;
int t, n;
char getch() {
  static char buf[100000], *s, *s2;
  return (s == s2) && (s2 = (s = buf) + fread(buf, 1, 100000, stdin)),
         s == s2 ? EOF : *s++;
}
int read() {
  int x = 0, w = 1;
  char ch = 0;
  while (!isdigit(ch)) {
    if (ch == '-')
      w = -1;
    ch = getch();
  }
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getch();
  return x * w;
}
void init() {}
void charming() {
  init();
  n = read();
  vector<int> a(n);
  ll sum = 0;
  for (int i = 0; i < n; ++i) {
    a[i] = read();
    sum += a[i];
  }
  if (sum % n)
    return cout << "NO" << endl, void(); // If not divisible by n, impossible
  auto isType2 = [](int x, int y) -> int {
    int z = x & y;
    if (x != z)
      return -1;
    y -= x;
    if ((y & -y) == y)
      return y;
    else
      return -1;
  };
  int avg = sum / n; // Compute the average number of candies
  vector<int> delta(M), cnt_giv(M), cnt_rcv(M); // delta stores net contribution, cnt_giv/cnt_rcv count how many powers of 2 are given/recv
  for (int i = 0, tar, k; i < n; ++i) {
    tar = abs(avg - a[i]);
    if (tar == 0)
      continue; // No change needed
    else if ((tar & -tar) == tar) { // If tar is a power of 2
      k = 63 - __builtin_clzll(tar); // Get bit position of the last set bit
      if (a[i] > avg)
        ++cnt_giv[k]; // Give away candies
      else
        ++cnt_rcv[k]; // Receive candies
    } else {
      // If it's not a power of 2, then we must represent it as a difference of two powers of 2
      tar = avg - a[i];
      bool chk = false;
      for (int j = 0; j < M; ++j) {
        k = (1 << j) - tar;
        if (k > 0 && (k & -k) == k) {
          chk = true;
          k = 63 - __builtin_clzll(k);
          --delta[j], ++delta[k]; // Adjust contribution
          break;
        }
      }
      if (!chk)
        return cout << "NO" << endl, void(); // No valid way to decompose, invalid
    }
  }
  for (int i = 0, add = 0, now; i < M; ++i) {
    now = delta[i] + add; // Current balance
    add = now + (cnt_giv[i] - cnt_rcv[i]); // New balance after giving/receiving
    if (add & 1) // If odd, then cannot balance, invalid
      return cout << "NO" << endl, void();
    else if (now + cnt_giv[i] + cnt_rcv[i] < 0 || // If total gives/gets would be negative
             now - cnt_giv[i] - cnt_rcv[i] > 0)  // If total net changes would be positive
      return cout << "NO" << endl, void();
    else
      add /= 2; // Halve to move to next stage
  }
  cout << "YES" << endl;
}
signed main() {
  t = read();
  while (t--)
    charming();
  return 0;
}


// https://github.com/VaHiX/CodeForces/