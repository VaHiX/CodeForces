# Problem: CF 1733 C - Parity Shuffle Sorting
# https://codeforces.com/contest/1733/problem/C

"""
Algorithm: Parity Shuffle Sorting
Techniques: Greedy approach with parity checking

Time Complexity: O(n) for each test case, where n is the length of the array
Space Complexity: O(n) for storing the array

The solution works by:
1. First, we ensure the first element is "correct" by making it equal to the last element if necessary (based on parity).
2. Then, we iterate through the array from the third element onwards and adjust elements based on parity.
"""

for __ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    print(n - 1)
    if n > 1:
        print(1, n)
    for i in range(2, n):
        if (a[i - 1] + a[0]) % 2 == 1:
            print(1, i)
        else:
            print(i, n)


# https://github.com/VaHiX/CodeForces/