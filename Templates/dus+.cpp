/*
*  author: yaoveil
*  date:   2021-06-25 13:29:12
*/
class Dsu {
public:
  vector<int> p;
  vector<int> sz;
  int n;

  Dsu(int _n) : n(_n) {
    p.resize(n);
    sz.resize(n);
    iota(p.begin(), p.end(), 0);
    fill(sz.begin(), sz.end(), 1);
  }

  inline int get(int x) {
    return (x == p[x] ? x : (p[x] = get(p[x])));
  }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      sz[y] += sz[x];
      return true;
    }
    return false;
  }

  int size(int par) {
    return sz[par];
  }
};