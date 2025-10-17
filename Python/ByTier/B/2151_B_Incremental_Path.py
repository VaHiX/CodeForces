# Problem: CF 2151 B - Incremental Path
# https://codeforces.com/contest/2151/problem/B

"""
B. Incremental Path

Algorithm/Technique:
- Simulation with set-based black cell tracking
- For each command sequence, simulate the movement and mark the final cell as black
- Use a set to efficiently check and update black cells

Time Complexity: O(n * m + k * log(k)) where n is the length of the command string, 
                 m is the number of initial black cells, and k is the total number of black cells at the end.
Space Complexity: O(m + k) where m is the initial black cells and k is the final black cells.

The solution simulates the process for each person who executes commands sequentially. 
For each command:
- 'A': move to next cell (x+1)
- 'B': move to the next white cell (minimum y > x such that cell y is white)
After executing all commands, mark the visited cell as black.
"""

def _input():
    return list(map(int, input().split()))


def main():
    n, m = _input()  # Read n (number of commands) and m (initial black cells)
    s = input()      # Read the command string
    black = set(_input())  # Read initial black cells into a set for fast lookup
    cur = 1          # Start position
    
    for sym in s:    # For each command in the string
        if sym == "A":
            cur += 1     # Move to next cell
            black.add(cur)  # Mark current cell as black (if it was already black, it remains black)
        else:
            cur += 1     # Move to next cell
            while cur in black:  # Find the next white cell (minimum y > cur such that y is not black)
                cur += 1
            black.add(cur)  # Mark the white cell as black
            cur += 1        # Move to next cell after the newly marked one
            while cur in black:  # Again find the next white cell
                cur += 1
    print(len(black))      # Print how many black cells there are
    print(*sorted(list(black)))  # Print them in increasing order


if __name__ == "__main__":
    for _ in range(int(input())):  # For each test case
        main()


# https://github.com/VaHiX/CodeForces/