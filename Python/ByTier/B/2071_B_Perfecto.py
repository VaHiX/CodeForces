# Problem: CF 2071 B - Perfecto
# https://codeforces.com/contest/2071/problem/B

"""
B. Perfecto

Purpose:
This code attempts to construct a "perfect" permutation of length n, where the prefix sum at each position is not a perfect square.
The algorithm uses a precomputed list of perfect squares and swaps elements in a way that avoids creating perfect square sums.

Algorithms/Techniques:
- Generates a base permutation [1, 2, ..., n]
- Swaps specific indices based on known problematic values (perfect squares)
- Uses a lookup table of known problematic values to avoid generating perfect square prefix sums

Time Complexity:
O(n) for each test case, as we perform a fixed number of operations per input.

Space Complexity:
O(n) due to the storage of the list L and constant space for other variables.
"""

t = int(input())
lol = [1, 8, 49, 288, 1681, 9800, 57121, 332928, 1940449]  # Precomputed values that cause issues
for i in range(t):
    n = int(input())
    if n in lol:
        print(-1)
        continue
    L = [i for i in range(1, n + 1)]  # Create base permutation: [1, 2, ..., n]
    for i in lol:
        if i < n:
            # Swap elements at positions i-1 and i to prevent perfect square prefix sums
            L[i - 1], L[i] = L[i], L[i - 1]
    ans = " ".join(map(str, L))
    print(ans)


# https://github.com/VaHiX/codeForces/