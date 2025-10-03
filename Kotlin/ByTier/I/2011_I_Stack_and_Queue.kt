// Contest 2011, Problem I: Stack and Queue
// URL: https://codeforces.com/contest/2011/problem/I

import java.io.*
import java.util.TreeMap
import java.util.TreeSet
import kotlin.random.Random
import kotlin.random.nextInt
import kotlin.system.measureTimeMillis

typealias pii = Pair<Int, Int>

typealias pll = Pair<Long, Long>

typealias ints = IntArray

typealias longs = LongArray

typealias bools = BooleanArray

fun Int.adjust(): Int {
  if (this >= p) {
    return this - p
  } else if (this < 0) {
    return this + p
  }
  return this
}

fun Int.snap(): Int {
  return if (this >= p) {
    this - p
  } else this
}

infix fun Int.mm(b: Int): Int {
  return ((this.toLong() * b) % p).toInt()
}

infix fun Int.mp(b: Int): Int {
  val ans = this + b
  return if (ans >= p) ans - p else ans
}

infix fun Int.ms(b: Int): Int {
  val ans = this - b
  return if (ans < 0) ans + p else ans
}

fun Long.modded(): Int = (this % p).toInt().adjust()

fun Int.inverse(): Int = intPow(this, p - 2)

fun Int.additiveInverse(): Int = if (this == 0) 0 else p - this

infix fun Int.modDivide(b: Int): Int {
  return this mm (b.inverse())
}

fun intPow(x: Int, e: Int): Int {
  var x = x
  var e = e
  var ret = 1
  while (e > 0) {
    if (e and 1 == 1) ret = ret mm x
    x = x mm x
    e = e shr 1
  }
  return ret
}

const val plarge = 1_000_000_727
const val nlarge = -plarge
const val phuge = 2_727_000_000_000_000_000L
const val nhuge = -phuge

fun IntArray.put(i: Int, v: Int) {
  this[i] = (this[i] + v).adjust()
}

val mint
  get() = mutableListOf<Int>()
val mong
  get() = mutableListOf<Long>()
val mchar
  get() = mutableListOf<Char>()

fun IntArray.minindex() = this.indexOf(this.minOrNull()!!)

fun IntArray.maxindex() = this.indexOf(this.maxOrNull()!!)

fun List<Char>.conca(): String = this.joinToString("")

val CharArray.conca: String
  get() = this.concatToString()
val IntArray.conca: String
  get() = this.joinToString(" ")

@JvmName("concaInt") fun List<Int>.conca(): String = this.joinToString(" ")

val LongArray.conca: String
  get() = this.joinToString(" ")

@JvmName("concaLong") fun List<Long>.conca(): String = this.joinToString(" ")

@JvmName("concaString") fun List<String>.conca(): String = this.joinToString("")

val Boolean.chi: Int
  get() = if (this) 1 else 0
val BooleanArray.chiarray: IntArray
  get() = IntArray(this.size) { this[it].chi }
val Char.code: Int
  get() = this.toInt() - 'a'.toInt()

fun order(a: Int, b: Int): Pair<Int, Int> = Pair(minOf(a, b), maxOf(a, b))

val String.size
  get() = this.length

fun Int.has(i: Int): Boolean = (this and (1 shl i) != 0)

fun Long.has(i: Int): Boolean = (this and (1L shl i) != 0L)

fun dist(a: Int, b: Int): Int = if (a > b) a - b else b - a

fun dist(a: Long, b: Long): Long = if (a > b) a - b else b - a

inline fun TIME(f: () -> Unit) {
  val t = measureTimeMillis { f() }
  println("$t ms")
}

fun rand(x: Int) = Random.nextInt(x)

fun rand(x: IntRange) = Random.nextInt(x)

inline fun assert(x: Boolean, act: () -> Any = {}) {
  if (!x) error(act())
}

const val interactive = false

val YES: Unit
  get() = put("YES")
val NO: Unit
  get() = put("NO")

inline fun chmin(array: IntArray, index: Int, newValue: Int) {
  if (newValue < array[index]) array[index] = newValue
}

inline fun chmax(array: IntArray, index: Int, newValue: Int) {
  if (newValue > array[index]) array[index] = newValue
}

inline fun chmin(array: LongArray, index: Int, newValue: Long) {
  if (newValue < array[index]) array[index] = newValue
}

inline fun chmax(array: LongArray, index: Int, newValue: Long) {
  if (newValue > array[index]) array[index] = newValue
}

@Target(AnnotationTarget.FUNCTION) @Retention(AnnotationRetention.RUNTIME) annotation class show

object Reader {
  private const val BS = 1 shl 16
  private const val NC = 0.toChar()
  private val buf = ByteArray(BS)
  private var bId = 0
  private var size = 0
  private var c = NC
  var fakein = StringBuilder()
  private var IN: BufferedInputStream = BufferedInputStream(System.`in`, BS)
  val OUT: PrintWriter = PrintWriter(System.out)
  private val char: Char
    get() {
      if (interactive) {
        val c = System.`in`.read()
        return if (c == -1) NC else c.toChar()
      }
      while (bId == size) {
        size = IN.read(buf)
        if (size == -1) return NC
        bId = 0
      }
      return buf[bId++].toChar()
    }

  fun nextLong(): Long {
    var neg = false
    if (c == NC) c = char
    while (c < '0' || c > '9') {
      if (c == '-') neg = true
      if (c == NC) throw Error("Bad Input")
      c = char
    }
    var res = 0L
    while (c in '0'..'9') {
      res = (res shl 3) + (res shl 1) + (c - '0')
      c = char
    }
    return if (neg) -res else res
  }

  fun nextString(): String {
    val ret = StringBuilder()
    while (true) {
      c = char
      if (c == NC) throw Error("Bad Input")
      if (!isWhitespace(c)) {
        break
      }
    }
    do {
      ret.append(c)
      c = char
    } while (!isWhitespace(c))
    return ret.toString()
  }

  private fun isWhitespace(c: Char): Boolean {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == NC
  }

  fun rerouteInput() {
    val S = fakein.toString()
    println("New Case ")
    println(S.take(80))
    println("...")
    fakein.clear()
    IN = BufferedInputStream(S.byteInputStream(), BS)
  }

  fun flush() {
    OUT.flush()
  }

  fun takeFile(name: String) {
    IN = BufferedInputStream(File(name).inputStream(), BS)
  }
}

fun keepimport() {
  val st1 = TreeSet<Int>()
  val st2 = TreeMap<Int, Int>()
}

fun put(aa: Any) {
  Reader.OUT.println(aa)
  if (interactive) {
    Reader.flush()
  }
}

fun put(vararg x: Any) {
  val count = x.size
  for ((pt, c) in x.withIndex()) {
    Reader.OUT.print(c)
    if (pt + 1 != count) Reader.OUT.print(" ")
  }
  Reader.OUT.print("\n")
  if (interactive) {
    Reader.flush()
  }
}

fun done() = Reader.OUT.close()

fun share(aa: Any) {
  Reader.fakein.append(format(aa) + "\n")
}

val getint: Int
  get() {
    val ans = getlong
    if (ans > Int.MAX_VALUE) {
      IntArray(1000000000)
      error("Input Overflow")
    }
    return ans.toInt()
  }
val getlong: Long
  get() = Reader.nextLong()
val getstr: String
  get() = Reader.nextString()

fun getline(n: Int): IntArray = IntArray(n) { getint }

fun getlineL(n: Int): LongArray = LongArray(n) { getlong }

fun subformat(a: Any?): String {
  return when (a) {
    null -> "null"
    is Iterable<*> -> a.joinToString(" ")
    is BooleanArray -> a.joinToString("") { if (it) "1" else "0" }
    is IntArray -> a.joinToString(" ")
    is LongArray -> a.joinToString(" ")
    else -> a.toString()
  }
}

fun format(a: Any?): String {
  return when (a) {
    null -> "null"
    is BooleanArray -> a.joinToString("") { if (it) "1" else "0" }
    is Array<*> -> "\n" + a.joinToString("\n") { subformat(it) }
    else -> subformat(a)
  }
}

var dmark = -1

infix fun Any.dei(a: Any?) {
  dmark++
  debug()
  println("<$dmark>   $this : ${format(a)}")
}

const val just = " "

enum class solveMode {
  real,
  rand,
  tc,
}

object solve {
  private var randCount = 100
  private var mode: solveMode = solveMode.real
  private var tcNum: Int = 0
  var rand: () -> Unit = {}
  private var TC: MutableMap<Int, () -> Unit> = mutableMapOf()
  private var tn: Long = 0

  fun cases(onecase: () -> Unit) {
    val t =
        if (mode == solveMode.real) {
          if (singleCase) 1 else getint
        } else if (mode == solveMode.tc) {
          1
        } else randCount
    if (mode != solveMode.real) tn = System.currentTimeMillis()
    repeat(t) {
      if (mode == solveMode.tc) {
        TC[tcNum]?.let { it() }
        Reader.rerouteInput()
      } else if (mode == solveMode.rand) {
        rand()
        Reader.rerouteInput()
      }
      onecase()
    }
    if (mode != solveMode.real) {
      val dt = System.currentTimeMillis() - tn
      println("Time $dt ms ")
    }
  }

  fun rand(a: () -> Unit) {
    this.rand = a
  }

  fun tc(id: Int = 0, a: () -> Unit) {
    TC[id] = a
  }

  fun usetc(a: Int = 0) {
    this.tcNum = a
    this.mode = solveMode.tc
  }

  fun userand(count: Int = 100) {
    this.randCount = count
    this.mode = solveMode.rand
  }
}

fun debug() {}

class BIT_Long(val n: Int) {

  val A = LongArray(n + 1)

  fun add(i: Int, v: Long) {
    var i = i
    i++
    while (i <= n) {
      A[i] += v
      i += i and (-i)
    }
  }

  fun set(i: Int, v: Long) = add(i, v - sumquery(i, i))

  fun presum(i: Int): Long {
    var ret = 0L
    var i = i
    i++
    while (i != 0) {
      ret += A[i]
      i -= i and (-i)
    }
    return ret
  }

  fun sumquery(l: Int, r: Int): Long {
    if (l > r) return 0
    return presum(r) - presum(l - 1)
  }

  override fun toString(): String {
    return (0 until n).map { sumquery(it, it) }.joinToString(" ")
  }
}

class simplePersistent(nSuggest: Int, ops: Int) {
  val empty = 0L

  fun op(l: Long, r: Long): Long {
    return l + r
  }

  val n = if (nSuggest >= 2) (nSuggest - 1).takeHighestOneBit() shl 1 else nSuggest
  val level = 31 - n.countLeadingZeroBits()
  val max = 2 * n + ops * (level + 1)

  val left = IntArray(max) { if (it <= n - 1) (it shl 1) else -1 }
  val right = IntArray(max) { if (it <= n - 1) (it shl 1) + 1 else -1 }
  val arr = LongArray(max) { empty }

  var rootNow = 1
  var size = 2 * n

  fun getVersionNumber(): Int {
    return rootNow
  }

  fun addvalue(i: Int, v: Long) {
    val new = addvaluerecur(i, v, rootNow, level)
    rootNow = new
  }

  private fun addvaluerecur(i: Int, v: Long, node: Int, l: Int): Int {
    val current = size++
    if (l == 0) {
      arr[current] = op(v, arr[node])
    } else {
      if (!i.has(l - 1)) {
        left[current] = addvaluerecur(i, v, left[node], l - 1)
        right[current] = right[node]
      } else {
        left[current] = left[node]
        right[current] = addvaluerecur(i, v, right[node], l - 1)
      }
      arr[current] = op(arr[left[current]], arr[right[current]])
    }
    return current
  }

  fun query(i: Int, l: Int, r: Int): Long {
    val l = maxOf(0, l)
    val r = minOf(n - 1, r)
    if (l > r) return 0L
    return query_recur(i, l, r, 0, n - 1)
  }

  private fun query_recur(i: Int, l: Int, r: Int, lo: Int, hi: Int): Long {
    if (lo > r || hi < l) return empty
    if (l <= lo && hi <= r) return arr[i]
    val m = (lo + hi) shr 1
    return op(query_recur(left[i], l, r, lo, m), query_recur(right[i], l, r, m + 1, hi))
  }

  fun compile(ver: Int): LongArray {
    return LongArray(n) { query(ver, it, it) }
  }

  override fun toString(): String {
    return compile(getVersionNumber()).conca
  }
}

inline fun BinarySearchFirstTrue(l: Int, r: Int, isTrue: (Int) -> Boolean): Int? {
  var L = l
  var R = r + 1
  while (L < R) {
    val m = (L + R) shr 1
    if (isTrue(m)) R = m else L = m + 1
  }
  return if (L == r + 1) null else L
}

inline fun BinarySearchLastTrue(l: Int, r: Int, isTrue: (Int) -> Boolean): Int? {
  var L = l - 1
  var R = r
  while (L < R) {
    val m = ((L + R) shr 1) + 1
    if (isTrue(m)) L = m else R = m - 1
  }
  return if (L == l - 1) null else L
}

inline fun BinarySearchFirstTrue(l: Long, r: Long, isTrue: (Long) -> Boolean): Long? {
  var L = l
  var R = r + 1
  while (L < R) {
    val m = (L + R) shr 1
    if (isTrue(m)) R = m else L = m + 1
  }
  return if (L == r + 1) null else L
}

inline fun BinarySearchLastTrue(l: Long, r: Long, isTrue: (Long) -> Boolean): Long? {
  var L = l - 1
  var R = r
  while (L < R) {
    val m = ((L + R) shr 1) + 1
    if (isTrue(m)) L = m else R = m - 1
  }
  return if (L == l - 1) null else L
}

class radd(val n: Int) {
  val things = LongArray(n + 1)

  fun add(l: Int, r: Int, inc: Int) {
    val ll = if (l < 0) 0 else l
    val rr = if (r > n - 1) n else r + 1
    if (ll > rr) return
    things[ll] += inc.toLong()
    things[rr] -= inc.toLong()
  }

  fun compile(): LongArray {
    val ret = LongArray(n)
    var here = 0L
    for (i in 0 until n) {
      here += things[i].toLong()
      ret[i] = here
    }
    return ret
  }
}

class raddp(val n: Int) {
  val things = IntArray(n + 1)

  fun add(l: Int, r: Int, inc: Int) {
    val ll = if (l < 0) 0 else l
    val rr = if (r > n - 1) n else r + 1
    if (ll > rr) return
    things[ll] += inc
    things[rr] -= inc
    things[ll] = things[ll].adjust()
    things[rr] = things[rr].adjust()
  }

  fun compile(): IntArray {
    val ret = IntArray(n)
    var here = 0
    for (i in 0 until n) {
      here += things[i]
      here = here.adjust()
      ret[i] = here
    }
    return ret
  }
}

const val p = 1_000_000_007
const val singleCase = true

fun main() {

  solve.cases {
    val n = getint
    val L = getline(n)

    var pos = 0

    val oneid = ints(n) { -1 }
    val twoid = ints(n) { -1 }
    val onefirst = ints(n) { -1 }
    val twofirst = ints(n) { -1 }

    val qs = Array(n) { intArrayOf(getint, getint - 1) }

    val timebuff = Array(2) { simplePersistent(n, n) }

    var qid = 0
    fun processevent(i: Int, mul: Int) {

      val (t, x) = qs[i]

      if (t == 1) {
        oneid[x] = pos++
        onefirst[x] = qid + 1

        timebuff[0].addvalue(oneid[x], L[x] * mul.toLong())
      } else if (t == 2) {
        twoid[x] = pos++
        twofirst[x] = qid + 1

        timebuff[1].addvalue(twoid[x], L[x] * mul.toLong())
      } else if (t == 3) {
        twoid[x] = oneid[x]

        timebuff[0].addvalue(oneid[x], -L[x] * mul.toLong())
        timebuff[1].addvalue(twoid[x], L[x] * mul.toLong())
      }
      qid++
    }

    val times = Array(2) { ints(n + 1) }

    for (t in 0..n) {
      for (i in 0 until 2) {
        times[i][t] = timebuff[i].getVersionNumber()
      }
      if (t != n) {
        processevent(t, 1)
      }
    }
    val S = radd(n + 1)
    for (x in 0 until n) {
      if (oneid[x] != -1 && twoid[x] != -1 && oneid[x] != twoid[x]) {
        val atleast = maxOf(onefirst[x], twofirst[x])
        var badtime =
            BinarySearchFirstTrue(atleast, n) { t ->
              val A = timebuff[0].query(times[0][t], 0, oneid[x] - 1)
              val B = timebuff[1].query(times[1][t], twoid[x] + 1, pos - 1)
              A < B + L[x]
            } ?: (n + 1)
        var goodagain =
            BinarySearchFirstTrue(atleast, n) { t ->
              val A = timebuff[0].query(times[0][t], 0, oneid[x] - 1)
              val B = timebuff[1].query(times[1][t], twoid[x] + 1, pos - 1)
              A <= B - L[x]
            } ?: (n + 1)

        if (badtime <= goodagain - 1) {
          S.add(badtime, goodagain - 1, 1)
        }
      }
    }
    val ans = S.compile()
    for (t in 1..n) {
      put(if (ans[t] > 0) "NO" else "YES")
    }
  }
  done()
}
