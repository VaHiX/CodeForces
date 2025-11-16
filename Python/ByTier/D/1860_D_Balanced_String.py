# Problem: CF 1860 D - Balanced String
# https://codeforces.com/contest/1860/problem/D

"""
Algorithm: Dynamic Programming + Bit Manipulation
Time Complexity: O(n^2)
Space Complexity: O(n)

The solution uses bit manipulation and dynamic programming to count the number of valid 01 and 10 subsequences,
and then calculates the minimum number of swaps needed to balance the string.
The approach involves:
1. Tracking prefix sums to calculate how many 01 and 10 subsequences exist.
2. Using bit operations to represent and combine possible combinations.
3. Finding a balance point by comparing the possible counts with target.
"""

q = " " + input()  # Prepend a space to make indexing easier (1-based)
n = len(q) - 1
F = [0] * 101  # F[i] represents possible number of 01 subsequence counts with i zeros
G = [0] * 101  # G[i] represents possible number of 10 subsequence counts with i ones
cnt, cur = 0, 0  # cnt: count of zeros seen so far, cur: cumulative count of 01 subseqs
F[0], G[0] = 1, 1  # Base case: no zeros/ones, one way to have 0 count

# Iterating through each character of the string
for i in range(1, n + 1):
    if q[i] == "0":
        cnt += 1  # Increment zero counter
        # Update F array: for each possible count of zeros, shift to account new zero
        for j in range(cnt, 0, -1):
            F[j] |= F[j - 1] << i
    else:
        cur += cnt  # Add number of zeros seen so far to total 01 count
        # Update G array: for each possible count of ones, shift to account new one
        for j in range(i - cnt, 0, -1):
            G[j] |= G[j - 1] << i

# Calculate tag based on total combinations minus zeros and ones combinations
tag = (n * (n - 1) - cnt * (cnt - 1) - (n - cnt) * (n - cnt - 1)) // 4

# Find the minimum swaps required to achieve balance
for x in range(n + 1):
    # Check if current configuration leads to balanced subsequence count
    if (F[x] << cur) & (G[x] << tag):
        print(x)
        break


# https://github.com/VaHiX/CodeForces/