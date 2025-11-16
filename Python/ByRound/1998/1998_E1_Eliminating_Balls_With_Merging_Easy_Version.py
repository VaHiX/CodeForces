# Problem: CF 1998 E1 - Eliminating Balls With Merging (Easy Version)
# https://codeforces.com/contest/1998/problem/E1

"""
Algorithm: Simulation with Merge Operations
Approach:
1. We simulate a process where elements (balls) are merged based on comparison of values.
2. The core idea is to use a priority queue (sorted by value descending) to process elements in an optimal order.
3. For each element removed from the set, we merge it with adjacent elements based on their values.
4. A "left" and "right" array maintains the linked list structure for efficient traversal.
5. An "acc" array tracks how many elements each node represents.
6. After all operations, only one element remains; return the count for that element.

Time Complexity: O(n log n) due to sorting and processing each element once.
Space Complexity: O(n) for the arrays used to track structure and values.
"""

inf = 10**9 + 23
ans = []
for _ in range(int(input())):
    n, m = [int(x) for x in input().split()]
    a = [inf] + [int(x) for x in input().split()]
    a.append(inf)
    b = [(a[i], i) for i in range(n + 2)]
    b.sort(reverse=True) # Sort elements by value in descending order to process largest first
    left = [i - 1 for i in range(n + 2)] # Left neighbor of each index
    right = [i + 1 for i in range(n + 2)] # Right neighbor of each index
    acc = [1] * (n + 2) # Number of elements represented by each index
    S = a[:] # Copy of initial values for merging logic
    while len(b) > 3: # Continue until only the final two boundary elements remain
        _, i = b.pop() # Pop the smallest value element to process
        L = left[i] # Left neighbor
        R = right[i] # Right neighbor
        if a[L] < a[R]: # If left value is smaller
            if S[i] >= a[L]: # If current node's value supports merging into left
                acc[L] += acc[i] # Add count of nodes being merged
            S[L] += S[i] # Merge current node into left
            right[L] = R # Update links
            left[R] = L
        else: # Otherwise right value is smaller or equal
            if S[i] >= a[R]: # If current node's value supports merging into right
                acc[R] += acc[i] # Add count of nodes being merged
            S[R] += S[i] # Merge current node into right
            left[R] = L # Update links
            right[L] = R
    _, i = b.pop() # Pick the last valid node to get result
    ans.append(acc[i]) # Accumulate result for final node
for z in ans:
    print(z)


# https://github.com/VaHiX/CodeForces/