# Problem: CF 2021 A - Meaning Mean
# https://codeforces.com/contest/2021/problem/A

# ==============================================================================
# Problem: Maximum Possible Final Element After Pairwise Operations
# Algorithm: Greedy with Sorting
# Time Complexity: O(n log n) per test case due to sorting; overall O(t*n*log n)
# Space Complexity: O(n) for storing the array
# ==============================================================================

for s in [*open(0)][2::2]:  # Read input lines, skipping every other line (test cases and arrays)
    p, *a = sorted(map(int, s.split()))  # Sort the array and unpack first element as `p`, others as `a`
    for x in a:  # Process each element in the sorted array
        p = x + p >> 1  # Compute floor of (x + p) / 2 using bit shift (equivalent to // 2)
    print(p)  # Output final result


# https://github.com/VaHiX/codeForces/