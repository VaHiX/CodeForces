// Problem: CF 584 C - Marina and Vasya
// https://codeforces.com/contest/584/problem/C

/*
Purpose: 
This code finds a string s3 of length n such that s3 differs from s1 and s2 in exactly t positions each.
It uses a greedy approach to construct the string.

Algorithm:
1. Read inputs n, t, s1, s2
2. Initialize result string a with '#' characters
3. For each position, if s1[i] == s2[i], place that character in a and reduce t1 and t2 (number of positions to modify)
4. Fill remaining positions from s1 or s2 to satisfy t1 or t2
5. For remaining positions, replace '#' with a character different from both s1[i] and s2[i]
6. Validate that the resulting string satisfies the condition f(s1,s3) = f(s2,s3) = t

Time Complexity: O(n)
Space Complexity: O(n)

*/

#include <iostream>
#include <string>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
using namespace std;
int main() {
  ll i, j, k;
  ll n, t;
  ll t1, t2;
  string s1, s2, a;
  cin >> n >> t;
  cin >> s1 >> s2;
  k = n;
  t1 = n - t;
  t2 = n - t;
  for (i = 0; i < n; i++)
    a.push_back('#'); // Initialize result string with placeholders
  i = 0;
  while (i < n && t1 > 0 && t2 > 0) {
    if (s1[i] == s2[i])
      a[i] = s1[i], t1--, t2--, k--; // If characters are same, we can place that character and reduce t1 and t2
    i++;
  }
  i = 0;
  while (t1 && k) { // Fill remaining positions from s1
    if (a[i] == '#')
      a[i] = s1[i], t1--, k--;
    i++;
  }
  i = 0;
  while (t2 && k) { // Fill remaining positions from s2
    if (a[i] == '#')
      a[i] = s2[i], t2--, k--;
    i++;
  }
  for (i = 0; i < n; i++) {
    if (a[i] == '#' && k) { // For remaining # positions, choose a different character
      for (j = 'a'; j <= 'z'; j++) {
        if (s1[i] != j && s2[i] != j) {
          a[i] = j;
          break;
        }
      }
    }
  }
  t1 = 0, t2 = 0;
  for (i = 0; i < n; i++) {
    if (a[i] != s1[i])
      t1++; // Count differences from s1
    if (a[i] != s2[i])
      t2++; // Count differences from s2
  }
  if (t == t1 && t == t2) // Check if differences are exactly t
    cout << a;
  else
    cout << "-1";
  return 0;
}


// https://github.com/VaHiX/CodeForces/