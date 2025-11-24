// Problem: CF 1860 C - Game on Permutation
// https://codeforces.com/contest/1860/problem/C

/*
Algorithm/Technique: 
    The problem is about determining "lucky" elements in a permutation where Alice can win if she starts from that element. 
    The key insight is to analyze the sequence from right to left and use a greedy approach:
        - For each element, we check if it can be part of a winning strategy.
        - We maintain two variables mn1 and mn2 to track the minimum values seen so far and the second minimum.
        - If an element is greater than mn2, it means it's not a valid candidate for a winning strategy.
        - Only elements that are greater than mn1 but not greater than mn2 are considered to be lucky (i.e. they can be the start of a winning sequence).

Time Complexity: O(n) - Each element is visited once.
Space Complexity: O(n) - For storing the permutation array.
*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

#define ll long long
using namespace std;
const int N = 2e5 + 5;
char getch() {
  static char buf[100000], *s1, *s2;
  return (s1 == s2) && (s2 = (s1 = buf) + fread(buf, 1, 100000, stdin)),
         s1 == s2 ? EOF : *s1++;
}
int read() {
  int x = 0;
  char ch = 0;
  while (!isdigit(ch))
    ch = getch();
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getch();
  return x;
}
int t, n;
void init() {}
void charming() {
  init();
  n = read();
  vector<int> a(n);
  int ans = 0, mn1 = n + 1, mn2 = n + 1;
  for (int i = 0; i < n; ++i) {
    a[i] = read(), mn1 = min(mn1, a[i]);
    if (a[i] <= mn1)
      continue;  // If current element is less than or equal to the minimum seen so far, skip
    else if (a[i] > mn2)
      continue;  // If current element is greater than the second minimum, it cannot be lucky
    else
      mn2 = a[i], ++ans;  // Update second minimum and increment the count of lucky elements
  }
  cout << ans << endl;
}
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  t = read();
  while (t--)
    charming();
  return 0;
}


// https://github.com/VaHiX/CodeForces/