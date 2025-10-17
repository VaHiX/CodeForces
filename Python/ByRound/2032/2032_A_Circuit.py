# Problem: CF 2032 A - Circuit
# https://codeforces.com/contest/2032/problem/A

# Flowerbox
"""
Problem: Circuit Light Toggle

Purpose:
Given a circuit with n lights and 2n switches, where each light is connected to exactly two switches,
and each switch is connected to exactly one light, determine the minimum and maximum number of lights
that can be on based on the given switch states.

Each switch toggles the state of its connected light. We are given the state of all 2n switches.
We need to find how many lights can potentially be on, considering different valid arrangements
of connections between switches and lights.

Algorithms/Techniques:
- Greedy approach for minimizing/maximizing lights turned on
- Counting zeros and ones in input

Time Complexity: O(n) per test case, as we iterate through the input once to count 0s and 1s.
Space Complexity: O(1), as we use only a constant amount of extra space regardless of input size.

Input:
- First line contains t (number of test cases)
- For each test case:
    - Line 1: n (number of lights)
    - Line 2: 2n integers representing switch states (0 = off, 1 = on)

Output:
- For each test case, two integers: min lights on, max lights on
"""

# Code with inline comments
for s in [*open(0)][2::2]:  # Iterate over every second line starting from index 2 (input lines for switch states)
    m, k = map(s.count, "01")  # Count number of 0s (m) and 1s (k) in the string s
    print(m % 2, min(m, k))   # Print minimum lights on (m mod 2) and maximum lights on (min(m, k))


# https://github.com/VaHiX/codeForces/