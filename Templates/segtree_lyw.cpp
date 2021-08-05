#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>

using namespace std;

const int inf = (int) 1e9 + 123;

template<typename T>
class segtree {
private:
  //global actually
  #define ls (i << 1 | 1)
  #define rs ((i << 1) + 2)
public:
  T dummy;
  int N;
  struct node {
    int l, r;
    T val;
    //don't forget to set a default value
  };
  vector<node> tree;

  segtree(int n) : dummy(0) {
    N = 1;
    while (N < n) {
      N *= 2;
    }
    tree.resize(2 * N - 1);
    build(0, 0, n - 1);
  }

  segtree(int n, vector<T>& A) : dummy(0) {
    assert(n == (int) A.size());
    N = 1;
    while (N < n) {
      N *= 2;
    }
    tree.resize(N * 2 - 1);
    build(0, 0, n - 1, A);
  }

  inline T combine(T A, T B) {
    return A + B;
  }

  inline void pull(int i) {
    tree[i].val = combine(tree[ls].val, tree[rs].val);
  }

  void build(int i, int L, int R, vector<T>& A) {
    tree[i].l = L;
    tree[i].r = R;
    if (L == R) {
      tree[i].val = A[L];
      return;
    }
    int mid = L + (R - L) / 2;
    build(ls, L, mid, A);
    build(rs, mid + 1, R, A);
    pull(i);
  }

  void build(int i, int L, int R) {
    tree[i].l = L;
    tree[i].r = R;
    tree[i].val = 0; // default
    if (L == R) {
      return;
    }
    int mid = L + (R - L) / 2;
    build(ls, L, mid);
    build(rs, mid + 1, R);
  }

  T query(int i, int L, int R) {
    if (tree[i].l > R or tree[i].r < L) {
      return dummy;
    }
    if (tree[i].l >= L and tree[i].r <= R) {
      return tree[i].val;
    }
    return combine(query(ls, L, R), query(rs, L, R));
  }

  int query(int i, int cutoff) {
    if (tree[i].l == tree[i].r) {
      return tree[i].val <= cutoff ? tree[i].l : -2; // index or invalid
    }
    if (tree[ls].val <= cutoff) {
      return query(ls, cutoff);
    } else {
      return query(rs, cutoff);
    }
  }

  void update(int i, int L, int R, T val) {
    if (tree[i].l > R or tree[i].r < L) {
      return;
    }
    if (tree[i].l == tree[i].r) {
      tree[i].val = val; // don't forget to ...
      return;
    }
    update(ls, L, R, val);
    update(rs, L, R, val);
    pull(i);
  }

  void update(int i, int p, T val) {
    if (tree[i].l == tree[i].r) {
      tree[i].val = val; // val + d
      return;
    }
    int mid = tree[i].l + (tree[i].r - tree[i].l) / 2;
    if (p <= mid) {
      update(ls, p, val);
    } else {
      update(rs, p, val);
    }
    pull(i);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  int N, Q;
  cin >> N >> Q;
  vector<long long> A(N);
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
  }
  segtree<long long> st(N, A);
  for (int q = 0; q < Q; ++q) {
    int op, A, B;
    cin >> op >> A >> B;
    if (op == 1) {
      st.update(0, A, B);
    } else {
      cout << st.query(0, A, B - 1) << '\n';
    }
  }
  return 0;
}