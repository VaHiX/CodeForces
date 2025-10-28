// Problem: CF 1615 B - And It's Non-Zero
// https://codeforces.com/contest/1615/problem/B

/*
B. And It's Non-Zero
Algorithms/Techniques: Bit manipulation, binary search on answer, prefix sum technique
Time Complexity: O(B * t) where B = 30 (number of bits), t = number of test cases
Space Complexity: O(1)

The problem asks to find the minimum number of elements to delete from [l, r] such that 
the bitwise AND of remaining elements is non-zero. This is done by checking each bit position,
and finding how many numbers in [l, r] have that bit set. The minimum deletions required
is determined by the bit that has the maximum count of numbers with that bit unset.
*/
#include <cstdio>
long f(long num, long idx) {
  long pow = 1 << idx;                    // Calculate 2^idx
  long a = num / (2 * pow);               // Number of complete groups of size 2*pow
  long b = num % (2 * pow);               // Remainder after dividing by 2*pow
  long c = (b - pow + 1);                 // How many numbers in the partial group have the bit set
  return a * pow + (c > 0 ? c : 0);       // Return total count of numbers with bit idx set
}
int main() {
  const long B = 30;                      // Since max r is 2*10^5, we need at most 30 bits
  long t;
  scanf("%ld", &t);
  while (t--) {
    long left, right;
    scanf("%ld %ld", &left, &right);
    long cnt(0);
    for (long p = 0; p < B; p++) {
      long tmp = f(right, p) - f(left - 1, p); // Count of numbers in [left, right] with bit p set
      cnt = (cnt > tmp) ? cnt : tmp;           // Keep track of maximum such count
    }
    printf("%ld\n", (right - left + 1) - cnt); // Minimum deletions = total - max set bits
  }
}


// https://github.com/VaHiX/codeForces/