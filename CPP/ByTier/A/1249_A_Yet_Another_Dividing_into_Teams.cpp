// Problem: CF 1249 A - Yet Another Dividing into Teams
// https://codeforces.com/contest/1249/problem/A

/*
Problem: Yet Another Dividing into Teams
Purpose: Given n students with distinct programming skills, divide them into minimum number of teams such that no two students with skills differing by exactly 1 are in the same team.

Algorithm:
- Sort the array of skills.
- Separate elements into two groups based on even and odd indices after sorting.
- For each element in the second group (odd indices), check if it differs by more than 1 from all elements in the first group (even indices).
- If all elements in second group satisfy this condition, we need only 1 team; else, we need 2 teams.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the two vectors

Techniques:
- Greedy approach with sorting
- Two-pointer like logic using vector iteration
*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 110
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
  sf(t);
  while (t--) {
    sf(n);
    int a[n];
    for (i = 0; i < n; i++)
      sf(a[i]);
    sort(a, a + n); // Sort the array to facilitate grouping
    vector<int> vec, vec2; // vec has elements at even indices, vec2 has elements at odd indices
    for (i = 0; i < n; i += 2) // Collect elements at even indices into vec
      vec.pb(a[i]);
    for (i = 1; i < n; i += 2) // Collect elements at odd indices into vec2
      vec2.pb(a[i]);
    int cnt = 0, cnt2 = 0;
    for (int e : vec2) { // For each element in vec2
      cnt = 0;
      for (i = 0; i < vec.size(); i++) {
        if (abs(e - vec[i]) > 1) // If difference is greater than 1, increment counter
          cnt++;
      }
      if (cnt == vec.size()) // If all differences are greater than 1, this element can go to same team as vec elements
        cnt2++;             // Increment count of such valid elements
    }
    if (cnt2 == vec2.size()) // If all elements in vec2 can be paired with vec without difference 1
      pf(1);                // Only 1 team needed
    else
      pf(2);                // Otherwise, 2 teams required
    nl;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/