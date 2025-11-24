# Problem: CF 2169 D1 - Removal of a Sequence (Easy Version)
# https://codeforces.com/contest/2169/problem/D1

"""
Purpose: 
  This code solves the problem of determining the k-th element in a sequence 
  after repeatedly removing elements at positions y, 2*y, 3*y, ..., m*y 
  for x iterations. The algorithm uses mathematical reasoning to avoid 
  simulating the full process, which is too slow due to the large size of the 
  initial sequence (up to 10^12).

Algorithms/Techniques:
  - Mathematical simulation: Instead of simulating removals, we compute
    how many elements remain after each step using the formula:
    new_length = current_length - current_length // y
  - Reverse calculation of position: We simulate the inverse process to 
    determine where the k-th element ends up in the final sequence.

Time Complexity: O(x), since we iterate x times for each test case.
Space Complexity: O(1), as only a constant amount of extra space is used.
"""

s = set()
for _ in range(int(input())):  # Read number of test cases
    x, y, k = map(int, input().split())  # Read x, y, k for current test case
    curn = 10**12  # Start with full sequence of length 10^12
    
    # Simulate the removal process x times
    for i in range(x):
        curn -= curn // y  # Remove every y-th element, update current length
    
    # If k is beyond the final sequence length, output -1
    if curn < k or y == 1:
        print(-1)
        continue

    ans = k  # Start with the position in the final sequence
    
    # Reverse simulate to compute what index in the original sequence maps to k-th position
    for i in range(x):
        ans += (ans - 1) // (y - 1)
    
    print(ans)  # Output the result


# https://github.com/VaHiX/CodeForces/