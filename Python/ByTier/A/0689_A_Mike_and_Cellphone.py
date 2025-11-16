# Problem: CF 689 A - Mike and Cellphone
# https://codeforces.com/contest/689/problem/A

"""
Code Purpose:
This program determines whether a given phone number can be uniquely represented 
by the finger movements on a traditional telephone keypad. It checks if there exists 
another distinct phone number that would produce the exact same sequence of finger movements.

Algorithms/Techniques:
- Frequency counting of digits in the input number
- Logical checks for horizontal and vertical movement patterns on the keypad
- Comparison logic to determine uniqueness of finger movements

Time Complexity: O(n) where n is the length of the input number string.
Space Complexity: O(1) as we use a fixed-size array of size 10 and a few variables.

The approach is based on the observation that if a number has finger movements 
that are identical to another, it must share the same pattern of horizontal and vertical 
movements that can be uniquely defined by digit positions.
"""

n = int(input())
number = input()
number = str(number)


a = [0] * 10  # Array to count frequency of each digit (0-9)
for i in number:
    l = int(i)
    a[l] += 1  # Count occurrences of each digit


# Check for horizontal movement patterns
# A horizontal movement is possible if there are digits from both top and bottom rows
horizontal = (
    a[0] != 0  # If 0 is present
    or (a[1] != 0 or a[4] != 0 or a[7] != 0)  # Or if any digit from top-middle-bottom row is present
    and (a[3] != 0 or a[6] != 0 or a[9] != 0)  # And if any digit from bottom-middle-top row is present
)

# Check for vertical movement patterns
# A vertical movement is possible if there are digits from both left and right columns
vertical = (a[1] != 0 or a[2] != 0 or a[3] != 0) and (  # If any digit from left-middle-right column is present
    a[7] != 0 or a[0] != 0 or a[9] != 0  # And if any digit from right-middle-left column is present
)


if horizontal and vertical:
    print("YES")  # Unique finger movements, so only one possible number
else:
    print("NO")  # Non-unique finger movements, multiple numbers possible


# https://github.com/VaHiX/CodeForces/