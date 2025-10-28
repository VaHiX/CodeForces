# Problem: CF 2038 A - Bonus Project
# https://codeforces.com/contest/2038/problem/A

"""
Problem: Optimal Work Distribution Among Engineers to Complete a Project

Algorithms/Techniques: Greedy approach with backward iteration
Time Complexity: O(n)
Space Complexity: O(n)

The problem involves n engineers deciding how much work to contribute to a project 
that requires k units of work to be completed. Each engineer has a bonus a[i] and a 
cost b[i] per unit of work. An engineer will contribute c[i] units if it maximizes 
their benefit s[i] = a[i] - c[i] * b[i]. The solution uses backward iteration to 
determine optimal contribution from each engineer, assuming all others have already 
contributed optimally.

Input:
- n: number of engineers
- k: required work units
- a: bonuses for each engineer
- b: cost per unit of work for each engineer

Output:
- c: optimal contribution of each engineer
"""

n, k = map(int, input().split())
a = list(map(int, input().split()))
b = list(map(int, input().split()))
c = [0] * n
s = 0
for i in range(n - 1, -1, -1):  # iterate from last to first engineer
    temp = a[i] // b[i]  # maximum units engineer i can contribute while still having positive benefit
    if s + temp <= k:  # if adding all these units doesn't exceed total required work
        c[i] = temp  # assign all possible units
    else:
        c[i] = k - s  # assign remaining units needed to complete project
    s += c[i]  # update total work completed so far
if sum(c) >= k:  # if enough work was contributed to finish the project
    print(*c)
else:
    print("0 " * n)  # if not enough work, no one contributes


# https://github.com/VaHiX/codeForces/