# Problem: CF 1970 A3 - Balanced Unshuffle (Hard)
# https://codeforces.com/contest/1970/problem/A3

"""
Balanced Unshuffle (Hard)
Algorithm: Reconstructs the original balanced parentheses sequence from its balanced shuffle.
Approach:
1. Parse the input string to determine layer structure based on balance changes.
2. Reconstruct the original sequence by traversing layers in reverse order, 
   maintaining a current layer index and updating it based on the character popped.
Time Complexity: O(n), where n is the length of the input string.
Space Complexity: O(n), for storing the layers and the result.
"""

from sys import stdin

s = stdin.readline().strip()
layers = [[]]  # Initialize list of layers to store characters by their balance level
cnt_up = 0     # Count of opening parentheses in current layer
expected_down = 0  # Expected number of closing parentheses to complete a layer

# First pass: distribute characters into layers based on balance tracking
for c in s:
    if c == ")":
        if expected_down == 0:
            # Start a new layer when we've finished the current one
            expected_down = cnt_up
            cnt_up = 0
            layers.append([])
        expected_down -= 1  # Decrease expected closing parentheses count
    else:
        cnt_up += 1  # Increment opening parentheses count
    layers[-1].append(c)  # Add character to the current layer

# Second pass: reconstruct original sequence from layers in reverse
curr_layer = 0  # Current layer index to process
result = []  # Resultant sequence being built

# Traverse each character in the original string length
for i in range(len(s)):
    c = layers[curr_layer].pop()  # Pop character from current layer
    result.append(c)  # Append to result
    # Update current layer index depending on whether the character is '(' or ')'
    curr_layer += 1 if c == "(" else -1

print("".join(result))  # Output the reconstructed balanced parentheses sequence


# https://github.com/VaHiX/CodeForces/