# Problem: CF 2061 G - Kevin and Teams
# https://codeforces.com/contest/2061/problem/G

"""
G. Kevin and Teams

Purpose:
This code solves an interactive problem where we need to find the maximum number of teams (k) that can be formed from n classmates,
such that all teams either consist of friends or non-friends, regardless of the actual relationships.

Algorithm:
- The approach uses a greedy method with a stack-based data structure.
- It queries friendships to group people into friend/non-friend groups and then forms teams accordingly.
- The algorithm makes at most n queries and outputs k teams at the end.

Time Complexity: O(n^2) in worst case due to nested operations, but actual performance is bounded by n queries.
Space Complexity: O(n) for storing intermediate data structures like s (stack) and t (team list).

Techniques Used:
- Adaptive interaction handling
- Stack-based grouping of related items
- Greedy team forming logic
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
printerr = (
    lambda *args, **kwargs: print(
        "\u001b[31m", *args, "\u001b[0m", file=sys.stderr, **kwargs
    )
    or len(args) == 1
    and args[0]
    or args
)


def main():
    n = int(input())
    k = (n + 1) // 3  # Maximum possible teams we claim to form based on theory
    print(k, flush=True)
    t = []  # List to store tuples of teams that meet the condition (i.e., all friend or all non-friend)
    s = []  # Stack to hold potential team members based on queries
    c = 0   # Variable to track if current group has same friendship status as previous ones
    
    for i in range(1, n + 1):  # Iterate through all classmates
        
        if not s:  # If stack is empty, just start building with first member
            s.append(i)
        else:
            print("?", s[-1], i, flush=True)  # Query if last stacked person and current are friends
            x = int(input())
            assert x != -1  # Ensure valid response from interactor
            
            if len(s) < 2 or x == c:  # If less than 2 already in stack OR friendship status matches
                s.append(i)
                c = x
            else:  # Conflict in friendship status, time to finalize a team
                m = s.pop()  # Pop the most recent added member
                v = s.pop()  # Pop second to last
                t.append((v, i, m) if x else (i, v, m))  # Add tuple to teams list
    
    # Extract elements from stack and team list for final answer formation
    a = s[: min(len(s) // 2 * 2, k * 2)]  # Take only up to 2k members that can form up to k teams
    # Use remaining slots in the answer based on available teams
    a += [x for p in t[: (k * 2 - len(a)) // 2] for x in (p[c], p[2])]  
    print("!", *a, flush=True)


tcs = int(input())
for tc in range(tcs):
    main()


# https://github.com/VaHiX/codeForces/