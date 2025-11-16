# Problem: CF 1039 A - Timetable
# https://codeforces.com/contest/1039/problem/A

"""
Algorithm: Difference Array + Greedy Construction
Time Complexity: O(n)
Space Complexity: O(n)

This solution uses a difference array technique to determine whether a valid timetable exists,
and then greedily constructs a valid timetable for stop B.

The key idea is to use difference array to track the constraints on the arrival times.
For each bus that departs at time a[i], it can arrive at position x[i]. We process the constraints
and ensure that the resulting sequence b is valid and satisfies all conditions.

The algorithm works by:
1. Using a difference array S to represent constraints on valid arrival positions
2. Checking if the constraints are feasible (non-negative prefix sum)
3. Constructing the b array greedily from right to left with appropriate adjustment rules
4. Validating the final constructed timetable
"""

import sys

input = lambda: sys.stdin.readline()[:-1]
ni = lambda: int(input())
na = lambda: list(map(int, input().split()))
yes = lambda: print("yes")
Yes = lambda: print("Yes")
YES = lambda: print("YES")
no = lambda: print("no")
No = lambda: print("No")
NO = lambda: print("NO")

n, t = na()
a = na()
x = na()

# Difference array to track valid arrival position constraints
S = [0] * (1 + n)
for i in range(n):
    S[x[i]] -= 1  # Mark that at position x[i], we have one less valid arrival
    S[i + 1] += 1  # Mark that after position i+1, we gain one more valid arrival
# Compute prefix sum to get actual constraint counts
for i in range(n):
    S[i + 1] += S[i]

# Check if constraint is feasible and x is non-decreasing
if all(x >= 0 for x in S) and all(x[i] <= x[i + 1] for i in range(n - 1)):
    b = [-1] * n  # Initialize b array
    FLAG = 1  # Flag to check special conditions
    
    # Process from right to left
    for i in range(n - 1, -1, -1):
        # Case 1: Same x value as previous bus & previous bus has a smaller x
        if i > 0 and x[i - 1] == x[i] and (i == n - 1 or x[i] < x[i + 1]):
            if x[i] < n and a[x[i]] - a[x[i] - 1] == 1:
                FLAG = 0  # Special condition violated
            b[i] = a[x[i] - 1] + 1  # Set b[i] to a[x[i]-1]+1
        elif i < n - 1 and x[i] == x[i + 1]:
            # Case 2: Same x value as next bus - set b[i] to be one less than next
            b[i] = b[i + 1] - 1
        else:
            # Case 3: Normal case - set b[i] to a[x[i]-1]
            b[i] = a[x[i] - 1]
    
    # Final validation
    if FLAG and all(b[i] < b[i + 1] for i in range(n - 1)):
        Yes()
        print(*[x + t for x in b])  # Add t to get actual arrival times
    else:
        No()
else:
    No()


# https://github.com/VaHiX/CodeForces/