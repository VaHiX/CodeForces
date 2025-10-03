# Problem: CF 2101 B - Quartet Swapping
# https://codeforces.com/contest/2101/problem/B

"""
B. Quartet Swapping

Problem Description:
Given a permutation of integers from 1 to n, we can perform operations where we swap elements at positions i and i+2, and also swap elements at positions i+1 and i+3. The goal is to find the lexicographically smallest possible permutation after any number of such operations.

Key Techniques/Algorithms:
- Greedy approach with sorting odd/even indexed elements separately.
- Simulation using a swap function that mimics the allowed operation.
- Index mapping for efficient lookups during swaps.

Time Complexity: O(n log n) per test case due to sorting of even and odd indexed elements.
Space Complexity: O(n) for storing indices, even/odd arrays, and auxiliary data structures.

The algorithm works by:
1. Separating elements at even and odd indices.
2. Sorting them in descending order so we can take the smallest elements first.
3. Iteratively placing the next smallest element into its correct position using swaps.
4. At the end, ensuring the final four elements are correctly ordered.

"""

for _ in range(int(input())):

    def swap(i, j):
        # Perform the allowed operation: swap pairs (i, i+2) and (i+1, i+3)
        a[i], a[j] = a[j], a[i]
        a[i + 1], a[j + 1] = a[j + 1], a[i + 1]
        # Update index mappings after swapping
        idx[a[i]] = i
        idx[a[j]] = j
        idx[a[i + 1]] = i + 1
        idx[a[j + 1]] = j + 1

    n = int(input())
    a = [int(i) for i in input().split()]
    idx = [0] * (n + 1)
    odd, even = [], []
    
    # Separate elements by their positions (odd/even index)
    for i in range(n):
        idx[a[i]] = i
        if i & 1:
            odd.append(a[i])
        else:
            even.append(a[i])
    
    # Sort both lists in descending order to get the smallest values first
    odd.sort(reverse=True)
    even.sort(reverse=True)
    
    # For all elements except last 4, greedily place them in ascending order
    for i in range(n - 4):
        if i & 1:
            x = odd.pop()  # Take from odd list
        else:
            x = even.pop()  # Take from even list
        
        # If the target element is at the last position, do a swap to bring it back
        if idx[x] == n - 1:
            swap(n - 2, n - 4)
        
        # Perform swap to move x to correct place
        swap(i, idx[x])
    
    # Fix the last four elements (a[n-4] to a[n-1]) if needed
    if a[n - 2] < a[n - 4]:
        swap(n - 2, n - 4)
    
    print(*a)


# https://github.com/VaHiX/codeForces/