// Problem: CF 2119 B - Line Segments
// https://codeforces.com/contest/2119/problem/B

/*
B. Line Segments
time limit per test1.5 seconds
memory limit per test256 megabytes

Algorithm/Technique: Geometry, Sorting, Greedy
Time Complexity: O(n log n) per test case due to sorting, where n is the number of operations.
Space Complexity: O(n) for storing the distances in a vector.

Problem Summary:
You are given two points (sx, sy) and (tx, ty), and a sequence of n distances.
Starting from (sx, sy), you must move exactly n times such that each step moves
exactly a[i] units (Euclidean distance). Determine whether it is possible to reach (tx, ty).

Key Insight:
The problem reduces to checking if the sum of all steps can cover or match 
the direct Euclidean distance from start to end.
We use sorting and greedy approach to find the minimal required total distance
by considering that we can choose any intermediate points but must obey step constraints.

Approach:
1. Compute the straight-line distance from (sx, sy) to (tx, ty).
2. Add this distance to the list of available steps, so now we have n+1 elements.
3. Sort all distances in ascending order.
4. Take the largest element (which must be used), subtract all smaller steps,
   and check if remaining distance is non-positive. If yes, then it's possible.

Sample Input:
5
2
1 1 5 1
3 3
3
1 1 3 3
2 3 4
2
100 100 100 100
4 5
1
5 1 1 4
5
2
10000000 10000000 10000000 10000000
10000 10000

Sample Output:
Yes
Yes
No
Yes
Yes
*/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll sx, sy, tx, ty;
    scanf("%lld %lld %lld %lld", &sx, &sy, &tx, &ty);
    std::vector<double> a(n + 1); // Store distances including the final straight-line distance
    for (ll p = 0; p < n; p++) {
      scanf("%lf", &a[p]); // Read the step distances
    }
    a[n] = sqrt((sx - tx) * (sx - tx) + (sy - ty) * (sy - ty)); // Compute straight-line distance from start to finish
    sort(a.begin(), a.end()); // Sort distances in ascending order for greedy selection
    double s(a.back()); // Start with the largest distance, which must be covered
    for (ll p = 0; p < n; p++) {
      s -= a[p]; // Subtract all shorter steps from the longest needed one
    }
    puts(s > 0 ? "No" : "Yes"); // If remaining distance is positive, it's not possible to reach target
  }
}


// https://github.com/VaHiX/codeForces/