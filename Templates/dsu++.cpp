class Dsu {
public:
  int n;
  vector<int> p;
  vector<int> weight;

  Dsu(int _n) : n(_n) {
    p.resize(n);
    weight.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) {
    if (x != p[x]) {
      int t = p[x];
      p[x] = get(p[x]);
      weight[x] += weight[t];
    }
    return p[x];
  }

  inline bool unite(int x, int y, int w = 0) {
    int px = get(x);
    int py = get(y);
    if (px != py) {
      p[px] = py;
      weight[px] = -weight[x] + weight[y] + w;
      return true;
    }
    // here should be some constraints
    return false;
  }
};