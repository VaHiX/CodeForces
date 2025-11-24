# Problem: CF 738 A - Interview with Oleg
# https://codeforces.com/contest/738/problem/A

"""
Algorithm: String Processing with Greedy Matching
Techniques: Two-pointer approach, substring matching

Time Complexity: O(n)
Space Complexity: O(n)

The algorithm processes the input string from left to right. When it encounters 
a "ogo" pattern, it greedily extends the match as far as possible by appending 
"go" repeatedly, replacing the entire filler with "***". This greedy approach 
ensures we match the maximal-length filler starting at each position.

The use of a while loop with manual index incrementing ensures we do not 
reprocess already matched parts of the string, leading to linear time complexity.
"""

n = int(input())
s = input()
interview_text = ""
i = 0

while i < n:
    # Check if current position starts with "ogo"
    if s[i : i + 3] == "ogo":
        # Replace the filler with "***"
        interview_text += "***"
        # Skip ahead by 2 to account for the "ogo" we already matched
        i += 2
        # Continue matching further "go" patterns to extend the filler
        while i + 1 < n and s[i + 1 : i + 3] == "go":
            i += 2
    else:
        # If no "ogo" at current position, just append the character
        interview_text += s[i]
    i += 1

print(interview_text)


# https://github.com/VaHiX/CodeForces/