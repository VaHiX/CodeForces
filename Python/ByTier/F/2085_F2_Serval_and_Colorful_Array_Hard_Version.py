# Problem: CF 2085 F2 - Serval and Colorful Array (Hard Version)
# https://codeforces.com/contest/2085/problem/F2

"""
F2. Serval and Colorful Array (Hard Version)

Purpose:
This code solves the problem of finding the minimum number of adjacent swaps needed to make at least one subarray of the given array "colorful". A colorful subarray is a subarray of length k where each integer from 1 to k appears exactly once.

Algorithms/Techniques:
- Sliding window technique with difference array optimization
- Prefix sum and difference array for efficient range updates

Time Complexity: O(n + k)
Space Complexity: O(n + k)

Input:
- t: number of test cases
- For each test case:
  - n, k: length of array and magic number
  - Array a of size n with values from 1 to k

Output:
- Minimum operations needed to make at least one colorful subarray
"""

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    a = [0] + list(map(int, input().split()))  # 1-indexed array
    b = [0] * (n + 1)  # stores last occurrence of each element
    c = [0] * (n + 1)  # difference array for range updates
    s, d, x = 0, -k, 10**18  # s: current cost, d: running delta, x: minimum cost
    
    for i in range(1, n + 1):
        if b[a[i]] == 0:
            # First occurrence of a[i]
            s += i - 1  # Add contribution to cost
        else:
            # Second or later occurrence of a[i]
            p = b[a[i]]  # previous occurrence index
            mid = (p + i) >> 1  # middle point for range update
            if (p + i) & 1:
                # Odd sum -> two positions modified
                c[mid] -= 1
                c[mid + 1] -= 1
            else:
                # Even sum -> one position modified twice
                c[mid] -= 2
        c[i] += 2  # Add cost increment at current index
        b[a[i]] = i  # Update last occurrence
        
    for i in range(1, n + 1):
        x = min(x, s)  # Track minimum cost so far
        d += c[i]  # Apply delta to running cost
        s += d  # Update current cost
        
    # Adjust for final offset due to window size k
    for i in range(1, k + 1):
        x -= abs(i - ((k + 1) >> 1))  # Subtract base cost of optimal arrangement
        
    print(x)


# https://github.com/VaHiX/codeForces/