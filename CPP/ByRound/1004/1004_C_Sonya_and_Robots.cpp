// Problem: CF 1004 C - Sonya and Robots
// https://codeforces.com/contest/1004/problem/C

/*
Code Purpose:
This code solves the problem of finding the number of valid pairs of numbers (p, q) that can be given to two robots such that they will not meet when moving towards each other. The robots read numbers from a row and stop at the first occurrence of their assigned number. To avoid meeting, the stopping positions must be different.

Approach:
1. For each unique number in the array, we track how many unique numbers appeared before it (using ans array).
2. For each number from 1 to 100000, sum up the number of unique numbers that appeared before it.
3. This sum gives us the total number of valid pairs where the first robot's number occurs before the second robot's number in the array.

Time Complexity: O(n + max_a), where n is the size of input array and max_a is the maximum value in the array (100000).
Space Complexity: O(max_a), for the arrays vis and ans.

Algorithms/Techniques:
- Preprocessing to count unique occurrences
- Prefix counting
- Iteration through unique values to compute total pairs
*/

#include <stdio.h>
#include <iosfwd>
#include <iosfwd>

using namespace std;
const int maxn = 500005;
int n, m, T, tot;
long long res;
int a[maxn], ans[maxn], vis[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    // Store the count of unique numbers seen so far for number a[i]
    ans[a[i]] = tot;
    // If this number hasn't been seen before, increment total unique count
    if (vis[a[i]] == 0)
      tot++;
    // Mark this number as seen
    vis[a[i]] = 1;
  }
  // For each possible number (from 1 to 100000), accumulate the count of unique numbers
  // that appeared before it in the input array. This represents valid starting pairs
  for (int i = 1; i <= 100000; i++)
    res += ans[i];
  printf("%lld\n", res);
  return 0;
}


// https://github.com/VaHiX/CodeForces/