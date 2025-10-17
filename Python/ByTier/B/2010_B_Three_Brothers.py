# Problem: CF 2010 B - Three Brothers
# https://codeforces.com/contest/2010/problem/B

# Flowerbox
"""
Problem: Three Brothers
Task: Determine which brother was late given two brothers who arrived on time
Algorithms/Techniques: Set operations, mathematical approach
Time Complexity: O(1) - constant time due to fixed set size and operations
Space Complexity: O(1) - constant space as sets contain only fixed number of elements

The solution uses the fact that brothers are numbered 1, 2, 3. 
We create a set with all brothers {1, 2, 3} and subtract the set of brothers who arrived on time.
The difference gives us the brother who was late.
"""

# Convert string "123" to set {"1", "2", "3"} representing all brothers
# Convert input to set and subtract it from all brothers set
# Print the remaining element (the late brother) using unpacking (*)
print(*set("123") - set(input()))


# https://github.com/VaHiX/codeForces/