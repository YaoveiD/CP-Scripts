#include <bits/stdc++.h>

using namespace std;

class fenwick {
public:
  int n;
  vector<int> tree;

  fenwick(int _n) : n(_n), tree(_n + 1) {}

  static constexpr int lowbit(int x) {
    return x & (-x);
  }

  //x -> position, d -> delta
  void update(int x, int d) {
    assert(x >= 0);
    while (x <= n) {
      tree[x] += d;
      x += lowbit(x);
    }
  }

  //(0, x]
  int query(int x) const {
    assert(x >= 0);
    int ret = 0;
    while (x > 0) {
      ret += tree[x];
      x -= lowbit(x);
    }
    return ret;
  }

  //[l, r]
  int range(int l, int r) const {
    return query(r) - query(l - 1);
  }
};

int main() {
  int N = 12;
  fenwick fen(N + 1);
  for (int i = 1; i <= N; ++i)
    cout << i << ": " << "[" << i - fen.lowbit(i) + 1 << "," << i << "]\n";

  for (int i = 1; i <= N; ++i)
    fen.update(i, 1);
  
  for (int i = 1; i <= N; ++i)
    fen.query(i);
  return 0;
}