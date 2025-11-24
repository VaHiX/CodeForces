# Problem: CF 2005 B1 - The Strict Teacher (Easy Version)
# https://codeforces.com/contest/2005/problem/B1

"""
B1. The Strict Teacher (Easy Version)

Algorithms/Techniques: 
    - Greedy strategy with optimal move simulation on a 1D line.
    - For each query, calculate the minimum number of moves required for teachers to catch David when both sides play optimally.
    
Time Complexity: O(1) per test case
Space Complexity: O(1)

The problem involves two teachers chasing David in a 1D line. Both players (teachers and David) play optimally:
- David tries to maximize the number of moves until caught.
- Teachers try to minimize it.

In an optimal strategy, David will move towards the midpoint between the two teachers if possible, or toward the edge if he's closer than halfway. 
The minimum distance from David to closest teacher (in one direction) gives us the time needed.
"""

for _ in range(int(input())):
    n = int(input().split()[0])  # Read n from first line of input
    a, b = sorted(map(int, input().split()))  # Get sorted positions of two teachers
    p = int(input())  # Position of David
    # If David is to the left of the first teacher, he can move towards left (1) to avoid capture for (a - 1) steps
    # If David is to the right of the second teacher, he can move towards right (n) to avoid capture for (n - b) steps
    # Otherwise, he's in between, and optimal play leads to a solution based on distance to closest teacher
    print(a - 1 if p < a else n - b if p > b else (b - a) // 2)


# https://github.com/VaHiX/codeForces/