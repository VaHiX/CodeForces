// Problem: CF 1251 C - Minimize The Integer
// https://codeforces.com/contest/1251/problem/C

/*
C. Minimize The Integer
Algorithm: Greedy with merge of odd and even digits
Time Complexity: O(n log n) due to sorting within vectors
Space Complexity: O(n) for storing digits in vectors

Approach:
- Separate odd and even digits while maintaining their relative order
- Merge the two sorted sequences (in ascending order) to get minimum integer
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;
char s[3000005];
int main() {
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    scanf("%s", s);
    int len(strlen(s));
    vector<char> v[2]; // v[0] for even digits, v[1] for odd digits
    for (int i(0); i < len; i++) {
      v[(s[i] - '0') & 1].push_back(s[i]); // separate digits by parity
    }
    merge(v[0].begin(), v[0].end(), v[1].begin(), v[1].end(), s); // merge sorted even and odd digits
    puts(s);
  }
}


// https://github.com/VaHiX/codeForces/