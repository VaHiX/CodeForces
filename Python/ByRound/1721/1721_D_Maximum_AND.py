# Problem: CF 1721 D - Maximum AND
# https://codeforces.com/contest/1721/problem/D

"""
Problem: Maximum AND
Algorithm: Greedy bit-by-bit construction
Time Complexity: O(30 * n * log(n)) = O(n * log(n)) per test case
Space Complexity: O(n) for storing arrays and intermediate results

Approach:
We want to maximize the bitwise AND of the array c where c[i] = a[i] XOR b[i].
To do this greedily, we iterate through bits from the most significant to least.
For each bit position, we try to set it to 1 in the result if possible.

We use the fact that for a fixed prefix of the answer, we can check whether 
there exists a way to assign elements of b to elements of a such that 
the AND of all (a[i] XOR b[i]) is at least the current prefix.

This is done by checking if the sorted arrays of (a[i] & ans) and (~b[i] & ans) 
are equal, ensuring a good assignment exists.
"""

t = int(input())
while t > 0:
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    res = 0
    bit = 1 << 29  # Start from the most significant bit (bit 29)
    while bit > 0:
        ans = res | bit  # Try setting the current bit to 1
        # Check if we can achieve this prefix
        # Sort based on how bits match the current answer prefix
        if sorted(i & ans for i in a) == sorted(~i & ans for i in b):
            res = ans  # If valid, update result
        bit >>= 1  # Move to the next lower bit

    print(res)
    t -= 1


# https://github.com/VaHiX/CodeForces/