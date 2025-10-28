# Problem: CF 1898 E - Sofia and Strings
# https://codeforces.com/contest/1898/problem/E

"""
Code Purpose:
This code determines whether a string `t` can be obtained from string `s` using two types of operations:
1. Remove a character at any index.
2. Sort any substring in alphabetical order.

The solution uses a greedy approach with pre-processing of character positions in `s`.

Algorithms/Techniques:
- Preprocessing: For each character in `s`, store its positions in reverse order.
- Greedy matching: For each character in `t`, find the leftmost available character in `s` that matches.
- Optimization: Use a stack-like approach to efficiently remove outdated indices.

Time Complexity: O(n + m), where n is the length of string s and m is the length of string t.
Space Complexity: O(n), for storing the indices of characters in s.
"""

def solve():
    n, m = map(int, input().split())
    a = input()
    b = input()
    V = [[] for _ in range(26)]  # List to store indices of each character in reverse order
    for i in range(26):
        V[i].clear()
    # Preprocess positions of characters in reverse order
    for i in range(n, 0, -1):
        V[ord(a[i - 1]) - ord("a")].append(i)
    # For each character in target string t
    for i in range(1, m + 1):
        u = ord(b[i - 1]) - ord("a")  # Current character index in alphabet
        if not V[u]:  # If no such character available
            print("NO")
            return
        now = V[u].pop()  # Get the leftmost position of current character
        # Remove all characters that appear before 'now' and are smaller than 'u'
        for v in range(u):
            while V[v] and V[v][-1] < now:
                V[v].pop()
    print("YES")


t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/