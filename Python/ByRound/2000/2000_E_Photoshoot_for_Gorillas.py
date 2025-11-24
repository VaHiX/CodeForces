# Problem: CF 2000 E - Photoshoot for Gorillas
# https://codeforces.com/contest/2000/problem/E

"""
E. Photoshoot for Gorillas

Purpose:
This code solves a problem where gorillas with specific heights need to be placed in a grid such that the total "spectacle" of all k×k sub-squares is maximized.

Algorithm:
- Sort gorilla heights in descending order to assign the tallest gorillas first.
- For each possible k×k sub-square in the n×m grid, compute its area (which contributes to spectacle).
- Sort these areas in descending order.
- Pair the largest gorilla heights with the largest sub-square areas to maximize total spectacle.

Time Complexity:
O(n * m + w * log(w) + (n - k + 1) * (m - k + 1) * log((n - k + 1) * (m - k + 1)))

Space Complexity:
O((n - k + 1) * (m - k + 1) + w)

Note:
The input is processed per test case and constraints guarantee that the solution fits within memory limits.
"""

for _ in range(int(input())):
    n, m, k = map(int, input().split())  # Read grid dimensions and sub-square size
    w = int(input())  # Number of gorillas
    a = sorted(map(int, input().split()), reverse=True)  # Sort gorilla heights in descending order

    # Generate all possible k×k sub-squares and their areas
    b = [
        (min(n, i + k) - max(i, k - 1)) * (min(m, j + k) - max(j, k - 1))
        for i in range(n)
        for j in range(m)
    ]
    
    b.sort(reverse=True)  # Sort the areas in descending order
    
    # Calculate maximum total spectacle by pairing largest gorilla with largest area
    print(sum(x * y for x, y in zip(a, b)))


# https://github.com/VaHiX/codeForces/