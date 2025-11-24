// Problem: CF 727 A - Transformation: from A to B
// https://codeforces.com/contest/727/problem/A

#include <cstdio>
#include <vector>
/*
 * Purpose: Transform number 'a' to 'b' using two operations:
 *          1. Multiply by 2 (x -> 2*x)
 *          2. Append 1 (x -> 10*x + 1)
 * 
 * Algorithm: DFS (Depth-First Search) with backtracking.
 *            Start from 'a', try both operations at each step,
 *            and backtrack if a path leads to a dead end.
 * 
 * Time Complexity: O(2^d) where d is the depth of the solution.
 *                  In worst case, we explore a binary tree up to the depth
 *                  needed to reach b from a. Since numbers are bounded,
 *                  this is manageable.
 * 
 * Space Complexity: O(d) for recursion stack depth, and O(d) for storing steps.
 *                   Thus overall space complexity is O(d).
 */
void dfs(std::vector<long long> &v, const long long target, bool &possible) {
  // Base case: if current value exceeds target or already found solution, stop
  if (v.empty() || possible || v.back() > target) {
    return;
  }
  // If reached target, mark as possible
  if (v.back() == target) {
    possible = true;
    return;
  }
  long long x = v.back();
  // Operation 1: multiply by 2
  v.push_back(2 * x);
  dfs(v, target, possible);
  // Backtrack if not successful
  if (possible) {
    return;
  } else {
    v.pop_back();
  }
  // Operation 2: append 1
  v.push_back(10 * x + 1);
  dfs(v, target, possible);
  // Backtrack if not successful
  if (possible) {
    return;
  } else {
    v.pop_back();
  }
  return;
}
int main() {
  long long a, b;
  scanf("%lld %lld", &a, &b);
  bool possible(0);
  std::vector<long long> steps;
  steps.push_back(a);
  dfs(steps, b, possible);
  if (possible) {
    puts("YES");
    printf("%ld\n", steps.size());
    for (int p = 0; p < steps.size(); p++) {
      printf("%lld ", steps[p]);
    }
    puts("");
  } else {
    puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/