# Problem: CF 1995 C - Squaring
# https://codeforces.com/contest/1995/problem/C

"""
C. Squaring

Problem Description:
Given an array of integers, we want to make it non-decreasing by replacing elements with their squares.
Each replacement counts as one "act of justice".
We need to find the minimum number of such acts required.

Algorithm:
- Greedily process the array from left to right.
- For each element, determine how many times we must square it to make it >= previous element.
- Track the current maximum value (after squaring) that we can use for comparison.
- If an element is 1 and it's less than our current max, it's impossible to proceed.

Time Complexity: O(n) where n is the total number of elements across all test cases.
Space Complexity: O(1) - only using constant extra space per test case.
"""

for _ in range(int(input())):
    n = int(input())
    p = 1         # Tracks the current value (after possible squaring)
    ans = 0       # Total number of operations
    c = 0         # Count of operations needed for current element
    
    for i in map(int, input().split()):
        # While we can still square the previous value and it's still less than current element
        while p < i and c:
            p *= p    # Square the previous value
            c -= 1    # Reduce count of operations needed for this step
        
        # If we have a 1 and it's smaller than our current max, impossible to fix
        if i == 1 and i < p:
            ans = -1
            break
            
        a = i         # Copy of current element
        # While the square of current (a) is less than our previous value (p)
        while a < p:
            a *= a    # Square it
            c += 1    # Increase operation count
        p = i         # Update previous to current element
        ans += c      # Add operations needed for this element
    
    print(ans)


# https://github.com/VaHiX/codeForces/