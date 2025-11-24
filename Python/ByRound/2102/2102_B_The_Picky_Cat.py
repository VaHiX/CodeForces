# Problem: CF 2102 B - The Picky Cat
# https://codeforces.com/contest/2102/problem/B

# B. The Picky Cat
# Purpose: Determine if the first element of an array can become the median after flipping signs of elements.
# Algorithm: 
# 1. For each test case, sort the absolute values of the array.
# 2. Check how many elements have absolute value less than the first element's absolute value.
# 3. If more than half of the elements are smaller in absolute value, then flipping signs may allow first element to become median.
# Time Complexity: O(n log n) due to sorting
# Space Complexity: O(n) for storing input array

for s in [*open(0)][2::2]:  # Read input lines starting from index 2, stepping by 2 (even indices)
    a = (*map(abs, map(int, s.split())),)  # Convert string line to tuple of absolute values
    print("YNEOS"[sum(x < a[0] for x in a) * 2 > len(a) :: 2])  # Evaluate condition and print YES/NO


# https://github.com/VaHiX/codeForces/