# Problem: CF 1691 C - Sum of Substrings
# https://codeforces.com/contest/1691/problem/C

"""
Code Purpose:
This code solves the problem of finding the minimum value of f(s) - the sum of all substrings of length 2 in a binary string s - after at most k adjacent swaps. It uses a mathematical approach to compute the result without simulating all swaps.

Algorithms/Techniques:
- Greedy approach with mathematical optimization.
- Uses properties of binary strings and their substrings to compute minimum f(s) value efficiently.
- Uses string reversal and index finding to calculate distances from '1's.

Time Complexity: O(n) where n is the length of the string. Each operation (find, count) is linear.
Space Complexity: O(n) for storing the string and reversed string.

"""

I = input
for _ in [0] * int(I()):
    n, k = map(int, I().split())
    s = I()
    # Find the index of the first '1' and the last '1' (reversed string)
    i, j = (x.find("1") % 8**10 for x in (s, s[::-1]))
    # Compute the minimum f(s) value using precomputed values and conditions
    print(11 * s.count("1") - (k >= i + j < n - 1 or i <= k < j) - 10 * (j <= k))


# https://github.com/VaHiX/CodeForces/