# Problem: CF 1767 B - Block Towers
# https://codeforces.com/contest/1767/problem/B

"""
Algorithm: Greedy approach to maximize blocks in tower 1.
Approach:
- Start with the first tower's block count as `f`.
- Sort the array (excluding first tower) in ascending order.
- For each tower (from left to right), if its block count is greater than `f`, 
  we can transfer blocks from it to tower 1.
- The number of blocks we can transfer is calculated as `(i - f + 1) // 2`.
- This ensures we are maximizing the final count in tower 1.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(1) if we ignore input storage; otherwise O(n) for the list `a`.
"""

for _ in range(int(input())):
    n = input()
    f, *a = map(int, input().split())
    a.sort()
    for i in a:
        if i > f:
            f += (i - f + 1) // 2
    print(f)


# https://github.com/VaHiX/CodeForces/