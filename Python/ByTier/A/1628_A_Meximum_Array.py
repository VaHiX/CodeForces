# Problem: CF 1628 A - Meximum Array
# https://codeforces.com/contest/1628/problem/A

"""
Problem: Meximum Array

Algorithm:
This problem uses a greedy approach to construct the lexicographically maximum array b by choosing optimal k values at each step. The key idea is to always greedily select the largest possible MEX value at each step.

Time Complexity: O(n) - Each element is processed at most twice (once in forward pass and once in backward pass), making it linear.
Space Complexity: O(n) - For storing the array d which stores indices of each value in reverse order.

Techniques:
- Greedy algorithm
- MEX calculation optimization using preprocessed indices
- Reverse iteration for efficient index lookup

The algorithm works by:
1. Preprocessing indices of all numbers in reverse order.
2. Using a greedy strategy to find the maximum possible MEX at each step, avoiding smaller MEXs that could reduce lexicographical order.
3. Selecting the farthest valid index to maximize the MEX.

"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    w = list(map(int, input().split()))
    ans = []
    # d[i] stores indices of value i in reversed order (from right to left)
    d = [[] for _ in range(n + 1)]
    for i in range(n - 1, -1, -1):   # Reverse iteration to build d
        d[w[i]].append(i)
    
    s = 0   # Start pointer of current segment
    while s < n:
        x = s   # Max index we can reach with current MEX
        for i in range(n + 1):
            # Remove indices that are before the start pointer 's'
            while d[i] and d[i][-1] < s:
                d[i].pop()
            if d[i] == []:   # If no more elements of value i, we can form MEX = i
                ans.append(i)
                s = x + 1    # Move start pointer forward
                break
            else:
                x = max(x, d[i][-1])   # Update maximum reachable index
    print(len(ans))
    print(" ".join(map(str, ans)))


# https://github.com/VaHiX/codeForces/