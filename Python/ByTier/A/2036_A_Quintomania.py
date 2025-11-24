# Problem: CF 2036 A - Quintomania
# https://codeforces.com/contest/2036/problem/A

# =============================================================================
# Problem: Determine if a melody is "perfect"
# Algorithm: For each melody, compute intervals between adjacent notes,
#            check whether all intervals are either 5 or 7 semitones.
# Time Complexity: O(n) per melody, where n is number of notes
# Space Complexity: O(1), only using constant extra space per melody
# =============================================================================

for s in [*open(0)][2::2]:  # Read input lines starting from index 2, step 2 (i.e., melody data)
    a = (*map(int, s.split()),)  # Convert line to tuple of integers (notes)
    # Compute set of absolute differences between adjacent notes
    # Check if all differences are in {5, 7} using subset comparison
    print("NYOE S"[{abs(x - y) for x, y in zip(a, a[1:])} <= {5, 7} :: 2])  # Output YES/NO based on condition


# https://github.com/VaHiX/codeForces/