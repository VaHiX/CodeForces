# Problem: CF 2041 E - Beautiful Array
# https://codeforces.com/contest/2041/problem/E

"""
Problem: Beautiful Array
Algorithm/Techniques: Constructive Algorithm
Time Complexity: O(1)
Space Complexity: O(1)

This solution constructs a valid array with mean 'a' and median 'b' by using a simple
approach: create an array of length 3 where the middle element is the median 'b',
and the other two elements are chosen such that the mean of the array equals 'a'.

The key idea is:
- Let the array be [x, b, y]
- Mean = (x + b + y) / 3 = a -> x + b + y = 3 * a -> x + y = 3 * a - b
- We choose x = 3 * a - b - 50000 and y = 50000 to satisfy the equation.
- The median is b because in a sorted array of size 3, the middle element is the median.
"""

from sys import stdin

input = stdin.readline


def read_int():
    return int(input())


def read_ints():
    return map(int, input().split())


mean, median = read_ints()
left = 3 * mean - median - 50000  # Calculate first element to satisfy mean constraint
right = 50000                     # Set second element to ensure mean condition holds
print(3)
print(left, median, right)


# https://github.com/VaHiX/CodeForces/