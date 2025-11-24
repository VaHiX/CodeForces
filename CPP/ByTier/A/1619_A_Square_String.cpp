// Problem: CF 1619 A - Square String?
// https://codeforces.com/contest/1619/problem/A

/*
Purpose: To determine if a given string is "square", meaning it can be split into two equal halves that are identical.
Algorithm: 
1. For each test case, check if the length of the string is even. If not, it cannot be square.
2. Split the string into two halves.
3. Compare the first half with the second half character by character.
4. If all characters match, the string is square; otherwise, it is not.

Time Complexity: O(n), where n is the length of the string. We check each character once in the comparison loop.
Space Complexity: O(1), excluding the input string storage, as we only use a constant amount of extra space.

Techniques:
- Two-pointer technique to compare the first and second halves of the string.
- Early termination upon mismatch.
*/

#include <stdio.h>
#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define nl printf("\n")
#define N 10101
#define inf 1e9
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
#define pp pair<int, int>
using namespace std;
int main() {
  int i, j, k;
  int n, m, t;
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    if (s.length() % 2) { // If length is odd, it can't be square
      cout << "NO" << endl;
      continue;
    }
    i = 0;
    j = s.length() / 2; // Start comparing from the middle
    k = 1;
    while (j < s.length()) {
      if (s[i] != s[j]) { // If characters don't match, not square
        k = 0;
        break;
      }
      i++, j++; // Move both pointers forward
    }
    if (k) // If all characters matched
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/