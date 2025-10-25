# Problem: CF 1637 A - Sorting Parts
# https://codeforces.com/contest/1637/problem/A

# Flowerbox
"""
Purpose: Determine if an array can be made unsorted after performing a specific sorting operation.
Algorithm/Technique: 
    - For each test case, check if there exists any valid split length (1 to n-1) such that
      sorting prefix and suffix independently results in an unsorted array.
    - This is done by comparing the original array with its sorted version for each possible split.
Time Complexity: O(n^2 log n) per test case due to sorting operations for up to n splits.
Space Complexity: O(n) for storing the array elements during processing.
"""

# Read all input lines and process every other line starting from index 2 (test cases)
for s in [*open(0)][2::2]:
    # Split the current line into integers and store in 'a'
    a = s.split()
    
    # Create a sorted version of 'a' and compare with original
    # If they are equal, then array is already sorted, so result will be "NO" (index 2)
    # Otherwise, check if sorting prefix/suffix can yield unsorted array
    print("YNEOS"[sorted(a, key=int) == a :: 2])


# https://github.com/VaHiX/codeForces/