# Problem: CF 2090 E2 - Canteen (Hard Version)
# https://codeforces.com/contest/2090/problem/E2

"""
E2. Canteen (Hard Version)

Algorithm: Binary search on answer + sliding window technique with prefix sum optimization.
Time Complexity: O(n * log(sum(a))) where n is the length of arrays and sum(a) is the total sum of array a.
Space Complexity: O(n) for storing prefix sums and temporary arrays.

The problem involves minimizing the number of rounds to zero out array 'a' after exactly k operations,
where each operation reduces one element of 'a' by 1. The key insight is to optimize the order of operations
to reduce the number of rounds needed, using binary search to test possible answers and a sliding window
approach with prefix sums for efficient validation.

Steps:
1. If initial sum(a) <= k, then no rounds are needed.
2. Perform k operations on array 'a', reducing values by 1 (greedily).
3. Try shifting the arrays to find optimal starting position using prefix sum.
4. Binary search over number of rounds for valid solution.
5. Use sliding window technique with prefix sum optimization to efficiently check if a given number
   of rounds is sufficient.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    
    # If we can make all elements of 'a' zero with k operations, then no rounds are needed
    if sum(a) <= k:
        print(0)
        continue
    
    # Apply the k operations to reduce elements in a
    for i in range(n):
        d = min(a[i], b[i])
        a[i] -= d
        b[i] -= d
    
    # If after applying b operations, 'a' is already <= k, then 1 round suffices
    if sum(a) <= k:
        print(1)
        continue
    
    # Find best rotation to minimize required rounds (prefix minimization)
    pref = [0]
    for i in range(n):
        pref.append(pref[-1] + a[i] - b[i])
    
    ex = pref.index(min(pref))
    
    # Rotate arrays so that the minimum prefix starts at index 0
    a = a[ex:] + a[:ex]
    b = b[ex:] + b[:ex]
    
    # Recalculate prefix sum after rotation
    pref = [0]
    for i in range(n):
        pref.append(pref[-1] + a[i] - b[i])
    
    # Binary search on the number of rounds required
    lo = 0
    hi = n
    
    while hi - lo > 1:
        aa = a[:]  # Copy current array 'a'
        mid = (lo + hi) // 2
        need = 0
        st = []  # Stack to manage indices in sliding window
        l = n - 1
        
        # Sliding window simulation for mid round length
        for r in range(n):
            st.append(r)
            x = b[r]
            # While we still have elements to consume and the window size is acceptable
            while x and st and r - st[-1] < mid:
                d = min(aa[st[-1]], x)  # Determine how much can be taken from index st[-1]
                x -= d
                aa[st[-1]] -= d
                if aa[st[-1]] == 0:
                    st.pop()  # Remove from stack when element becomes zero
        
        need = sum(aa)  # Total remaining elements after simulation
        
        if need <= k:  # If this mid value is enough, try smaller
            hi = mid
        else:  # Otherwise, we need more rounds
            lo = mid
    
    print(hi)


# https://github.com/VaHiX/codeForces/