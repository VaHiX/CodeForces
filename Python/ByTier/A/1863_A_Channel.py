# Problem: CF 1863 A - Channel
# https://codeforces.com/contest/1863/problem/A

"""
Problem: Determine if all subscribers have read a post based on online/offline notifications.

Algorithms/Techniques:
- Simulation of subscriber online/offline events
- Tracking minimum and maximum possible online subscribers
- Greedy approach to determine certainty

Time Complexity: O(q) where q is the number of notifications
Space Complexity: O(1) - only using a few variables for tracking

The solution works by:
1. Tracking how many subscribers could be offline at any point ('l' tracks this)
2. Tracking how many online events occurred ('k' tracks this)
3. Using these to determine if all subscribers could have read the post
4. Checking if the final state allows all subscribers to have read the post
"""

I = input
for _ in [0] * int(I()):
    n, a, q = map(int, I().split())  # n: total subscribers, a: initial online, q: notifications
    k = l = m = 0  # k: net online changes, l: minimum offline count, m: total offline events
    for x in I():  # process each notification
        if "+" < x:  # if online event
            k += 1  # increase net online count
        else:  # if offline event
            m += 1  # increment offline count
            l += k < 1  # if no one online, increment offline counter
            k -= k > 0  # decrease online count if possible
    # Determine result based on whether constraints are met
    print(("YES", "MAYBE", "NO")[(m < n - a) + (l < n - a)])


# https://github.com/VaHiX/CodeForces/