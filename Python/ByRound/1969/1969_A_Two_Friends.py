# Problem: CF 1969 A - Two Friends
# https://codeforces.com/contest/1969/problem/A

"""
Algorithm: 
The problem is about finding the minimum number of invitations to send so that at least 2 friends come to the party. 
Each friend comes only if both they and their best friend receive invitations. 
The key observation is that we want to find cycles in the friendship graph.
- If there exists a mutual friendship (a cycle of length 2), then we only need 2 invitations.
- If the smallest cycle is of length 3 or more, then at least 3 invitations are needed.

Time Complexity: O(n) where n is the number of friends.
Space Complexity: O(1) as we only use a constant amount of extra space.

Techniques:
- Cycle detection in a permutation
- Greedy approach based on cycle lengths
"""

import sys

input = lambda: sys.stdin.readline().strip()


def solve():
    n = int(input())
    arr = list(map(int, input().split()))
    # Check for any mutual friendship (cycle of length 2)
    for i in range(n):
        # If i and arr[i] are mutual friends (i.e., arr[arr[i] - 1] - 1 == i)
        if i == arr[arr[i] - 1] - 1:
            return 2
    # If no mutual friendship, minimum is 3
    return 3


for _ in range(int(input())):
    print(solve())


# https://github.com/VaHiX/CodeForces/