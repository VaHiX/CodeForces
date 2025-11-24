# Problem: CF 1886 F - Diamond Theft
# https://codeforces.com/contest/1886/problem/F

"""
Algorithm: Dynamic Programming with Simulation
Time Complexity: O(n^2)
Space Complexity: O(n)

This solution simulates the process of hacking cameras and stealing diamonds.
It uses a greedy approach combined with simulation to find the minimum time needed
to steal both diamonds.

The algorithm works by:
1. Categorizing cameras based on their monitoring type (1, 2, or both)
2. Simulating time steps to determine when each camera becomes available
3. Using counters to track disabled camera coverage
4. Applying greedy logic to decide when to steal diamonds
5. Checking if it's possible to steal both diamonds in the correct order

The key insight is that Monocarp must steal the first diamond before the second,
and at each step, we calculate if there are enough disabled cameras to steal.
"""

N = 1550
n = int(input())
vec = [[] for _ in range(3)]
contador1 = [0] * (4 * N + 10)
contador2 = [0] * (4 * N + 10)
pila = []
for _ in range(n):
    tipo, segundos = map(int, input().split())
    if tipo >= 3:
        tipo = 0
    vec[tipo].append(segundos)
vec[0].sort(reverse=True)
encontrarRespuesta = False
total = n
for pos in range(1, 2 * n + 6):
    contador1 = [0] * (4 * N + 10)
    contador2 = [0] * (4 * N + 10)
    # Move cameras that become available at this time step
    while vec[0] and vec[0][-1] <= pos:
        segundos = vec[0].pop()
        vec[1].append(segundos)
        vec[2].append(segundos)
    total = sum(len(vec[tipo]) for tipo in range(3))
    # Update counters for camera disabling times
    for segundos in vec[1]:
        contador1[pos + segundos - 1] += 1
    for segundos in vec[2]:
        if segundos < pos:
            contador2[segundos] += 1
        else:
            contador2[segundos - 1] += 1
    valido = True
    suma1 = 0
    # Check if we can steal the second diamond (condition: enough disabled cameras)
    for i in range(pos):
        suma1 += contador2[i]
        if suma1 > i:
            valido = False
            break
    if not valido:
        continue
    tipo2 = 0
    suma2 = 0
    pila = [0] * n
    top = 0
    cur = len(vec[0]) - 1
    # Simulate the process to find the minimum time needed
    for i in range(1, 4 * N + 11):
        suma2 += contador1[pos + i - 1] + contador2[pos + i - 1]
        tipo2 += contador2[pos + i - 1]
        # Add any cameras that become active at this time step
        while cur >= 0 and vec[0][cur] == pos + i:
            pila[top] = vec[0][cur]
            top += 1
            cur -= 1
        # Adjust greedy decisions to make sure we do not exceed necessary steps
        while suma2 + top > i and 1 + suma1 < pos:
            if suma1 + suma2 + top <= i + pos - 1 and tipo2 > 0:
                tipo2 -= 1
                suma2 -= 1
                suma1 += 1
            else:
                if top <= 0 or pila[top - 1] <= i:
                    break
                suma1 += 1
                contador1[pos + pila[top - 1] - 1] += 1
                top -= 1
                total += 1
        # Check if we've completed both diamond thefts
        if suma2 + top > i:
            valido = False
            break
        if suma2 + suma1 + top == total:
            encontrarRespuesta = True
            break
    if not valido:
        continue
    if encontrarRespuesta:
        print(2 + total)
        break
if not encontrarRespuesta:
    print(-1)


# https://github.com/VaHiX/CodeForces/