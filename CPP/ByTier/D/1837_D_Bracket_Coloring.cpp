// Problem: CF 1837 D - Bracket Coloring
// https://codeforces.com/contest/1837/problem/D

/*
Algorithm: Bracket Coloring
Purpose: To color a bracket sequence using minimum colors such that each color forms a beautiful bracket sequence.
Techniques:
- Greedy coloring based on prefix balance
- Check if the sequence is valid, and if not, determine if it can be split into two beautiful sequences
Time Complexity: O(n) for each test case
Space Complexity: O(n) for storing the input string

The approach:
1. First, validate if the input is a balanced bracket sequence.
2. Then, simulate the balancing process from left to right to determine if the sequence is "bad" (both positive and negative balance occurs),
   which implies it must be split into two colors.
3. If it's a simple balanced sequence, all brackets can be colored with one color.
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define _int64 long long
#define mo 998244353
char s[210000];
int main() {
  int i, j, k, n, l, t, m, x, y, o, b1, b2, tmp, half, cnt0, cnt1;
  scanf("%d", &t);
  for (l = 0; l < t; l++) {
    scanf("%d", &n);
    scanf("%s", s);
    cnt0 = 0;
    cnt1 = 0;
    for (i = 0; i < n; i++)
      if (s[i] == '(')
        cnt0++;
      else
        cnt1++;
    if (cnt0 != cnt1) {
      printf("-1\n");
      continue;
    }
    b1 = 0;
    b2 = 0;
    tmp = 0;
    for (i = 0; i < n; i++) {
      if (s[i] == '(')
        tmp++;
      else
        tmp--;
      if (tmp > 0)
        b1 = 1;
      if (tmp < 0)
        b2 = 1;
    }
    if ((b1 == 1) && (b2 == 1)) {
      printf("2\n");
      half = n / 2;
      for (i = 0; i < half; i++)
        if (s[i] == '(')
          printf("1 ");
        else
          printf("2 ");
      for (i = half; i < n; i++)
        if (s[i] == '(')
          printf("2 ");
        else
          printf("1 ");
      printf("\n");
    } else {
      printf("1\n");
      for (i = 0; i < n; i++)
        printf("1 ");
      printf("\n");
    }
  }
}


// https://github.com/VaHiX/CodeForces/