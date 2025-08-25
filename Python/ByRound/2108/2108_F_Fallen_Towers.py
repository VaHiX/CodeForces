# Contest 2108, Problem F: Fallen Towers
# URL: https://codeforces.com/contest/2108/problem/F

import sys


def solve():
    t = int(sys.stdin.readline())
    ans_list = []

    for _ in range(t):
        size = int(sys.stdin.readline())
        towers = list(map(int, sys.stdin.readline().split()))

        # expires[i] = nombre de +1 à retirer à l'indice i
        expires = [0] * size

        # Vérifie si l'on peut obtenir MEX >= goal
        def feasible(goal):
            # reset du tableau expires
            for j in range(size):
                expires[j] = 0
            active = 0
            for i in range(size):
                # 1) on retire les effets périmés
                active -= expires[i]

                # 2) combien de blocs doivent déjà être tombés pour suivre la MEX
                req = i - (size - goal)
                if req < 0:
                    req = 0

                # 3) si on n'a pas assez de blocs → impossible
                if active < req:
                    return False

                # 4) on abat la tour i
                prev = active
                lim = i + towers[i] + prev - req + 1
                # ce nouveau knock ajoute exactement 1 bloc actif
                active = prev + 1

                # 5) on programme la fin de cet effet
                if lim < size:
                    expires[lim] += 1

            return True

        # recherche binaire du MEX optimal dans [1..size]
        lo, hi = 1, size + 1
        while hi - lo > 1:
            mid = (lo + hi) // 2
            if feasible(mid):
                lo = mid
            else:
                hi = mid

        ans_list.append(str(lo))

    sys.stdout.write("\n".join(ans_list))


if __name__ == "__main__":
    solve()
