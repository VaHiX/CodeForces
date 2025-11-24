# Problem: CF 1862 A - Gift Carpet
# https://codeforces.com/contest/1862/problem/A

"""
Code Purpose:
This code determines whether a given carpet (2D grid of lowercase letters) contains the sequence "vika" 
when read column by column from left to right, selecting exactly one letter per column.

Algorithms/Techniques:
- Greedy approach: For each column from left to right, we search for the next required character of "vika".
- We iterate through columns and rows to match the expected order of characters.
- Once we have matched all four characters in sequence, we stop and check if the collected string matches "vika".

Time Complexity: O(n * m), where n is the number of rows and m is the number of columns.
Space Complexity: O(1), as we only use a constant amount of extra space (variables f and k).
"""

t = int(input())  # Read number of test cases
for _ in range(t):
    n, m = map(int, input().split())  # Read dimensions of carpet
    l = []  # Initialize list to store rows of carpet
    for i in range(n):
        s = input()
        l.append(s)  # Store each row in the list
    
    s = "vika"  # Target string to find
    k = 0       # Index to track which character of "vika" we're looking for
    f = ""      # String to collect matched characters
    
    for i in range(m):  # Iterate over each column
        if k > 3:       # If all characters of "vika" have been matched
            break
        else:
            for j in range(n):  # Iterate over each row in current column
                if l[j][i] == s[k]:  # If character matches expected
                    f += l[j][i]     # Add character to result
                    k += 1           # Move to next character
                    break            # Break inner loop to move to next column
    
    if f == s:  # Check if we successfully found the sequence
        print("YES")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/