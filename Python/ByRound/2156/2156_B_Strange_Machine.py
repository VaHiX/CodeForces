# Problem: CF 2156 B - Strange Machine
# https://codeforces.com/contest/2156/problem/B

"""
Algorithm: Simulation
Time Complexity: O(q * max_steps) where max_steps is the maximum number of steps needed for any query.
Space Complexity: O(1) excluding the input and output storage.

This solution simulates the process for each query by following the circular arrangement of machines.
Each machine updates the value of 'a' according to its type (A decreases by 1, B performs floor division by 2).
The simulation continues until 'a' becomes 0, tracking the number of steps taken.
"""

import sys


def solve():

    data = sys.stdin.buffer.read().split()

    it = iter(data)
    t = int(next(it))
    answers = []

    for _ in range(t):
        n = int(next(it))
        q = int(next(it))
        s = next(it).decode()
        queries = [int(next(it)) for _ in range(q)]

        # If there are no machines of type B, each query just needs 'val' steps
        # because all machines are of type A and decrease by 1 each step.
        if "B" not in s:
            answers.extend(str(val) for val in queries)
            continue

        machines = s
        for val in queries:
            current = val
            pos = 0
            steps = 0

            while current > 0:
                if machines[pos] == "A":
                    current -= 1
                else:
                    current //= 2
                steps += 1

                if current == 0:
                    break

                pos += 1
                if pos == n:
                    pos = 0

            answers.append(str(steps))

    sys.stdout.write("\n".join(answers))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/