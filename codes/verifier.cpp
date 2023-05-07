#include <bits/stdc++.h>
#include <chrono>
using namespace std;

const char SYMBOLS[] = {'-', '|'};
vector<int> N;
vector<vector<int>> R;
vector<vector<char>> S;
int m, n, r;

/* Information to track */
vector<int> D, P;
chrono::steady_clock::time_point start, finish;

void initialize() {
    R.assign(m + 1, vector<int>(n + 1, 0));
    S.assign(m + 1, vector<char>(n + 1, 0));
    N.assign(r + 1, 0), D.assign(r + 1, 0), P.assign(r + 1, 0);
}

bool check_number_within_territory() {
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            if (S[i][j] == '-')
                D[R[i][j]]++;
            else
                P[R[i][j]]++;

    for (int i = 1; i <= r; i++)
        if (N[i] != -1 && D[i] != N[i] && P[i] != N[i])
            return false;

    return true;
}

bool check_three_consecutive_cells() {
    // Check for three vertically consecutive -'s
    for (int i = 1; i + 2 <= m; i++)
        for (int j = 1; j <= n; j++)
            if (S[i][j] == '-' && S[i+1][j] == '-' && S[i+2][j] == '-')
                return false;

    // Check for three horizontally consecutive |'s
    for (int i = 1; i <= m; i++)
        for (int j = 1; j + 2 <= n; j++)
            if (S[i][j] == '|' && S[i][j+1] == '|' && S[i][j+2] == '|')
                return false;
    return true;
}

int main() {
    cin >> m >> n >> r;

    initialize();

    for (int i = 1; i <= r; i++)
        cin >> N[i];

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> R[i][j];

    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> S[i][j];
    
    start = chrono::steady_clock::now();
    bool isValid = check_number_within_territory() && check_three_consecutive_cells();
    finish = chrono::steady_clock::now();

    cout << "Configuration is " << (isValid ? "" : "not ") << "a solution\n";

    long double timeTaken = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
    cout << "Time taken: "<< timeTaken/1000.0 << " microsecond(s)" << '\n';
}
