# Problem: CF 2151 G2 - Hidden Single (Version 2)
# https://codeforces.com/contest/2151/problem/G2

# G2. Hidden Single (Version 2)
# Purpose:
#   This code solves an interactive problem where there is a hidden array of length 2*n - 1,
#   containing numbers from 1 to n, each appearing twice except one number that appears once.
#   The goal is to find the number that occurs exactly once using at most 925 queries.
#
# Algorithm/Techniques:
#   - Divide and conquer approach with binary search logic using subset queries
#   - Uses DFS-like recursion to narrow down subsets of possible candidates
#   - Initial partitioning based on parity (even vs odd indices)
#   - Time complexity: O(n log n) due to recursive splitting and querying
#   - Space complexity: O(n) for storing subsets and recursive stack space

import random
import sys

input = sys.stdin.readline


def ask(i, vec):
    # Query the interactor for existence of value i in subset vec
    print("?", i, len(vec), *vec)
    sys.stdout.flush()
    res = int(input())
    return res


def DFS(S, V):
    # Recursive depth first search to find the unique element
    global ans
    if ans or not S or not V:
        return  # Early termination if answer found or no more elements
    A1, A2 = [], []
    V1, V2 = [], []
    random.shuffle(S)
    fl = 0
    for i in S:
        if fl:
            A1.append(i)
        else:
            A2.append(i)
        fl ^= 1  # Toggle between A1 and A2
    for i in V:
        l = ask(i, A1)  # Check if value i exists in A1
        if not l:
            V2.append(i)
            continue
        r = ask(i, A2)  # Check if value i exists in A2
        if l and r:
            continue  # Value i found in both subsets, skip
        V1.append(i)  # Value i found in only one subset (either A1 or A2)
    if len(A1) == 1 and len(V1) == 1:
        ans = V1[0]
        return
    if len(A2) == 1 and len(V2) == 1:
        ans = V2[0]
        return
    DFS(A1, V1)
    DFS(A2, V2)


t = int(input())
for _ in range(t):
    n = int(input())
    ans = 0
    S = list(range(1, 2 * n))  # All indices from 1 to 2*n-1 (since array is 1-indexed)
    V = list(range(1, n + 1))  # Values from 1 to n
    A1, A2 = [], []
    V1, V2, V3 = [], [], []
    
    # Partition S into even and odd indexed elements
    for i in S:
        if i % 2 == 0:
            A1.append(i)
        else:
            A2.append(i)
            
    # Classify values from V based on whether they exist in A1 or A2
    for i in V:
        l = ask(i, A1)  # Check existence of value i in A1 subset
        if not l:
            V2.append(i)
            continue
        r = ask(i, A2)  # Check existence of value i in A2 subset
        if l and r:
            V3.append(i)  # Value exists in both subsets - no info
        else:
            V1.append(i)  # Value exists in one subset (either just A1 or just A2)

    # Determine which DFS branch to follow based on parity of the difference
    if (len(A1) - len(V3)) & 1:
        DFS(A1, V1)
    else:
        DFS(A2, V2)
        
    print("!", ans)
    sys.stdout.flush()


# https://github.com/VaHiX/CodeForces/