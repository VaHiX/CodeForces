# Problem: CF 2172 A - ASCII Art Contest
# https://codeforces.com/contest/2172/problem/A

"""
Problem: ASCII Art Contest
Algorithm/Techniques: Sorting, conditional logic
Time Complexity: O(1) - sorting 3 elements is constant time
Space Complexity: O(1) - only using a fixed-size list

Given three scores, determine if the scores are "close enough" to decide final standings.
If max - min >= 10, output "check again", otherwise output "final median".
"""

gcl = list(map(int, input().split()))  # Read and convert input scores to a list of integers
gcl.sort()  # Sort the scores in non-decreasing order to easily find min, max, and median
# Check if the difference between max and min is less than 10
# If so, print "final" followed by the median (middle element after sorting)
# Otherwise, print "check again"
print(f"final {gcl [1 ]}" if max(gcl) - min(gcl) < 10 else "check again")


# https://github.com/VaHiX/CodeForces/