// Contest 1958, Problem G: Observation Towers
// URL: https://codeforces.com/contest/1958/problem/G

import java.io.BufferedReader
import java.io.InputStreamReader
import java.io.PrintWriter
import java.util.*
import kotlin.math.*
import kotlin.system.exitProcess
import kotlin.system.measureNanoTime

const val iinf: Int = 0x3fffffff
const val inf: Long = 0x1fffffffffffffff
const val eps: Double = 1e-9
const val MOD: Int = 1000000007

fun solve() {
  val n = In.nextInt()
  val k = In.nextInt()
  val x = In.nextIntArray(k) { it - 1 }
  val h = In.nextIntArray(k)
  val q = In.nextInt()
  val ans = ia(q)
  val ls = ia(q)
  val rs = ia(q)
  val right = ia(n, init = n * 2)
  val left = ia(n, init = -n)
  for (i in 0 until k) {
    right[x[i]] = x[i] - h[i]
    left[x[i]] = x[i] + h[i]
  }
  for (i in 0 until n - 1) {
    left[i + 1] = max(left[i], left[i + 1])
    right[n - i - 2] = min(right[n - i - 2], right[n - i - 1])
  }
  for (i in 0 until q) {
    ls[i] = In.nextInt() - 1
    rs[i] = In.nextInt() - 1
    val lv = max(0, min(ls[i] - left[ls[i]], right[ls[i]] - ls[i]))
    val rv = max(0, min(rs[i] - left[rs[i]], right[rs[i]] - rs[i]))
    val cs1 = (ls[i] + rs[i]) / 2
    val cs2 = (ls[i] + rs[i] + 1) / 2
    val av = max(0, min(rs[i] - left[cs1], right[cs2] - ls[i]))
    ans[i] = min(lv + rv, av)
  }
  println(ans.joinToString(" "))
}

fun Int.testbit(n: Int) = ((this shr n) and 1) == 1

typealias IPair = Pair<Int, Int>

typealias LPair = Pair<Long, Long>

typealias ILPair = Pair<Int, Long>

typealias Vec<E> = MutableList<E>

typealias Arr<E> = Array<E>

typealias LA = LongArray

typealias LAA = Array<LA>

typealias LAAA = Array<LAA>

typealias IA = IntArray

typealias IAA = Array<IA>

typealias IAAA = Array<IAA>

val out: PrintWriter = PrintWriter(System.out, false)
val err: PrintWriter = PrintWriter(System.err, true)

fun ia(n0: Int, init: Int = 0) = IA(n0) { init }

fun iaa(n0: Int, n1: Int, init: Int = 0) = IAA(n0) { IA(n1) { init } }

fun iaaa(n0: Int, n1: Int, n2: Int, init: Int = 0) = IAAA(n0) { iaa(n1, n2, init) }

fun la(n0: Int, init: Long = 0L) = LA(n0) { init }

fun laa(n0: Int, n1: Int, init: Long = 0L) = LAA(n0) { LA(n1) { init } }

fun laaa(n0: Int, n1: Int, n2: Int, init: Long = 0L) = LAAA(n0) { laa(n1, n2, init) }

operator fun Long.plus(x: Mint): Mint = x.plus(this)

operator fun Long.minus(x: Mint): Mint = x.minus(this)

operator fun Long.times(x: Mint): Mint = x.times(this)

operator fun Long.div(x: Mint): Mint = x.div(this)

operator fun Int.plus(x: Mint): Mint = x.plus(this)

operator fun Int.minus(x: Mint): Mint = x.minus(this)

operator fun Int.times(x: Mint): Mint = x.times(this)

operator fun Int.div(x: Mint): Mint = x.div(this)

class Mint private constructor(val value: UInt) {
  companion object {
    val ZERO = Mint(0u)
    val ONE = Mint(1u)
    val TWO = Mint(2u)
    val THREE = Mint(3u)
    val UMOD: UInt = MOD.toUInt()

    fun Int.mint(): Mint = Mint(this.mod(MOD).toUInt())

    fun Long.mint(): Mint = Mint(this.mod(MOD).toUInt())
  }

  private fun mod(x: UInt) = Mint(min(x, x - UMOD))

  operator fun plus(mi: Mint): Mint = mod(value + mi.value)

  operator fun minus(mi: Mint): Mint = mod(value - mi.value + UMOD)

  operator fun times(mi: Mint): Mint = Mint((value.toULong() * mi.value.toULong() % UMOD).toUInt())

  operator fun div(mi: Mint): Mint = times(mi.inv())

  operator fun plus(x: Int): Mint = plus(x.toLong())

  operator fun minus(x: Int): Mint = minus(x.toLong())

  operator fun times(x: Int): Mint = times(x.toLong())

  operator fun div(x: Int): Mint = times(x.mint().inv())

  operator fun plus(x: Long): Mint = (value.toLong() + x).mint()

  operator fun minus(x: Long): Mint = (value.toLong() - x).mint()

  operator fun times(x: Long): Mint = (value.toLong() * x).mint()

  operator fun div(x: Long): Mint = times(x.mint().inv())

  fun inv(): Mint {
    var a = value.toInt()
    var b = MOD
    var u = 1L
    var v = 0L
    while (b >= 1) {
      val t = (a / b).toLong()
      a -= (t * b).toInt()
      val tmp1 = a
      a = b
      b = tmp1
      u -= t * v
      val tmp2 = u
      u = v
      v = tmp2
    }
    if (a != 1) {
      throw ArithmeticException("divide by zero")
    }
    return u.mint()
  }

  infix fun pow(b: Long): Mint {
    if (b < 0) {
      throw ArithmeticException("negative power")
    }
    var b = b
    var a = value.toLong()
    var res = ONE
    while (b > 0) {
      if (b and 1 == 1L) {
        res *= a
      }
      a = a * a % MOD
      b = b shr 1
    }
    return res
  }

  override fun toString(): String = value.toString()

  override fun equals(other: Any?) = other is Mint && value == other.value

  override fun hashCode() = value.toInt()
}

fun main() {
  Thread(
          null,
          {
            try {
              System.err.printf(
                  "%.1f ms",
                  measureNanoTime {
                    solve()
                    out.flush()
                  } / 1000000.0,
              )
            } catch (t: Throwable) {
              out.flush()
              t.printStackTrace()
              exitProcess(-1)
            }
          },
          "main",
          1 shl 28,
      )
      .start()
}

fun debug(vararg args: Any?) {
  err.println(
      args.joinToString(" ") {
        when (it) {
          is IA -> it.contentToString()
          is LA -> it.contentToString()
          is Arr<*> -> it.contentDeepToString()
          is Double -> String.format("%.10f", it)
          else -> it.toString()
        }
      }
  )
}

fun println(vararg args: Any?) {
  out.println(
      args.joinToString(" ") {
        when (it) {
          is IA -> it.joinToString(" ")
          is LA -> it.joinToString(" ")
          is Arr<*> -> it.joinToString(" ")
          is Double -> String.format("%.10f", it)
          else -> it.toString()
        }
      }
  )
}

object In {
  private val reader = BufferedReader(InputStreamReader(System.`in`), 0x10000)
  private var tokenizer: StringTokenizer? = null

  fun next(): String {
    while (tokenizer?.hasMoreTokens() != true) {
      tokenizer = StringTokenizer(reader.readLine())
    }
    return tokenizer!!.nextToken()
  }

  fun nextInt() = next().toInt()

  fun nextLong() = next().toLong()

  fun nextDouble() = next().toDouble()

  fun nextCharArray() = next().toCharArray()

  fun nextCharGrid(n: Int, m: Int) = Arr(n) { nextCharArray() }

  fun nextStringArray(n: Int, op: (String) -> String = { it }) = Arr(n) { op(next()) }

  fun nextIntArray(n: Int, op: (Int) -> Int = { it }) = IA(n) { op(nextInt()) }

  fun nextIntMatrix(h: Int, w: Int, op: (Int) -> Int = { it }) = IAA(h) { nextIntArray(w, op) }

  fun nextLongArray(n: Int, op: (Long) -> Long = { it }) = LA(n) { op(nextLong()) }

  fun nextLongMatrix(h: Int, w: Int, op: (Long) -> Long = { it }) = LAA(h) { nextLongArray(w, op) }

  fun nextGraph(n: Int, m: Int, directed: Boolean = false): Arr<Vec<Int>> {
    val res: Arr<Vec<Int>> = Arr(n) { mutableListOf() }
    for (i in 0 until m) {
      val u = nextInt() - 1
      val v = nextInt() - 1
      res[u].add(v)
      if (!directed) {
        res[v].add(u)
      }
    }
    return res
  }
}
