# Problem: CF 1711 B - Party
# https://codeforces.com/contest/1711/problem/B

"""
Code Purpose:
This code solves a problem where a club wants to organize a party with some members,
minimizing the total unhappiness value while ensuring the number of cakes eaten is even.
Cakes are eaten when both friends from a pair are invited.
The solution involves:
1. Finding the minimum sum of unhappiness for any valid pair of friends (even if no other constraints)
2. If the total number of edges (friend pairs) is even, we can always achieve 0 unhappiness by not inviting anyone
3. If odd, we must invite at least one person from an odd-degree node to even out the cake count
Time Complexity: O(n + m) per test case
Space Complexity: O(n) for storing indegree array
"""

t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    unhappiness = list(map(int, input().split()))
    ans = int(1e9)  # Initialize with a large value
    indegree = [0] * n  # Track degree of each node (member)
    for _ in range(m):
        x, y = map(int, input().split())
        x -= 1  # Convert to 0-based indexing
        y -= 1
        ans = min(ans, unhappiness[x] + unhappiness[y])  # Minimum pair unhappiness
        indegree[x] += 1
        indegree[y] += 1

    if m % 2 == 0:
        # If number of edges is even, we can avoid all cakes (0 cakes eaten)
        print(0)
    else:
        # If number of edges is odd, at least one edge must be "used" 
        # i.e., we must invite someone from an odd-degree node
        for i, v in enumerate(indegree):
            if v % 2 == 1:  # Odd degree node
                ans = min(ans, unhappiness[i])

        print(ans)


# https://github.com/VaHiX/CodeForces/