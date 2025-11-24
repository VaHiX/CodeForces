# Problem: CF 1862 D - Ice Cream Balls
# https://codeforces.com/contest/1862/problem/D

"""
Ice Cream Balls Problem
Algorithm: Mathematical approach to find minimum number of balls to form exactly n different 2-ball ice cream combinations.
Techniques: Binary search or direct formula derivation using quadratic equation.
Time Complexity: O(1) per test case
Space Complexity: O(1) excluding output storage

The problem is about determining the minimum number of distinct ball types needed
to create exactly n unique pairs (combinations of 2 balls). This reduces to solving:
C(x, 2) >= n  where C(x, 2) = x*(x-1)/2
We need to find smallest x such that x*(x-1)/2 >= n
This can be solved using quadratic formula and adjustment.
"""

tm = int(input())
ans = [""] * tm
for t in range(tm):
    n = int(input())
    if n <= 1:
        ans[t] = "2"
        continue
    # Estimate x using quadratic formula: x = sqrt(2*n + 0.25) - 0.5
    res = int((2 * n + 0.25) ** 0.5 + 0.500001)
    # Adjust if our estimate is too large
    if n - res * (res - 1) // 2 < 0:
        res -= 1
    # Ensure we have sufficient number of balls to form exactly n combinations
    res += n - res * (res - 1) // 2
    ans[t] = str(res)
print("\n".join(ans))


# https://github.com/VaHiX/CodeForces/