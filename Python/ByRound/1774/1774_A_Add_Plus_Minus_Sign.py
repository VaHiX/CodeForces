# Problem: CF 1774 A - Add Plus Minus Sign
# https://codeforces.com/contest/1774/problem/A

"""
Code Purpose:
This code solves the problem of assigning '+' and '-' signs between consecutive bits in a binary string to minimize the absolute value of the resulting expression. It uses a greedy approach where it processes the string from left to right, deciding whether to add '+' or '-' based on the current bit and the sign of the previous result.

Algorithms/Techniques:
- Greedy algorithm
- Single pass through the string
- Sign tracking to alternate between positive and negative contributions

Time Complexity: O(n), where n is the length of the input string. Each character is processed exactly once.
Space Complexity: O(n), for storing the output string of signs.
"""

for s in [*open(0)][2::2]:  # Read input lines starting from index 2, skipping test case count
    ans = ""  # Initialize the result string for signs
    sign = 1  # Track the sign of the accumulated value (1 for positive, -1 for negative)
    for x in s.split()[0]:  # Iterate through each character in the binary string
        if x == "0":  # If the character is '0', always add '+'
            ans += "+"
        else:  # If the character is '1', decide sign based on current sign
            ans += "+" if sign > 0 else "-"  # Add '+' if current sign is positive, else '-'
            sign *= -1  # Flip the sign for next iteration
    print(ans[1:])  # Print the result string excluding the first character (which is always '+')


# https://github.com/VaHiX/CodeForces/