# Problem: CF 1954 B - Make It Ugly
# https://codeforces.com/contest/1954/problem/B

"""
Code Purpose:
This code solves the problem of finding the minimum number of elements to remove from a beautiful array 
to make it not beautiful. The key insight is based on the observation that a beautiful array can be 
transformed into a uniform array if we can repeatedly apply operations where we replace an element 
with its neighbors if they are equal.

The approach:
- For each element in the array, we check if it is the same as the first element.
- We create a string of spaces and stars where:
  - Space represents elements that are the same as the first element
  - Star represents elements that are different from the first element
- Then we split this string by spaces and find the minimum length of segments of stars.
- This minimum length corresponds to the minimum number of elements that need to be removed.
- If this minimum is 0, that means we can't break the array into segments, which implies the array 
  is already uniform and cannot be made not beautiful, so we return -1.

Algorithms/Techniques:
- String manipulation and pattern recognition
- Linear scanning of array elements
- Splitting strings and analyzing gaps

Time Complexity: O(n), where n is the length of the array.
Space Complexity: O(n), to store the string representation of the array.
"""

for s in [*open(0)][2::2]:
    a = s.split()
    print(min(map(len, "".join(" *"[x == a[0]] for x in a).split())) % len(a) or -1)


# https://github.com/VaHiX/CodeForces/