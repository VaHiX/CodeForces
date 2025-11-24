# Problem: CF 1759 G - Restore the Permutation
# https://codeforces.com/contest/1759/problem/G

"""
Algorithm: 
- This problem involves reconstructing a lexicographically minimal permutation from given max pairs.
- The key idea is to process elements from largest to smallest and assign them to positions ensuring that for each pair (b[i], ans[i]), we have b[i] = max(p[2*i-1], p[2*i]).
- We use a heap to manage the available indices for assignment and ensure the smallest lexicographical order.
- Time Complexity: O(n log n) due to heap operations.
- Space Complexity: O(n) for storing indices and auxiliary arrays.
"""

from sys import stdin
input = lambda: stdin.readline()[:-1]
from heapq import *

def solve():
    n = int(input())  # Read length of permutation
    a = list(map(lambda x: int(x) - 1, input().split()))  # Read b array and convert to 0-indexed
    
    s = set(a)  # Set of unique elements in b
    if len(s) != n // 2:  # If not all elements of b are unique, impossible to construct
        print(-1)
        return

    idx = [-1] * n  # Array to store index of each element in b
    for i in range(n // 2):  # Assign index in b for each element
        idx[a[i]] = i

    ans = [-1] * (n // 2)  # Result array to hold smaller element of each pair
    hq = []  # Heap to maintain available indices
    
    # Process elements from n-1 down to 0
    for i in range(n - 1, -1, -1):
        if idx[i] != -1:  # If this element belongs to b
            heappush(hq, -idx[i])  # Push negative index to simulate max heap
        else:
            if hq:  # Assign smallest possible element
                x = -heappop(hq)  # Get the index of pair
                ans[x] = i  # Assign current element as smaller part of the pair
            else:
                print(-1)  # No valid arrangement
                return

    ANS = []  # Final answer array
    for i in range(n // 2):
        x, y = a[i], ans[i]  # Take elements from b and computed smaller elements
        if x > y:  # Ensure x <= y to get ordered pairs
            x, y = y, x
        ANS.append(x)
        ANS.append(y)
    print(*[i + 1 for i in ANS])  # Print result with 1-based indexing

for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/