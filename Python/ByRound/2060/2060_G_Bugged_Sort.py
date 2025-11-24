# Problem: CF 2060 G - Bugged Sort
# https://codeforces.com/contest/2060/problem/G

"""
G. Bugged Sort

Problem Description:
Given two arrays 'a' and 'b' of length n each, containing all integers from 1 to 2*n exactly once,
determine if both arrays can be sorted in increasing order simultaneously using a special swap operation.

Swap Operation:
- Given indices i and j (i ≠ j), swap a[i] with b[j], and swap b[i] with a[j].
This means elements are exchanged between the two arrays while keeping their relative positions.

Algorithm:
The key insight is to model this as a graph problem where each element in [1, 2*n] forms a cycle.
We process elements one by one and group them into cycles. For each cycle, we check whether we can
arrange the elements such that both arrays end up sorted. This involves checking parity conditions.

Time Complexity: O(n)
Space Complexity: O(n)

"""

import sys

input = sys.stdin.readline
t = int(input())
for _ in range(t):
    n = int(input())
    arr = [0 for _ in range(2 * n)]        # Stores the type of each element (0 or 1) based on which array they initially came from
    couple = [0 for _ in range(2 * n)]     # Maps an index to its pair in the other array
    visited = [0 for _ in range(2 * n)]    # Tracks visited indices in the graph traversal
    
    a = [*map(lambda x: int(x) - 1, input().split())]   # Convert to 0-based indexing
    b = [*map(lambda x: int(x) - 1, input().split())]   # Convert to 0-based indexing

    # Build mapping of elements to their original array (a or b)
    for i in range(n):
        arr[a[i]] = 0
        arr[b[i]] = 1
        couple[a[i]] = b[i]
        couple[b[i]] = a[i]

    cnt = 0                    # Number of mismatches (when current element from 'a' is not 0)
    end = 0                    # Flag to exit early if impossible
    Q = []                     # Stores positions where we have an ordering conflict for later checks
    ansa, ansb = [], []        # Stacks storing the current segment boundaries

    # Traverse all elements in order and form cycles
    for i in range(2 * n):
        if visited[i]:
            continue
        visited[i] = 1
        visited[couple[i]] = 1

        # Initialize first segment
        if not ansa:
            ansa.append(i)
            ansb.append(couple[i])
            if arr[i] == 1:
                cnt += 1
        elif ansa[-1] < ansb[-1]:
            # Check if we need to split the segment (conflict in ordering)
            if ansb[-1] < i:
                Q.append(len(ansa))
            if arr[i] == 1:
                cnt += 1
            ansa.append(i)
            # Update b segment
            if ansb[-1] < couple[i]:
                ansb.append(couple[i])
            else:
                end = 1
                print("NO")
                break
        else:
            # Check if we need to split the segment (conflict in ordering)
            if ansa[-1] < i:
                Q.append(len(ansa))
            if arr[i] == 0:
                cnt += 1
            ansb.append(i)
            # Update a segment
            if ansa[-1] < couple[i]:
                ansa.append(couple[i])
            else:
                end = 1
                print("NO")
                break

    if not end:
        # If n is odd, always possible
        if n % 2:
            print("YES")
        else:
            # If even n, check parity and conflicts
            if cnt % 2 == 0:
                print("YES")
            else:
                check = 0
                for val in Q:     # Check if any segment had conflict that can be resolved
                    if val % 2:
                        check = 1
                if check:
                    print("YES")
                else:
                    print("NO")


# https://github.com/VaHiX/codeForces/