# Problem: CF 2010 A - Alternating Sum of Numbers
# https://codeforces.com/contest/2010/problem/A

# ======================================================================
# Problem: Alternating Sum of Numbers
# Algorithm: Direct computation with alternating signs
# Time Complexity: O(n) where n is the length of the sequence
# Space Complexity: O(n) for storing the input sequence
# ======================================================================

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip test cases count and sequence length)
    (*a,) = map(int, s.split())  # Convert string numbers to integers and unpack into list a
    print(sum(a[::2]) - sum(a[1::2]))  # Sum elements at even indices and subtract sum of elements at odd indices


# https://github.com/VaHiX/codeForces/