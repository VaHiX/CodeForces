# Problem: CF 2165 A - Cyclic Merging
# https://codeforces.com/contest/2165/problem/A

"""
Algorithm: Dynamic Programming with Greedy Approach on Ring
Technique: Rotate the array to start from maximum element, then process elements in increasing order.
           For each element, if its adjacent elements are already processed, add the current element's value to the cost.

Time Complexity: O(n log n) due to sorting, where n is the size of the array.
Space Complexity: O(n) for storing visited array and sorted list.

This approach ensures that we always merge smaller elements with already merged (processed) neighbors,
which minimizes the total cost of merging.
"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    mx = max(a)
    idx = a.index(mx)
    a = a[idx:] + a[:idx]  # Rotate array to start with the maximum element

    vis = [False] * (n + 2)  # Boolean array to track visited indices, extra space for boundary checks

    v = sorted([(x, i + 1) for i, x in enumerate(a)])  # Sort elements with their original indices (1-based)
    ans = 0
    for x, idx in v:  # Process elements in increasing order
        vis[idx] = True  # Mark current index as visited
        if vis[idx - 1]:  # If left neighbor is visited
            ans += x
        if vis[idx + 1]:  # If right neighbor is visited
            ans += x
    print(ans)


# https://github.com/VaHiX/CodeForces/