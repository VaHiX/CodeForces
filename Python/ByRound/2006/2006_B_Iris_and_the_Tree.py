# Contest 2006, Problem B: Iris and the Tree
# URL: https://codeforces.com/contest/2006/problem/B

import sys

def main():
    input = sys.stdin.read().split()
    ptr = 0
    t = int(input[ptr])
    ptr += 1
    for _ in range(t):
        n, w = int(input[ptr]), int(input[ptr+1])
        ptr += 2
        p = [0] * (n + 1)
        for i in range(2, n+1):
            p[i] = int(input[ptr])
            ptr += 1
        children = [[] for _ in range(n+1)]
        for i in range(2, n+1):
            children[p[i]].append(i)
        Rx = [0] * (n + 1)
        for x in range(n, 0, -1):
            Rx[x] = x
            for c in children[x]:
                if Rx[c] > Rx[x]:
                    Rx[x] = Rx[c]
        C = [0] * (n + 2)
        for x in range(2, n+1):
            pair1 = x - 1
            pair2 = Rx[x]
            C[pair1] += 1
            C[pair2] += 1
        processed_count = [0] * (n + 2)
        K = n
        S = 0
        output = []
        for __ in range(n-1):
            x = int(input[ptr])
            y = int(input[ptr+1])
            ptr += 2
            pair1 = x - 1
            pair2 = Rx[x]
            for pair in [pair1, pair2]:
                processed_count[pair] += 1
                if processed_count[pair] == C[pair]:
                    K -= 1
            S += y
            W_total = w - S
            ans = 2 * S + W_total * K
            output.append(str(ans))
        print(' '.join(output))

if __name__ == "__main__":
    main()