# Problem: CF 1889 B - Doremy's Connecting Plan
# https://codeforces.com/contest/1889/problem/B

"""
Algorithm: Greedy Approach with Prefix Sums
Purpose: Determine if a graph of cities can be made connected based on a specific condition.
Time Complexity: O(n) per test case
Space Complexity: O(1) excluding input storage

The approach uses a greedy method where we try to connect components in a way that 
maximizes the number of connections. We maintain a running sum of city populations 
and check if we can connect the current node with the previous component.

Key insight:
- We process nodes from left to right.
- For each node, we check if the sum of population in the current component 
  is sufficient to connect it to the previous component.
- If so, we merge the components; otherwise, we continue.
"""

import sys

input = sys.stdin.readline


def ok(b):
    print(["NO", "YES"][b])


def li():
    return list(map(int, input().split()))


def mi():
    return map(int, input().split())


MOD = 10**9 + 7
MO = 998244353
INF = float("inf")
NINF = float("-inf")


def solve():
    n, c = mi()  # Read number of nodes and constant c
    cities = li()  # Read populations of each city
    
    # Initialize with first city
    cur = cities[0]  # Current component sum
    sum = cur  # Running total sum
    last = 0  # Last node successfully connected
    
    # Iterate through remaining cities
    for i in range(1, n):
        sum += cities[i]  # Add current city to total sum
        # Check if we can connect current city to the previous component
        if cur + cities[i] >= c * (i + 1):
            cur = sum  # Merge components
            last = i   # Update last successfully connected node
    
    # If last connected node is the last node, the graph is connected
    ok(last == n - 1)


z = int(input())  # Read number of test cases
for _ in range(z):
    solve()


# https://github.com/VaHiX/CodeForces/