# Problem: CF 1812 G - Colour Vision
# https://codeforces.com/contest/1812/problem/G

"""
Task: Determine if two strings of equal length can be made identical by changing characters.
Algorithm: Greedy approach - check each position and verify that the characters at that position are the same.
Time Complexity: O(n) where n is the length of the strings
Space Complexity: O(1) - only using a constant amount of extra space

Techniques:
- Bitwise AND operation (&) to combine boolean values
- Direct character comparison
- Single pass through the strings
"""

if __name__ == "__main__":
    t = int(input())  # Read number of test cases
    for _ in range(t):
        n = int(input())  # Read length of strings
        a = input()       # Read first string
        b = input()       # Read second string
        ok = True         # Initialize result flag
        for i in range(n):  # Iterate through each position
            # Check if both characters are 'R' or both are not 'R'
            # Using boolean equivalence: (a[i] == "R") == (b[i] == "R")
            ok &= (a[i] == "R") == (b[i] == "R")
        print("YES" if ok else "NO")  # Print result based on flag


# https://github.com/VaHiX/CodeForces/