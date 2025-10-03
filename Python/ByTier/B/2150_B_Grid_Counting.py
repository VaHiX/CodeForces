# Problem: CF 2150 B - Grid Counting
# https://codeforces.com/contest/2150/problem/B

"""
B. Grid Counting

Approach:
This problem involves counting valid configurations of black cells in an n×n grid under specific constraints.

Key Observations:
- For each row k, exactly a_k cells must be black.
- Each "max(x_i, y_i) = k" value is unique for exactly one cell.
- Each "max(x_i, n+1-y_i) = k" value is unique for exactly one cell.
  
These constraints indicate that:
- The black cells form a pattern where we can think of them distributed in rows from top to bottom,
  such that for row i, a_i black cells are placed.
- The constraint on "max(x_i, y_i)" ensures that the rightmost black cell in each row is unique and increasing.
- The constraint on "max(x_i, n+1-y_i)" ensures similar for diagonal with respect to bottom-left to top-right.

This leads to a dynamic programming type solution where:
- We maintain how many cells are allowed (cur) to be placed at each level.
- At each row from the middle outwards, we calculate binomial coefficients for placing a_i black cells in available positions.
- If it's impossible (e.g., exceeding the number of available slots), return 0.

Time Complexity: O(n)
Space Complexity: O(n)

"""
import sys

input = sys.stdin.readline
MOD = 998_244_353
fact = [1]
factinv = [1]
for i in range(1, 220_000):
    fact.append((fact[-1] * i) % MOD)
for i in range(1, 220_000):
    factinv.append(pow(fact[i], -1, MOD)) # Precompute inverse factorials
for i in range(int(input())):
    n = int(input())
    l = list(map(int, input().split()))
    if sum(l) != n:  # If total black cells don't add up to n, invalid
        print(0)
        continue
    if sum(l[(n + 1) // 2 :]) > 0:  # If any row past the middle has black cells, invalid due to constraints
        print(0)
        continue
    res = 1
    cur = 1
    if n % 2 == 0:
        cur += 1
    flag = False
    for i in range((n - 1) // 2, 0, -1):  # Iterate from middle row down to first row
        if l[i] > cur:  # If more black cells than available slots, invalid
            flag = True
            break
        res = (res * fact[cur] * factinv[l[i]] * factinv[cur - l[i]]) % MOD  # Compute binomial coefficient C(cur, l[i])
        cur -= l[i]
        cur += 2  # Adjust the available slots for next row upwards
    if flag:
        print(0)
        continue
    print(res)


# https://github.com/VaHiX/CodeForces/