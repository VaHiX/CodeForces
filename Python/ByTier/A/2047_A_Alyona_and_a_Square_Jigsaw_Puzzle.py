# Problem: CF 2047 A - Alyona and a Square Jigsaw Puzzle
# https://codeforces.com/contest/2047/problem/A

# A. Alyona and a Square Jigsaw Puzzle
# Algorithms/Techniques: Simulation, Layer Completion Check
# Time Complexity: O(n^2) where n is the number of days (due to nested operations in sum calculation)
# Space Complexity: O(1) - only uses a constant amount of extra space

for s in [*open(0)][2::2]:  # Read input lines skipping first two, then every second line starting from index 2
    t = 0  # t tracks the total number of pieces placed so far
    print(sum((t := t + int(x)) ** 0.5 % 2 == 1 for x in s.split()))  # For each day's piece count x:
        # Update t with x (t += x), compute sqrt(t), check if it's odd (sqrt(t) % 2 == 1)
        # Sum up all days where this condition is true


# https://github.com/VaHiX/codeForces/