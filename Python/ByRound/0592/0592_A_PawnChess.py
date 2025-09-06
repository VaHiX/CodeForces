# Contest 592, Problem A: PawnChess
# URL: https://codeforces.com/contest/592/problem/A

board = [e.strip('\n') for e in [*open(0)]]
board = [''.join(e) for e in zip(*board)]
white, black = float('inf'), float('inf')
for e in board:
    if e[0:e.find('W')] == '.'*e.find('W'):
        white = min(white,e.find('W'))
    pos = 0
    for i,x in enumerate(e):
        if x == 'B':
            pos = i
    if e[pos+1:] == '.' * (7-pos):
        black = min(black,7-pos)
if white <= black:
    print('A')
else:
    print('B')