# Problem: CF 1747 D - Yet Another Problem
# https://codeforces.com/contest/1747/problem/D

"""
Algorithm: 
- Preprocess the array to compute prefix XOR and prefix sum.
- Use a hashmap to track the last occurrence of each prefix XOR value to determine if a subarray can be reduced with one operation.
- For each query:
    - If prefix XOR of subarray is not zero, it's impossible.
    - If prefix sum is zero, it's already all zeros.
    - Otherwise, check for possible one or two operations based on length and last occurrence of prefix XOR.

Time Complexity: O(n + q)
Space Complexity: O(n)
"""

import sys

n, q = [int(i) for i in sys.stdin.readline().split()]
a = [int(i) for i in sys.stdin.readline().split()]

cur = 0
odd = {}  # stores last index where odd-length prefix XOR occurred
even = {}  # stores last index where even-length prefix XOR occurred
last = [-1] * (n + 1)  # stores the last index of a prefix XOR value
pxor = [0] * (n + 1)  # prefix XOR array
psum = [0] * (n + 1)  # prefix sum array

# Compute prefix XOR and prefix sum and keep track of last positions of prefix XOR
for i, num in enumerate(a):
    pxor[i + 1] = pxor[i] ^ num  # compute prefix XOR
    psum[i + 1] = psum[i] + num  # compute prefix sum
    cur = pxor[i + 1]
    if i & 1 == 0:  # even length prefix
        if cur in odd:
            last[i + 1] = odd[cur]  # update last seen index
        even[cur] = i + 1
    else:  # odd length prefix
        if cur in even:
            last[i + 1] = even[cur]  # update last seen index
        odd[cur] = i + 1

# Process queries
for _ in range(q):
    l, r = [int(i) for i in sys.stdin.readline().split()]
    # Check if the subarray can be made all zeros by XOR
    if pxor[l - 1] != pxor[r]:
        print("-1")
    elif psum[l - 1] == psum[r]:
        # If prefix sums are equal, subarray is all zeros
        print("0")
    else:
        # Subarray is not all zeros, check number of operations needed
        if (r - l) % 2 == 0:
            # Even length subarray - can be reduced with one operation to a single value
            print("1")
        elif a[l - 1] == 0 or a[r - 1] == 0:
            # Odd length with either boundary being zero, can be done with one operation
            print("1")
        elif last[r] >= l:
            # If previous prefix XOR matched, two operations necessary
            print("2")
        else:
            # No way to reduce to all zeros
            print("-1")


# https://github.com/VaHiX/CodeForces/