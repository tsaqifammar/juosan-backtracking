#include <bits/stdc++.h>
using namespace std;

int m, n, r;
vector<int> N;
vector<vector<int>> R;
vector<vector<char>> S;

vector<int> D, P;

void initialize() {
    N.resize(r + 1);
    D.resize(r + 1);
    P.resize(r + 1);
    R.resize(m + 1, vector<int>(n + 1));
    S.resize(m + 1, vector<char>(n + 1));
}

bool verify() {
    fill(D.begin(), D.end(), 0);
    fill(P.begin(), P.end(), 0);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            (S[i][j] == '-') ? D[R[i][j]]++ : P[R[i][j]]++;
            if (i+2 <= m && S[i][j] == '-' && S[i+1][j] == '-' && S[i+2][j] == '-')
                return false;            
            if (j+2 <= n && S[i][j] == '|' && S[i][j+1] == '|' && S[i][j+2] == '|')
                return false;
        }
    }

    for (int i = 1; i <= r; i++)
        if (N[i] != -1 && D[i] != N[i] && P[i] != N[i])
            return false;

    return true;
}

void printSolution() {
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cout << S[i][j] << " \n"[j == n];
}

void solve() {
    int CELL_COUNT = m*n;
    long long CONFIGS_COUNT = (1ll << CELL_COUNT);
    assert(CONFIGS_COUNT >= 1);

    for (int bitmask = 0; bitmask < CONFIGS_COUNT; bitmask++) {
        // Generate config
        for (int num = 0; num < CELL_COUNT; num++) {
            int x = (num/m) + 1, y = (num%m) + 1;
            S[x][y] = (bitmask & (1ll << num)) ? '|' : '-';
        }

        // Verify config
        if (verify()) {
            printSolution();
            return;
        }
    }
    cout << "No solution\n";
}

int main() {
    cin >> m >> n >> r;

    initialize();

    for (int i = 1; i <= r; i++)
        cin >> N[i];
    
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> R[i][j];

    solve();
}
