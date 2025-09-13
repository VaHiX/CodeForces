fun main() {
    val n = readInt()
    val g = Array(n) { mutableListOf<Int>() }
    val dist = Array(n) { IntArray(n) { n + 2 } }
    for (i in 0 until n - 1) {
        val (x, y) = readInts().map { it - 1 }
        g[x].add(y)
        g[y].add(x)
        dist[x][y] = 1
        dist[y][x] = 1
    }
    for (i in 0 until n) {
        dist[i][i] = 0
    }
    for (k in 0 until n) {
        for (i in 0 until n) {
            for (j in 0 until n) {
                dist[i][j] = minOf(dist[i][j], dist[i][k] + dist[k][j])
            }
        }
    }
    val md = 998244353L
    val comb = Array(n + 1) { LongArray(n + 1) }
    for (i in 0..n) {
        comb[i][0] = 1
        for (j in 1..i) {
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % md
        }
    }
    val fact = LongArray(n + 1) { 1 }
    for (i in 1..n) {
        fact[i] = fact[i - 1] * i % md
    }
    var leaves = 0
    for (i in 0 until n) {
        if (g[i].size == 1) {
            leaves += 1
        }
    }
    var root = 0
    while (g[root].size == 1) {
        root += 1
    }
    val free = BooleanArray(n) { false }
    var ans = 0L
    val f = Array(n) { Array(n + 1) { Array(n + 1) { LongArray(n + 1) } } }
    val sz = IntArray(n)
    fun dfs(v: Int, pv: Int, vy: Int) {
        for (x in 0..n) {
            for (y in 0..n) {
                for (z in 0..n) {
                    f[v][x][y][z] = 0
                }
            }
        }
        if (g[v].size == 1) {
            if (free[v]) {
                f[v][0][0][0] = 1
            } else {
                f[v][0][1][0] = 1
                if (leaves % 2 == 1) {
                    f[v][1][0][1] = 1
                }
            }
            sz[v] = 1
            return
        }
        var aux = Array(3) { Array(1) { Array(1) { LongArray(1) } } }
        sz[v] = 0
        aux[0][0][0][0] = 1
        for (u in g[v]) {
            if (u == pv) {
                continue
            }
            dfs(u, v, vy)
            val newAux = Array(3) { Array(sz[v] + sz[u] + 1) { Array(sz[v] + sz[u] + 1) { LongArray(sz[v] + sz[u] + 1) } } }
            for (ux in 0..sz[u]) {
                for (uy in 0..sz[u]-ux) {
                    for (uz in 0..sz[u]) {
                        if (f[u][ux][uy][uz] > 0) {
                            for (done in 0..2) {
                                for (x in 0..sz[v]) {
                                    for (y in 0..sz[v]) {
                                        for (z in 0..sz[v]) {
                                            if (aux[done][x][y][z] > 0) {
                                                for (mx in 0..minOf(x, ux)) {
                                                    for (my in 0..minOf(y, uy)) {
                                                        var ways = aux[done][x][y][z] * f[u][ux][uy][uz] % md
                                                        ways = ways * comb[x][mx] % md * comb[ux][mx] % md
                                                        ways = ways * comb[y][my] % md * comb[uy][my] % md
                                                        ways = ways * fact[mx] % md * fact[my] % md
                                                        val newDone = if (uy > 0) 2 else maxOf(if (ux > 0) 1 else 0, done)
                                                        val newX = x + ux - 2 * mx
                                                        val newY = y + uy - 2 * my
                                                        val newZ = z + uz
                                                        newAux[newDone][newX][newY][newZ] =
                                                            (newAux[newDone][newX][newY][newZ] + ways) % md
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            aux = newAux
            sz[v] += sz[u]
        }
        for (done in 0..2) {
            for (x in 0..sz[v]) {
                for (y in 0..sz[v]) {
                    for (z in 0..sz[v]) {
                        val ways = aux[done][x][y][z]
                        if (ways > 0) {
                            if (done == 2 && v == vy) {
                                continue
                            }
                            if (done == 0 && !free[v]) {
                                continue
                            }
                            f[v][x][y][z] = (f[v][x][y][z] + ways) % md
                        }
                    }
                }
            }
        }
    }
    if (leaves % 2 == 0) {
        dfs(root, -1, -1)
        ans = f[root][0][0][0] * fact[leaves / 2] % md
    } else {
        for (vx in 0 until n) {
            if (g[vx].size == 1) {
                for (vy in 0 until n) {
                    if (vx == vy || g[vy].size > 1) {
                        for (i in 0 until n) {
                            free[i] = (dist[vx][i] + dist[i][vy] == dist[vx][vy])
                        }
                        dfs(root, -1, vy)
                        for (z in 0..n) {
                            if (f[root][0][0][z] > 0) {
                                val ways = f[root][0][0][z] * fact[z / 2] % md * fact[(leaves - 1 - z) / 2] % md
                                ans = (ans + ways) % md
                            }
                        }
                    }
                }
            }
        }
    }
    println("${(leaves + 1) / 2} $ans")
}

private fun readInt() = readln().toInt()
private fun readLong() = readln().toLong()
private fun readDouble() = readln().toDouble()
private fun readStrings() = readln().split(" ")
private fun readInts() = readStrings().map { it.toInt() }
private fun readLongs() = readStrings().map { it.toLong() }
private fun readDoubles() = readStrings().map { it.toDouble() }
