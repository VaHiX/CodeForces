# Problem: CF 1950 E - Nearly Shortest Repeating Substring
# https://codeforces.com/contest/1950/problem/E

"""
Problem: Nearly Shortest Repeating Substring
Algorithm: Brute-force approach checking all possible lengths of repeating substrings.
Time Complexity: O(n^3) in the worst case due to string comparisons and iteration over all divisors.
Space Complexity: O(n) for storing the substring and auxiliary variables.

Approach:
- For each possible length l from 1 to n//2:
  - Check if l divides n (i.e., n % l == 0)
  - Split the string s into parts of length l
  - Try to determine a repeating pattern that matches most of the parts,
    allowing at most one mismatch.
  - If valid pattern found, return l.
- If no such pattern exists, return n (entire string is the answer).
"""

t = int(input())


def similar(s1, s2):
    # Check if two strings differ in at most one position
    if len(s1) != len(s2):
        return False
    hit = False
    for i in range(len(s1)):
        if s1[i] != s2[i]:
            if hit:
                return False
            hit = True
    return True


def solve(n, s):
    # Iterate through all potential repeating substring lengths
    for l in range(1, n // 2 + 1):
        if n % l == 0:  # Only consider lengths that divide n evenly
            main = ""       # The main repeating pattern
            maincount = 0   # Number of times main appears
            extra = ""      # A different pattern (if needed)
            valid = True    # Whether current candidate is valid
            
            # Process each group of length l
            for j in range(n // l):
                c = s[j * l : (j + 1) * l]  # Extract substring of length l

                # If no main pattern yet, assign it
                if main == "":
                    main = c
                    maincount = 1
                elif main == c:
                    # Same as main pattern, increment count
                    maincount += 1
                else:
                    # First mismatch
                    if extra == "":
                        # Check if this is similar to main (allowing at most 1 difference)
                        if similar(main, c):
                            extra = c  # Store this as alternative pattern
                        else:
                            valid = False  # Not similar, invalid
                            break
                    elif maincount < 2 and c == extra:
                        # Swap main and extra, and increment main count
                        main, extra = extra, main
                        maincount += 1
                    else:
                        valid = False  # Either not matching or already 2+ main counts and mismatch
                        break
            if valid:
                return l
    return n  # If no valid shorter pattern found, return full length


for i in range(t):
    n = int(input())
    s = input()
    print(solve(n, s))


# https://github.com/VaHiX/CodeForces/