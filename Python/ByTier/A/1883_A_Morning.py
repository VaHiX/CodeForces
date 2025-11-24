# Problem: CF 1883 A - Morning
# https://codeforces.com/contest/1883/problem/A

"""
Code Purpose:
This code solves the problem of finding the minimum number of seconds to enter a 4-digit PIN on a special keypad where:
- The keypad layout is a circular arrangement of digits 1-9, followed by 0.
- The cursor starts at digit '1'.
- Each second, you can either press the current digit or move to an adjacent digit.
- The goal is to compute the minimal time to enter the entire PIN.

The approach is:
1. For each digit in the PIN:
   - Add 1 second for pressing the digit.
   - Calculate minimal distance between current cursor position and target digit.
   - Add the distance (as moving takes that many seconds) to total time.

Algorithms/Techniques:
- Simulation with precomputed keypad layout
- Distance calculation on circular arrangement

Time Complexity: O(n * m) where n is number of test cases and m is length of PIN (constant 4)
Space Complexity: O(1) excluding input/output storage
"""

import sys

input_data = sys.stdin.read()


def solution(input_data):
    lines = input_data.strip().split("\n")
    int(lines[0])  # Read number of test cases but don't use it directly
    test_cases = lines[1:]
    # Define the circular keypad layout
    keypad = "1234567890"
    results = []
    for pin in test_cases:
        # Initial cursor position is at '1'
        current_pos = keypad.index("1")
        seconds = 0
        for digit in pin:
            # Press the current digit (1 second)
            seconds += 1
            # Find the target position of the digit
            target_pos = keypad.index(digit)
            # Calculate the distance between current and target positions
            # On a circular keypad, the distance is the minimum of clockwise or counter-clockwise
            distance = abs(target_pos - current_pos)
            # Add the minimal distance to the total seconds
            seconds += distance
            # Update the current position
            current_pos = target_pos
        results.append(seconds)
    output_data = "\n".join(map(str, results))
    return output_data


print(solution(input_data))


# https://github.com/VaHiX/CodeForces/