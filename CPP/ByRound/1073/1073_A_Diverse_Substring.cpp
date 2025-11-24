// Problem: CF 1073 A - Diverse Substring
// https://codeforces.com/contest/1073/problem/A

/*
Algorithm: Check for any two consecutive different characters in the string.
If found, output those two characters as a diverse substring.
If no such pair exists, the entire string consists of same characters,
and hence no diverse substring of length > 1 exists.

Time Complexity: O(n), where n is the length of the string.
Space Complexity: O(1), excluding the input storage.
*/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 1000005
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
#define pp pair<int, int>
using namespace std;

void exec() {
  pfs("NO\n");
  exit(0);
}

int main() {
  int i, j, k;
  int n, m, l;
  string s, t;
  sf(n);
  cin >> s;
  
  // If string has only one character, it cannot form a diverse substring of length > 1
  if (n == 1)
    exec();
    
  // Iterate through the string to find two consecutive different characters
  for (i = 0; i < n - 1; i++) {
    if (s[i] != s[i + 1]) {
      pfs("YES\n");
      cout << s[i] << s[i + 1] << endl;
      return 0;
    }
  }
  
  // If all characters are same, no diverse substring exists
  pfs("NO\n");
  return 0;
}


// https://github.com/VaHiX/CodeForces/