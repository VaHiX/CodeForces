# Problem: CF 2038 I - Polyathlon
# https://codeforces.com/contest/2038/problem/I

"""
I. Polyathlon
time limit per test3 seconds
memory limit per test512 megabytes

This problem involves simulating a polyathlon competition where participants compete in m sports,
and the order of sports is determined by a random roll from 1 to m. For each starting sport x,
we simulate the competition and find which participant wins.

Algorithm:
- For each potential starting sport (x), we simulate the competition step-by-step.
- In each round, we determine which participants are eliminated based on skill in the current sport.
- The simulation ends when a single participant remains.

Key technique:
- Sorting the participants by their skill strings in descending order initially helps in efficiently partitioning
  them as per current sport's requirements (skilled vs unskilled). 
- Use of efficient data structures for real-time elimination and reordering during simulation.

Time Complexity: O(n * m * log(n)) due to sorting once followed by m rounds each involving up to n comparisons.
Space Complexity: O(n * m) for storing the grid and data structures used in simulation.

Input:
- n participants, m sports
- Binary matrix of size n x m representing participant skills

Output:
- m integers indicating winner index for each starting sport x from 1 to m
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def main():
    m, n = map(int, input().split())  # Read number of participants and sports
    data = []
    grid = []
    for i in range(m):
        s = input().decode("utf-8")[:n]  # Read skill string for each participant
        grid.append(s)
        data.append((s, i + 1))  # Store (skill_string, participant_index)
    data.sort(reverse=True)  # Sort participants by skill string in descending order
    ranking = [data[i][1] for i in range(m)]  # Extract participant indices in sorted order
    ans = [0] * n  # Initialize result array
    ans[0] = ranking[0]  # First sport's winner is first in sorted list
    
    for j in range(n - 1, 0, -1):  # Iterate from last to first sport (in the rotation)
        left = []   # Participants skilled in current sport
        right = []  # Participants unskilled in current sport
        for index in ranking:  # Go through current list of participants
            if grid[index - 1][j] == "1":  # If participant is skilled in this sport
                left.append(index)
            else:
                right.append(index)
        ranking = left + right  # Apply elimination rule: skilled go forward, unskilled eliminated
        ans[j] = ranking[0]     # Winner of current step

    print(*ans)  # Print all winners for each starting sport


main()


# https://github.com/VaHiX/codeForces/