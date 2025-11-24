# Problem: CF 2066 A - Object Identification
# https://codeforces.com/contest/2066/problem/A

"""
Interactive problem to determine whether a hidden object is a directed graph (Object A) or 
a set of points on a coordinate plane (Object B).

Algorithms/Techniques:
- Uses two queries to distinguish between the objects.
- For Object A: Queries return shortest path distances in a directed graph.
- For Object B: Queries return Manhattan distances between points.

Time Complexity: O(n) per test case
Space Complexity: O(n) for the visited array and input storage

The approach works as follows:
1. First, check if there's a missing number from 1 to n in the input array x.
   If so, query the missing number against the first element of x.
2. Otherwise, find positions of 1 and n in the array x and compare distances between them in both directions.

This method efficiently distinguishes between Object A and B with only two queries.
"""

import sys

def solve():
    n = int(input())
    arr = list(map(int, input().split()))
    visited = [False] * (n + 1)  # Track which numbers from 1 to n are present
    for i in arr:
        visited[i] = True  # Mark numbers that exist in the array
    for i in range(1, n + 1):
        if not visited[i]:
            # If a number from 1 to n is missing, query it against first element
            print(f"? {i} {arr[0]}")
            sys.stdout.flush()
            dist = int(input())
            if dist == 0:
                print("! A")
            else:
                print("! B")
            return
    
    # If no number is missing, find positions of 1 and n in the array
    a = arr.index(1) + 1   # Position of 1 (1-indexed)
    b = arr.index(n) + 1   # Position of n (1-indexed)
    
    # Query distances between these two points/vertices
    print(f"? {a} {b}")
    sys.stdout.flush()
    first = int(input())
    
    print(f"? {b} {a}")
    sys.stdout.flush()
    second = int(input())
    
    # Compare the results to determine which object it is
    if first != second:
        print("! A")
        return
    if first < n - 1:
        print("! A")
        return
    print("! B")

for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/codeForces/