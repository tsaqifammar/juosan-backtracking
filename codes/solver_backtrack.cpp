#include <bits/stdc++.h>
#include <chrono>
using namespace std;

const char SYMBOLS[] = {'-', '|'};
const int MAX_M = 45, MAX_N = 45, MAX_R = MAX_M*MAX_N;
int R[MAX_M + 1][MAX_N + 1], N[MAX_R + 1], sz[MAX_R + 1];
int m, n, r;

/* Information to track */
int HV[MAX_M + 1][MAX_N + 1];
int VH[MAX_M + 1][MAX_N + 1];
int HH[MAX_M + 1][MAX_N + 1];
int D[MAX_R + 1], P[MAX_R + 1];
char current[MAX_M + 1][MAX_N + 1];
chrono::steady_clock::time_point start, finish;

void initialize() {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            current[i][j] = '.';
            HV[i][j] = VH[i][j] = HH[i][j] = 0;
        }
    }
    for (int i = 1; i <= r; i++)
        D[i] = P[i] = 0;
}

pair<int,int> getNextCell(int i, int j) {
    return (j + 1 <= n ? make_pair(i, j + 1) : make_pair(i + 1, 1));
}

void fill(int i, int j, char symbol) {
    current[i][j] = symbol;
    if (symbol == '-') {
        VH[i][j] = VH[i - 1][j] + 1;
        HH[i][j] = HH[i][j - 1] + 1;
        D[R[i][j]]++;
    } else {
        HV[i][j] = HV[i][j - 1] + 1;
        P[R[i][j]]++;
    }
}

void unfill(int i, int j) {
    assert(current[i][j] == '-' || current[i][j] == '|');
    if (current[i][j] == '-') {
        VH[i][j] = HH[i][j] = 0;
        D[R[i][j]]--;
    } else {
        HV[i][j] = 0;
        P[R[i][j]]--;
    }
    current[i][j] = '.';
}

bool mustBacktrack(int i, int j) {
    bool condA = HV[i][j] == 3;
    bool condB = VH[i][j] == 3;
    bool condC = (HH[i][j] >= 3) && (HH[i - 1][j] >= 3);
    if (condA || condB || condC) return true;
    if (N[R[i][j]] != -1) {
        int E = sz[R[i][j]] - (D[R[i][j]] + P[R[i][j]]);
        int rem = sz[R[i][j]] - max(D[R[i][j]], P[R[i][j]]);
        bool condD = min(D[R[i][j]], P[R[i][j]]) > N[R[i][j]];
        bool condE = E + max(D[R[i][j]], P[R[i][j]]) < N[R[i][j]];
        bool condF = (max(D[R[i][j]], P[R[i][j]]) > N[R[i][j]]) && (rem < N[R[i][j]]);
        if (condD || condE || condF) return true;
    }
    return false;
}

void printSolution() {
    cout << "===================\n";
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cout << current[i][j] << " \n"[j == n];
    cout << "Time taken: "<< chrono::duration_cast<chrono::milliseconds>(finish - start).count() << " ms" << '\n';
}

void search(int i, int j) {
    if (i <= m) {
        for (char symbol : SYMBOLS) {
            fill(i, j, symbol);
            if (!mustBacktrack(i, j)) {
                pair<int,int> nextCell = getNextCell(i, j);
                search(nextCell.first, nextCell.second);
            }
            unfill(i, j);
        }
    } else {
        finish = chrono::steady_clock::now();
        printSolution();
        exit(0);
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> m >> n >> r;

    for (int i = 1; i <= r; i++)
        cin >> N[i];
    
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> R[i][j], sz[R[i][j]]++;

    initialize();

    start = chrono::steady_clock::now();
    search(1, 1);
}
