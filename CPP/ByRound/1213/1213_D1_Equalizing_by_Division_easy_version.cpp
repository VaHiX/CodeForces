// Problem: CF 1213 D1 - Equalizing by Division (easy version)
// https://codeforces.com/contest/1213/problem/D1

/*
Equalizing by Division (easy version)
Algorithms/Techniques: Hash map + sorting + greedy
Time Complexity: O(n * log(max(a)) * log(n))
Space Complexity: O(n * log(max(a)))

The problem asks to find the minimum number of operations required to make at least k elements equal in the array.
Each operation allows us to divide an element by 2 (integer division) any number of times.
We use a map to store all possible values that each element can reach through divisions,
along with how many steps (operations) it takes to get there.
Then for each unique value, we check if there are at least k elements that can reach it.
Among those, we compute the minimum sum of operations.

Key insight:
- For any number x, all its ancestors in the binary tree (by dividing by 2) are reachable,
  and the path length corresponds to number of operations.
- We track these paths using a map where key is value reached and value is list of steps needed.
- Finally, for each value that has at least k occurrences, we select top k smallest steps and sum them.
*/

#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <utility>

int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::map<long, std::vector<long>> m;  // Map to store value -> list of operations needed
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    long cnt(0);  // Number of operations to reach current value
    while (x) {
      m[x].push_back(cnt);  // Store number of operations needed to reach x
      ++cnt;
      x /= 2;  // Move up in the binary tree (divide by 2)
    }
    m[0].push_back(cnt);  // Add 0 as a possible value reached after all divisions
  }
  long res(100 * n);  // Initialize with large enough value for minimum
  for (std::map<long, std::vector<long>>::iterator it = m.begin();
       it != m.end(); it++) {
    std::vector<long> v = it->second;  // Get the list of operations needed to reach this value
    if (v.size() < k) {
      continue;  // Not enough elements to form a group
    }
    sort(v.begin(), v.end());  // Sort to get smallest operations first
    long s(0);
    for (long p = 0; p < k; p++) {
      s += v[p];  // Sum up k smallest operations
    }
    res = (res < s) ? res : s;  // Keep track of minimum total operations
  }
  printf("%ld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/