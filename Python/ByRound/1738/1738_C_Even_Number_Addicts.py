# Problem: CF 1738 C - Even Number Addicts
# https://codeforces.com/contest/1738/problem/C

"""
Algorithm: Game Theory on Odd/Even Numbers
Purpose: Determine the winner of a game where Alice and Bob alternately pick numbers from a sequence,
         with Alice winning if the sum of her picked numbers is even, otherwise Bob wins.
        
Time Complexity: O(n) for each test case, where n is the length of the sequence.
Space Complexity: O(1), only using a few variables for computation.

Techniques:
- Counting odd and even numbers in the sequence.
- Applying game theory logic based on parity of counts.
"""

for _ in range(int(input())):
    n = int(input())
    # Count number of odd numbers in the sequence
    b = sum([*map(lambda x: int(x) % 2, input().split())])
    # Count number of even numbers
    a = n - b
    # Determine the winner based on game theory conditions
    print(["Alice", "Bob"][b % 4 == 2 or not (b % 4 in [0, 3] or a % 2)])


# https://github.com/VaHiX/CodeForces/