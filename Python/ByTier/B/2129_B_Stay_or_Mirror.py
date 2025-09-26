# Problem: CF 2129 B - Stay or Mirror
# https://codeforces.com/contest/2129/problem/B

"""
B. Stay or Mirror
Algorithm: For each element in the permutation, decide whether to keep it as is (p[i]) or mirror it (2*n - p[i]).
The goal is to minimize the number of inversions in the resulting array.

Time Complexity: O(n^2) due to nested loops checking all previous elements for each current element.
Space Complexity: O(1) - only using a few variables for computation, no extra space proportional to input size.

Approach:
- For each position i, we calculate how many elements before it are greater than p[i].
- Then decide whether to keep p[i] or use 2*n - p[i] such that the total inversions are minimized.
"""

for i in range(int(input())):
    n, p, s = int(input()), list(map(int, input().split())), 0
    for j in range(n):
        x = 0
        for k in range(j):
            if p[k] > p[j]:
                x += 1
        s += min(x, n - p[j] - x)  # Choose the option that gives fewer inversions
    print(s)


# https://github.com/VaHiX/codeForces/