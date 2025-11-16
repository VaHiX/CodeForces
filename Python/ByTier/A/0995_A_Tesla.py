# Problem: CF 995 A - Tesla
# https://codeforces.com/contest/995/problem/A

"""
Algorithms/Techniques: 
- Simulated annealing-like approach with a systematic traversal of the parking grid
- Uses a spiral-like path (sos) to move cars and create space for parking
- Greedily handles cars that are already in their correct positions at the top and bottom rows
- Time complexity: O(n^2) in worst case due to nested loops, but bounded by 20000 operations
- Space complexity: O(n) for storing the grid and result moves

This code solves the parking problem where cars must be moved from initial positions in rows 2 and 3
to their designated parking spots in rows 1 and 4. It uses a spiral-like traversal to create space
for moving cars and ensures that cars are only moved into their correct spots when appropriate.
"""

n, k = map(int, input().split())
sp = [list(map(int, input().split())) for _ in range(4)]
res = []
# Create a spiral-like path around the grid to enable movement
sos = [(1, c) for c in range(n)] + [(2, c) for c in range(n - 1, -1, -1)]
L = 2 * n
# Process cars already in correct spots in the top and bottom rows
for i in range(n):
    if sp[1][i] != 0 and sp[0][i] == sp[1][i]:
        car = sp[1][i]
        sp[1][i] = 0
        res.append((car, 1, i + 1))
    if sp[2][i] != 0 and sp[3][i] == sp[2][i]:
        car = sp[2][i]
        sp[2][i] = 0
        res.append((car, 4, i + 1))

# Main loop to move cars to their correct positions
while True:
    flag = True
    # Check if all cars in rows 2 and 3 are in correct positions
    for i in range(n):
        if sp[1][i] != 0 or sp[2][i] != 0:
            flag = False
            break
    if flag:
        break
    
    zero = -1
    # Find the first empty space in spiral order
    for i, (a, b) in enumerate(sos):
        if sp[a][b] == 0:
            zero = i
            break
    
    # If no empty space found, try to move cars to correct spots or report impossible
    if zero == -1:
        f = False
        # Try to move cars already in correct positions to their spots
        for c in range(n):
            if sp[1][c] != 0 and sp[0][c] == sp[1][c]:
                car = sp[1][c]
                sp[1][c] = 0
                res.append((car, 1, c + 1))
                f = True
            if sp[2][c] != 0 and sp[3][c] == sp[2][c]:
                car = sp[2][c]
                sp[2][c] = 0
                res.append((car, 4, c + 1))
                f = True
        if not f:
            print(-1)
            exit()
        else:
            continue
    
    # Move cars along the spiral path to create space
    for i in range(1, L):
        tt = (zero - i) % L
        r, c = sos[tt]
        nr, nc = sos[(tt + 1) % L]
        if sp[r][c] != 0 and sp[nr][nc] == 0:
            car = sp[r][c]
            sp[r][c] = 0
            sp[nr][nc] = car
            res.append((car, nr + 1, nc + 1))
    
    # Again process cars already in correct spots after moving
    for i in range(n):
        if sp[1][i] != 0 and sp[0][i] == sp[1][i]:
            car = sp[1][i]
            sp[1][i] = 0
            res.append((car, 1, i + 1))
        if sp[2][i] != 0 and sp[3][i] == sp[2][i]:
            car = sp[2][i]
            sp[2][i] = 0
            res.append((car, 4, i + 1))
    
    # Check if maximum number of moves exceeded
    if len(res) > 20000:
        print(-1)
        exit()

# Output results
print(len(res))
for a, b, c in res:
    print(a, b, c)


# https://github.com/VaHiX/CodeForces/