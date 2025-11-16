# Problem: CF 1764 D - Doremy's Pegging Game
# https://codeforces.com/contest/1764/problem/D

"""
Algorithm: Dynamic Programming + Combinatorics
Time Complexity: O(n^2)
Space Complexity: O(n)

This code computes the number of possible arrays 'a' that can be produced by removing
red pegs from a regular n-sided polygon such that the rubber band does not touch
the blue peg in the center. The process involves choosing a peg to remove at each
step, appending to array 'a', and continuing until the rubber band touches the blue peg.

The algorithm uses combinatorics and dynamic programming:
- Precompute factorials and inverse factorials for combinations
- Iterate over valid configurations and count valid removal sequences
- Use modular arithmetic throughout to handle large numbers
"""

n, p = map(int, input().split())
F = [1]
for i in range(n):
    F.append(F[-1] * (i + 1) % p)
I = [pow(F[-1], p - 2, p)]  # modular inverse of factorial
for i in range(n):
    I.append(I[-1] * (n - i) % p)
I = I[::-1]  # reverse to get inverse factorials for decreasing values
ans = 0
m = n // 2
for i in range(m - 1, 2 * (m - 1) + 1):
    if n - i == 2:
        ans = (ans + n * F[i]) % p
    else:
        for j in range(n - i - 2):
            ans = (
                ans
                + n
                * (min(m - 1, i) - max(i - m + 1, 0) + 1)
                * F[n - i - 3]
                * I[j]
                * I[n - i - j - 3]
                * F[i + j]
            ) % p
print(ans)


# https://github.com/VaHiX/CodeForces/