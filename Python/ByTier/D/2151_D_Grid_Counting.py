# Problem: CF 2151 D - Grid Counting
# https://codeforces.com/contest/2151/problem/D

"""
D. Grid Counting
Algorithms/Techniques: Dynamic Programming with Combinatorics, Preprocessing Factorials and Modular Inverses

Time Complexity: O(n) per test case (preprocessing factorials + constant time per query)
Space Complexity: O(n) for storing factorials and inverse factorials

The problem asks us to count the number of valid ways to color cells in an n×n grid such that:
- Each row k has exactly a[k] black cells.
- There exists exactly one cell (xi, yi) in each row where max(xi, yi) = k.
- There exists exactly one cell (xi, yi) in each row where max(xi, n+1-yi) = k.

This is solved using dynamic programming and combinatorics to count valid placements,
where we simulate the process of placing black cells row by row, ensuring constraints
are satisfied at each step. The use of precomputed factorials and modular inverses is for
efficient binomial coefficient computation.

"""

nt = int(input())
M = 998_244_353
f = [1] * 200_033
for i in range(1, 200_033):
    f[i] = (i * f[i - 1]) % M
fi = [pow(x, -1, M) for x in f]  # Precompute modular inverses of factorials

for _ in range(nt):
    n = int(input())
    xs = [int(i) for i in input().split()]
    
    if xs[0] < 2:
        print(0)
        continue
    if sum(xs) != n:
        print(0)
        continue
    if sum(xs[(n - 1) // 2 + 1 :]) != 0:
        print(0)
        continue

    ans = 1
    r = 2 if n % 2 == 0 else 1  # Starting "available slots" for placement
    for i in range(((n - 1) // 2), -1, -1):
        if xs[i] > r:
            # Impossible to place more black cells than available positions
            ans *= 0
        else:
            # Compute binomial coefficient C(r, xs[i]) mod M and update answer
            ans *= (f[r] * fi[xs[i]] * fi[r - xs[i]]) % M
            ans = ans % M
        r += 2 - xs[i]  # Update number of available slots for next iteration
    
    print(ans)


# https://github.com/VaHiX/CodeForces/