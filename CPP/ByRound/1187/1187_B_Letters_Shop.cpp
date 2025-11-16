// Problem: CF 1187 B - Letters Shop
// https://codeforces.com/contest/1187/problem/B

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;
const int N = 2e5 + 9;
vector<int> v[127]; // Precompute positions of each character in the string s
char s[N];
int n, m;

int main() {
  scanf("%d%s%d", &n, &s, &m);
  // Build a list of positions for each character in the string s
  for (int i = 0; s[i]; ++i)
    v[s[i]].push_back(i);
  // Process each friend's name
  for (; m--; printf("%d\n", n + 1)) {
    scanf("%s", s);
    vector<int> p(127, 0); // Pointer for each character to track position in v[c]
    for (int i = n = 0; s[i]; ++i) {
      // Find the next occurrence of character s[i] that is beyond current position
      // Update n to the maximum position needed so far
      n = max(n, v[s[i]][p[s[i]]++]);
    }
  }
}


// https://github.com/VaHiX/codeForces/