// Problem: CF 1087 A - Right-Left Cipher
// https://codeforces.com/contest/1087/problem/A

/*
 * Problem: A. Right-Left Cipher
 * Purpose: Decrypt a string that was encrypted using the Right-Left cipher algorithm.
 * Algorithm:
 *   - The encryption process starts with the first character,
 *     then alternately appends (right) and prepends (left) characters.
 *   - To decrypt, we reverse this process by reconstructing the original string
 *     from the end of the encrypted string, working backwards in alternating fashion.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 100100
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
#define pp pair<string, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  string s, t = "";
  cin >> s;
  n = s.length();
  
  // Determine the starting index based on whether length is odd or even
  if (n % 2 == 1)
    k = n / 2;
  else
    k = (n / 2) - 1;
  
  // Start with the middle character of the original string
  t.pb(s[k]);
  
  i = k + 1;   // pointer to the right side
  j = k - 1;   // pointer to the left side
  
  // Reconstruct the original string by alternating from both sides
  while (t.length() < n) {
    if (i < n)
      t.pb(s[i]), i++;   // append character from the right
    if (j >= 0)
      t.pb(s[j]), j--;   // prepend character from the left
  }
  
  cout << t;
  return 0;
}


// https://github.com/VaHiX/codeForces/