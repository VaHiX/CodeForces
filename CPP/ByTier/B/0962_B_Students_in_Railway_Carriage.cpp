// Problem: CF 962 B - Students in Railway Carriage
// https://codeforces.com/contest/962/problem/B

/*
Purpose: To determine the maximum number of students (programmers and athletes) that can be seated in a railway carriage such that no two students of the same type are adjacent. The carriage has some seats already occupied by jury members.

Algorithms/Techniques:
- Greedy approach: For each available seat, assign the student type (A for programmer, B for athlete) that hasn't been used consecutively and is available.
- The strategy prioritizes placing more abundant student type first to maximize the number of students placed.

Time Complexity: O(n), where n is the length of the string s. We iterate through the string once.
Space Complexity: O(n), for storing the string s and auxiliary variables.

*/
#include <stdio.h>
#include <iostream>
#include <string>
#include <utility>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 150
#define inf 1000000
#define pp pair<int, int>
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d\n", n)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s\n", s)
#define pb(n) push_back(n)
using namespace std;
int main() {
  int i, j, k;
  int n, m;
  int a, b;
  int x, y;
  char c1, c2;
  string s, t;
  scanf("%d%d%d", &n, &a, &b);
  cin >> s;
  i = 0;
  n = s.length();
  while (i < n) {
    if (s[i] == '*') // Skip jury occupied seats
      i++;
    else {
      c1 = 'A'; // Student programmer
      c2 = 'B'; // Student athlete
      if (a > 0)
        x = 1; // Check if there are programmers left
      else
        x = 0;
      if (b > 0)
        y = 1; // Check if there are athletes left
      else
        y = 0;
      if (b > a) // Prioritize placing the student type which is more abundant
        swap(c1, c2), swap(y, x);
      if (i == 0) { // First seat
        if (x) { // If programmers are available
          s[i] = c1; // Assign the chosen student type
          if (c1 == 'A')
            a--; // Decrease count of available programmers
          else
            b--; // Decrease count of available athletes
        } else if (y) { // If athletes are available and no programmers
          s[i] = c2; // Assign the chosen student type
          if (c2 == 'A')
            a--;
          else
            b--;
        }
        i++;
      } else { // Not first seat
        if (s[i - 1] != c1 && x) { // If previous seat is not of same type and student type is available
          s[i] = c1;
          if (c1 == 'A')
            a--;
          else
            b--;
        } else if (s[i - 1] != c2 && y) { // Else if previous seat is not of same type and other student type is available
          s[i] = c2;
          if (c2 == 'A')
            a--;
          else
            b--;
        }
        i++;
      }
    }
  }
  int cnt = 0;
  for (i = 0; i < n; i++) {
    if (s[i] == 'A' || s[i] == 'B') // Count how many students we placed
      cnt++;
  }
  pf(cnt);
  return 0;
}


// https://github.com/VaHiX/CodeForces/