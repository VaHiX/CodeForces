# Problem: CF 1742 A - Sum
# https://codeforces.com/contest/1742/problem/A

# ======================================================================
# Problem: Determine if one of three integers is the sum of the other two
# Algorithm: Sort and check if sum of two smallest equals largest
# Time Complexity: O(1) per test case (sorting 3 elements is constant time)
# Space Complexity: O(1) (only using constant extra space)
# ======================================================================

for s in [*open(0)][1:]:  # Read all lines except first (number of test cases)
    a, b, c = sorted(map(int, s.split()))  # Sort the three numbers
    print("YNEOS"[a + b != c :: 2])  # Check if sum of two smallest equals largest


# https://github.com/VaHiX/codeForces/