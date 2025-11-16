// Problem: CF 1144 A - Diverse Strings
// https://codeforces.com/contest/1144/problem/A

/*
Code Purpose:
This program determines whether a given string is "diverse". A diverse string is one where:
1. All characters are unique (no duplicates).
2. The characters form a contiguous segment in the alphabet (i.e., their ASCII values form a consecutive sequence).

Algorithm:
- For each string, we first sort the characters.
- Then, we check if each character is exactly one ASCII value greater than the previous character.
- If all adjacent characters satisfy this condition, the string is diverse.

Time Complexity: O(n * m * log(m)) where n is the number of strings and m is the average length of the strings.
Space Complexity: O(m) where m is the length of the string (due to sorting).

Techniques:
- Sorting the string to arrange characters in ascending order.
- Iterating through sorted string to check sequential ASCII values.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 2500
#define inf 1e18
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<ll, ll>
using namespace std;

int main() {
  int i, j, k;
  int n, m, t;
  string s;
  sf(t); // Read number of test cases
  while (t--) {
    cin >> s; // Read the string
    sort(s.begin(), s.end()); // Sort the characters to check for contiguous sequence
    k = 1; // Flag to indicate if string is diverse
    n = s.length(); // Get the length of string
    for (i = 1; i < n; i++) {
      if (s[i] - s[i - 1] != 1) { // Check if current char is exactly 1 more than previous
        k = 0; // If not, mark as not diverse
        break;
      }
    }
    if (k) // If diverse
      pfs("yes\n");
    else // If not diverse
      pfs("no\n");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/