# Problem: CF 2009 B - osu!mania
# https://codeforces.com/contest/2009/problem/B

"""
Problem: osu!mania
Algorithms/Techniques: Simulation
Time Complexity: O(n * 4) = O(n) per test case, where n is the number of rows
Space Complexity: O(n) for storing the column positions

The solution simulates the process of reading the beatmap and identifying the column
where each note ('#') appears. Notes are processed from top to bottom, and the column
indices are stored in reverse order (since the bottommost note is processed first in the problem).
Finally, the result is printed in the correct order.
"""

for tc in range(int(input())):  # Process each test case
    n = int(input())  # Read number of rows
    a = []  # List to store column positions of notes
    for i in range(n):  # For each row
        s = input().strip()  # Read the row string
        for j in range(4):  # Check each column
            if s[j] == "#":  # If note is found
                a.append(j + 1)  # Store column index (1-based)
                break  # Move to next row after finding the note
    for x in reversed(a):  # Print in reverse order (bottom to top)
        print(x, end=" ")
    print()  # New line after test case


# https://github.com/VaHiX/CodeForces/