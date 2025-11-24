# Problem: CF 2171 C2 - Renako Amaori and XOR Game (hard version)
# https://codeforces.com/contest/2171/problem/C2

"""
Code Purpose:
This solution determines the winner of a game between Ajisai and Mai where they take turns swapping elements in arrays a and b.
The game follows these rules:
- On odd turns, Ajisai can swap a[i] and b[i] if i is odd.
- On even turns, Mai can swap a[i] and b[i] if i is even.
- After all moves, Ajisai's score is the XOR of all elements in array a, and Mai's score is the XOR of all elements in array b.
- The player with the higher score wins; if scores are equal, it's a tie.

The key insight is:
1. XOR of all a[i] = xa, XOR of all b[i] = xb
2. The difference between these two XORs (s = xa ^ xb) indicates the potential for a winning move.
3. If s == 0, then no move can change the outcome, so it's a tie.
4. Otherwise, we check for the first bit that differs between a[i] and b[i] in the highest position.
   - If such an index i is even (0-indexed) then Ajisai has a winning strategy.
   - If such an index i is odd (0-indexed) then Mai has a winning strategy.

Algorithms/Techniques:
- XOR bitwise operation
- Bit manipulation
- Greedy decision making based on most significant bit difference

Time Complexity: O(n), where n is the length of the arrays
Space Complexity: O(1), as we use only a constant amount of extra space
"""

t = int(input())
for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    xa = 0
    xb = 0
    for i in range(n):
        xa ^= a[i]
        xb ^= b[i]
    s = xa ^ xb
    if s == 0:
        print("Tie")
        continue
    k = s.bit_length() - 1  # Find the highest bit that differs
    l = -1
    for i in range(n):
        if ((a[i] ^ b[i]) >> k) & 1:  # Check if the k-th bit differs between a[i] and b[i]
            l = i
    print("Ajisai" if l % 2 == 0 else "Mai")


# https://github.com/VaHiX/CodeForces/