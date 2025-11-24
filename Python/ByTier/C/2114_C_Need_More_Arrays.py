# Problem: CF 2114 C - Need More Arrays
# https://codeforces.com/contest/2114/problem/C

"""
C. Need More Arrays

Algorithm:
This problem involves maximizing the number of arrays created by a specific grouping algorithm. 
The key idea is to greedily decide when to start a new array based on the condition:
if current_element > previous_element + 1, then start a new array.

Approach:
- Iterate through the sorted array.
- Keep track of the last element added to the current array (`c`).
- When encountering an element that is greater than `c + 1`, increment the count of arrays (`o`) and update `c` to this new element.
- This greedy strategy ensures we form as many arrays as possible by delaying the start of a new array as long as possible.

Time Complexity: O(n) where n is the number of elements in the array. We process each element exactly once.
Space Complexity: O(1) - only using a constant amount of extra space.
"""

for _ in range(int(input())):  # Process each test case
    n = int(input())           # Read size of the array
    a = list(map(int, input().split()))  # Read the array elements
    o = 0                      # Count of arrays formed
    c = -1                     # Last element added to current array (-1 means no array started yet)
    
    for i in a:                # Iterate over each element in the array
        if i > c + 1:          # If this element cannot be part of the current array
            o += 1             # Start a new array
            c = i              # Update the last element in the new array
    print(o)                   # Print the total number of arrays formed


# https://github.com/VaHiX/CodeForces/