// Problem: CF 1173 A - Nauuo and Votes
// https://codeforces.com/contest/1173/problem/A

/*
A. Nauuo and Votes
Problem Description:
Given x upvotes, y downvotes, and z unknown voters, determine if the final outcome is certain or uncertain.
The outcome depends on whether there are more upvotes, more downvotes, or an equal number of both.
If all possible combinations of z's votes lead to the same result, output that result; otherwise output "?".

Algorithms/Techniques:
- Brute force enumeration of all possible votes for z unknown persons (0 to z upvotes)
- For each scenario, compute the total upvotes and downvotes
- Store unique results in a set
- If only one result exists, output it; otherwise output "?"

Time Complexity: O(z), where z is the number of unknown voters
Space Complexity: O(1), since the set size is bounded by 3 (at most three distinct outcomes: '+', '-', '0')

*/
#include <stdio.h>
#include <iostream>
#include <set>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 200100
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
int a[N];
int main() {
  int i, j, k;
  int n, m, t;
  int x, y, z;
  set<char> s; // Set to store unique results
  sff(x, y); // Read x (upvotes) and y (downvotes)
  sf(z); // Read z (unknown voters)
  m = x - y - z; // Calculate difference between upvotes and downvotes if all unknown vote down
  for (i = 0; i <= z; i++) { // Iterate through all possible numbers of upvotes from unknown voters (0 to z)
    k = m + 2 * i; // Adjust the difference based on i upvotes from unknown voters
    if (k > 0) // If more upvotes than downvotes
      s.insert('+'); 
    else if (k == 0) // If equal upvotes and downvotes
      s.insert('0');
    else // If more downvotes than upvotes
      s.insert('-');
  }
  if (s.size() == 1) // If only one possible result
    cout << *s.begin(); // Output the result
  else
    cout << "?"; // Otherwise result is uncertain
  return 0;
}


// https://github.com/VaHiX/codeForces/