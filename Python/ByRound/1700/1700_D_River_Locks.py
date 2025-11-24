# Problem: CF 1700 D - River Locks
# https://codeforces.com/contest/1700/problem/D

"""
Code Purpose:
This program solves the river locks problem where we need to determine the minimum number of pipes to open 
so that all locks are filled within a given time. It uses prefix sums and mathematical optimization to 
calculate the minimum required pipes efficiently.

Algorithms/Techniques:
- Prefix sum calculation to determine cumulative volumes
- Mathematical optimization to find minimum pipes needed for a given time
- Binary search or direct calculation approach based on derived formulas

Time Complexity: O(n + q), where n is the number of locks and q is the number of queries.
Space Complexity: O(n), for storing the volumes of locks.

"""
n = int(input())
p = m = 0
r = list(map(int, input().split()))
# Calculate prefix sums and find the minimum time required to fill all locks
for i in range(n):
    p += r[i]  # Prefix sum of volumes
    m = max(m, (p + i) // (i + 1))  # Minimum time to fill first i+1 locks
for _ in range(int(input())):
    t = int(input())
    if t < m:
        print(-1)  # Impossible to fill all locks in time t
    else:
        print((p + t - 1) // t)  # Minimum number of pipes needed


# https://github.com/VaHiX/CodeForces/