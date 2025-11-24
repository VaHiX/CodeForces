# Problem: CF 1858 A - Buttons
# https://codeforces.com/contest/1858/problem/A

"""
Purpose: Determine the winner of a game where Anna and Katie take turns pressing buttons in a laboratory.
         Buttons are categorized into three types:
         - a buttons only Anna can press
         - b buttons only Katie can press
         - c buttons either can press
         Anna goes first. If a player cannot make a move, they lose.

Algorithms/Techniques:
- Greedy strategy based on parity of c (number of ambiguous buttons)
- If c is odd, Anna gains an extra turn advantage by using one of the c buttons in her first move
- Compare adjusted button counts to decide the winner

Time Complexity: O(1) - constant time per test case
Space Complexity: O(1) - only using a fixed amount of extra space regardless of input size

"""
def main():
    t = int(input())
    r = [str(solution(i, t)) for i in range(t)]
    print("\n".join(r))


def solution(ti, tn):
    a, b, c = map(int, input().split())
    # If c is odd, Anna gets an extra turn advantage by taking one of the c buttons
    if c % 2 == 1:
        a += 1
    # Anna wins if she has more effective buttons than Katie
    return "First" if a > b else "Second"


main()


# https://github.com/VaHiX/CodeForces/