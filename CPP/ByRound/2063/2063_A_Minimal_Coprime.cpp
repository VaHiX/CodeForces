// Problem: CF 2063 A - Minimal Coprime
// https://codeforces.com/contest/2063/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b;
    scanf("%ld %ld", &a, &b);
    // The formula computes the number of minimal coprime segments in [a, b]
    // A minimal coprime segment is a segment [l,r] where l and r are coprime
    // and no proper subsegment [l',r'] with l' < l and r' > r is also coprime.
    // This count equals the number of pairs (l, r) such that gcd(l, r) = 1,
    // and there is no smaller interval [l', r'] contained in [a,b] satisfying this condition.
    // Simplifying it, it's equivalent to counting all coprime pairs (l,r) such that a <= l < r <= b,
    // but only those where l=r or adjacent numbers are considered. But the actual formula can be derived:
    // If we consider only intervals [l,l] where l is coprime with itself (always true),
    // and other cases such as [l, l+1] which are always coprime except when both are even.
    // For interval [a,b], the count of minimal coprime segments equals b - a + (a == b && a == 1).
    // This accounts: all segments from 'a' to 'b', plus one extra if it's exactly [1,1].
    printf("%ld\n", b - a + (a == b && a == 1));
  }
}


// https://github.com/VaHiX/codeForces/