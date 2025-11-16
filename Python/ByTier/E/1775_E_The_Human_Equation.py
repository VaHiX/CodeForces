# Problem: CF 1775 E - The Human Equation
# https://codeforces.com/contest/1775/problem/E

"""
Algorithm: Prefix Sum and Range Tracking
Purpose: To determine the minimum number of operations required to reduce all elements of the sequence to zero by applying specific operations on subsequences.
The key insight is that each operation affects the prefix sums of the array in a predictable way.
We compute prefix sums and track the maximum and minimum values of these prefix sums.
The difference between the maximum and minimum prefix sums gives us the minimum number of operations needed.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(n) for storing the prefix sum array.

This solution leverages the fact that each operation effectively adds or subtracts 1 from a range of values 
in the prefix sum array, and the total number of such operations needed is determined by the range 
between the highest and lowest prefix sums.
"""

from sys import stdin

input = lambda: stdin.readline()[:-1]
t = int(input())
for u in range(0, t):
    n = int(input())
    a = list(map(int, input().split()))
    data = [0] * (n + 1)  # Prefix sum array initialized with zeros
    max_ = 0              # Tracks maximum prefix sum encountered
    min_ = 0              # Tracks minimum prefix sum encountered
    for i in range(1, n + 1):
        # Compute prefix sum at position i
        data[i] = data[i - 1] + a[i - 1]
        # Update maximum prefix sum
        if max_ < data[i]:
            max_ = data[i]
        # Update minimum prefix sum
        if min_ > data[i]:
            min_ = data[i]
    # The result is the difference between max and min prefix sums
    print(max_ - min_)


# https://github.com/VaHiX/CodeForces/