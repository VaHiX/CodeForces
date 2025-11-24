# Problem: CF 1875 A - Jellyfish and Undertale
# https://codeforces.com/contest/1875/problem/A

"""
Purpose: 
    This code solves the problem of maximizing the time until a bomb explodes in the game Undertale, 
    by optimally choosing when to use tools that increase the bomb's timer. 
    The bomb starts at time 'b', and each second it decreases by 1. 
    Using a tool can increase the timer by a value x_i, but if that puts it above 'a', it resets to 'a'.
    The goal is to find the maximum time until the bomb explodes.

Algorithms/Techniques:
    Greedy approach with preprocessing:
        - For each tool, decide whether using it immediately (or at some point) gives a benefit.
        - A tool can be beneficial if it increases the timer more than the decrease (1) 
          and does not exceed 'a' when used, or if it allows a jump to 'a' and subsequent delays.

Time Complexity: O(n), where n is the number of tools
Space Complexity: O(1), only using a few variables for computation
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    a, b, n = list(map(int, input().split()))
    x = list(map(int, input().split()))
    ans = b  # Start with the initial timer value
    for i in x:
        # If the increase from this tool, when added to 1 (the decrease per second), 
        # exceeds the maximum allowed value 'a', then we should consider using it to 
        # bring the timer up to 'a' (since it can't go higher anyway)
        if i + 1 > a:
            # Special case: if a == 1 and i+1 >= 1, then we'd only get to 1 anyway, 
            # and we won't benefit from using this tool since it can't help delay the bomb further.
            if a == 1 and i + 1 >= 1:
                break
            else:
                # If we use this tool, we can only gain up to (a - 1) time 
                # because after that, even if we use a tool that adds more, we're capped at 'a',
                # and since we lose 1 per second, we effectively gain (a - 1) time
                ans += a - 1
        else:
            # Otherwise, if using the tool doesn't push the timer over 'a', 
            # we just gain the value of the tool itself
            ans += i
    print(ans)


# https://github.com/VaHiX/CodeForces/