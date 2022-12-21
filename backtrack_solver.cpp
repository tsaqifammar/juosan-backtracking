#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
 
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<vc> vvc;
#define fi first
#define se second

const char CHARS[] = {'-', '|'};

int main() {
    HANDLE hConsole; hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // for region coloring
    int m, n, r;
    cin >> m >> n >> r;

    vi N(r + 1);
    for (int i = 1; i <= r; i++)
        cin >> N[i];
    
    vvi R(m + 1, vi(n + 1));
    vi sz(r + 1);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            cin >> R[i][j],
            sz[R[i][j]]++;
    
    function<pii(int, int)> nextCell = [&](int i, int j) -> pii {
        if (j + 1 <= n) return make_pair(i, j + 1);
        return make_pair(i + 1, 1);
    };

    /* TO TRACK */
    vvi HV(m + 1, vi(n + 1)), VH = HV, HH = HV;
    vi count0(r + 1), count1(r + 1);

    vvc current(m + 1, vc(n + 1, '.'));

    auto print = [&]() { std::cout << "===================\n"; for (int i = 1; i <= m; i++) { for (int j = 1; j <= n; j++) { SetConsoleTextAttribute(hConsole, (R[i][j]) % 16 + 1); std::cout << current[i][j] << " \n"[j == n]; } } };
    auto check = [&]() -> bool { for (int i = 1; i <= r; i++) if (N[i] != -1 && count0[i] != N[i] && count1[i] != N[i]) return false; return true; };

    auto mark = [&](int i, int j, char c) {
        current[i][j] = c;
        if (c == '-') {
            VH[i][j] = VH[i - 1][j] + 1;
            HH[i][j] = HH[i][j - 1] + 1;
            count0[R[i][j]]++;
        } else {
            HV[i][j] = HV[i][j - 1] + 1;
            count1[R[i][j]]++;
        }
    };

    auto unmark = [&](int i, int j, char c){
        current[i][j] = '.';
        VH[i][j] = HH[i][j] = HV[i][j] = 0;
        if (c == '-')
            count0[R[i][j]]--;
        else 
            count1[R[i][j]]--;
    };

    auto doBacktrack = [&](int i, int j) {
        if (HV[i][j] == 3) return true;
        if (VH[i][j] == 3) return true;
        if (HH[i][j] >= 3 && HH[i - 1][j] >= 3) return true;
        if (N[R[i][j]] == -1) return false;
        int E = sz[R[i][j]] - (count0[R[i][j]] + count1[R[i][j]]);
        if (E + max(count0[R[i][j]], count1[R[i][j]]) < N[R[i][j]]) return true;

        int sisa = sz[R[i][j]] - max(count0[R[i][j]], count1[R[i][j]]);
        if (max(count0[R[i][j]], count1[R[i][j]]) > N[R[i][j]] && sisa < N[R[i][j]]) return true;
        
        if (min(count0[R[i][j]], count1[R[i][j]]) > N[R[i][j]]) return true;
        return false;
    };
    
    int cnt = 0;
    function<void(int,int)> search = [&](int i, int j) {
        if (i > m) {
            // in theory, every cells should be filled by this point
            cnt++;
            print();
        } else {
            for (char c : CHARS) {
                mark(i, j, c);
                if (!doBacktrack(i, j)) {
                    pii nxt = nextCell(i, j);
                    search(nxt.fi, nxt.se);
                }
                unmark(i, j, c);
            }
        }
    };

    search(1, 1);
    cout << "Number of solutions found: " << cnt << '\n';
}
 