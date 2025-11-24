// Problem: CF 949 B - A Leapfrog in the Array
// https://codeforces.com/contest/949/problem/B

/*
 * Problem: B. A Leapfrog in the Array
 * 
 * Algorithm:
 * This problem requires determining the final position of elements in an array after a specific 
 * iterative process. Key insight is that the process simulates a binary tree traversal where 
 * elements move according to their indices and the rules of the leapfrog.
 * 
 * The algorithm uses a reverse simulation approach:
 * 1. For each query index x, we trace back the path that led to that position.
 * 2. If x is even, it means it was moved from a previous index, so we compute the previous index using x/2 + n.
 * 3. Continue this process until x becomes odd.
 * 4. Once x is odd, the result is (x + 1) / 2.
 * 
 * Time Complexity: O(log n) per query, since in the worst case we divide x by 2 repeatedly.
 * Space Complexity: O(1), only constant space is used.
 */

#include <cstdio>
typedef long long ll;
int main() {
  ll n, q;
  scanf("%lld %lld", &n, &q);
  while (q--) {
    ll x;
    scanf("%lld", &x);
    // While x is even, it means it was moved from another position, so we compute previous position
    while (x % 2 == 0) {
      x = x / 2 + n;
    }
    // Once x is odd, the result is (x + 1) / 2
    printf("%lld\n", (x + 1) / 2);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/