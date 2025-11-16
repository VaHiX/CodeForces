# Problem: CF 1558 A - Charmed by the Game
# https://codeforces.com/contest/1558/problem/A

"""
Code Purpose:
This code determines all possible numbers of breaks that can occur in a tennis match between Alice and Borys,
given the total number of games each player won. A break happens when the receiving player wins the game.
The match alternates serves between players, starting with either Alice or Borys.

Algorithms/Techniques:
- Mathematical analysis of valid break counts based on the difference in games won.
- Uses range() to generate all valid break counts efficiently.

Time Complexity: O(1) per test case - only constant time operations are used.
Space Complexity: O(1) - only a few variables are used regardless of input size.

"""
for s in [*open(0)][1:]:
    a, b = map(int, s.split())
    s = a + b
    print(len(r := range(d := abs(a - b) // 2, s - d + 1, 2 - s % 2)), *r)


# https://github.com/VaHiX/CodeForces/