# Problem: CF 2035 G1 - Go Learn! (Easy Version)
# https://codeforces.com/contest/2035/problem/G1

"""
Problem: G1. Go Learn! (Easy Version)
Algorithm: Dynamic Programming with Binary Search Simulation
Time Complexity: O(m^2 * n * log n) where m is number of tests, n is array size
Space Complexity: O(m * n) for storing test cases and DP states

This problem involves finding the minimum number of tests to remove from a set of 
tests such that there exists a valid array satisfying the remaining tests. Each test
is of the form (x, k), meaning that a[x] == k and when performing binary search for k,
the result is x.

The solution uses dynamic programming:
- For each test, we compute the longest valid sequence it can extend
- We also track the number of valid arrays that can be formed
- Binary search simulation is used to determine constraints on array elements
- Modular arithmetic is used throughout for large number handling

Key Concepts:
1. Binary Search Logic: The given algorithm finds the leftmost position where value k can be inserted
2. Test Validity: A test is valid if the element at index x equals k, and binary search on k returns x
3. DP States: L[i] = maximum length of valid sequence ending at test i; W[i] = number of valid arrays for sequence ending at test i
"""

from collections import defaultdict

P = 998244353


def solve():
    n, m = map(int, input().split())
    a = [list(map(int, input().split())) for _ in range(m)]

    def bsearch(x):
        # Simulate binary search for value x
        l, h = 1, n
        while l < h:
            m = l + h >> 1  # Midpoint calculation
            yield m
            if m < x:
                l = m + 1
            else:
                h = m

    # Add sentinel values to simplify boundary conditions
    a.append([0, 0])
    a.append([n + 1, n + 1])
    a.sort()  # Sort tests by index
    
    # Initialize DP arrays
    L = [1] * len(a)  # L[i] stores the maximum length of sequence ending at test i
    W = [0] * len(a)  # W[i] stores the count of valid arrays for sequence ending at test i
    W[0] = 1  # Base case: one way to form empty sequence
    
    for i in range(1, len(a)):
        x2, k2 = a[i]  # Current test
        l = 0  # Maximum length of valid sequence before current test
        
        # Find maximum L[j] among valid previous tests
        for j in range(i):
            x1, k1 = a[j]  # Previous test
            if k1 < k2 and W[j]:  # k1 < k2 and previous sequence is valid
                l = max(l, L[j])  # Update max length
                
        L[i] = l + 1  # Extend current sequence
        
        # Calculate number of valid arrays for current sequence
        for j in range(i):
            x1, k1 = a[j]  # Previous test
            q = defaultdict(int)  # Constraint tracking
            
            # If previous test is compatible with current
            if k1 < k2 and L[j] == l:
                # Simulate binary search for x1
                for t in bsearch(x1):
                    if x1 < t < x2:  # t is in valid range
                        q[t] += max(0, k1 - 1)  # Add constraint
                
                # Simulate binary search for x2
                for t in bsearch(x2):
                    if x1 < t < x2:  # t is in valid range
                        q[t] += n - k2 + 1  # Add constraint
                        
                # Compute number of valid assignments
                z = W[j] * pow(n, x2 - x1 - len(q) - 1, P) % P  # Modular exponentiation
                
                # Apply constraints
                for v in q.values():
                    z = z * (n - v) % P
                    
                W[i] = (W[i] + z) % P  # Add to total count
    
    # Output: minimum tests to remove and count of valid arrays
    print(m - L[-1] + 2, W[-1])


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/