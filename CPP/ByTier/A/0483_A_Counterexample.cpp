// Problem: CF 483 A - Counterexample 
// https://codeforces.com/contest/483/problem/A

/*
 * Problem: Find three distinct numbers (a, b, c) such that:
 *   - (a, b) are coprime
 *   - (b, c) are coprime
 *   - (a, c) are NOT coprime
 *   - l <= a < b < c <= r
 * 
 * Algorithm:
 *   - If l is even and there are at least 3 numbers in range (r - l >= 2):
 *       Try a = l, b = l + 1, c = l + 2. These will be coprime in pairs but (a,c) not coprime.
 *   - If l is odd and there are at least 4 numbers in range (r - l >= 3):
 *       Try a = l + 1, b = l + 2, c = l + 3.
 *   - Otherwise, no such triple exists.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */
#include <cstdio>
int main() {
  long long l, r;
  scanf("%lld %lld\n", &l, &r);
  if (l % 2 == 0 && (r - l) >= 2) {
    // If l is even, we can pick l, l+1, l+2:
    //   - (l, l+1) are coprime since consecutive integers are always coprime
    //   - (l+1, l+2) are coprime for same reason
    //   - (l, l+2) are NOT coprime if l is even (both divisible by 2)
    printf("%lld %lld %lld\n", l, l + 1, l + 2);
  } else if (l % 2 == 1 && (r - l) >= 3) {
    // If l is odd, check if we have at least 4 numbers:
    //   - Try l+1, l+2, l+3
    //   - (l+1, l+2) and (l+2, l+3) are consecutive so coprime
    //   - (l+1, l+3) may be coprime, but it's a valid case when l+1 and l+3 share common factor 2 if l is odd
    //   However, the specific construction here works under constraints
    printf("%lld %lld %lld\n", l + 1, l + 2, l + 3);
  } else {
    puts("-1");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/