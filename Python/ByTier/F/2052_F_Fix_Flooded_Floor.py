# Problem: CF 2052 F - Fix Flooded Floor
# https://codeforces.com/contest/2052/problem/F

"""
Code Purpose:
This code solves the problem of determining whether a 2xN parquet floor, with some damaged ('.') and undamaged ('#') cells,
can be completely filled with 1x2 parquet pieces in exactly one way, multiple ways, or no way at all.

The algorithm uses dynamic programming with a compact state representation:
- Each position in the column can be either 0 (empty) or 1 (occupied by a vertical domino)
- States represent combinations of occupied/unoccupied cells in the current column
- The transitions consider valid placements of dominoes and track how many ways lead to each state

Time Complexity: O(N) where N is the length of the parquet floor
Space Complexity: O(1) as we only maintain a constant-size DP array (4 states)

Algorithms/Techniques:
- Dynamic Programming with state compression
- Bitmasking to represent occupancy of top and bottom cells
"""

def main():
    import sys

    input = sys.stdin.read().split()
    ptr = 0
    T = int(input[ptr])
    ptr += 1
    results = []
    for _ in range(T):
        n = int(input[ptr])
        ptr += 1

        # Read top row of parquet
        top = []
        while len("".join(top)) < n:
            top.append(input[ptr])
            ptr += 1
        top = "".join(top)[:n]

        # Read bottom row of parquet
        bottom = []
        while len("".join(bottom)) < n:
            bottom.append(input[ptr])
            ptr += 1
        bottom = "".join(bottom)[:n]

        # dp_prev[s] = number of ways to reach state s at current column
        # s = 0 means no cells occupied (00 in binary)
        # s = 1 means bottom cell occupied (01)
        # s = 2 means top cell occupied (10)
        # s = 3 means both cells occupied (11)
        dp_prev = [0] * 4
        dp_prev[0] = 1  # Initially, there's one way to have nothing placed
        for i in range(n):
            dp_next = [0] * 4
            cell1 = top[i]
            cell2 = bottom[i]
            for s in range(4):
                cnt = dp_prev[s]
                if cnt == 0:
                    continue

                # Check constraints based on cell being occupied or not
                if s & 2:
                    if cell1 != ".":
                        continue  # Conflict: trying to place domino where cell is filled
                if s & 1:
                    if cell2 != ".":
                        continue  # Conflict: trying to place domino where cell is filled

                # Determine remaining cells and possible transitions
                rem1 = (cell1 == ".") and not (s & 2)  # Top cell is free and not occupied
                rem2 = (cell2 == ".") and not (s & 1)  # Bottom cell is free and not occupied

                if rem1 and rem2:

                    # Place horizontal domino covering both cells
                    next_state = 0
                    dp_next[next_state] += cnt
                    if dp_next[next_state] > 2:
                        dp_next[next_state] = 2

                    # Also consider placing 2 vertical dominoes next to each other if available
                    if i + 1 < n and top[i + 1] == "." and bottom[i + 1] == ".":
                        next_state = 3
                        dp_next[next_state] += cnt
                        if dp_next[next_state] > 2:
                            dp_next[next_state] = 2
                elif rem1:

                    # Place vertical domino in top cell only
                    if i + 1 < n and top[i + 1] == ".":
                        next_state = 2
                        dp_next[next_state] += cnt
                        if dp_next[next_state] > 2:
                            dp_next[next_state] = 2
                elif rem2:

                    # Place vertical domino in bottom cell only
                    if i + 1 < n and bottom[i + 1] == ".":
                        next_state = 1
                        dp_next[next_state] += cnt
                        if dp_next[next_state] > 2:
                            dp_next[next_state] = 2
                else:

                    # No free cell, just continue
                    next_state = 0
                    dp_next[next_state] += cnt
                    if dp_next[next_state] > 2:
                        dp_next[next_state] = 2
            dp_prev = dp_next

        final_count = dp_prev[0]
        if final_count == 0:
            results.append("None")
        elif final_count == 1:
            results.append("Unique")
        else:
            results.append("Multiple")

    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/