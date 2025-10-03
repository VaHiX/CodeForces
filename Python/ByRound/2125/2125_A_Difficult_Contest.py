# Problem: CF 2125 A - Difficult Contest
# https://codeforces.com/contest/2125/problem/A

# Problem: Rearrange contest problems to avoid "FFT" or "NTT" substrings
# Algorithm: Sort characters in reverse order, then check for forbidden patterns
# Time Complexity: O(n log n) where n is the length of string due to sorting
# Space Complexity: O(n) for storing the sorted characters

for s in [*open(0)][1:]:  # Read all lines except first (test cases count)
    # Sort characters in reverse order (largest first) 
    sorted_chars = sorted(s)[::-1]  
    # Join and print result
    print("".join(sorted_chars))


# https://github.com/VaHiX/codeForces/