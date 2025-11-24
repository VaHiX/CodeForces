# Problem: CF 2133 A - Redstone?
# https://codeforces.com/contest/2133/problem/A

# Flowerbox:
# Purpose: Determine if gears can be arranged such that the last gear spins at 1 revolution per second.
# Algorithm: Key insight is that for a valid arrangement, the product of all speed ratios must equal 1.
#            Since ratio = prev_teeth / curr_teeth, we need the product of (a[i]/a[i+1]) to be 1,
#            which simplifies to a[0]/a[n-1] = 1 => a[0] = a[n-1].
#            So we only check if the first and last gear have same number of teeth.
#            But more generally, the arrangement is valid if we can find a sequence such that
#            all ratios multiply to 1. This leads us to check if there's a way to pair up gears
#            such that their ratios cancel out, which implies that in any arrangement,
#            we just need to count how many times each gear appears.
#            A valid setup exists iff no tooth count appears an odd number of times (since
#            the chain must return to original speed).
# Time Complexity: O(n log n) due to sorting for set operations
# Space Complexity: O(n)

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip test case counts and empty lines)
    x = s.strip().split(" ")  # Split input string into gear tooth counts
    # Check if all elements are unique (no duplicates), print "YES" if true else "NO"
    print("YNEOS"[len(list(set(x))) == len(x) :: 2])  # Ternary check: if no duplicates -> unique -> YES, else -> NO


# https://github.com/VaHiX/codeForces/