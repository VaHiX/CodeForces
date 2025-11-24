# Problem: CF 2128 E2 - Submedians (Hard Version)
# https://codeforces.com/contest/2128/problem/E2

"""
E2. Submedians (Hard Version)

This solution finds all possible submedians in an array by:
1. Using binary search on the median value to find valid subarrays for each candidate
2. For each candidate median, use sliding window with two heaps to maintain medians
3. Merge overlapping intervals to cover all unique submedians

Algorithms/Techniques:
- Binary search on answer (for median values)
- Two heaps (min+max) for efficient median maintenance in sliding window
- Sliding window technique for subarray processing
- Interval merging for final output consolidation

Time Complexity: O(n * log n * log n)
Space Complexity: O(n)

Input:
    Multiple test cases, each with:
    - n: array length
    - k: minimum subarray length
    - Array a of n integers between 1 and n

Output:
    For each test case, outputs all unique submedians along with corresponding subarrays.
"""

import sys

input = sys.stdin.readline
import heapq

for _ in range(int(input())):
    n, k = [int(t) for t in input().split()]
    a = [int(t) - 1 for t in input().split()]

    def solve(m):
        # Transform array: +1 if element >= m else -1
        b = [+1 if e >= m else -1 for e in a]
        p = [0]
        for e in b:
            p.append(p[-1] + e)
        best = 0
        L = 0
        # Scan all subarrays of length k or more to check if median m is achievable
        for R in range(k, n + 1):
            if p[R - k] < best:
                best = p[R - k]
                L = R - k
            if p[R] >= best:
                return (L, R)
        return 0

    def opt():
        # Binary search over median value to find one that works
        x = 0
        jump = 1 << 19
        while jump:
            if solve(x + jump):
                x += jump
            jump //= 2
        l, r = solve(x)
        return x, l, r

    # Find a valid median m along with the first subarray where it's achievable
    Mx, L, R = opt()
    a = [n - 1 - e for e in a]  # Invert array to find minimums as maximums, vice versa
    mx, l, r = opt()
    mx = n - 1 - mx  # Re-invert the result
    a = [n - 1 - e for e in a]  # Re-invert back to original
    
    # Determine overall interval bounds
    bl = min(l, L)
    br = max(r, R)
    
    # Initialize line array for storing intervals
    line = [0] * n
    
    # Process two different median candidates separately
    for cl, cr, f, last in ((l, r, max, mx), (L, R, min, Mx)):
        hl = []  # Max heap for smaller half (using negative values)
        hr = []  # Min heap for larger half
        med = last  # Current median
        
        def insert(t):
            # Insert element t into the two heaps maintaining median property
            global med
            if hr and t < hr[0]:
                heapq.heappush(hl, -t)  # Push to left heap (max), negate for min behavior
            else:
                heapq.heappush(hr, t)
            while len(hr) > len(hl) + 1:
                heapq.heappush(hl, -heapq.heappop(hr))
            while len(hl) > len(hr) + 1:
                heapq.heappush(hr, -heapq.heappop(hl))
            if len(hl) == len(hr):
                med = f(-hl[0], hr[0])
            elif len(hl) > len(hr):
                med = -hl[0]
            else:
                med = hr[0]

        def update():
            # Update line[] with the range of elements that should map to current median
            global last
            nxt = f(last, med)
            if nxt == last and not nxt == med:
                return  # No change
            for i in range(last, nxt + 1, +1):
                line[i] = (i + 1, cl + 1, cr)
            for i in range(last, nxt - 1, -1):
                line[i] = (i + 1, cl + 1, cr)
            last = nxt

        # Process initial window from cl to cr
        for i in range(cl, cr):
            insert(a[i])
        update()
        
        # Expand window to the left and right if needed
        while cl > bl:
            cl -= 1
            insert(a[cl])
            update()
        while cr < br:
            insert(a[cr])
            cr += 1
            update()
            
    print(sum(e != 0 for e in line))
    for e in line:
        if e == 0:
            continue
        print(*e)


# https://github.com/VaHiX/codeForces/