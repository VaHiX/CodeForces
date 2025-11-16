# Problem: CF 2000 D - Right Left Wrong
# https://codeforces.com/contest/2000/problem/D

# D. Right Left Wrong
# Algorithm: Greedy with sliding window technique.
# Time Complexity: O(n) per test case, where n is the length of the string.
# Space Complexity: O(1), only using a few variables for tracking.

I = input
for _ in [0] * int(I()):
    I()  # Read n (not used directly, just consumes line)
    a = I().split()  # Read array of integers
    s = I()  # Read string of 'L' and 'R'
    
    l = t = 0  # l tracks count of 'L's seen so far; t accumulates total score
    r = s.count("R")  # r tracks remaining 'R's in the string
    
    for x, y in zip(a, s):  # Iterate through elements of a and characters of s together
        l += y < "R"  # Increment l if current char is 'L' (since 'L' < 'R')
        t += min(l, r) * int(x)  # Add contribution from current element to total score
        r -= y > "L"  # Decrement r if current char is 'R' (since 'R' > 'L')
    
    print(t)


# https://github.com/VaHiX/codeForces/