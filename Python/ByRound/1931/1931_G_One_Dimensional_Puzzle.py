# Problem: CF 1931 G - One-Dimensional Puzzle
# https://codeforces.com/contest/1931/problem/G

"""
Code Purpose:
This code solves the problem of counting the number of ways to arrange puzzle pieces in a one-dimensional chain. 
Each piece has a left and right connection that must match adjacent pieces. There are four types of pieces, 
and the counts of each type are given. The solution uses combinatorics and dynamic programming principles, 
particularly involving factorials and modular arithmetic to handle large numbers.

Algorithms/Techniques:
- Precomputed factorials for efficient combination calculations
- Modular arithmetic for handling large results
- Case analysis based on relative counts of piece types

Time Complexity: O(n) where n is up to 2 * 10^6 (precomputed factorials)
Space Complexity: O(n) for storing precomputed factorials
"""

mod = 998244353
f = [1]
for i in range(1, 2 * 10**6 + 1):
    f.append(f[-1] * i % mod)
for _ in range(int(input())):
    a, b, c, d = map(int, input().split())
    if abs(a - b) > 1:
        print(0)
    elif a == b:
        if a == 0:
            print(int((c == 0) or (d == 0)))
        else:
            # Compute combinations using precomputed factorials
            result = (
                (f[a - 1 + c] * f[a + d] + f[a - 1 + d] * f[a + c])
                * pow(f[a - 1] * f[d] * f[a] * f[c], -1, mod)
                % mod
            )
            print(result)
    else:
        # Handle the case where a and b differ by 1
        a = max(a, b)
        result = (
            f[a - 1 + c]
            * f[a - 1 + d]
            * pow(f[a - 1] ** 2 * f[c] * f[d], -1, mod)
            % mod
        )
        print(result)


# https://github.com/VaHiX/CodeForces/