# Problem: CF 2168 A1 - Encode and Decode (Easy Version)
# https://codeforces.com/contest/2168/problem/A1

"""
Encode and Decode (Easy Version)

Algorithms/Techniques:
- Encoding: Convert each integer a[i] (1-26) to a letter by mapping it to chr(ord('a') + a[i] - 1).
- Decoding: Reverse the process by converting each character back to its numeric value.

Time Complexity: O(n) for both encoding and decoding phases, where n is the length of the array.
Space Complexity: O(n) for storing the encoded string and decoded array.

First Run (Encoding):
- Read n and array a.
- Map each element of a to a lowercase letter using chr(ord('a') + a[i] - 1).
- Output the resulting string.

Second Run (Decoding):
- Read the encoded string.
- Convert each character back to its original numeric value using ord(c) - ord('a') + 1.
- Output the length and the decoded array.
"""

t = input()

if t == "first":
    n = int(input())
    a = [int(x) for x in input().split()]

    r = ""
    for i in a:
        r += chr(ord("a") + i - 1)  # Map integer to corresponding lowercase letter

    print(r)

else:
    a = input()

    n = []
    for c in a:
        n.append(ord(c) - ord("a") + 1)  # Convert character back to integer

    print(len(n))
    print(*n)


# https://github.com/VaHiX/CodeForces/