# Problem: CF 2063 A - Minimal Coprime
# https://codeforces.com/contest/2063/problem/A

# Flowerbox
"""
Problem: Count the number of minimal coprime segments in [l, r].
A segment [l, r] is coprime if gcd(l, r) == 1.
A coprime segment is minimal if it contains no other coprime segment inside it.
Algorithm:
- A segment [l, r] is minimal coprime if and only if l == r == 1 or l and r are coprime and
  there's no smaller coprime segment contained within.
- The key insight is that a segment [l, r] is minimal coprime if:
  - l == 1 and r == 1 (trivial case)
  - gcd(l, r) == 1 and for no k in [l+1, r-1], the segments [l,k] and [k,r] are both coprime.
- However, we can derive that the answer is:
  - If l == r == 1, result = 1
  - Otherwise, result is (number of coprime pairs in range) minus overlaps.
- Direct formula: (l == r == 1) + (r - l)
  - When l == r == 1 → 1
  - Otherwise, count of minimal segments = r - l
Time Complexity: O(1) per test case
Space Complexity: O(1)
"""

for s in [*open(0)][1:]:
    l, r = map(int, s.split())
    # If both l and r are 1, it's a single element segment that is coprime and minimal.
    # Otherwise, the number of minimal coprime segments equals r - l.
    print((l == r == 1) + r - l)


# https://github.com/VaHiX/codeForces/