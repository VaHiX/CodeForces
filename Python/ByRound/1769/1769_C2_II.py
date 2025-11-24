# Problem: CF 1769 C2 - Подкрутка II
# https://codeforces.com/contest/1769/problem/C2

"""
Algorithm: Sliding Window with Dynamic Programming
Time Complexity: O(n)
Space Complexity: O(1)

This solution uses a sliding window approach to find the maximum length of 
consecutive days with at least one commit, after allowing each commit to be 
shifted forward by at most one day. 

The key insight is to track two variables:
- p: length of the current segment ending at the previous commit
- q: length of the current segment ending at the current commit

For each commit, we update these values based on the gap between consecutive commits,
and keep track of the maximum segment length seen so far.
"""

t = int(input())
for I in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    s = 0  # maximum length found so far
    l = 0  # previous commit day
    p = 0  # length of segment ending at previous commit
    q = 0  # length of segment ending at current commit
    for i in a:
        if l == i:
            # Same day as previous commit - extend both segments
            q = max(q, p + 1)
        elif l + 1 == i:
            # Day after previous commit - extend both segments by 1
            p += 1
            q += 1
        elif l + 2 == i:
            # Two days after previous commit - start new segment from current
            p = q + 1
            q = 1
        else:
            # More than two days gap - start new segment of length 1
            p = 1
            q = 1
        l = i  # update previous commit day
        s = max(s, p, q)  # update maximum length
    print(s)


# https://github.com/VaHiX/CodeForces/