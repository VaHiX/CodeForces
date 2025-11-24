# Problem: CF 1548 A - Web of Lies
# https://codeforces.com/contest/1548/problem/A

"""
A. Web of Lies

Purpose:
This code simulates a process where nobles (nodes) with friendships (edges) are removed if they are "vulnerable". 
A noble is vulnerable if it has at least one friend and all its friends have higher power than itself.
The process iteratively removes vulnerable nobles and their associated edges until no more nobles are vulnerable.
This is handled using a degree tracking approach where we maintain how many neighbors each node still has, 
and track how many nobles are currently "vulnerable" (i.e., have at least one neighbor but all neighbors have higher power).

Algorithms/Techniques:
- Graph representation using adjacency list (simulated through degree counting)
- Efficient simulation of the process with tracking variables for vulnerable nodes
- Dynamic updates to degrees when adding/removing edges

Time Complexity: O(n + m + q * log n), where each query is handled in amortized time considering updates and checks.
Space Complexity: O(n + m), for storing graph structure and auxiliary data.

"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
print = sys.stdout.write
n, m = list(map(int, input().split()))
ls = [0] * (n + 1)  # Degree count for each noble
res = 0             # Number of nobles that are currently vulnerable
for i in range(m):
    a, b = sorted(list(map(int, input().split())))  # Read and sort friendship endpoints
    ls[a] = ls[a] + 1   # Increment degree of node 'a'
for i in range(1, n + 1):
    if ls[i] == 0:
        res = res + 1       # Count nobles with no friends (they are always vulnerable)
q = int(input())
for i in range(q):
    x = input().decode()    # Read query as string
    if x[0] == "3":
        print(str(res) + "\n")   # Output number of remaining nobles after simulation
        continue
    c, a, b = list(map(int, x.split()))  # Parse query type and nodes
    if a > b:
        a, b = b, a     # Ensure a <= b to keep ordering consistent
    if c == 1:          # Add friendship
        ls[a] = ls[a] + 1
        if ls[a] == 1:  # First friend added; possibly makes node vulnerable
            res = res - 1
    elif c == 2:        # Remove friendship
        ls[a] = ls[a] - 1
        if ls[a] == 0:  # No more friends left; not vulnerable anymore
            res = res + 1



# https://github.com/VaHiX/codeForces/