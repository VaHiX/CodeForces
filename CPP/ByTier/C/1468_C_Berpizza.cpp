// Problem: CF 1468 C - Berpizza
// https://codeforces.com/contest/1468/problem/C

/*
C. Berpizza
Algorithms/Techniques: Simulation with multiple data structures to support efficient retrieval of minimum and maximum elements.
Time Complexity: O(q * log q) where q is the number of queries
Space Complexity: O(q)

The problem simulates a queue system where customers are served based on two criteria:
- Monocarp (type 2): Serve the earliest arriving customer
- Polycarp (type 3): Serve the customer who spent the most money, with ties broken by arrival time

Data Structures Used:
- std::set<long> s: Maintains order of customer IDs in insertion order (for first-come-first-served)
- std::set<std::pair<long, long>> t: Stores (money_spent, -insertion_time), allowing retrieval of max money spent
- std::map<long, long> r: Maps customer ID to the money they are expected to spend

Each insertion and deletion operation in sets/map takes O(log n) time.
*/

#include <cstdio>
#include <map>
#include <set>
#include <iterator>
#include <utility>

int main() {
  const long N = 1e9;
  std::set<long> s;           // Stores customer IDs in insertion order (for FIFO)
  std::set<std::pair<long, long>> t;  // Stores (money_spent, -insertion_time) for max money selection
  std::map<long, long> r;     // Maps customer ID to money spent
  long q;
  scanf("%ld", &q);
  long cnt(0);                // Counter for customer IDs
  while (q--) {
    long w;
    scanf("%ld", &w);
    if (w == 1) {             // Customer arrives
      ++cnt;
      long m;
      scanf("%ld", &m);
      s.insert(cnt);          // Add to insertion order set
      t.insert(std::make_pair(m, N - cnt));  // Add to money-time set
      r[cnt] = m;             // Store money spent for this customer
    } else if (w == 2) {      // Monocarp serves oldest customer
      long num = *(s.begin()); // Get oldest customer ID
      printf("%ld ", num);
      s.erase(num);           // Remove from insertion order set
      t.erase(std::make_pair(r[num], N - num)); // Remove from money-time set
      r.erase(num);           // Remove from mapping
    } else if (w == 3) {      // Polycarp serves highest money customer
      std::pair<long, long> cust = *t.rbegin(); // Get largest money spent (with smallest time)
      long num = N - cust.second; // Get original insertion time
      long spend = cust.first;
      printf("%ld ", num);
      s.erase(num);           // Remove from insertion order set
      t.erase(cust);          // Remove from money-time set
      r.erase(num);           // Remove from mapping
    }
  }
  puts("");
}


// https://github.com/VaHiX/codeForces/