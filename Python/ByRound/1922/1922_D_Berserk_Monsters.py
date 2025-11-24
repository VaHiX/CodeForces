# Problem: CF 1922 D - Berserk Monsters
# https://codeforces.com/contest/1922/problem/D

"""
Algorithm: Simulation with Linked List-like Structure
Time Complexity: O(n^2) in worst case, but optimized with efficient data structure
Space Complexity: O(n)

The solution simulates the combat rounds by maintaining a list of alive monsters
and updating their left and right neighbors' connections after each death.
Each round, we calculate total damage to each monster and kill those whose defense
is less than the damage received.
"""

import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    out_lines = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        a = list(map(int, data[index : index + n]))
        index += n
        d = list(map(int, data[index : index + n]))
        index += n
        # left_arr[i] stores the index of the left neighbor of monster i
        left_arr = [-1] * n
        # right_arr[i] stores the index of the right neighbor of monster i
        right_arr = [-1] * n
        if n > 1:
            # Initialize neighbors (each monster points to its adjacent ones)
            for i in range(1, n):
                left_arr[i] = i - 1
            for i in range(n - 1):
                right_arr[i] = i + 1
        # dead[i] tracks whether monster i is dead
        dead = [False] * n
        # ans_rounds[i] stores number of monsters dying in round i
        ans_rounds = [0] * n
        # candidate_set contains indices of monsters that are alive and may be affected in the current round
        candidate_set = set(range(n))
        for round_i in range(n):
            if not candidate_set:
                break
            # to_remove contains indices of monsters that will die in this round
            to_remove = []
            for i in candidate_set:
                if dead[i]:
                    continue
                total_damage = 0
                # Get left neighbor
                lf = left_arr[i]
                if lf != -1 and not dead[lf]:
                    total_damage += a[lf]
                # Get right neighbor
                rt = right_arr[i]
                if rt != -1 and not dead[rt]:
                    total_damage += a[rt]
                # If damage exceeds defense, monster dies
                if total_damage > d[i]:
                    to_remove.append(i)
            # next_candidate_set will contain monsters that may be affected in the next round
            next_candidate_set = set()
            for i in to_remove:
                if dead[i]:
                    continue
                dead[i] = True
                # Update neighbors of adjacent monsters
                L = left_arr[i]
                R = right_arr[i]
                if L != -1:
                    right_arr[L] = R
                if R != -1:
                    left_arr[R] = L
                # Add adjacent monsters to the set for next round
                if L != -1 and not dead[L]:
                    next_candidate_set.add(L)
                if R != -1 and not dead[R]:
                    next_candidate_set.add(R)
            # Record the number of deaths in this round
            ans_rounds[round_i] = len(to_remove)
            candidate_set = next_candidate_set
        out_lines.append(" ".join(map(str, ans_rounds)))
    print("\n".join(out_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/