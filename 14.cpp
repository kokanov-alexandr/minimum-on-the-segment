const int LOGN = 20;
//разреженная таблица
struct Sparse_table {
    int size;
    vector<vector<int>> table;
    vector<int> logn;
    //конструктор
    Sparse_table(const vector<int> &values) {
        size = values.size();
        table.resize(LOGN, vector<int> (values.size()));
        logn.resize(values.size() + 1);
        logn[0] = logn[1] = 0;

        for (int i = 2; i <= values.size(); ++i) {
            logn[i] = 1 + logn[i / 2];
        }
        //на отрезке длины один значение будет этим самым элементом
        for (int i = 0; i < values.size(); ++i) {
            //table[i][j] это мин на отрезке длины 2 в степени i начиная с j
            table[0][i] = values[i];
        }
        for (int k = 1; k < LOGN; ++k) {
            for (int i = 0; i + (1 << k) <= values.size(); ++i) {
                table[k][i] = min(
                        table[k - 1][i],
                        table[k - 1][i + (1 << (k - 1))]
                );
            }
        }
    }
    int get_min(int l, int r) {
        int k = logn[r - l];
        return min(
                table[k][l],
                table[k][r - (1 << k)]
        );
    }
};


int main() {
    vector<int> a {1, 2, 34, 23, 53, 2, 343, 2};
    Sparse_table table = Sparse_table(a);
    int l, r;
    cin >> l >> r;
    cout << table.get_min(l, r);
    return 0;
}