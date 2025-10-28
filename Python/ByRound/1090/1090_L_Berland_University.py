# Problem: CF 1090 L - Berland University
# https://codeforces.com/contest/1090/problem/L

"""
Problem: Berland University

Purpose:
This code solves a problem where we have t students, n lectures, and two auditoriums with capacities a and b.
Lectures alternate between auditoriums (odd weeks in first, even in second).
Each student needs to attend at least k lectures to pass the course.
We want to maximize the number of students who can attend at least k lectures.

Algorithms/Techniques:
Greedy approach with binary search or direct calculation.
The key observation is that we distribute students optimally across auditoriums
to maximize the number of students passing the course.

Time Complexity: O(1) - Constant time due to mathematical approach and no loops.
Space Complexity: O(1) - Only using a constant amount of extra space.
"""

t, n, a, b, k = map(int, input().split())
m = n // 2  # Number of odd lectures (first auditorium)
n -= m      # Remaining even lectures
s = min(t, (n * a + m * b) // k) * (k <= n + m)  # Base case: all students can attend if possible
if k > n:
    s = min(s, m * b // (k - n))  # If more than n lectures needed, use only odd week capacity
if k > m:
    s = min(s, n * a // (k - m))  # If more than m lectures needed, use only even week capacity
print(s)


# https://github.com/VaHiX/codeForces/