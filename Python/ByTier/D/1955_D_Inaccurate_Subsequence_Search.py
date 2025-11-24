# Problem: CF 1955 D - Inaccurate Subsequence Search
# https://codeforces.com/contest/1955/problem/D

"""
Algorithm: Sliding Window with Frequency Counting
Purpose: Count the number of subsegments of array 'a' of length 'm' that can be rearranged to have at least 'k' matching elements with array 'b'.

Approach:
- Use a sliding window of size 'm' over array 'a'
- Maintain frequency counts for elements in current window and in 'b'
- For each window, calculate how many elements in 'b' can be matched with elements in the window
- Use a variable 'tmp' to track the count of such matches
- Adjust 'tmp' when sliding the window

Time Complexity: O(n + max(a) + max(b)) per test case
Space Complexity: O(max(a) + max(b)) for frequency arrays
"""

from sys import stdin

input = stdin.readline
yesno = ["Yes", "No"]
noyes = ["No", "Yes"]
FS = ["First", "Second"]
SF = ["Second", "First"]
mi = lambda: map(int, input().split())
li = lambda: list(mi())
t = int(input())


def solve():
    n, m, k = mi()  # Read n, m, k
    b = li()  # Read array b
    a = li()  # Read array a
    N = max(max(a), max(b)) + 1  # Determine size of frequency arrays
    da = [0] * (N)  # Frequency array for elements in a
    db = [0] * N  # Frequency array for elements in b
    
    # Count frequency of elements in a
    for i in a:
        da[i] += 1
    
    tmp = 0  # Current number of matches between window and b
    ans = 0  # Result counter
    
    # Initialize the first window of size m from b
    for i in range(m):
        In = b[i]  # Element entering the window
        if da[In] > db[In]:  # If this element can be matched
            tmp += 1
        db[In] += 1  # Increment frequency in b
    
    # Check if initial window is good
    if tmp >= k:
        ans += 1
    
    # Slide the window across the array a
    for i in range(n - m):
        In = b[i + m]  # Element entering the window
        out = b[i]     # Element leaving the window
        
        # Update tmp if element leaving is contributing to match count
        if da[out] >= db[out]:
            tmp -= 1
        db[out] -= 1  # Decrease frequency of leaving element
        
        # Update tmp if element entering can contribute to match count
        if da[In] > db[In]:
            tmp += 1
        db[In] += 1  # Increase frequency of entering element
        
        # Check if current window is good
        if tmp >= k:
            ans += 1
    
    print(ans)
    return


for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/