// Problem: CF 1515 B - Phoenix and Puzzle
// https://codeforces.com/contest/1515/problem/B

/*
B. Phoenix and Puzzle
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Phoenix is playing with a new puzzle, which consists of n identical puzzle pieces. Each puzzle piece is a right isosceles triangle as shown below.

A puzzle piece

The goal of the puzzle is to create a square using the n pieces. He is allowed to rotate and move the pieces around, but none of them can overlap and all n pieces must be used (of course, the square shouldn't contain any holes as well). Can he do it?

Input
The input consists of multiple test cases. The first line contains an integer t (1 <= t <= 10^4) — the number of test cases.
The first line of each test case contains an integer n (1 <= n <= 10^9) — the number of puzzle pieces.

Output
For each test case, if Phoenix can create a square with the n puzzle pieces, print YES. Otherwise, print NO.

Example
Input

3
2
4
6

Output

YES
YES
NO

Note
For n=2, Phoenix can create a square like this:

For n=4, Phoenix can create a square like this:

For n=6, it is impossible for Phoenix to create a square.

Algorithm:
- Each triangle piece contributes to forming a square.
- To form a square using right isosceles triangles, we need to consider how many triangles can fit in a square.
- We observe that:
  - If n = 2k, we can arrange them as 2 triangles to make one square.
    This means a square of area k must be possible (i.e., k is a perfect square).
  - If n = 4k, where k is some integer, then we can arrange the pieces to form a larger square.
    So this means we need (n/4) to be a perfect square.
- Optimization: Precompute all square numbers up to 1e5 to speed up lookups.

Time Complexity: O(sqrt(max_n)) for preprocessing, O(1) per query
Space Complexity: O(sqrt(max_n)) for storing squares in set
*/

#include <cstdio>
#include <set>
typedef long long ll;

int main() {
  std::set<ll> s;  // Store all perfect squares up to 1e10 (since 1e5 squared is 1e10)
  for (ll p = 1; p < 1e5; p++) {  // Loop until sqrt(1e10) ~ 1e5
    s.insert(p * p);  // Insert perfect squares into set for fast lookup
  }
  
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    // Check if either:
    // 1. n is even and n/2 is a perfect square, OR
    // 2. n is divisible by 4 and n/4 is a perfect square
    puts(((n % 2 == 0 && s.count(n / 2)) || (n % 4 == 0 && s.count(n / 4)))
             ? "YES"
             : "NO");
  }
}


// https://github.com/VaHiX/codeForces/