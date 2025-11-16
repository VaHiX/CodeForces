// Problem: CF 1154 B - Make Them Equal
// https://codeforces.com/contest/1154/problem/B

/*
Code Purpose:
This program determines the minimum non-negative integer D such that by adding
or subtracting D from elements of a given sequence, all elements can be made
equal. The approach involves using a set to store unique values, then analyzing
the sorted unique values to determine if a valid D exists and what its value is.

Algorithms/Techniques:
- Use of std::set to store unique values from input
- Analyze the sorted unique values to determine D:
  - If only one unique value, D = 0
  - If two unique values, D = (diff)/2 if diff is even, else D = diff
  - If three unique values, check if they form an arithmetic sequence
  - If more than three unique values, impossible to equalize, return -1

Time Complexity: O(n log n) due to insertion into set and iteration
Space Complexity: O(n) for storing elements in set
*/

#include <set>
#include <stdio.h>

typedef long long int ll;
typedef unsigned long long int ull;
#define nl printf("\n");
#define N 550
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
  int n, m, x, y, z;
  sf(n);
  set<int> s; // Store unique values from input
  for (i = 0; i < n; i++)
    sf(m), s.insert(m); // Insert all values into set to get unique ones

  auto itr = s.begin(); // Iterator to traverse the set
  if (s.size() == 1)    // Only one unique element, no operations needed
    pf(0);
  else if (s.size() == 2) { // Two unique elements
    x = *itr;               // First smallest element
    itr++;
    y = *itr;        // Second smallest element
    if ((y - x) % 2) // If difference is odd, D = difference
      pf(y - x);
    else // If difference is even, D = difference/2
      pf((y - x) / 2);
  } else if (s.size() == 3) { // Three unique elements
    x = *itr;                 // First smallest
    itr++;
    y = *itr; // Middle
    itr++;
    z = *itr;           // Largest
    if (y - x == z - y) // Check if they form arithmetic progression
      pf(z - y);        // D = common difference
    else
      pf(-1); // Not possible to equalize
  } else
    pf(-1); // More than 3 unique elements, impossible

  return 0;
}

// https://github.com/VaHiX/CodeForces/