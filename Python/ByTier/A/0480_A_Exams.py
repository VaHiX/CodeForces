# Problem: CF 480 A - Exams
# https://codeforces.com/contest/480/problem/A

"""
Problem: Valera needs to schedule exams to ensure that the dates recorded in his grade book are in non-decreasing order.
Approach: 
  - For each exam, we can take it either on day `a_i` (scheduled) or `b_i` (early).
  - We want to minimize the final exam date while maintaining non-decreasing order.
  - Greedy strategy: sort exams by their scheduled date `a_i`. For each exam, choose the earliest possible day (`b_i` if valid) such that it doesn't violate the non-decreasing order.

Complexity:
  - Time: O(n log n) due to sorting
  - Space: O(n) for storing the exam data
"""

c = 0
# Read all exam data and sort by scheduled date
for i in sorted([*map(int, s.split())] for s in [*open(0)][1:]):
    # Choose the earliest valid day for this exam
    # If current day c <= early date b_i, then we can use b_i
    # Otherwise, use the scheduled date a_i
    c = i[c <= i[1]]
print(c)


# https://github.com/VaHiX/CodeForces/