# Problem: CF 1858 E2 - Rollbacks (Hard Version)
# https://codeforces.com/contest/1858/problem/E2

"""
Online Rollback Query Processing

This solution efficiently handles queries on an array with rollback functionality using a segment tree-like approach with bit manipulation and lazy propagation.
It maintains a history of changes using a stack to support rollback operations.

Algorithms:
- Bit manipulation with parent-child relationships in virtual segment tree
- Stack-based history tracking for rollback operations
- Lazy propagation technique to handle range updates efficiently

Time Complexity: O(q * log^2(max_value)) where q is number of queries
Space Complexity: O(q * log(max_value)) for maintaining the virtual tree structure
"""

import os
import sys

input = sys.stdin.buffer.readline


def g(u, v):
    # Helper function to get parent node in virtual segment tree
    x, y = (u + c0[v]) >> 1, (u + c0[v]) & 1
    return parent[x] & z if not y else parent[x] >> 20


q = int(input())
u, m = 0, 0  # u: current node, m: current position in array
st = [0]  # Stack to track history for rollback
st0 = []  # Stack to track changes in distinct elements
l = pow(10, 6) + 5  # Maximum possible value + 5 for padding
parent = [0] * (10 * l)  # Virtual segment tree parent array
c0 = [0] * (q + 1)  # Array to store node positions
a = [0] * (q + 1)  # Array to store actual values
pow2 = [1]  # Powers of 2 precomputed
for _ in range(19):
    pow2.append(2 * pow2[-1])
z = sum(pow2)  # Bitmask for bit operations
c = [l] * l  # Tracking distinct element positions
ans0 = [0]  # Stack to store the count of distinct elements at each step
ans = 0  # Current count of distinct elements
j = 0  # Node counter for virtual tree

for _ in range(q):
    t = list(input().rstrip().decode().split())
    if t[0] == "+":
        # Add element to array
        x = int(t[1])
        m += 1
        # Update parent information
        parent[j >> 1] ^= u if not j & 1 else u << 20
        j += 1
        a[m] = x
        st.append(m)
        # Update virtual tree structure for new element
        for i in range(20):
            if not i < c0[u + 1] - c0[u]:
                break
            p = g(i, u)
            parent[j >> 1] ^= p if not j & 1 else p << 20
            j += 1
            u = p
        c0[m + 1] = j
        # Handle distinct elements count
        if c[x] == l:  # If element never seen before
            st0.append(c[x])
            c[x] = m
            ans += 1
        else:  # If element seen before
            u = m
            for i in range(19, -1, -1):  # Binary search for previous occurrence
                if i < c0[u + 1] - c0[u] and g(i, u) >= c[x]:
                    u = g(i, u)
            if u ^ c[x]:  # If not same as previous occurrence
                st0.append(c[x])
                c[x] = m
                ans += 1
            else:
                st0.append(0)  # No increase in distinct elements
        ans0.append(ans)
        u = m
    elif t[0] == "-":
        # Remove k elements from end of array
        k = int(t[1])
        for i in range(20):
            if k & pow2[i]:  # Handle bit-by-bit
                k ^= pow2[i]
                u = g(i, u)
            if not k:
                break
        ans = ans0[u]  # Get previous distinct elements count
        st.append(u)
    elif t[0] == "!":
        # Rollback to previous state
        v = st.pop()
        u = st[-1]  # Get previous state
        if u < v:  # Only if rollback is necessary
            cx = st0.pop()  # Get value from rollback stack
            if cx:  # If element was added in this state
                c[a[v]] = cx  # Restore previous position
        ans = ans0[u]  # Restore answer
    else:
        # Query distinct elements count
        ans = ans0[u]
        os.write(1, b"%d\n" % ans)  # Output result


# https://github.com/VaHiX/CodeForces/