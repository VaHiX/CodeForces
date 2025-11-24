# Problem: CF 1705 D - Mark and Lightbulbs
# https://codeforces.com/contest/1705/problem/D

"""
Algorithm: 
This problem involves transforming one binary string to another using specific operations.
The key insight is that we can only toggle a bulb at position i (2 <= i <= n-1) if s[i-1] != s[i+1].
This means that each operation changes the middle element of a "pattern" where adjacent elements are different.

Approach:
1. Identify all indices where adjacent characters differ in both the initial and target strings.
2. If the count of such indices is different, or if first/last characters are not equal, transformation is impossible.
3. Calculate the minimum cost by matching the indices from the initial to the target string in an optimal way. This is done by summing the absolute differences between corresponding indices.

Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) for storing the indices.
"""

for _ in range(int(input())): # Process each test case
    n = int(input()) # Read number of lightbulbs
    a, b = input(), input() # Read initial and target strings
    
    a_ = [] # Store indices where adjacent characters differ in initial string
    b_ = [] # Store indices where adjacent characters differ in target string
    
    # Loop through pairs of adjacent characters to find pattern breaks
    for i in range(n - 1):
        if a[i] != a[i + 1]: # If adjacent characters in initial string differ
            a_.append(i)
        if b[i] != b[i + 1]: # If adjacent characters in target string differ
            b_.append(i)
    
    # Check if transformation is possible:
    # 1. Different number of pattern breaks
    # 2. First or last characters do not match
    if len(a_) != len(b_) or a[0] != b[0] or a[-1] != b[-1]:
        print(-1)
        continue
    
    res = 0 # Initialize result counter
    
    # Sum up the absolute differences between corresponding indices
    for i in range(len(a_)):
        res += abs(a_[i] - b_[i])
    
    print(res) # Print the minimum operations required


# https://github.com/VaHiX/CodeForces/