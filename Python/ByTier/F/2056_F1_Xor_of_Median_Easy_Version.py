# Problem: CF 2056 F1 - Xor of Median (Easy Version)
# https://codeforces.com/contest/2056/problem/F1

"""
Problem: Xor of Median (Easy Version)

Purpose:
This code computes the XOR of medians of all "good" sequences of length n
with elements in range [0, m). A sequence is "good" if for any two values i < j 
present in the sequence, cnt[i] <= cnt[j], where cnt[x] is the count of x in the sequence.

Algorithms/Techniques:
- Bit manipulation and combinatorics
- Enumeration over valid combinations
- XOR operations

Time Complexity: O(n * m * k), where n = 2^k, k is the number of bits in n,
                 and m is the upper bound on elements.
Space Complexity: O(1) - constant extra space (excluding input)

Note: This implementation focuses on handling small constraints due to being 
      the "easy version" of the problem.
"""

for _ in range(int(input())):
    k, m = [int(x) for x in input().split()]
    s = input().strip()
    n = sum(1 for i in s if int(i) & 1)  # Count of set bits in binary representation of n
    a = 0  # Result accumulator
    for k in range(1, n + 1):  # Loop over possible counts of elements in sequence
        if n - k & (k - 1 >> 1):  # Skip invalid combinations using bit trickery
            continue
        for mm in range(1, m):  # Iterate through all valid element values
            if (mm & k - 1) == k - 1:  # Check if this combination satisfies condition
                a ^= mm  # XOR the value into final result
    print(a)


# https://github.com/VaHiX/codeForces/