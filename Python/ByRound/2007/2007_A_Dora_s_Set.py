# Problem: CF 2007 A - Dora's Set
# https://codeforces.com/contest/2007/problem/A

# Problem: Maximum number of operations on a set of integers [l, r]
# Algorithm: Mathematical approach to compute maximum operations
# Time Complexity: O(1) per test case
# Space Complexity: O(1)

for s in [*open(0)][1:]:
    l, r = map(int, s.split())
    # Key insight:
    # Each operation removes 3 integers from the set.
    # To maximize operations, we want to pick triples (a,b,c) such that gcd(a,b)=gcd(b,c)=gcd(a,c)=1.
    # We can observe that the maximum number of operations is approximately (r - l + 1) // 4,
    # but we must account for edge cases and parity considerations.
    # The formula r - l + l % 2 + 1 >> 2 computes this efficiently using bit shifting.
    print(r - l + l % 2 + 1 >> 2)


# https://github.com/VaHiX/codeForces/