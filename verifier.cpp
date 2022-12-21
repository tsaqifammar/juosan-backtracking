#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
 
typedef vector<int> vi;
typedef vector<vi> vvi;

const char CHARS[] = {'-', '|'};

bool verify(int m, int n, int r, vvi& R, vi& N, vvi& S) {
    vector<array<int, 2>> cnt(r);
    vvi HV(m, vi(n)), VH(m, vi(n));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (S[i][j] == '-') {
                cnt[R[i][j]].fi += 1;
                if (i - 1 >= 0) VH[i][j] = VH[i - 1][j] + 1;
                else VH[i][j] = 1;
            } else {
                cnt[R[i][j]].se += 1;
                if (j - 1 >= 0) HV[i][j] = VH[i][j - 1] + 1;
                else HV[i][j] = 1;
            }
        }
    }

    for (int i = 0; i < r; i++)
        if (cnt[i].fi != N[i] && cnt[i].se != N[i])
            return false;
    
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (HV[i][j] >= 3 || VH[i][j] >= 3)
                return false;

    return true;
}

int main() {
    int m, n;
    cin >> m >> n;

    int r;
    cin >> r;

    vi N(r);
    for (int i = 0; i < r; i++)
        cin >> N[i];

    vvi R(m, vi(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> R[i][j];

    vvi S(m, vi(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> S[i][j];

    if (verify(m, n, r, R, N, S)) {
        cout << "Valid\n";
    } else {
        cout << "Invalid\n";
    }
}
