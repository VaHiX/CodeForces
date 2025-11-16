# Problem: CF 1884 A - Simple Design
# https://codeforces.com/contest/1884/problem/A

"""
Algorithm: Brute-force search for the smallest k-beautiful number >= x
Approach:
    - For each test case, start from x and incrementally check if the digit sum is divisible by k
    - Use a helper function `get` to compute digit sum
    - Time complexity: O(d * log(x)) per test case where d is the average number of digits in the search path
    - Space complexity: O(1)

Time Complexity: O(d * log(x)) per test case, where d is the average number of digits
Space Complexity: O(1)
"""

import sys

input = lambda: sys.stdin.readline().strip()


def get(x):
    # Calculate the digit sum of x
    res = 0
    while x:
        res += x % 10  # Add the last digit
        x //= 10       # Remove the last digit
    return res


for test in range(int(input())):
    x, k = map(int, input().split())  # Read x and k for current test case
    while 1:
        if get(x) % k == 0:  # If digit sum is divisible by k
            break
        x += 1  # Increment x to check next number
    print(x)


# https://github.com/VaHiX/CodeForces/