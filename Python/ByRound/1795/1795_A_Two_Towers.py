# Problem: CF 1795 A - Two Towers
# https://codeforces.com/contest/1795/problem/A

"""
Problem: Two Towers
Algorithm/Technique: Simulation with string manipulation and counting
Time Complexity: O(n + m) per test case, where n and m are lengths of the two strings
Space Complexity: O(n + m) due to string concatenation and reversal

This problem involves determining whether we can make two towers "beautiful" by moving 
blocks between them. A tower is beautiful if no two adjacent blocks have the same color.
We simulate the process by concatenating the two strings (reversing the second), then
counting consecutive same-color blocks to check if it's possible to arrange the towers
into a beautiful configuration.
"""

for a in range(int(input())):  # Read number of test cases
    l = input()  # Read n and m (unused in logic but required for input parsing)
    s1 = input()  # First tower string
    s2 = input()[::-1]  # Reverse the second tower string to simulate top block movement
    s = s1 + s2  # Concatenate the two towers
    n = 0  # Counter for consecutive same characters
    for i in range(len(s) - 1):  # Iterate through concatenated string
        if s[i] == s[i + 1]:  # If adjacent characters are same
            n += 1  # Increment counter
    if n < 2:  # If less than two consecutive same characters
        print("YES")  # It's possible to make it beautiful
    else:
        print("NO")  # Otherwise not possible


# https://github.com/VaHiX/codeForces/