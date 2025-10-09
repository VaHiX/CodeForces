// Problem: CF 2087 H - Nim with Special Numbers
// https://codeforces.com/contest/2087/problem/H

// Flowerbox: 
// Problem: H. Nim with Special Numbers
// Algorithms/Techniques: Segment Tree with lazy propagation, TreeSet for maintaining sorted set S,
//                        Grundy Number calculation (Nimber), XOR operation for game state.
// Time Complexity:
//   - Build tree: O(M)
//   - Query/Update: O(log M) per operation
//   - Overall: O(Q * log M) where Q is number of queries
// Space Complexity: O(M) for segment tree storage

import java.io.BufferedInputStream
import java.util.TreeSet
import kotlin.math.min
import kotlin.math.max

private class FastScanner {
    private val input = BufferedInputStream(System.`in`)
    private val buffer = ByteArray(1 shl 16)
    private var len = 0
    private var ptr = 0
    private fun readByte(): Int {
        if (ptr >= len) {
            len = input.read(buffer)
            ptr = 0
            if (len <= 0) return -1
        }
        return buffer[ptr++].toInt()
    }
    
    fun nextInt(): Int {
        var c = readByte()
        while (c <= 32 && c >= 0) c = readByte()
        var sign = 1
        if (c == '-'.code) {
            sign = -1
            c = readByte()
        }
        var res = 0
        while (c > 32) {
            res = res * 10 + (c - '0'.code)
            c = readByte()
        }
        return res * sign
    }
}

data class Node(var x: Int = -1, var a: Int = -1, var b: Int = -1)

fun getFromNode(n: Node, x: Int): Int {
    return when {
        n.x == -1 -> x
        x < n.x -> n.a
        else -> n.b
    }
}

fun combine(a: Node, b: Node): Node {
    if (a.x == -1) return b
    if (b.x == -1) return a
    return Node(a.x, getFromNode(b, a.a), getFromNode(b, a.b))
}

fun emptyNode(): Node = Node(-1, -1, -1)

fun fromLength(len: Int): Node = if (len == -1) emptyNode() else Node(len, len, len - 1)

const val M = 300001

lateinit var T: Array<Node>

fun build(v: Int, l: Int, r: Int) {
    if (l == r - 1) {
        T[v] = emptyNode()
    } else {
        val m = (l + r) / 2
        build(v * 2 + 1, l, m)
        build(v * 2 + 2, m, r)
        T[v] = combine(T[v * 2 + 1], T[v * 2 + 2])
    }
}

fun upd(v: Int, l: Int, r: Int, pos: Int, x: Int) {
    if (l == r - 1) {
        T[v] = fromLength(x)
    } else {
        val m = (l + r) / 2
        if (pos < m) upd(v * 2 + 1, l, m, pos, x) else upd(v * 2 + 2, m, r, pos, x)
        T[v] = combine(T[v * 2 + 1], T[v * 2 + 2])
    }
}

fun getNode(v: Int, l: Int, r: Int, L: Int, R: Int): Node {
    if (L >= R) return emptyNode()
    if (L == l && R == r) return T[v]
    val m = (l + r) / 2
    val left = getNode(v * 2 + 1, l, m, L, min(m, R))
    val right = getNode(v * 2 + 2, m, r, maxOf(L, m), R)
    return combine(left, right)
}

fun main() {
    val fs = FastScanner()
    val q = fs.nextInt()
    T = Array(4 * M) { emptyNode() }
    build(0, 0, M)
    val S = TreeSet<Int>()
    upd(0, 0, M, 0, 0)
    S.add(0)
    val out = StringBuilder()

    fun insertValue(x: Int) {
        val it = S.ceiling(x) // Find smallest element >= x
        if (it != null) {
            upd(0, 0, M, it, it - x)
        }
        val lower = S.lower(x) // Find largest element < x
        if (lower != null) {
            upd(0, 0, M, x, x - lower)
        }
        S.add(x)
    }

    fun eraseValue(x: Int) {
        upd(0, 0, M, x, -1) // Mark as deleted in segment tree
        S.remove(x)
        val it = S.ceiling(x) // Find next element after erased one
        if (it != null) {
            val y = it
            val low = S.lower(y)
            if (low != null) {
                upd(0, 0, M, y, y - low)
            }
        }
    }

    fun getGrundy(x: Int): Int {
        if (x == 0) return 0
        val n = getNode(0, 0, M, 0, x) // Get node information up to position x
        val it = S.lower(x) // Find largest element < x
        if (it == null) return x
        val y = it
        val valY = getFromNode(n, 0) // Get value associated with index y
        val dist = x - y
        return if (dist <= valY) dist - 1 else dist
    }

    repeat(q) {
        val t = fs.nextInt()
        if (t == 1) {
            val x = fs.nextInt()
            if (S.contains(x)) eraseValue(x) else insertValue(x)
        } else {
            val k = fs.nextInt()
            var xr = 0
            repeat(k) {
                val a = fs.nextInt()
                xr = xr xor getGrundy(a) // Compute XOR of all Grundy numbers
            }
            out.append(if (xr != 0) "First\n" else "Second\n") // If XOR is not zero, first wins
        }
    }
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/