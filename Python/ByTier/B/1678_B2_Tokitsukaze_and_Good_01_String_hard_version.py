# Problem: CF 1678 B2 - Tokitsukaze and Good 01-String (hard version)
# https://codeforces.com/contest/1678/problem/B2

"""
Code Purpose:
This code determines the minimum number of operations needed to make a binary string "good" (where all contiguous segments have even lengths) and also finds the minimum number of such segments possible in any optimal solution.

Algorithms/Techniques:
- Uses a greedy approach by iterating through the string in pairs of characters.
- Compares adjacent characters to determine if changes are needed.
- Tracks the number of operations (a) and the number of segments (b) needed.
- Time Complexity: O(n), where n is the length of the string.
- Space Complexity: O(1), as only a few variables are used.
"""

for _ in range(int(input())):
    n = int(input())  # Read length of string
    a = b = 0  # a: operations count, b: segment count
    c = "-"  # previous character, initialized to something invalid
    
    # Iterate over the string two characters at a time
    for x, y in zip(*[iter(input())] * 2):
        if x != y:  # If characters in pair differ, one change is needed
            a += 1
        else:  # If same, check if a new segment starts
            b += x != c  # Increment b if current char differs from previous
            c = x  # Update previous character
            
    # Output: minimum operations and minimum segments
    print(a, max(1, b))


# https://github.com/VaHiX/CodeForces/