# Problem: CF 1976 C - Job Interview
# https://codeforces.com/contest/1976/problem/C

"""
Algorithm: Greedy with precomputation and adjustment
Time Complexity: O(n + m)
Space Complexity: O(n + m)

This solution uses a greedy approach to assign candidates to positions based on their skills.
It precomputes the optimal assignment for all candidates, then adjusts the result for each candidate
by removing them from the team and recalculating the skill based on the remaining assignments.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def solve646():
    n, m = map(int, input().split())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    k = n + m + 1
    res = [0] * k

    def solve1(a):
        s = sum(a)
        for i in range(k):
            res[i] = s - a[i]
        return res

    # If no programmers or testers are needed, simply return sum minus each element
    if n == 0:
        return solve1(b)
    if m == 0:
        return solve1(a)
    
    # Initialize arrays for storing assignment data
    c = [0] * k      # c[i] stores the skill value (either a[i] or b[i]) assigned to candidate i
    t = [-1] * k     # t[i] stores the position type (0 for programmer, 1 for tester) assigned to candidate i
    adj_idx = -1     # Index of the candidate whose removal affects assignment (when no space in either position)
    nn, mm = n, m    # Copy of original n and m

    # Greedily assign each candidate to best available position
    for i in range(k):
        if a[i] > b[i]:  # If programming skill is higher, assign to programmer
            if n > 0:    # If there is still space for programmers
                n -= 1
                c[i] = a[i]
                t[i] = 0
            elif adj_idx == -1:  # First candidate that can't be assigned to their preferred role
                adj_idx = i
                t[i] = 0
            else:  # Assign to tester (no slots left for programmers)
                m -= 1
                c[i] = b[i]
                t[i] = 1
        else:  # If testing skill is higher or equal, assign to tester
            if m > 0:  # If there is still space for testers
                m -= 1
                c[i] = b[i]
                t[i] = 1
            elif adj_idx == -1:  # First candidate that can't be assigned to their preferred role
                adj_idx = i
                t[i] = 1
            else:  # Assign to programmer (no slots left for testers)
                n -= 1
                c[i] = a[i]
                t[i] = 0

    # Calculate total skill of the team
    sc = sum(c)
    # Store the skills of the candidate at adj_idx for use in calculation
    adj = [a[adj_idx], b[adj_idx]]

    # For each candidate, calculate team skill if they were excluded
    for i in range(k):
        if i != adj_idx:  # If current candidate is not the one whose removal causes assignment changes
            if t[i] == t[adj_idx]:  # If same position type as the adjusting candidate
                res[i] = sc - c[i] + adj[t[adj_idx]]  # Remove this person's skill, add adjusted one
            else:
                # If different position, adjust from other position
                res[i] = sc - c[i] + adj[(t[adj_idx] + 1) % 2]
        else:
            # If the current candidate is the one whose removal affects others,
            # then the team skill stays the same (just don't include them)
            res[i] = sc
    return res


res_test = []
for _ in range(int(input())):
    res_test.append(" ".join(map(str, solve646())))
sys.stdout.write("\n".join(map(str, res_test)))


# https://github.com/VaHiX/CodeForces/