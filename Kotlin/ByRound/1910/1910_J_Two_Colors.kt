// Contest 1910, Problem J: Two Colors
// URL: https://codeforces.com/contest/1910/problem/J

import java.io.BufferedInputStream
import java.io.File
import java.io.PrintWriter
import java.util.TreeMap
import java.util.TreeSet
import kotlin.math.absoluteValue
import kotlin.random.Random
import kotlin.random.nextInt
import kotlin.system.measureTimeMillis

fun Int.adjust(): Int {
  if (this >= p) {
    return this - p
  } else if (this < 0) {
    return this + p
  }
  return this
}

fun Int.snap(): Int {
  if (this >= p) {
    return this - p
  } else return this
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

val Boolean.chi: Int
  get() = if (this) 1 else 0
val BooleanArray.chiarray: IntArray
  get() = IntArray(this.size) { this[it].chi }
val Char.code: Int
  get() = this.toInt() - 'a'.toInt()

fun IntArray.put(i: Int, v: Int) {
  this[i] = (this[i] + v).adjust()
}

val mint: MutableList<Int>
  get() = mutableListOf<Int>()
val mong: MutableList<Long>
  get() = mutableListOf<Long>()
val mchar: MutableList<Char>
  get() = mutableListOf()

fun IntArray.minindex(): Int = this.indexOf(this.minOrNull()!!)

fun IntArray.maxindex(): Int = this.indexOf(this.maxOrNull()!!)

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

typealias pii = Pair<Int, Int>

typealias pll = Pair<Long, Long>

fun order(a: Int, b: Int): Pair<Int, Int> = Pair(minOf(a, b), maxOf(a, b))

val String.size
  get() = this.length
const val randCount = 100

fun Int.has(i: Int): Boolean = (this and (1 shl i) != 0)

fun Long.has(i: Int): Boolean = (this and (1L shl i) != 0L)

inline fun TIME(f: () -> Unit) {
  val t = measureTimeMillis() { f() }
  println("$t ms")
}

fun rand(x: Int) = Random.nextInt(x)

fun rand(x: IntRange) = Random.nextInt(x)

fun dist(a: Int, b: Int): Int = (a - b).absoluteValue

fun dist(a: Long, b: Long): Long = (a - b).absoluteValue

typealias ints = IntArray

typealias longs = LongArray

typealias bools = BooleanArray

inline fun assert(x: Boolean, act: () -> Any = {}) {
  if (!x) error(act())
}

const val interactive = false

object Reader {
  private const val BS = 1 shl 16
  private const val NC = 0.toChar()
  private val buf = ByteArray(BS)
  private var bId = 0
  private var size = 0
  private var c = NC
  var warningActive = true
  var fakein = StringBuilder()
  private var IN: BufferedInputStream = BufferedInputStream(System.`in`, BS)
  val OUT: PrintWriter = PrintWriter(System.out)
  private val char: Char
    get() {
      if (interactive) {
        return System.`in`.read().toChar()
      }
      while (bId == size) {
        size = IN.read(buf)
        if (size == -1) return NC
        bId = 0
      }
      return buf[bId++].toChar()
    }

  fun nextInt(): Int {
    var neg = false
    if (c == NC) c = char
    while (c < '0' || c > '9') {
      if (c == '-') neg = true
      c = char
    }
    var res = 0
    while (c in '0'..'9') {
      res = (res shl 3) + (res shl 1) + (c - '0')
      c = char
    }
    return if (neg) -res else res
  }

  fun nextLong(): Long {
    var neg = false
    if (c == NC) c = char
    while (c < '0' || c > '9') {
      if (c == '-') neg = true
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
      if (!isWhitespace(c)) {
        break
      }
    }
    ret.append(c)
    while (true) {
      c = char
      if (isWhitespace(c)) {
        break
      }
      ret.append(c)
    }
    return ret.toString()
  }

  fun isWhitespace(c: Char): Boolean {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t'
  }

  fun rerouteInput() {
    if (warningActive) {
      put("Custom test enabled")
      println("Custom test enabled")
      warningActive = false
    }
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

fun eat() {
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
  for (c in x) {
    Reader.OUT.print(c)
    Reader.OUT.print(" ")
  }
  Reader.OUT.print("\n")
  if (interactive) {
    Reader.flush()
  }
}

fun done() {
  Reader.OUT.close()
}

fun share(aa: Any) {
  Reader.fakein.append(format(aa))
  Reader.fakein.append("\n")
}

val getintfast: Int
  get() = Reader.nextInt()
val getint: Int
  get() {
    val ans = getlong
    if (ans > Int.MAX_VALUE) IntArray(1000000000)
    return ans.toInt()
  }
val getlong: Long
  get() = Reader.nextLong()
val getstr: String
  get() = Reader.nextString()

fun getline(n: Int): IntArray = IntArray(n) { getint }

fun getlineL(n: Int): LongArray = LongArray(n) { getlong }

fun subformat(a: Any?): String {
  return if (a == null) "null"
  else if (a is Iterable<*>) a.joinToString(" ")
  else if (a is BooleanArray) a.joinToString("") { if (it) "1" else "0" }
  else if (a is IntArray) a.joinToString(" ")
  else if (a is LongArray) a.joinToString(" ") else a.toString()
}

fun format(a: Any?): String {
  if (a == null) {
    return "null"
  } else if (a is BooleanArray) {
    return a.joinToString("") { if (it) "1" else "0" }
  } else if (a is Array<*>) {
    return "\n" + a.joinToString("\n") { subformat(it) }
  } else {
    return subformat(a)
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
  var mode: solveMode = solveMode.real
  var tcNum: Int = 0
  var rand: () -> Unit = {}
  var TC: MutableMap<Int, () -> Unit> = mutableMapOf()
  var tn: Long = 0

  fun cases(onecase: () -> Unit) {
    val t =
        if (mode == solveMode.real) {
          if (singleCase) 1 else getint
        } else if (mode == solveMode.tc) {
          1
        } else randCount
    if (p != 998_244_353 && p != 1_000_000_007) {
      throw AssertionError("Not usual primes!")
    }
    if (t == 1 && mode != solveMode.real) {
      tn = System.currentTimeMillis()
    }
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
    if (t == 1 && mode != solveMode.real) {
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

  fun userand() {
    this.mode = solveMode.rand
  }
}

fun debug() {}

const val graphWeighed = true

class Graph(val n: Int, val m: Int, val directed: Boolean) {
  val maxedge = if (directed) m else m * 2

  var edgecount = 0

  val next = IntArray(maxedge)
  val head = IntArray(n) { -1 }
  val to = IntArray(maxedge)
  val from = IntArray(maxedge)
  val weights = IntArray(if (graphWeighed) m else 0)

  private fun primitive_add(u: Int, v: Int): Int {
    next[edgecount] = head[u]
    head[u] = edgecount
    to[edgecount] = v
    from[edgecount] = u
    edgecount++
    return edgecount - 1
  }

  fun add(u: Int, v: Int): Int {
    val e = primitive_add(u, v)
    if (!directed) primitive_add(v, u)
    return if (directed) e else e shr 1
  }

  fun addWeighted(u: Int, v: Int, w: Int): Int {
    val e = add(u, v)
    weights[e] = w
    return e
  }

  inline fun NS(a: Int, act: (Int) -> Unit) {
    var i = head[a]
    while (i != -1) {
      act(to[i])
      i = next[i]
    }
  }

  inline fun NS_E(a: Int, act: (e: Int, v: Int) -> Unit) {
    var i = head[a]
    while (i != -1) {
      act(i, to[i])
      i = next[i]
    }
  }

  inline fun everyEdge(act: (a: Int, b: Int, e: Int) -> Unit) {
    val s = if (directed) 1 else 2
    for (e in 0 until edgecount step s) {
      act(from[e], to[e], e)
    }
  }

  inline fun everyDirectedEdge(act: (a: Int, b: Int) -> Unit) {
    for (e in 0 until edgecount) {
      act(from[e], to[e])
    }
  }

  var root = 0
  var hasDFSorder: Boolean = false
  val preorder = IntArray(n)
  var postorder = IntArray(0)
  val parent = IntArray(n) { -1 }
  val parentEdge: IntArray = IntArray(n) { -1 }

  fun dfstree(singleComponent: Boolean) {

    hasDFSorder = true
    var preorderpt = 0
    val explored = BooleanArray(n)
    val S = IntArray(m + 1)
    var pt = 0
    parent.fill(-1)

    for (i in 0 until n) {
      if (parent[i] != -1 || (singleComponent && i != root)) continue
      S[pt++] = i
      parent[i] = i
      parentEdge[i] = -1
      while (pt > 0) {
        val v = S[--pt]
        if (explored[v]) {
          continue
        }
        preorder[preorderpt++] = v
        explored[v] = true
        NS_E(v) { e, w ->
          if (!explored[w]) {
            S[pt++] = w
            parent[w] = v
            parentEdge[w] = e
          }
        }
      }
    }
  }

  fun treeOrderDFS() = dfstree(true)

  fun dfsTreePostOrder(singleComponent: Boolean) {

    hasDFSorder = true
    var preorderpt = 0
    val explored = BooleanArray(n)

    val S = IntArray(m + 1)
    val Spopped = BooleanArray(m + 1)
    var pt = 0

    var postorderpt = 0
    postorder = IntArray(n)
    parent.fill(-1)

    for (i in 0 until n) {
      if (parent[i] != -1 || (singleComponent && i != root)) continue
      Spopped[pt] = false
      S[pt++] = i
      parent[i] = i
      parentEdge[i] = -1
      while (pt > 0) {
        val v = S[--pt]
        if (Spopped[pt]) {
          postorder[postorderpt++] = v
        }
        if (explored[v]) {
          continue
        }
        preorder[preorderpt++] = v
        Spopped[pt] = true
        explored[v] = true
        pt++
        NS_E(v) { e, w ->
          if (!explored[w]) {
            Spopped[pt] = false
            S[pt++] = w

            parent[w] = v
            parentEdge[w] = e
          }
        }
      }
    }
  }

  inline fun BFS(distRoot: Int): IntArray {
    val Q = IntArray(n)
    val explored = IntArray(n + 1) { -1 }
    val dist = IntArray(n) { -1 }
    var startpt = 0
    var endpt = -1

    Q[++endpt] = distRoot
    explored[distRoot] = distRoot
    dist[distRoot] = 0

    while (startpt <= endpt) {
      val x = Q[startpt++]
      NS(x) { a ->
        if (explored[a] == -1) {
          explored[a] = x
          dist[a] = dist[x] + 1
          Q[++endpt] = a
        }
      }
    }
    return dist
  }

  inline fun leafFirst(act: (Int) -> Unit) {
    if (!hasDFSorder) treeOrderDFS()
    for (i in preorder.lastIndex downTo 0) {
      act(preorder[i])
    }
  }

  inline fun rootFirst(act: (Int) -> Unit) {
    if (!hasDFSorder) treeOrderDFS()
    for (a in preorder) {
      act(a)
    }
  }

  inline fun rootFirstEdge(act: (from: Int, to: Int, e: Int) -> Unit) {
    if (!hasDFSorder) treeOrderDFS()
    for (i in preorder.indices) {
      val v = preorder[i]
      val p = parent[v]
      if (p == v) continue
      act(p, v, parentEdge[v])
    }
  }

  fun calculateSizes(): IntArray {
    val ret = IntArray(n) { 1 }
    leafFirst { v -> if (parent[v] != v) ret[parent[v]] += ret[v] }
    return ret
  }

  fun calculateSubtreeSum(weights: IntArray) {
    leafFirst { v -> if (parent[v] != v) weights[parent[v]] += weights[v] }
  }

  fun calculateDepth(): IntArray {
    val ret = IntArray(n)
    rootFirst { v -> if (parent[v] != v) ret[v] = ret[parent[v]] + 1 }
    return ret
  }

  inline fun subs(v: Int, act: (Int) -> Unit) {
    NS(v) { w -> if (w != parent[v]) act(w) }
  }

  fun calculateDepthWeighted(): LongArray {
    val ret = LongArray(n)
    rootFirstEdge { from, to, e -> ret[to] = ret[from] + weights[e] }
    return ret
  }

  fun outdegree(): IntArray {
    val ret = IntArray(n)
    everyDirectedEdge { a, b -> ret[a]++ }
    return ret
  }

  fun indegree(): IntArray {
    val ret = IntArray(n)
    everyDirectedEdge { a, b -> ret[b]++ }
    return ret
  }

  fun degree(): IntArray = outdegree()

  fun intime(): IntArray {
    val tin = IntArray(n)
    if (!hasDFSorder) treeOrderDFS()
    for (i in 0 until n) tin[preorder[i]] = i
    return tin
  }

  fun outtime(): IntArray {
    val tout = intime()
    leafFirst { v ->
      val p = parent[v]
      if (p != v) tout[p] = maxOf(tout[p], tout[v])
    }
    return tout
  }

  fun rootComponent(): IntArray {
    val ret = IntArray(n)
    rootFirst { v ->
      if (v == root) return@rootFirst
      if (parent[v] == root) {
        ret[v] = v
        return@rootFirst
      }
      ret[v] = ret[parent[v]]
    }
    return ret
  }

  fun compress(map: IntArray): Graph {
    val max = map.maxOrNull()!!
    val G = Graph(max + 1, this.m, this.directed)
    this.everyEdge { a, b, _ ->
      if (map[a] != map[b]) {
        G.add(map[a], map[b])
      }
    }
    return G
  }
}

const val p = 1_000_000_007
const val singleCase = true

fun main() {
  solve.cases {
    val n = getint
    val L = getline(n)
    val G = Graph(n, n - 1, false)

    repeat(n - 1) { G.addWeighted(getint - 1, getint - 1, getint) }

    val a = L.count { it == 0 }
    val b = L.count { it == 1 }

    if (a != b) {
      return@cases put("Infinity")
    }

    val depth = G.calculateDepth()
    val st = L.copyOf()
    G.calculateSubtreeSum(st)
    val sizes = G.calculateSizes()

    var cost = 0L
    G.everyEdge { a, b, e ->
      val lower = if (depth[a] > depth[b]) a else b
      val onelower = st[lower]
      val two = sizes[lower] - onelower
      val real = dist(two, onelower)
      cost += real.toLong() * G.weights[e shr 1]
    }
    put(cost)
  }
  done()
}
