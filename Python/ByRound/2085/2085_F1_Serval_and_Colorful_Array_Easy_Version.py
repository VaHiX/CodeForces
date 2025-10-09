# Problem: CF 2085 F1 - Serval and Colorful Array (Easy Version)
# https://codeforces.com/contest/2085/problem/F1

"""
Problem: Serval and Colorful Array (Easy Version)

Purpose:
This code finds the minimum number of adjacent swaps required to ensure that there exists at least one "colorful" subarray of length k in the given array a. A colorful subarray is defined as a subarray of length k where each integer from 1 to k appears exactly once.

Algorithms/Techniques:
- Sliding window / difference array technique
- Prefix sum optimization
- Efficient tracking of positions of elements

Time Complexity: O(n * k) where n <= 3000 and k <= n.
Space Complexity: O(n + k) for arrays b, c, and auxiliary storage.

"""

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = [0] + list(map(int, input().split()))  # 1-indexed array
    b = [0] * (n + 1)        # stores last occurrence of each element
    c = [0] * (n + 1)        # difference array for updates
    s, d, x = 0, -k, 10**18   # s: prefix sum of operations needed so far, d: current delta, x: minimum answer
    
    for i in range(1, n + 1):
        if b[a[i]] == 0:
            # First time we see element a[i], add cost to distance from previous position (i-1)
            s += i - 1
        else:
            p = b[a[i]]           # Previous position of a[i]
            mid = (p + i) >> 1    # Midpoint for symmetric adjustment
            if (p + i) & 1:       # If sum is odd
                c[mid] -= 1       # Subtract from two points to maintain balance
                c[mid + 1] -= 1
            else:                 # If sum is even
                c[mid] -= 2       # Adjust midpoint by subtracting 2 for correct handling
        c[i] += 2                  # Increase cost for the current index
        b[a[i]] = i                # Update last occurrence of a[i]
    
    # Compute prefix sums and find minimum operations across all positions
    for i in range(1, n + 1):
        x = min(x, s)              # Track minimal number of swaps needed
        d += c[i]                  # Apply the delta changes to current cumulative value
        s += d                     # Propagate the accumulated change
    
    # Subtract correction terms based on ideal placement of first k elements
    for i in range(1, k + 1):
        x -= abs(i - ((k + 1) >> 1))  # Optimal center shift for minimal cost
    
    print(x)


# https://github.com/VaHiX/codeForces/