# Problem: CF 1267 L - Lexicography
# https://codeforces.com/contest/1267/problem/L

"""
Algorithm/Techniques:
- Count frequency of each character in the input string
- Distribute characters to form n words of length l
- Ensure words are lexicographically ordered
- Minimize the k-th word in lexicographical order

Time Complexity: O(n * l) - We process each character once, and the nested loops are bounded by the input size.
Space Complexity: O(n * l) - To store the answer matrix and character counts.
"""

import sys

input = sys.stdin.buffer.readline


def process(n, l, k, S):
    # Count frequency of each character
    d = [0 for i in range(26)]
    for c in S:
        d[ord(c) - ord("a")] += 1
    
    # Initialize the answer matrix
    answer = [[None for j in range(l)] for i in range(n)]
    
    # Assign first character of first k-1 words to be smallest possible
    I = 0
    for i in range(k):
        while d[I] == 0:
            I += 1
        answer[i][0] = I
        d[I] -= 1
    
    # For the k-th word (to minimize)
    j = 0
    while j + 1 <= l - 1:
        # If this is first word or comparison says we are OK to add more characters
        if k == 1 or (answer[k - 2][j] < answer[k - 1][j]):
            # Fill the k-th word with minimal characters
            for j2 in range(j + 1, l):
                while d[I] == 0:
                    I += 1
                answer[k - 1][j2] = I
                d[I] -= 1
            break
        else:
            # Find the index where to insert new character to maintain lexicographic order
            i1 = k - 1
            while i1 > 0 and answer[i1 - 1][j] == answer[k - 1][j]:
                i1 -= 1
            # Assign remaining positions with minimal characters
            for j2 in range(i1, k):
                while d[I] == 0:
                    I += 1
                answer[j2][j + 1] = I
                d[I] -= 1
            j += 1
    
    # Fill remaining positions with remaining characters
    for i in range(n):
        for j in range(l):
            if answer[i][j] is None:
                while d[I] == 0:
                    I += 1
                answer[i][j] = I
                d[I] -= 1
    
    # Convert integers back to characters and print
    for row in answer:
        row = [chr(x + ord("a")) for x in row]
        row = "".join(row)
        sys.stdout.write(f"{row}\n")


n, l, k = [int(x) for x in input().split()]
S = input().decode().strip()
process(n, l, k, S)


# https://github.com/VaHiX/CodeForces/