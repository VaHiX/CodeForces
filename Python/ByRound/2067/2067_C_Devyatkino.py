# Problem: CF 2067 C - Devyatkino
# https://codeforces.com/contest/2067/problem/C

# /*
# Problem: Minimum operations to make a number contain digit '7'
# Algorithm: For each test case, try adding 9s in different patterns (1*9, 2*9, ..., 9*9)
#            and check how many operations are needed to reach a number containing '7'.
#            The approach tries all combinations of adding digits like 9, 99, 999, etc.
#
# Time Complexity: O(1) per test case (since we loop at most 9 times for each input)
# Space Complexity: O(1) (only using a few variables and list with fixed size)
# */

for i in [*open(0)][1:]:
    t = int(i)  # Read current number
    l = []      # List to store number of operations for each pattern
    n = t       # Save original number for reseting
    for i in range(1, 10):  # Try adding 9, 99, 999, ..., 999999999 (1 to 9 times 9)
        c = 0               # Counter for operations in this pattern
        while "7" not in str(t):  # While the current number doesn't contain '7'
            t += int(i * "9")     # Add next number made of i nines
            c += 1                # Increment operation count
        l += [c]                  # Store count for this pattern
        t = n                     # Reset original number
    print(min(l))                 # Print minimum operations needed


# https://github.com/VaHiX/codeForces/