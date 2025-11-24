// Problem: CF 1089 L - Lazyland
// https://codeforces.com/contest/1089/problem/L

/*
L. Lazyland
Algorithms/Techniques: Sorting, nth_element, Greedy
Time Complexity: O(n log n)
Space Complexity: O(n)

The kingdom of Lazyland has n idlers and k jobs. Each idler chooses a job,
and the king wants to assign all jobs to idlers by persuading some idlers
to switch jobs. The goal is to minimize the total persuasion time.

Approach:
1. For each idler, if their chosen job is not already assigned to someone else:
   store the persuasion cost in an array.
2. Use nth_element to find the k-th smallest element, which separates
   the minimal costs from the rest.
3. Sum up the first k elements (the minimum costs for persuasion).
*/
#include <algorithm>
#include <cstdio>
#include <utility>

const int N = 1e5 + 5;
int t[N], b[N], a[N];
int main() {
  int n, k, x, c = 0; // c counts persuasion costs
  long long s = 0;   // total time spent persuading
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i)
    scanf("%d", &a[i]); // read chosen jobs
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &x);   // read persuasion time for idler i
    if (x > t[a[i]])  // if current cost is greater than stored
      std::swap(x, t[a[i]]); // swap to keep the smaller cost in t[]
    if (x)             // if persuasion cost is not zero
      b[++c] = x;      // store this cost
  }
  // Find the k-th smallest value in the array of costs
  std::nth_element(b + 1, b + c - n + k, b + 1 + c);
  // Sum up all values before that k-th element (which are smallest)
  for (int i = 1; i <= c - n + k; ++i)
    s += b[i];
  printf("%lld\n", s); // Print minimimum total persuasion time
  return 0;
}


// https://github.com/VaHiX/codeForces/