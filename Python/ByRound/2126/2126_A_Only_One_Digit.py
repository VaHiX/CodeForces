# Problem: CF 2126 A - Only One Digit
# https://codeforces.com/contest/2126/problem/A

# Flowerbox
"""
Problem: Find smallest non-negative integer y such that x and y share at least one common digit
Algorithm: Brute force check from 0 upwards
Time Complexity: O(d * log(x)) where d is the number of digits in x (at most 4 for x <= 1000)
Space Complexity: O(log(x)) for storing digits of x
"""

for *s, _ in [*open(0)][1:]:  # Read all lines except first (test cases count), process each line
    x = int(''.join(s))  # Convert the digits back to integer x
    
    # Check from 0 upward until we find a number that shares a digit with x
    for y in range(100000):  # Arbitrary large upper bound to ensure we find solution
        # Create sets of digits for both numbers
        digits_x = set(str(x))  # Get unique digits in x
        digits_y = set(str(y))  # Get unique digits in y
        
        # Check if there's any intersection between sets (common digit exists)
        if digits_x & digits_y:  # If intersection is not empty
            print(y)  # Output the first valid y found
            break  # Stop searching further


# https://github.com/VaHiX/codeForces/