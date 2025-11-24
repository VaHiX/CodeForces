# Problem: CF 1089 L - Lazyland
# https://codeforces.com/contest/1089/problem/L

"""
L. Lazyland
Algorithms/Techniques: Greedy algorithm with hash map and sorting
Time Complexity: O(n log n)
Space Complexity: O(n)

The problem involves assigning k jobs to n idlers such that each job is done by exactly one idler,
and each idler does at most one job. Some idlers have already chosen a job; others may need to be
persuaded (at cost b_i) to switch to another job.

Approach:
1. Track the minimum persuasion time needed for each job using a dictionary.
2. For each idler, if their chosen job is not yet assigned, assign it with current persuasion cost.
3. If the job is already assigned, keep track of the cheaper persuasion time in a spare list.
4. If all jobs are assigned, output 0.
5. Otherwise, sort spares and pick the cheapest ones to cover remaining job slots.

Key steps:
- Use dictionary to assign jobs greedily
- Use a list (spares) to store unused costs
- Sort and take minimums to reduce total time spent
"""

import sys

input = sys.stdin.readline
arr = list(map(int, input().split()))
n, k = arr[0], arr[1]
dict = {}  # Dictionary to track job -> minimum persuasion cost
chosen = list(map(int, input().split()))
unfilledCount = k  # Number of jobs not yet assigned
convince = list(map(int, input().split()))
spares = []  # Stores persuasion costs for reassigning idlers
i = 0
while i < n:
    if chosen[i] not in dict.keys():  # If job is not yet assigned
        dict[chosen[i]] = convince[i]  # Assign it with current cost
        unfilledCount -= 1  # Decrease unassigned job count
    else:  # Job already assigned
        if dict[chosen[i]] > convince[i]:  # If we can do better with current idler
            spares.append(convince[i])  # Add the new (cheaper) cost
        else:
            spares.append(dict[chosen[i]])  # Keep the old (more expensive) cost
            dict[chosen[i]] = convince[i]  # Update to new (more expensive) cost
    i += 1
if unfilledCount == 0:  # All jobs assigned
    print(0)
else:
    spares.sort()  # Sort to find minimum persuasion costs
    print(sum(spares[:unfilledCount]))  # Sum up the cheapest ones for unassigned jobs


# https://github.com/VaHiX/codeForces/