# Problem: CF 1609 E - William The Oblivious 
# https://codeforces.com/contest/1609/problem/E

"""
Segment Tree with Dynamic Programming for Subsequence abc Detection
Time Complexity: O((n+q) * log(n)) 
Space Complexity: O(n)

This solution uses a segment tree where each node stores dynamic programming values
representing the minimum cost to eliminate "abc" subsequences in different states:
- State 0: Count of 'a's seen so far
- State 1: Count of 'ab' subsequences formed
- State 2: Count of 'abc' subsequences formed
- State 3: Count of 'b's seen so far
- State 4: Count of 'bc' subsequences formed
- State 5: Count of 'c's seen so far

Each node in the segment tree is updated in O(log n) time, and each query is processed in O(log n) time.
"""

import sys

input = sys.stdin.readline

n, q = map(int, input().split())
S = input().strip()

# Preprocessing arrays to mark which character each position has
A = [0] * n
B = [0] * n
C = [0] * n

for i in range(n):
    if S[i] == "a":
        A[i] = 1
    elif S[i] == "b":
        B[i] = 1
    else:
        C[i] = 1


def seg_function(x, y):
    """
    Combines two segment tree nodes to form a new node.
    Each node stores an array of 6 values representing different state transitions.
    """
    z = [0, 0, 0, 0, 0, 0]

    # Base case updates: sum of counts
    z[0] = x[0] + y[0]
    z[3] = x[3] + y[3]
    z[5] = x[5] + y[5]

    # Transition updates
    z[1] = min(x[0] + y[1], x[1] + y[3])  # a followed by b  
    z[2] = min(x[0] + y[2], x[1] + y[4], x[2] + y[5])  # a followed by b followed by c
    z[4] = min(x[3] + y[4], x[4] + y[5])  # b followed by c

    return z


# Segment tree initialization
seg_el = 1 << ((n + 1).bit_length())
SEG = [[0] * 6 for i in range(2 * seg_el)]

# Fill the leaves of the segment tree
for i in range(n):
    if A[i] == 1:
        SEG[i + seg_el][0] = 1  # a
    elif B[i] == 1:
        SEG[i + seg_el][1] = 1  # b
        SEG[i + seg_el][3] = 1  # b
    else:
        SEG[i + seg_el][2] = 1  # c
        SEG[i + seg_el][4] = 1  # c
        SEG[i + seg_el][5] = 1  # c

# Build the segment tree
for i in range(seg_el - 1, 0, -1):
    SEG[i] = seg_function(SEG[i * 2], SEG[i * 2 + 1])


def update(n, x, seg_el):
    """
    Updates the leaf node at position n with new values x and propagates updates up the tree.
    """
    i = n + seg_el
    SEG[i] = x
    i >>= 1

    while i != 0:
        SEG[i] = seg_function(SEG[i * 2], SEG[i * 2 + 1])
        i >>= 1


def getvalues(l, r):
    """
    Gets the combined segment tree values for range [l, r].
    """
    L = l + seg_el
    R = r + seg_el
    ANS = [0] * 6

    while L < R:
        if L & 1:
            ANS = seg_function(ANS, SEG[L])
            L += 1

        if R & 1:
            R -= 1
            ANS = seg_function(ANS, SEG[R])
        L >>= 1
        R >>= 1

    return ANS


ALIST = []
for i in range(q):
    x, y = input().split()
    x = int(x) - 1

    # Map character to segment tree update values
    if y == "a":
        z = [1, 0, 0, 0, 0, 0]
    elif y == "b":
        z = [0, 1, 0, 1, 0, 0]
    else:
        z = [0, 0, 1, 0, 1, 1]

    update(x, z, seg_el)

    ALIST.append(str(min(SEG[1])))

print("\n".join(ALIST))


# https://github.com/VaHiX/CodeForces/