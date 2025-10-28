// Problem: CF 1144 D - Equalize Them All
// https://codeforces.com/contest/1144/problem/D

/*
D. Equalize Them All
Algorithms/Techniques: Greedy, Simulation
Time Complexity: O(n)
Space Complexity: O(n)

The approach is as follows:
1. Find the most frequent element in the array (target).
2. Use greedy strategy to move all other elements towards this target.
3. For each element not equal to target:
   - If it's smaller than target, push it right.
   - If it's larger than target, push it left.
4. The operations are simulated using adjacent swaps with appropriate weights.

The key insight is that we only need to move elements toward the most frequent value,
since this minimizes total operations required among all possible targets.
*/

#include <cstdio>
#include <map>
#include <vector>
struct action {
  long w, from, to;
};
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  std::map<long, long> cm; // Count frequency of each element
  long target(0), pos(-1), mx(-1); // target = most frequent value, pos = its position
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
    ++cm[a[p]];
    if (cm[a[p]] > mx) { // Update maximum frequency and corresponding element
      mx = cm[a[p]];
      target = a[p];
      pos = p;
    }
  }
  std::vector<action> res; // Store sequence of operations
  for (long p = pos + 1; p < n; p++) {
    if (a[p] == target) { // Skip if already target
      continue;
    }
    action x;
    x.w = 1 + (a[p] > target); // Weighted operation: 1 for equal, 2 if larger
    x.from = p;  // Operation from index p
    x.to = p + 1; // Operation to next index
    res.push_back(x);
  }
  for (long p = pos - 1; p >= 0; p--) {
    if (a[p] == target) { // Skip if already target
      continue;
    }
    action x;
    x.w = 1 + (a[p] > target); // Weighted operation: 1 for equal, 2 if larger
    x.from = p + 2;  // Operation from index p+2 (to align with leftward moves)
    x.to = p + 1;   // Operation to current index
    res.push_back(x);
  }
  printf("%ld\n", res.size());
  for (long p = 0; p < res.size(); p++) {
    printf("%ld %ld %ld\n", res[p].w, res[p].to, res[p].from); // Print operations in required format
  }
  puts("");
  return 0;
}


// https://github.com/VaHiX/codeForces/