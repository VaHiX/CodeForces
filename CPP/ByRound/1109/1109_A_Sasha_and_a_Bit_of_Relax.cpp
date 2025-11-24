// Problem: CF 1109 A - Sasha and a Bit of Relax
// https://codeforces.com/contest/1109/problem/A

/*
 * Problem: A. Sasha and a Bit of Relax
 * Algorithms/Techniques: Prefix XOR, Hashing, Two-pointer technique
 * Time Complexity: O(n)
 * Space Complexity: O(2^20) = O(1) (since maxn is fixed at 2^20)
 *
 * The solution uses prefix XOR to efficiently compute XOR of subarrays.
 * For each even-length subarray, we split it into two halves and check
 * if their XORs are equal. This is equivalent to checking if the total
 * XOR of the entire subarray is 0. We use a hash map to count occurrences
 * of prefix XOR values to quickly find how many previous positions can form
 * a valid "funny" pair with the current position.
 */

#include <stdio.h>
#include <iosfwd>

#define maxn (1 << 20)
#define LL long long
using namespace std;
int n, f[maxn][2]; // f[x][i&1] stores count of prefix XORs equal to x ending at even/odd index
int main() {
  scanf("%d", &n);
  LL ans = 0;
  f[0][0]++; // Base case: prefix XOR 0 occurs once before array starts
  for (int i = 1, sum = 0; i <= n; i++) {
    int a;
    scanf("%d", &a);
    // Calculate prefix XOR up to current element
    ans += f[sum ^= a][i & 1]++; // Add count of previous prefixes that would make current subarray funny
  }
  printf("%I64d\n", ans);
}


// https://github.com/VaHiX/codeForces/