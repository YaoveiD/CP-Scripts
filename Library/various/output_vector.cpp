template<typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    os << p.first << ' ' << p.second;
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    bool first = true;
    for (int x : v) {
        if (!first) os << ' ';
        os << x;
        first = false;
    }
    return os;
}
template<typename T, typename U, typename V>
pair<T, U> operator+(const pair<T, U>& p, V add) {
    return pair<T, U>{p.first + add, p.second + add};
}
template<typename T, char sep = ' '>
void output_vector(const vector<T>& v, const bool add_one = false, int start = -1, int end = -1) {
    if (start < 0) start = 0;
    if (end < 0) end = (int) v.size();

    for (int i = start; i < end; ++i) {
        if (i != start) cout << sep;
        cout << (add_one ? v[i] + 1 : v[i]);
    }
    cout << '\n';
}
