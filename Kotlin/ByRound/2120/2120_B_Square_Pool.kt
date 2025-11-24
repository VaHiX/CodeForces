// Problem: CF 2120 B - Square Pool
// https://codeforces.com/contest/2120/problem/B

/**
 * Problem: B. Square Pool
 *
 * Purpose:
 *   Given a square pool table of side length s with pockets at each corner,
 *   determine how many balls are potted based on their initial positions and directions.
 *   Each ball moves at 45-degree angles, bouncing elastically off edges.
 *
 * Algorithm:
 *   - A ball will be potted if it hits one of the four corners (0,0), (0,s), (s,0), (s,s).
 *   - To solve this efficiently without simulating full trajectory:
 *     1. For each ball with direction (dx, dy) and position (x, y):
 *        - Determine when the vertical movement reaches edge y = 0 or y = s.
 *        - Similarly for horizontal movement to x = 0 or x = s.
 *        - A ball will reach a pocket if it hits one of these at time T where T is such
 *          that both coordinates of the position (x + dx*T, y + dy*T) lie on an edge.
 *     2. We observe that balls are potted precisely when they hit specific corners under certain conditions:
 *        - If both x and y are equal to 0 or s after traveling a certain number of steps,
 *          then it's in a pocket.
 *     3. Simplified logic:
 *        - If dx == dy, then the ball must end up at (s,s) for pocketing — check whether
 *          (x + y) % s == 0 and (dx + dy) == 2 to ensure final position lands at corner.
 *        - If dx != dy and both are ±1, we can derive conditions for hitting pockets:
 *          - Ball goes towards (s,0) or (0,s) → check if (x + y) = s and (dx+dy)=0
 *     - So, two cases suffice for checking if ball is potted:
 *        1. dx == dy && x == y → means it will head to (s,s)
 *        2. dx + dy == 0 && x + y == s → hits pocket (0,s) or (s,0)
 *
 * Time Complexity:
 *   O(n) per test case — since we just process all n balls once.
 *
 * Space Complexity:
 *   O(1) additional space — no extra data structures beyond fixed size arrays and variables.
 */
@file:OptIn(ExperimentalStdlibApi::class, ExperimentalContracts::class)
import kotlin.contracts.ExperimentalContracts
import kotlin.contracts.contract
import kotlin.experimental.ExperimentalTypeInference
import kotlin.math.absoluteValue

const val MOD = 998_244_353

@JvmInline
value class Imt private constructor(private val value: Int) {
    constructor() : this(0)
    override fun toString(): String = value.toString()
    
    operator fun plus(other: Imt): Imt {
        val sum = value + other.value
        return if (sum >= MOD) Imt(sum - MOD) else Imt(sum)
    }
    
    operator fun minus(other: Imt): Imt =
        if (value >= other.value) Imt(value - other.value)
        else Imt(value + MOD - other.value)
    
    operator fun times(other: Imt): Imt = (value.toLong() * other.value).toImt()
    
    companion object {
        fun fromInt(value: Int): Imt = Imt(if (value >= 0) value else value + MOD)
    }
    
    operator fun unaryPlus(): Imt = this
    operator fun unaryMinus(): Imt = 0.toImt() - this
    
    fun pow(p: Long): Imt {
        var lp = (p % (MOD - 1)).toInt()
        if (lp < 0) lp += MOD - 1
        var cur = this
        var res = 1.toImt()
        while (lp > 0) {
            if (lp % 2 == 1) res *= cur
            cur *= cur
            lp /= 2
        }
        return res
    }
    
    fun pow(p: Int) = pow(p.toLong())
    fun inv() = pow(MOD - 2)
    operator fun div(other: Imt) = times(other.inv())
}

fun Int.toImt() = Imt.fromInt(this)
fun Long.toImt() = (this % MOD).toInt().toImt()

fun readInt() = readln().toInt()
fun readLong() = readln().toLong()
fun readInts() = readln().split(' ').map { it.toInt() }
fun readLongs() = readln().split(' ').map { it.toLong() }

fun out(a: Any) = println(a)
fun out(a: Iterable<*>) = println(a.joinToString(separator = " "))
fun out(a: Array<*>) = println(a.joinToString(separator = " "))
fun out(a: IntArray) = println(a.joinToString(separator = " "))
fun out(a: LongArray) = println(a.joinToString(separator = " "))
fun out(a: BooleanArray) = println(a.map { if (it) '1' else '0' }.joinToString(separator = ""))

@OptIn(ExperimentalTypeInference::class)
@OverloadResolutionByLambdaReturnType
inline fun if0(p: Boolean, block: () -> Int) = if (p) block() else 0

@OptIn(ExperimentalTypeInference::class)
@OverloadResolutionByLambdaReturnType
inline fun if0(p: Boolean, block: () -> Long) = if (p) block() else 0

@OptIn(ExperimentalContracts::class)
fun <R> ifNull(p: Boolean, block: () -> R): R? {
    contract {
        returnsNotNull() implies p
    }
    return if (p) block() else null
}

interface FctCtx {
    val f: Array<Imt>
    val rf: Array<Imt>
    val r: Array<Imt>
    fun binom(n: Int, k: Int): Imt = if (k < 0 || k > n) Imt() else f[n] * rf[k] * rf[n - k]
}

class FctCtxImpl(mx: Int) : FctCtx {
    override val f = Array(mx + 1) { Imt() }
    override val rf = Array(mx + 1) { Imt() }
    override val r = Array(mx + 1) { Imt() }
    
    init {
        f[0] = 1.toImt()
        for (i in 1 .. mx) f[i] = f[i - 1] * i.toImt()
        rf[mx] = f[mx].inv()
        for (i in mx - 1 downTo 0) rf[i] = rf[i + 1] * (i + 1).toImt()
        for (i in 1 .. mx) r[i] = rf[i] * f[i - 1]
    }
    
    constructor() : this(10)
}

interface PrimesCtx {
    val primes: List<Int>
    val isPrime: BooleanArray
}

class PrimesCtxImpl(mx: Int) : PrimesCtx {
    override val primes = mutableListOf<Int>()
    override val isPrime = BooleanArray(mx + 1) { true }
    
    init {
        isPrime[0] = false
        isPrime[1] = false
        for (i in 2 .. mx) {
            if (isPrime[i]) {
                primes.add(i)
                for (j in 2 * i .. mx step i) isPrime[j] = false
            }
        }
    }
    
    constructor() : this(10)
}

class MergedCtx(fctCtx: FctCtx, primesCtx: PrimesCtx) : FctCtx by fctCtx, PrimesCtx by primesCtx {
    fun solve(tc: Int) {
        val (n, s) = readInts()
        var cnt = 0
        for (i in 0 until n) {
            val (dx, dy, x, y) = readInts()
            // Check if ball ends up in pocket at (0,0), (0,s), (s,0), or (s,s)
            if (x == y && dx == dy) ++cnt
            else if (x + y == s && dx + dy == 0) ++cnt
        }
        println(cnt)
    }
}

fun yes() = println("YES")
fun no() = println("NO")

fun main() = MergedCtx(FctCtxImpl(), PrimesCtxImpl()).run {
    var t = 1
    t = readInt()
    repeat(t, ::solve)
}


// https://github.com/VaHiX/CodeForces/