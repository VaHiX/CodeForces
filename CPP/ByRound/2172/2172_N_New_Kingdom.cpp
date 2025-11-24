// Problem: CF 2172 N - New Kingdom
// https://codeforces.com/contest/2172/problem/N

// # Island Cartographer: Penultimate Chapter Solution
// ## Algorithm
// This problem involves constructing a connected graph with specific
// properties:
// 1. All edges connect two different vertices (simple graph)
// 2. The graph is connected
// 3. Exactly k vertices have odd degree
// 4. Exactly b edges are vital (bridge edges)

// The solution approach:
// - Handle special cases like n=1, n=2
// - For general cases, construct a star graph with additional edges to satisfy
// the constraints
// - Use careful edge placement to ensure:
//   - The number of vertices with odd degree equals k
//   - The number of bridges equals b
// - Time complexity: O(n) per test case
// - Space complexity: O(n) for storing the edges

#include <algorithm>
#include <stdio.h>
#include <utility>
#include <vector>

#define int long long
#define db long double
#define mp(a, b) make_pair(a, b)
#define lowbit(x) (x & -x)
using namespace std;
int T, n, b, c;
vector<pair<int, int>> ans;
signed main() {
  scanf("%lld", &T);
  while (T--) {
    scanf("%lld%lld%lld", &n, &c, &b);
    // Check if k (number of odd degree vertices) is odd - impossible in any
    // graph
    if (c & 1) {
      puts("No");
      continue;
    }
    // Check if we have too many bridges - impossible to create more than n-1
    // bridges
    if (b + 1 == n - 1) {
      puts("No");
      continue;
    }
    // Special case: k = 0
    if (c == 0) {
      if (b == 0) {
        if (n == 1)
          puts("Yes\n0");
        else if (n == 2)
          puts("No");
        else {
          puts("Yes");
          printf("%lld\n", n);
          for (int i = 1; i <= n; i++)
            printf("%lld %lld\n", i, i % n + 1);
        }
      } else {
        puts("No");
      }
      continue;
    }
    // Special case: b = 0 (no bridges)
    if (b == 0) {
      if (n == 3) {
        if (c == 0) {
        } else
          puts("No");
      } else {
        ans.clear();
        // Create a cycle first
        for (int i = 1; i <= n; i++)
          ans.push_back(mp(i, i % n + 1));
        // Add additional edges to make odd degrees
        int l = 1, r = n / 2 + 1;
        while (c) {
          ans.push_back(mp(l, r));
          l++, r++;
          c -= 2;
        }
        puts("Yes");
        printf("%lld\n", (int)ans.size());
        for (auto x : ans)
          printf("%lld %lld\n", x.first, x.second);
      }
      continue;
    }
    // Special case: n = 2
    if (n == 2) {
      if (c == 2 && b == 1) {
        puts("Yes\n1\n1 2");
      } else
        puts("No");
      continue;
    }
    ans.clear();
    // General case
    if (b + 1 > c) {
      // Create a star graph with b+1 leaves
      for (int i = 2; i <= c + 1; i++)
        ans.push_back(mp(1, i));
      // Add bridges in the middle of the star
      for (int i = c + 1; i < b + 1; i++)
        ans.push_back(mp(i, i + 1));
      // Connect remaining nodes to the star
      if (b + 2 <= n) {
        ans.push_back(mp(1, b + 2));
        ans.push_back(mp(1, n));
        for (int i = b + 2; i < n; i++)
          ans.push_back(mp(i, i + 1));
      }
    } else if (b + 1 == c) {
      // Exactly one star with b+1 edges
      for (int i = 2; i <= c; i++)
        ans.push_back(mp(1, i));
      // Connect other nodes
      if (c + 1 <= n) {
        ans.push_back(mp(1, c + 1));
        ans.push_back(mp(1, n));
        for (int i = c + 1; i < n; i++)
          ans.push_back(mp(i, i + 1));
      }
    } else {
      // When b+1 < c, we need to build more edges to get required odd degrees
      if (b == n - 3) {
        // Special case for this constraint
        if (n == 4) {
          puts("No");
          continue;
        }
        for (int i = 2; i <= b - 1; i++)
          ans.push_back(mp(1, i));
        ans.push_back(mp(1, b + 2));
        ans.push_back(mp(1, n));
        for (int i = b + 2; i < n; i++)
          ans.push_back(mp(i, i + 1));
        ans.push_back(mp(b, b + 2));
        ans.push_back(mp(b + 1, n));
      } else {
        // General case: build star and additional edges
        for (int i = 2; i <= b + 1; i++)
          ans.push_back(mp(1, i));
        ans.push_back(mp(1, b + 2));
        ans.push_back(mp(1, n));
        for (int i = b + 2; i < n; i++)
          ans.push_back(mp(i, i + 1));
        c -= b;
        if (b & 1)
          c--;
        int sp = n - (b + 2) + 1;
        vector<pair<int, int>> pp;
        if (sp & 1) {
          int l = b + 2, r = l + (sp + 1) / 2;
          if (b % 2 == 0)
            pp.push_back(mp(1, l + (sp / 2)));
          for (; r <= n; l++, r++)
            pp.push_back(mp(l, r));
        } else {
          int l = b + 2, r = l + sp / 2;
          for (; r <= n; l++, r++)
            pp.push_back(mp(l, r));
        }
        // Add remaining edges to adjust degrees
        while (c) {
          ans.push_back(pp.back());
          pp.pop_back();
          c -= 2;
        }
      }
    }
    puts("Yes");
    printf("%lld\n", (int)ans.size());
    for (auto x : ans)
      printf("%lld %lld\n", x.first, x.second);
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/