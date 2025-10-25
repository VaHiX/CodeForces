// Problem: CF 2007 A - Dora's Set
// https://codeforces.com/contest/2007/problem/A

#include <cstdio>
// Problem: A. Dora's Set
// Description: Given a range [l, r], we need to find the maximum number of operations
// where each operation removes three distinct integers a, b, c such that gcd(a,b)=gcd(b,c)=gcd(a,c)=1.
// Algorithm: The key insight is that we can always pick numbers such that their pairwise GCDs are 1.
// The optimal strategy involves pairing up consecutive numbers to form valid triplets,
// which leads to the formula derived from the count of valid triplets in the range.
// Time Complexity: O(1) per test case
// Space Complexity: O(1)

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    // Formula to compute maximum operations:
    // ((b + 1) / 2 - (a / 2)) / 2
    // Explanation:
    // We count how many odd numbers are in the range [a, b] and then calculate
    // how many valid triplets we can form. This formula efficiently computes that.
    printf("%ld\n", ((b + 1) / 2 - (a / 2)) / 2);
  }
}


// https://github.com/VaHiX/codeForces/