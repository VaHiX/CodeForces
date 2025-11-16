# Problem: CF 806 A - Success Rate
# https://codeforces.com/contest/806/problem/A

"""
Problem: Success Rate

Algorithm/Technique: Mathematical reasoning and greedy approach
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem is to find the minimum number of submissions to make so that the success rate becomes exactly p/q.
We need to find the smallest k such that (x + a) / (y + k) = p / q, where a is the number of successful submissions,
and k - a is the number of unsuccessful submissions.

The key insight is to determine how many total submissions (k*q) we need such that:
(x + a) / (y + k) = p / q

Rearranging:
(x + a) * q = p * (y + k)
x*q + a*q = p*y + p*k
a*q - p*k = p*y - x*q

We solve for the minimal k such that the fraction (x + a) / (y + k) = p/q.

The approach is to compute the minimum k using mathematical derivation:
- We calculate k = max((x + p - 1) // p, (y - x + q - p - 1) // (q - p))
- Then result = k * q - y

This ensures that:
1. x + a is a multiple of p
2. y + k is a multiple of q
3. The ratio remains p/q

Special cases:
- If p == 0, then x must also be 0
- If q == p, then y must be equal to x
"""

t = int(input())

for test_id in range(t):
    x, y, p, q = map(int, input().split())

    if p == 0:
        if x == 0:
            print(0)
        else:
            print(-1)
        continue
    if q - p == 0:
        if y - x == 0:
            print(0)
        else:
            print(-1)
        continue
    k = max((x + p - 1) // p, (y - x + q - p - 1) // (q - p))
    print(k * q - y)


# https://github.com/VaHiX/CodeForces/