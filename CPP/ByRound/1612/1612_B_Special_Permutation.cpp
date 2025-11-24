// Problem: CF 1612 B - Special Permutation
// https://codeforces.com/contest/1612/problem/B

/*
Code Purpose:
This program generates a permutation of length n such that:
- The minimum element in the left half equals 'a'
- The maximum element in the right half equals 'b'
It uses a greedy approach to construct the permutation and checks the constraints at the end.

Algorithms/Techniques:
- Greedy construction of permutation
- Linear scan to verify constraints

Time Complexity: O(n)
- The construction loop runs in O(n) time.
- The verification steps also take O(n) time.
- Overall: O(n) for each test case.

Space Complexity: O(n)
- A vector of size n is used to store the result permutation.
- Additional variables use constant space.
- Overall: O(n) for each test case.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b;
    scanf("%ld %ld %ld", &n, &a, &b);
    std::vector<long> res(n, -1);
    res[0] = a;  // Place 'a' at the start to ensure it's the minimum in the left half
    res[n - 1] = b;  // Place 'b' at the end to ensure it's the maximum in the right half
    long cur = n;  // Start filling from the largest unused number
    for (long p = 1; p < n - 1; p++) {
      while (cur == a || cur == b) {
        cur--;  // Skip 'a' and 'b' to avoid conflicts with their required positions
      }
      res[p] = cur--;  // Assign current largest unused number
    }
    long mn(n + 1), mx(-1);
    for (long p = 0; p < n / 2; p++) {
      mn = (mn < res[p] ? mn : res[p]);  // Find minimum in the left half
    }
    for (long p = n / 2; p < n; p++) {
      mx = (mx > res[p] ? mx : res[p]);  // Find maximum in the right half
    }
    if (mn != a || mx != b) {
      puts("-1");  // If constraints not satisfied, output -1
      continue;
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", res[p]);
    };
    puts("");  // Print the resulting permutation
  }
}


// https://github.com/VaHiX/CodeForces/