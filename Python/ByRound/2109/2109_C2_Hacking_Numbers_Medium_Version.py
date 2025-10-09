# Problem: CF 2109 C2 - Hacking Numbers (Medium Version)
# https://codeforces.com/contest/2109/problem/C2

"""
C2. Hacking Numbers (Medium Version)

Algorithms/Techniques: 
- Interactive problem solving using fixed command sequences
- Mathematical operations to manipulate unknown integer x to match target n
- Digit sum operation to reduce number size, followed by division for further reduction

Time Complexity: O(1) - Fixed number of operations per test case (4 commands)
Space Complexity: O(1) - Only storing a few variables regardless of input size

This solution works by:
1. First resetting x to 9 (assuming initial value is 9)
2. Adding the difference between target and 9 to reach target
3. Then using a fixed sequence of digit sum + division to simplify any remaining large numbers
"""

for i in range(int(input())):
    print(f"mul 9\ndigit\ndigit\nadd {int(input())-9}\n!")  # Apply fixed command sequence to solve
    for j in range(5):  # Read 5 responses from jury (1 for each command plus final "!")
        input()


# https://github.com/VaHiX/codeForces/