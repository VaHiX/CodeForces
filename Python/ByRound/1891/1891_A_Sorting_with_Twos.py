# Problem: CF 1891 A - Sorting with Twos
# https://codeforces.com/contest/1891/problem/A

# /*
# Problem: Sorting with Twos
# Algorithm/Technique: Greedy with bit manipulation and prefix checks
# Time Complexity: O(n * log n) per test case due to sorting operations inside the loop
# Space Complexity: O(n) for storing the array and sorting temporary slices
#
# The problem allows subtracting 1 from the first 2^m elements of an array.
# We can use a greedy check on subarrays of size 2^i for i=0..4 to see if we can make
# any increasing pair. If such a pair exists, then it is not possible to sort the array.
#
# For each input line:
# - Read array elements from stdin
# - For all powers of 2 (1, 2, 4, 8, 16) up to n:
#   - Take a slice of size 2^i starting at position 2^i
#   - Sort that slice and compare with original
#   - If it's not sorted, return NO ("N" in "YNEOS")
# - Otherwise return YES ("Y" in "YNEOS")
# */

for s in [*open(0)][2::2]:  # Read input lines starting from index 2, step 2 (skip n values)
    (*a,) = map(int, s.split())  # Parse line into list of integers
    print("YNEOS"[any(sorted(x := a[1 << i : 1 << i + 1]) < x for i in range(5)) :: 2])  # Check if any slice is not sorted after sorting and output result


# https://github.com/VaHiX/codeForces/