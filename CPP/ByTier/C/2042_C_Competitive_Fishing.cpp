// Problem: CF 2042 C - Competitive Fishing
// https://codeforces.com/contest/2042/problem/C

/*
C. Competitive Fishing
Algorithms/Techniques: Greedy + Sorting + Prefix Sum
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing prefix sums

The problem asks to find the minimum number of groups such that Bob's score exceeds Alice's by at least k.
We process the fish in order, track contribution of each fish to the difference in scores when we consider grouping,
and then greedily select the best groups to maximize the difference.
*/

#include <stdio.h>
#include <algorithm>

#define ll long long
using namespace std;

const int N = 200010;
int t, n, c[N];
char a[N];
ll k;

int main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d%lld%s", &n, &k, a + 1);
    c[n + 1] = 0; // Initialize suffix array to 0
    for (int i = n; i >= 2; i--)
      if (a[i] == '0') // If fish caught by Alice
        c[i] = c[i + 1] - 1; // Subtract 1 from cumulative sum
      else
        c[i] = c[i + 1] + 1; // Add 1 to cumulative sum (Bob's contribution)
    
    sort(c + 2, c + n + 1); // Sort the contributions (excluding first element)

    ll sum = 0;
    int ans = 1;
    for (int i = n; i >= 2; i--)
      if (sum < k) {
        sum += c[i]; // Greedily add largest contribution
        ans++;
      } else
        break;

    if (sum < k)
      puts("-1"); // Not enough to achieve required difference
    else
      printf("%d\n", ans);
  }
}


// https://github.com/VaHiX/codeForces/