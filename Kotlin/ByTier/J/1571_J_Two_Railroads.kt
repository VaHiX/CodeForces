// Contest 1571, Problem J: Two Railroads
// URL: https://codeforces.com/contest/1571/problem/J

import java.io.*
import java.util.*
import kotlin.math.min
import kotlin.system.measureTimeMillis

class LineReader(tempReader: Reader) {
  private val reader = BufferedReader(tempReader)

  fun hasNext() = peek() != -1

  private fun peek(): Int {
    reader.mark(1)
    val result = reader.read()
    return if (result == -1) result else result.apply { reader.reset() }
  }

  fun skipSpaces() {
    while (Character.isWhitespace(peek())) reader.read()
  }

  fun readLine(): String = reader.readLine()

  fun longList() = readLine().split(' ').map(String::toLong)

  fun intList() = readLine().split(' ').map(String::toInt)
}

typealias ML = MutableList<Long>

typealias MI = MutableList<Int>

typealias LL = List<Long>

typealias LLL = List<LL>

typealias PLL = Pair<Long, Long>

typealias PPLL = Pair<Long, PLL>

const val E6 = 1000000
const val E7 = 10000000
const val M7 = 1000000007L
const val M9 = 1000000009L
const val MFFT = 998244353L
const val INF = 2000000000000000000L

infix fun Int.middle(other: Int): Int {
  return this + (other - this) / 2
}

infix fun Double.middle(other: Double): Double {
  return this + (other - this) / 2
}

infix fun Long.middle(other: Long): Long {
  return this + (other - this) / 2
}

fun <T : Comparable<T>> Iterable<T>.shrink(): List<T> {
  val list = sorted()
  return buildList {
    var i = -1
    while (++i < list.size) {
      add(list[i])
      while (i + 1 < list.size && list[i] == list[i + 1]) ++i
    }
  }
}

fun lowerBound(from: Long, to: Long, comparison: (Long) -> Long): Long {
  var left = from
  var right = to + 1
  while (left < right) {
    val mid = left middle right
    val result = comparison(mid)
    if (result >= 0) {
      right = mid
    } else {
      left = mid + 1
    }
  }
  return left
}

fun upperBound(from: Long, to: Long, comparison: (Long) -> Long): Long {
  var left = from
  var right = to + 1
  while (left < right) {
    val mid = left middle right
    val result = comparison(mid)
    if (result > 0) {
      right = mid
    } else {
      left = mid + 1
    }
  }
  return left
}

fun binarySearch(
    from: Double,
    to: Double,
    epsilon: Double = 1e-6,
    comparison: (Double) -> Double,
): Double {
  var left = from
  var right = to
  while (right - left >= epsilon) {
    val mid = left middle right
    val result = comparison(mid)
    if (result > 0) {
      right = mid
    } else {
      left = mid
    }
  }
  return left
}

fun <T : Comparable<T>> List<T>.upperBound(key: T, from: Int = 0, to: Int = size - 1): Int {
  return upperBound(from.toLong(), to.toLong()) { this[it.toInt()].compareTo(key).toLong() }.toInt()
}

fun <T : Comparable<T>> List<T>.lowerBound(key: T, from: Int = 0, to: Int = size - 1): Int {
  return lowerBound(from.toLong(), to.toLong()) { this[it.toInt()].compareTo(key).toLong() }.toInt()
}

fun <T : Comparable<T>> Array<T>.upperBound(key: T, from: Int = 0, to: Int = size - 1): Int {
  return upperBound(from.toLong(), to.toLong()) { this[it.toInt()].compareTo(key).toLong() }.toInt()
}

fun <T : Comparable<T>> Array<T>.lowerBound(key: T, from: Int = 0, to: Int = size - 1): Int {
  return lowerBound(from.toLong(), to.toLong()) { this[it.toInt()].compareTo(key).toLong() }.toInt()
}

fun binPow(number: Long, power: Long, mod: Long): Long {
  var result = 1L
  var a = number % mod
  var n = power
  while (n > 0) {
    if (n % 2 != 0L) result = (result * a) % mod
    a = (a * a) % mod
    n /= 2
  }
  return result
}

tailrec fun gcd(a: Long, b: Long): Long = if (b == 0L) a else gcd(b, a % b)

fun lcm(a: Long, b: Long) = a * b / gcd(a, b)

fun main(args: Array<String>) {
  if (args.isNotEmpty() && args.first() == "local") {
    val reader = LineReader(FileReader("input.txt"))
    PrintWriter(File("output.txt")).use {
      while (reader.hasNext()) {
        it.println(
            "\n${
                        measureTimeMillis {
                            solve(reader, it)
                        }
                    } ms\n"
        )
        reader.skipSpaces()
      }
    }
  } else {
    val reader = LineReader(InputStreamReader(System.`in`))
    PrintWriter(System.out).use { solve(reader, it) }
  }
}

class MinCostFlowSolver(n: Int) {
  data class Edge(var to: Int, var cost: Long, var capacity: Long, var flow: Long = 0)

  val g = Array<MutableList<Int>>(n) { mutableListOf() }
  val edges = mutableListOf<Edge>()

  private val was = BooleanArray(n)
  private val p = LongArray(n)
  private val d = LongArray(n)

  private var s: Int = 0
  private var t: Int = n - 1

  fun addEdge(v: Int, u: Int, c: Long, w: Long) {
    g[v].add(edges.size)
    edges.add(Edge(u, w, c))
    g[u].add(edges.size)
    edges.add(Edge(v, -w, 0))
  }

  private fun calcPotentials(): Boolean {
    val queue: Queue<Int> = LinkedList()
    was.fill(false)
    d.fill(INF)
    p.fill(0)

    queue.offer(s)
    was[s] = true
    d[s] = 0

    while (queue.isNotEmpty()) {
      val v = queue.remove()
      was[v] = false

      for (i in g[v]) {
        val edge = edges[i]
        val u = edge.to

        if (edge.flow >= edge.capacity) continue
        if (d[v] + edge.cost >= d[u]) continue

        d[u] = d[v] + edge.cost
        if (!was[u]) {
          queue.offer(u)
          was[u] = true
        }
      }
    }
    return d[t] < INF
  }

  private fun calcDistances(): Boolean {
    for (i in d.indices) {
      d[i] += p[i] - p[s]
    }

    d.copyInto(p)
    d.fill(INF)
    was.fill(false)

    val queue: Queue<Pair<Long, Int>> = PriorityQueue(compareBy(Pair<Long, Int>::first))

    d[s] = 0
    queue.offer(d[s] to s)

    while (queue.isNotEmpty()) {
      val (dv, v) = queue.remove()

      if (was[v]) continue
      was[v] = true

      for (i in g[v]) {
        val edge = edges[i]
        val u = edge.to

        if (edge.flow >= edge.capacity) continue

        val du = dv + edge.cost + p[v] - p[u]

        if (du < d[u]) {
          d[u] = du
          queue.offer(du to u)
        }
      }
    }
    was.fill(false)
    return d[t] < INF
  }

  private fun pushFlow(v: Int, flow: Long): Long {
    if (v == t) return flow
    if (was[v]) return 0L
    was[v] = true

    var totalFlow = 0L
    for (i in g[v]) {
      val edge = edges[i]
      val u = edge.to

      if (edge.flow >= edge.capacity) continue
      if (d[v] + p[v] - p[u] + edge.cost != d[u]) continue

      val pushed = pushFlow(u, min(flow - totalFlow, edge.capacity - edge.flow))
      totalFlow += pushed
      edges[i].flow += pushed
      edges[i xor 1].flow -= pushed
      if (totalFlow == flow) break
    }
    return totalFlow
  }

  fun minCostFlow(source: Int, sink: Int, flow: Long): Pair<Long, Long> {
    s = source
    t = sink

    if (!calcPotentials()) return 0L to 0L

    var totalFlow = 0L
    var totalCost = 0L

    while (calcDistances() && totalFlow < flow) {
      var pushed = pushFlow(s, flow - totalFlow)
      while (pushed > 0) {
        totalFlow += pushed
        totalCost += pushed * (d[t] + p[t])

        was.fill(false)
        pushed = pushFlow(s, flow - totalFlow)
      }
    }

    return totalFlow to totalCost
  }

  fun minCostAnyFlow(source: Int, sink: Int): Pair<Long, Long> {
    s = source
    t = sink

    if (!calcPotentials()) return 0L to 0L

    var totalFlow = 0L
    var totalCost = 0L

    while (calcDistances() && d[t] + p[t] < 0) {
      var pushed = pushFlow(s, INF)
      while (pushed > 0) {
        totalFlow += pushed
        totalCost += pushed * (d[t] + p[t])

        was.fill(false)
        pushed = pushFlow(s, INF)
      }
    }

    return totalFlow to totalCost
  }

  fun minCostMaxFlow(source: Int, sink: Int): Pair<Long, Long> {
    s = source
    t = sink

    if (!calcPotentials()) return 0L to 0L

    var totalFlow = 0L
    var totalCost = 0L

    while (calcDistances()) {
      var pushed = pushFlow(s, INF)
      while (pushed > 0) {
        totalFlow += pushed
        totalCost += pushed * (d[t] + p[t])

        was.fill(false)
        pushed = pushFlow(s, INF)
      }
    }

    return totalFlow to totalCost
  }
}

class MaxFlowSolver(n: Int) {
  data class Edge(var to: Int, var capacity: Long, var flow: Long = 0)

  val g = Array<MutableList<Int>>(n) { mutableListOf() }
  val edges = mutableListOf<Edge>()

  private val queue: Queue<Int> = LinkedList()
  private val idx = IntArray(n)
  private val d = LongArray(n)

  private var s: Int = 0
  private var t: Int = n - 1

  fun addEdge(v: Int, u: Int, c: Long) {
    g[v].add(edges.size)
    edges.add(Edge(u, c))
    g[u].add(edges.size)
    edges.add(Edge(v, 0))
  }

  private fun calcLayers(): Boolean {
    idx.fill(0)
    d.fill(INF)

    queue.offer(s)
    d[s] = 0

    while (queue.isNotEmpty()) {
      val v = queue.remove()

      for (i in g[v]) {
        val edge = edges[i]
        val u = edge.to

        if (d[v] + 1 >= d[u]) continue
        if (edge.flow >= edge.capacity) continue

        d[u] = d[v] + 1
        queue.offer(u)
      }
    }
    return d[t] < INF
  }

  private fun pushFlow(v: Int, flow: Long): Long {
    if (v == t) return flow

    var totalFlow = 0L
    while (idx[v] < g[v].size) {
      val i = g[v][idx[v]]
      val edge = edges[i]
      val u = edge.to

      if (d[v] + 1 == d[u] && edge.flow < edge.capacity) {
        val pushed = pushFlow(u, min(flow - totalFlow, edge.capacity - edge.flow))
        totalFlow += pushed
        edges[i].flow += pushed
        edges[i xor 1].flow -= pushed
        if (totalFlow == flow) break
      }

      ++idx[v]
    }
    return totalFlow
  }

  fun maxFlow(source: Int, sink: Int): Long {
    s = source
    t = sink

    var totalFlow = 0L

    while (calcLayers()) {
      var pushed = pushFlow(s, INF)
      while (pushed > 0) {
        totalFlow += pushed
        pushed = pushFlow(s, INF)
      }
    }

    return totalFlow
  }

  fun minCut(): List<Int> =
      g.filterIndexed { v: Int, _: List<Int> -> d[v] < INF }
          .flatMap { e: MutableList<Int> ->
            e.filter { d[edges[it].to] >= INF && edges[it].flow > 0 }
          }
}

fun createSegmentTree(size: Int): LongArray =
    LongArray(size * 4) {
      return@LongArray INF
    }

fun LongArray.update(index: Int, value: Long, vl: Int = 0, vr: Int = size / 4, v: Int = 1) {
  if (vl + 1 == vr) {
    this[v] = value
    return
  }
  val mid = vl middle vr
  if (index < mid) update(index, value, vl, mid, v * 2)
  else update(index, value, mid, vr, v * 2 + 1)
  this[v] = min(this[v * 2], this[v * 2 + 1])
}

fun LongArray.query(l: Int, r: Int, vl: Int = 0, vr: Int = size / 4, v: Int = 1): Long {
  if (vr <= l || r <= vl) return INF
  if (l <= vl && vr <= r) return this[v]
  val mid = vl middle vr
  return min(query(l, r, vl, mid, v * 2), query(l, r, mid, vr, v * 2 + 1))
}

fun solve(reader: LineReader, writer: PrintWriter) {
  val n = reader.readLine().toInt()
  val a = reader.longList()
  val b = reader.longList()
  val c = reader.longList()

  val toLeft = LongArray(n - 1)
  val toRight = LongArray(n - 1)

  val sum = c.runningFold(0L, Long::plus)

  var minB: Long
  minB = b[0]
  toLeft[0] = a[0] + minB
  for (i in 1..n - 2) {
    minB = min(minB + c[i], b[i])
    toLeft[i] = a[i] + minB
  }

  minB = b[n - 2]
  toRight[n - 2] = a[n - 2] + minB
  for (i in n - 2 downTo 1) {
    minB = min(minB + c[i], b[i - 1])
    toRight[i - 1] = a[i - 1] + minB
  }

  val mnTree = createSegmentTree(n - 1)
  val sumTree = createSegmentTree(n - 1)
  val diffTree = createSegmentTree(n - 1)

  for (i in 0 until n - 1) {
    mnTree.update(i, min(toLeft[i], toRight[i]))
    sumTree.update(i, a[i] + sum[i + 1])
    diffTree.update(i, a[i] - sum[i + 1])
  }

  val queries = reader.readLine().toInt()
  repeat(queries) {
    val (ql, qr) = reader.intList().map { it - 1 }
    val ans =
        minOf(
            mnTree.query(ql, qr),
            sumTree.query(ql, qr) - sum[ql],
            diffTree.query(ql, qr) + sum[qr + 1],
        )
    writer.print("$ans ")
  }
}
