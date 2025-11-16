# Problem: CF 1768 F - Wonderful Jump
# https://codeforces.com/contest/1768/problem/F

"""
Algorithm: Dynamic Programming with Optimized Transitions
Time Complexity: O(n^2) in worst case, but often better due to early breaks
Space Complexity: O(n) for the cost array

This solution uses dynamic programming where for each index, we compute the minimum cost
to reach that index from index 1. The key idea is to limit the jump distance based on the 
value of the current element, and use early termination to avoid unnecessary computations.
The algorithm maintains two pointers (left and right) to explore valid jumps with a 
distance constraint defined by min(arr[i], arr[i+1], ..., arr[j]) * (j - i)^2.
"""

n = int(input())
arr = [int(x) for x in input().split()]
cost = [float("inf") for i in range(n)]
cost[0] = 0
for i in range(n):
    # Calculate the maximum allowed distance for a jump from index i
    dist = n // arr[i] + 1
    j = i - 1
    # Explore jumps to the left, stopping early if arr[j] <= arr[i]
    while j >= 0 and i - j <= dist:
        cost[i] = min(cost[i], cost[j] + arr[i] * (j - i) ** 2)
        if arr[j] <= arr[i]:
            break
        j -= 1
    j = i + 1
    # Explore jumps to the right, stopping early if arr[j] <= arr[i]
    while j < n and j - i <= dist:
        cost[j] = min(cost[j], cost[i] + arr[i] * (j - i) ** 2)
        if arr[j] <= arr[i]:
            break
        j += 1
print(" ".join([str(x) for x in cost]))


# https://github.com/VaHiX/CodeForces/