// Problem: CF 2038 A - Bonus Project
// https://codeforces.com/contest/2038/problem/A

/*
A. Bonus Project
time limit per test2 seconds
memory limit per test512 megabytes

Algorithms/Techniques: Greedy algorithm with backward iteration.

Time Complexity: O(n)
Space Complexity: O(n)

There is a team of n software engineers numbered from 1 to n. Their boss promises to give them a bonus if they complete an additional project. The project requires k units of work in total. The bonus promised to the i-th engineer is a_i burles. The boss doesn't assign specific tasks to engineers; it is expected that every engineer will voluntarily complete some integer amount of work units.

The amount of work that can be performed by each engineer is not limited. However, all engineers value their labour. The i-th engineer estimates one unit of their work as b_i burles. If the bonus is paid, the benefit s_i of the i-th engineer for completing c units of work is defined as s_i = a_i - c * b_i.

Engineers are eager to get the bonus, so they agreed on the following process:
- Each engineer in order says how much work they will do.
- Every engineer acts to maximize their own benefit.
- If total work is less than k, no one gets the bonus and all engineers contribute 0 work.

This greedy solution works by simulating reverse order of decision making:
1. We start from the last engineer and simulate how much work they can contribute
   without making the project impossible to complete under constraint of remaining k.
2. For each engineer from right to left, we decide how many units to contribute
   based on optimal benefit and remaining capacity.
3. Finally, we check if total contribution meets or exceeds k.

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  std::vector<long> b(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &b[p]);
  }
  std::vector<long> c(n, 0); // stores how much each engineer contributes
  long rem(k);               // remaining work units to be completed
  for (long p = n - 1; p >= 0; p--) {
    long w = a[p] / b[p];    // maximum possible units this engineer can do
                             // before their benefit becomes negative
    c[p] = (w < rem ? w : rem); // take min of what they can do or remaining work needed
    rem -= c[p];             // subtract from remaining work
  }
  for (long p = 0; p < n; p++) {
    printf("%ld ", rem ? 0 : c[p]); // output result only if bonus is paid
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/