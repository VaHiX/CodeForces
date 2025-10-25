# Problem: CF 1826 A - Trust Nobody
# https://codeforces.com/contest/1826/problem/A

# Flowerbox:
# Problem: Trust Nobody
# Purpose: Determine the number of liars in a group of people, where each person claims there are at least 'l_i' liars among them.
# Algorithm: Frequency counting and iterative validation.
# Time Complexity: O(n^2) - For each potential number of liars, we iterate through all people to check consistency.
# Space Complexity: O(1) - Only using fixed-size array (size 101) and a few variables.

for s in [*open(0)][2::2]: # Read input lines skipping every other one starting from index 2
    n = len(a := s.split()) # Get length of the list a (number of people)
    b = [0] * 101           # Frequency array to count how many people claim each liar number
    r = i = -1              # r stores result, i is counter for potential liar count
    for x in a:             # For each person's claim
        b[int(x)] += 1      # Increment frequency of that claim value
    for x in b:             # Go through possible number of liars
        i += 1              # Increase current assumption of liar count
        n -= x              # Decrease remaining people by those who made this claim
        r = (r, i)[n == i]  # If remaining people equals assumed liars, update result
    print(r)                # Print the determined number of liars or -1 if impossible


# https://github.com/VaHiX/codeForces/