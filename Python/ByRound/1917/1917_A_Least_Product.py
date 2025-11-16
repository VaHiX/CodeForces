# Problem: CF 1917 A - Least Product
# https://codeforces.com/contest/1917/problem/A

"""
Algorithm/Technique: Greedy approach
Time Complexity: O(n), where n is the length of the array. We iterate through the array a constant number of times.
Space Complexity: O(n), for storing the input array and performing operations.

This solution determines the minimum product of the array elements by strategically setting elements to 0 or choosing appropriate values.
The key idea is:
1. If there is a zero in the array, the minimum product is already 0.
2. If there are no zeros and the number of negative numbers is even, the minimum product is also 0 (by setting one element to 0).
3. If there are no zeros and the number of negative numbers is odd, the minimum product cannot be 0, so we need to perform one operation to make it 0.
"""

for s in [*open(0)][2::2]:
    print(("1 1 0", 0)["0" in s.split() or s.count("-") % 2])


# https://github.com/VaHiX/CodeForces/