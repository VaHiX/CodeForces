# Problem: CF 2075 C - Two Colors
# https://codeforces.com/contest/2075/problem/C

"""
C. Two Colors

Purpose:
This code calculates the number of ways to paint a fence with exactly two colors,
such that each color is used at least once and all planks of the same color form
a continuous sequence. The constraint is that each color can be used no more than
a_i planks, where a_i is the maximum capacity of the i-th color.

Algorithm:
The approach uses prefix sums to efficiently count how many planks are painted
with a color (or more) from the right. For each possible split point in the fence,
we compute valid combinations of left and right segments using the given capacities.

Time Complexity: O(n + m)
Space Complexity: O(n + m)

"""

for t in range(int(input())):
    n, m = map(int, input().split())
    l1 = [0] * (n + 1)  # Array to store count of planks that can be painted with each color
    for i in map(int, input().split()):  # Read capacities and accumulate
        l1[i] += 1
    for i in range(n - 1, 0, -1):  # Build suffix sum (from right to left)
        l1[i] += l1[i + 1]
    ans = 0
    for i in range(1, n):  # Try all possible split points
        a1 = l1[i]      # Count of planks >= i that can be used (left segment)
        a2 = l1[n - i]  # Count of planks >= n-i that can be used (right segment)
        tmp = i if i >= n - i else n - i  # Find the smaller segment
        ans += a1 * a2 - l1[tmp]  # Subtract overlaps to avoid invalid combinations
    print(ans)


# https://github.com/VaHiX/codeForces/