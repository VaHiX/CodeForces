#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

#define mp make_pair

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template <typename T> using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

// Constants and large arrays used by the solution.
// IT: number of iterations used to try advancing time in small steps
// N: upper bound on number of interval endpoints/events
// S: size for union-find / value buckets (kept large to allow creating merged
// buckets)
const int IT = 8;
const int N = 400200;
const int S = (int)2e7;

// Arrays of size S (careful: large memory). They represent merged-value buckets
// after repeated halving/rebuilding. `par` is a DSU parent pointer so that when
// buckets collapse they can be merged under a new representative.
int par[S];
int sz[S]; // size (count of original intervals) in each bucket
ll val[S]; // value associated with each bucket (may be updated during rebuild)

// Problem state variables
int n, evSz;   // n = number of input intervals, evSz = number of events stored
int a[N];      // list of active bucket ids (sparse list of buckets currently
               // present)
pli na[N];     // temporary (value,id) pairs used during rebuild
int m = 0;     // number of active entries in `a`
pii ev[2 * N]; // event list: pairs (time, id or -id) for interval starts/ends
ll B; // threshold B: if sum of values exceeds B, trigger rebuild/halving

// Running accumulators used by the sweep:
int curSz = 0;  // total count of intervals currently active
ll curSum = 0;  // sum of values (value * multiplicity) across active buckets
ll curTime = 0; // current sweep time
ll ANS = 0;     // accumulated answer (sum over time of curSum)
ll addToAll =
    0; // value added to all active buckets lazily (delayed increments)

int getPar(int v) { return par[v] == v ? v : par[v] = getPar(par[v]); }

bool isSimple() {
  if (m <= 1)
    return true;
  if (m > 2)
    return false;
  // When exactly two distinct buckets remain, the process is "simple"
  // (no complex merging required) iff their values differ by exactly 1.
  return abs(val[a[0]] - val[a[1]]) == 1;
}

void rebuild() {
  // Rebuild buckets when values grew too large: we apply the pending
  // `addToAll` to each active bucket, halve the values (integer division),
  // and then merge buckets with identical resulting values into a single
  // representative. This compaction keeps the number of active buckets small.
  int k = 0;
  curSum = 0;
  for (int i = 0; i < m; i++) {
    int v = a[i];
    if (sz[v] == 0)
      continue; // skip empty buckets
    // Apply lazy additive delta and then halve the bucket's value
    val[v] += addToAll;
    val[v] /= 2;
    curSum += val[v] * sz[v];
    na[k++] = mp(val[v], v);
  }
  // Sort by resulting value so we can merge equal-valued buckets
  sort(na, na + k);
  addToAll = 0; // we've materialized the lazy additions
  m = 0;
  int l = 0;
  while (l < k) {
    int r = l + 1;
    while (r < k && na[l].first == na[r].first)
      r++;
    if (r - l == 1) {
      // Unique value: keep the original bucket id
      a[m++] = na[l].second;
    } else {
      // Multiple buckets collapsed to same value: create a new merged node
      assert(n + 10 < S);
      n++;                  // allocate new bucket id
      val[n] = na[l].first; // set merged value
      par[n] = n;
      sz[n] = 0;
      // Redirect old buckets to be children of the new merged representative
      for (int i = l; i < r; i++) {
        int v = na[i].second;
        par[v] = n;
        sz[n] += sz[v];
      }
      a[m++] = n;
    }
    l = r;
  }
}

void advanceTime(ll maxTime) {
  assert(m > 0);
  assert(curTime < maxTime);
  assert(curSz > 0);
  if (curSum > B) {
    while (curTime < maxTime && curSum > B) {
      curTime++;
      rebuild();
    }
    return;
  }
  // If current sum <= B, we can advance time in a batch of k steps until
  // the sum would exceed B or we hit maxTime. In each time unit,
  // the curSum increases by curSz (each active interval contributes one
  // unit per time). The arithmetic series formula accumulates ANS quickly.
  ll k = (B - curSum) / curSz + 1;
  k = min(k, maxTime - curTime);
  assert(k > 0);
  // Add the contribution of curSum over k time units: curSum + (curSum+curSz)+
  // ...
  ANS += (curSum + curSum + (k - 1) * curSz) * k / 2;
  curSum += k * curSz; // curSum increased by curSz each time unit
  addToAll += k;       // lazily add k to all bucket values
  curTime += k;        // advance the global time
}

void advanceInLoop(ll maxTime) {
  ll startTime = curTime;
  ll startAns = ANS;
  for (int it = 0; it < IT; it++)
    if (curTime < maxTime)
      advanceTime(maxTime);
  if (curTime == maxTime)
    return;
  ll deltaTime = curTime - startTime;
  ll deltaAns = ANS - startAns;
  assert(deltaTime > 0);
  // Try to detect a repeating cycle of behavior after a few iterations
  // of `advanceTime`. If a steady delta (deltaTime, deltaAns) is observed,
  // we can fast-forward by multiplying this delta as many times as fits.
  ll k = (maxTime - curTime) / deltaTime;
  curTime += deltaTime * k;
  ANS += deltaAns * k;
  // Complete remaining steps naively
  while (curTime < maxTime)
    advanceTime(maxTime);
}

int main() {
  // Read input: n intervals and threshold B
  scanf("%d%lld", &n, &B);
  for (int i = 1; i <= n; i++) {
    int l, r;
    scanf("%d%d%lld", &l, &r, &val[i]);
    r++;                    // events are [l, r) so we put an end event at r
    ev[evSz++] = mp(l, i);  // start event
    ev[evSz++] = mp(r, -i); // end event (negative id)
    par[i] = i;             // initial DSU parent is itself
    sz[i] = 1;              // each original bucket has size 1
  }

  // Process events in chronological order
  sort(ev, ev + evSz);
  for (int pos = 0; pos < evSz; pos++) {
    // Ensure time monotonically increases to event time
    assert(curTime <= ev[pos].first);
    if (curSz == 0)
      // If no active intervals, we can jump current time to this event
      curTime = ev[pos].first;

    // Advance time up to the event time while the system is not in a
    // degenerate "simple" state. This uses a combination of direct
    // advanceTime calls and a fast-forwarding loop.
    while (curTime < ev[pos].first) {
      if (isSimple())
        break;
      advanceTime(ev[pos].first);
    }
    for (int it = 0; it < 3 * IT; it++)
      if (curTime < ev[pos].first)
        advanceTime(ev[pos].first);
    if (curTime < ev[pos].first)
      advanceInLoop(ev[pos].first);
    assert(curTime == ev[pos].first);

    // Process the event: insertion or deletion of an interval's bucket
    if (ev[pos].second > 0) {
      int v = ev[pos].second;
      curSz++;
      curSum += val[v];
      // When a bucket becomes active we store its value adjusted by
      // the current lazy offset so future operations treat it correctly
      val[v] -= addToAll;
      a[m++] = v;
    } else {
      int v = -ev[pos].second;
      v = getPar(v); // use merged representative for this bucket
      curSum -= val[v] + addToAll;
      sz[v]--;
      curSz--;
    }
  }

  // Print final accumulated answer
  printf("%lld\n", ANS);

  return 0;
}
// https://github.com/VaHiX/CodeForces/