# Problem: CF 1714 D - Color with Occurrences
# https://codeforces.com/contest/1714/problem/D

"""
Algorithm: Greedy
Purpose: Given a text and a set of strings, color all characters of the text red by covering 
         substrings with the given strings. Find the minimum number of operations needed.
         
Time Complexity: O(|t| * n * |s|) where |t| is the length of the text, n is number of strings, 
                 and |s| is the average length of the strings.
Space Complexity: O(n * |s|) for storing the strings.

The approach uses a greedy method:
1. For each position in the text, check all strings to see if they match starting at that position.
2. Keep track of the furthest reachable position (rr) and the best string to extend coverage.
3. When we cannot extend coverage (rr == i), it's impossible to color the entire text.
4. Record the operations needed in the answer.
"""

def f():
    t = input()  # Read the text

    n = int(input())  # Read number of strings
    s = [input() for i in range(n)]  # Read all strings
    
    r = (0, -1)  # Initialize r to track the best extension (furthest reach, string index, start position)
    ans = []  # To store the operations

    rr = 0  # Current furthest reachable position
    
    for i in range(len(t)):  # Iterate through each character in the text
        for j, x in enumerate(s):  # Check each string in the set
            if t[i : i + len(x)] == x:  # If the string matches at position i
                r = max(r, (i + len(x), j, i))  # Update r to the furthest reach with this string
        if i == rr:  # When we reach the last reachable position
            if r[0] <= i:  # If we cannot extend further, it's impossible
                print(-1)
                return
            rr = r[0]  # Update furthest reach
            ans.append((r[2], r[1] + 1))  # Store the operation (start pos, string index+1)
    
    print(len(ans))  # Print number of operations
    for l, r in ans:  # Print each operation
        print(r, l + 1)  # r is string index+1, l is start position (0-based)


for _ in range(int(input())):  # Process multiple test cases
    f()  # Run function for each test case


# https://github.com/VaHiX/CodeForces/