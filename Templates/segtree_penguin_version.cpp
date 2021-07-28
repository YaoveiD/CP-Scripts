//codeforces penguin

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

//segment_tree, 1-indexed
template<typename T>
struct segment_tree{
    long long N;
    T INF;
    vector<T> node;
    segment_tree(vector<T> &X, T INF_) : INF(INF_){
        N = 1;
        while(N <= X.size()) N <<= 1;
        node.resize(2*N, INF);
        for (int i = 0; i < (int) X.size(); ++i) node[N+i] = X[i];
        for (int i = N - 1; i >= 0; --i) node[i] = compare(node[i*2], node[i*2+1]);
    }
    T compare(T A, T B){
        return std::max(A, B);
    }
    //for max_right, min_left
    //compare をいじった時にはこちらも変えた方がよい
    bool is_lower(T A, T B){
        return A < B;
    }
    //isAdd == true: add
    //isAdd == false: update
    void update(ll index, T val, bool isAdd){
        index += N;
        if(isAdd) node[index] += val;
        else node[index] = val;
        while(index > 0){
            index >>= 1;
            node[index] = compare(node[index*2], node[index*2+1]);
        }
    }
    T calc(ll left, ll right){
        T ret = INF;
        left += N;
        right += N;
        while(left < right){
            if(left & 1) ret = compare(node[left++], ret);
            if(right & 1) ret = compare(node[--right], ret);
            left >>= 1;
            right >>= 1;
        }
        return ret;
    }
    //[left, inf)
    ll min_left(ll left, T val, ll now = 1, ll l = 0, ll r = -1){
        if(r < 0) r = N;
        if(is_lower(node[now], val) || r<=left) return r;
        if(N <= now) return l;
        ll vl = min_left(left, val, now*2, l, (l+r)/2);
        if(vl == (l+r)/2) return min_left(left, val, now*2+1, (l+r)/2, r);
        return vl;
    }
    //(-inf, right]
    //内部では (-inf, right+1)
    ll max_right(ll right, T val, ll now = 1, ll l = 0, ll r = -1){
        if(r < 0) r = N, right++;
        if(is_lower(node[now], val) || right<=l) return l-1;
        if(N <= now) return l;
        ll vr = max_right(right, val, now*2+1, (l+r)/2, r);
        if(vr == (l+r)/2-1) return max_right(right, val, now*2, l, (l+r)/2);
        return vr;
    }
};