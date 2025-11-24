# Problem: CF 1923 F - Shrink-Reverse
# https://codeforces.com/contest/1923/problem/F

"""
Problem: F. Shrink-Reverse
Algorithms/Techniques: Greedy, Simulation, String manipulation, Bit manipulation
Time Complexity: O(n^2) in worst case due to string comparisons in compare function;
Space Complexity: O(n) for storing the string and auxiliary arrays.

This solution attempts to minimize the binary value of a string by performing at most k operations.
Operations allowed:
1. SWAP: swap two characters.
2. SHRINK-REVERSE: remove leading zeros and reverse the string.

The approach involves:
- Identifying positions of '1's.
- Exploring possible configurations using swaps and shrink-reverse.
- Comparing different string segments to find the minimum value.
- Calculating the resulting integer value modulo 10^9 + 7.
"""

ans = []
n, k = [int(x) for x in input().split()]
s = [int(char) for char in input()]
ones = []
for i in range(n):
    if s[i]:
        ones.append(i)


def place_ones(t, arr):
    return arr


k = min(k, len(ones))  # Limit k to number of 1s to avoid redundant operations
check = [(ones[k] if k < len(ones) else n, n, 1)]  # Initial configuration to consider
for i in range(k):
    check.append((ones[len(ones) - k + i], ones[i] - 1, -1))  # Reverse configurations
for i in range(k - 1):
    check.append((ones[i], ones[len(ones) - k + i + 1] + 1, 1))  # Forward configurations


def compare(a, b):
    # Compare two string segments based on their values
    d = abs(a[0] - a[1]) - abs(b[0] - b[1])
    if d < 0:
        return a
    if d > 0:
        return b
    for k in range(abs(a[0] - a[1]) + 1):
        d = s[a[0] + k * a[2]] - s[b[0] + k * b[2]]
        if d < 0:
            return a
        if d > 0:
            return b
    return a


m = -1
for c in check:
    if m == -1:
        m = c
    else:
        m = compare(m, c)  # Keep track of the lexicographically smallest string configuration

# Extract the string segment based on comparison result
m = s[m[0] : m[1] : m[2]] if m[1] > 0 else s[m[0] :: m[2]]

# Calculate the minimum value using the selected string segment
place = len(ones) - sum(m)  # Number of zeros to be placed to form the smallest value
value = 0
acc = 1
MOD = 10**9 + 7
while m or place:
    if m:
        e = m.pop()  # Get the next bit
        if e:
            value = (value + acc) % MOD  # Add corresponding power of 2 if bit is 1
        elif place:
            value = (value + acc) % MOD  # Add if leading zero exists
            place -= 1
    else:
        value = (value + acc) % MOD  # Add if still have leading zeros
        place -= 1
    acc = (2 * acc) % MOD  # Move to next bit value
print(value)


# https://github.com/VaHiX/CodeForces/