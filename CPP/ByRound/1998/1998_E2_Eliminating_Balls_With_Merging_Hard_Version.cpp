// Problem: CF 1998 E2 - Eliminating Balls With Merging (Hard Version)
// https://codeforces.com/contest/1998/problem/E2

/*
Algorithm: Using Union-Find (Disjoint Set Union) with a stack-based approach to simulate the merging process.
Techniques:
  - Union-Find with path compression and union by size for efficient merging.
  - Stack-based approach to maintain a monotonic structure and efficiently determine valid merges.
  - Preprocessing with prefix sums to quickly compute subarray sums.

Time Complexity: O(n α(n)) where α(n) is the inverse Ackermann function, nearly constant in practice.
Space Complexity: O(n) for storing arrays and auxiliary data structures.

Problem:
For each prefix of the array, determine how many starting indices can result in a single element after all possible merging operations.
*/

#include <stdint.h>
#include <iostream>
#include <utility>

using std::cin;
using std::cout;
using ll = long long;
using ull = unsigned long long;
using pii = std::pair<int, int>;
const char endl = '\n';
const int N = 2E5 + 193;
int ancestor[N], sz[N]; // Union-Find data structure
int find(const int &x) {
  if (x == ancestor[x])
    return x;
  return ancestor[x] = find(ancestor[x]); // Path compression
}
void merge(int x, int y) {
  x = find(x), y = find(y);
  if (x == y)
    return;
  ancestor[x] = y;
  sz[y] += sz[x]; // Union by size
}
int a[N], n, x;
ll sum[N]; // Prefix sums for quick subarray sum computation
int son[N][2], root; // Tree structure to represent the monotonic stack
int stack[N], size_stack; // Stack to maintain monotonic property
int ans[N]; // Result array for f(i) values

void solve() {
  cin >> n >> x;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    sum[i] = sum[i - 1] + a[i]; // Build prefix sums
    ancestor[i] = i;
    sz[i] = 1;
    son[i][0] = son[i][1] = 0; // Initialize tree children
  }
  size_stack = 0;
  for (int i = 1; i <= n; ++i) {
    int top = size_stack;
    // Pop elements from stack while they are smaller than current element
    while (top and a[stack[top]] < a[i])
      top--;
    son[stack[top]][1] = i; // Connect right child
    son[i][0] = stack[size_stack = top + 1]; // Connect left child
    stack[size_stack] = i; // Push current index to stack
    
    // Check if merge is possible with previous element (left child)
    if (son[i][0] and sum[i - 1] - sum[stack[top]] >= a[i])
      merge(son[i][0], i);
      
    int f = find(stack[1]), u = son[f][1]; // Start with the head of the stack
    // Traverse the chain of nodes and merge if possible
    while (u) {
      if (sum[i] - sum[f] >= a[f])
        merge(f, u);
      f = find(u), u = son[f][1]; // Move to next node
    }
    ans[i] = sz[find(stack[1])]; // Number of elements in the root set
  }
  for (int i = x; i <= n; ++i)
    cout << ans[i] << " \n"[i == n]; // Output the result
}
int32_t main() {
#ifdef _DEBUG
  auto start_time = clock();
#else
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
#endif
  int tc = 1;
  cin >> tc;
  while (tc--)
    solve();
#ifdef _DEBUG
  cout << std::endl;
  cout << "Time used: " << clock() - start_time << "ms" << std::endl;
  system("pause");
  return 0;
#endif
}


// https://github.com/VaHiX/CodeForces/