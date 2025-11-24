# Problem: CF 1812 I - Mountain Climber
# https://codeforces.com/contest/1812/problem/I

"""
Problem: Mountain Climber
Algorithm: String parsing with balance tracking
Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) - only using constant extra space

This problem checks if a string represents a valid "mountain" pattern.
The idea is to simulate a mountain where:
- Letters 'b', 'd', 'f', 'h', 'k', 'l', 't' represent upward steps (h += 1)
- Letters 'g', 'j', 'p', 'q', 'y' represent downward steps (h -= 1)
- The mountain must never go below ground level (h >= 0)
- The mountain must end at ground level (h == 0)
"""

for _ in range(int(input())):  # Read number of test cases
    s = input()  # Read the input string
    h = 0  # Current height (initially at ground level)
    ok = True  # Flag to track if the string is valid
    
    for c in s:  # Iterate through each character in the string
        if c in "bdfhklt":  # If character represents upward step
            h += 1  # Increase height
        elif c in "gjpqy":  # If character represents downward step
            h -= 1  # Decrease height
        if h < 0:  # If we go below ground level
            ok = False  # Mark as invalid
    if h != 0:  # If we don't end at ground level
        ok = False  # Mark as invalid
    print("YES" if ok else "NO")  # Print result


# https://github.com/VaHiX/CodeForces/