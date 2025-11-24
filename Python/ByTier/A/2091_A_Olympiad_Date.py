# Problem: CF 2091 A - Olympiad Date
# https://codeforces.com/contest/2091/problem/A

# =====================================================================
# Problem: Determine the minimum number of steps to form the date "01.03.2025"
#          from a sequence of drawn digits.
#
# Algorithm: Greedy approach with frequency counting.
#            - Maintain a target string "01032025" (without dots)
#            - For each digit in input, try to match it to the target
#            - Keep track of how many characters are matched until full match
#            - If we can form a complete date, return step number; else 0
#
# Time Complexity: O(n) where n is the length of the input sequence.
# Space Complexity: O(1) since we use fixed size string and variables.
# =====================================================================

for q in [*open(0)][2::2]:  # Read input lines starting from index 2, step 2 (skip n lines)
    x = q.replace(" ", "")   # Remove spaces from the input line
    y = "01032025"           # Target date string to match
    z = 0                    # Result counter for minimum steps
    
    for i in range(len(x)):  # Iterate through each drawn digit
        y = y.replace(x[i], "", 1)  # Remove one occurrence of the digit from target
        if len(y) == 0:            # If no more digits needed to form date
            z = i + 1              # Record step number (1-indexed)
            break                  # Exit early once full match reached
    
    print(z)  # Output result for current test case


# https://github.com/VaHiX/codeForces/