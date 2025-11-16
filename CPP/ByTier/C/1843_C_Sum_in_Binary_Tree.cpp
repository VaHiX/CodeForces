// Problem: CF 1843 C - Sum in Binary Tree
// https://codeforces.com/contest/1843/problem/C

/*
C. Sum in Binary Tree
Algorithms/Techniques: Path traversal in a binary tree where each node has two children,
and nodes are numbered sequentially by layers. To find the sum of the path from root (1)
to node n, we trace the path backwards by repeatedly dividing n by 2 to find its parent,
adding each node value to the result.

Time Complexity: O(log n) per test case, as we divide n by 2 in each iteration until n becomes 0.
Space Complexity: O(1), only using a constant amount of extra space.

Input:
- t: number of test cases
- For each test case: n (vertex number)

Output:
- Sum of vertex numbers on path from root to node n
*/

#include <cstdio>
typedef long long ll;

int main() {
  long t; // number of test cases
  scanf("%ld", &t);
  while (t--) {
    ll n; // current vertex number
    scanf("%lld", &n);
    ll res(0); // accumulate the sum of path
    while (n) {
      res += n; // add current node to sum
      n /= 2;   // move to parent node (binary tree property)
    }
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/