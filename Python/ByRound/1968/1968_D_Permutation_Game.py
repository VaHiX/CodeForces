# Problem: CF 1968 D - Permutation Game
# https://codeforces.com/contest/1968/problem/D

"""
Algorithm/Technique: 
- The problem involves simulating a game between two players (Bodya and Sasha) on a permutation with a fixed number of moves (k).
- Each player starts at a position and can either stay or move according to the permutation array.
- The score is accumulative, with each move adding the value at the current position.
- The key insight is to use a simulation with cycle detection to avoid unnecessary computation for large k.
- We track the best possible score in all possible paths up to k turns, leveraging properties of cycles in permutations.

Time Complexity: O(n + k) per test case, where n is the permutation length and k is the number of turns.
Space Complexity: O(n) for storing the permutation, scores, and tracking seen positions.
"""

def solve():
    n, k, pb, ps = map(int, input().split())
    pb -= 1
    ps -= 1
    p = list(map(int, input().split()))
    p = [x - 1 for x in p]  # Convert to 0-based indexing
    score = list(map(int, input().split()))
    mx = max(score)
    d = set([i for i in range(n) if score[i] == mx])  # Set of indices with maximum score

    def get_score(pos, k):
        ans = 0
        now = 0
        seen = set()
        while k:
            # Update max possible score considering remaining turns
            ans = max(ans, now + score[pos] * k)
            seen.add(pos)
            # If not in a cycle (no repeated path) and can move, do so
            if pos not in d and p[pos] not in seen:
                now += score[pos]
                pos = p[pos]
            else:
                # If in a cycle or final step, stop early to optimize
                break
            k -= 1
        return ans

    sb, ss = get_score(pb, k), get_score(ps, k)
    if sb > ss:
        print("Bodya")
    elif sb < ss:
        print("Sasha")
    else:
        print("Draw")


T = int(input())
for _ in range(T):
    solve()


# https://github.com/VaHiX/CodeForces/