# Problem: CF 1701 E - Text Editor
# https://codeforces.com/contest/1701/problem/E

"""
Text Editor Problem

Algorithm:
This problem uses dynamic programming with three states:
- dp0[j]: minimum moves to make first j chars of t match s[1:i] with cursor at end
- dp1[j]: minimum moves to make first j chars of t match s[1:i] with cursor at beginning  
- dp2[j]: minimum moves to make first j chars of t match s[1:i] with cursor at some position in middle

Transitions:
The key insight is that we can move cursor in different ways and perform operations like backspace.
We maintain three states to represent where the cursor is in the current string s[1:i] that we've built so far.

Time Complexity: O(n * m) where n is length of s and m is length of t
Space Complexity: O(m) as we only store current and previous dp arrays
"""

T = int(input())
for iiii in range(T):
    n, m = map(int, input().split())
    # Prepend "#" to make indexing easier (1-based)
    s = ["#"] + list(input())
    t = ["#"] + list(input())
    
    # dp0: cursor at end of s
    # dp1: cursor at beginning of s  
    # dp2: cursor at middle of s
    dp0 = [10**10] * (m + 3)
    dp1 = [10**10] * (m + 3)
    dp2 = [10**10] * (m + 3)
    
    # Initial state
    dp0[0] = 0
    dp1[0] = 0
    dp2[0] = 1  # cursor starts at end, so 1 move to go to beginning
    
    for i in range(1, n + 1):
        newdp0 = [10**10] * (m + 3)
        newdp1 = [10**10] * (m + 3)
        newdp2 = [10**10] * (m + 3)

        for j in range(m + 1):
            si = s[i]
            tj = t[j]
            if i == j == 0:
                continue
            
            # Move cursor to end and continue
            newdp0[j] = dp0[j] + 2
            
            # If characters match
            if si == tj:
                # We can match character and move to next state
                newdp0[j] = min(newdp0[j], dp0[j - 1] + 1)

            # If characters match, also consider cursor being at beginning or middle
            if si == tj:
                # To go from middle to matching, we need backspace or home + insertion
                newdp1[j] = min(newdp1[j], dp1[j - 1], dp0[j - 1] + 1)

            # Move cursor to end from other positions
            newdp2[j] = min(dp1[j] + 1, dp0[j] + 1 + 1, dp2[j] + 1)

            if si == tj:
                # Match from middle, update state appropriately
                newdp2[j] = min(
                    newdp2[j], dp1[j - 1] + 1, dp0[j - 1] + 1 + 1, dp2[j - 1] + 1
                )

        dp0 = newdp0
        dp1 = newdp1
        dp2 = newdp2
        
    ans = min(dp0[m], dp1[m], dp2[m])
    if ans > 10**8:
        ans = -1
    print(ans)


# https://github.com/VaHiX/CodeForces/