/* #define debug */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <vector>
using namespace std;
#ifdef ONLINE_JUDGE

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1++)
char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf;

#endif
int read() {
	int p = 0, flg = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') flg = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		p = p * 10 + c - '0';
		c = getchar();
	}
	return p * flg;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}
const int N = 1e5 + 5;
array <int, N> s;
namespace subtask1 {

vector <vector <int> > f(1005, vector <int>(1005, 0));
int net(int l, int r) {
	if (l < r) return l + 1;
	else return l - 1;
}
int cnt;
bool dfs(int l, int r, int minn, int maxn) {
	cnt++;
	if (l == r) {
		f[l][r] = true;
		return true;
	}
	if (~f[l][r]) return f[l][r];
	f[l][r] = 0;
	minn = min(minn, s[l]);
	maxn = max(maxn, s[l]);
	if (abs(minn - s[net(l, r)]) <= 1 ||
		abs(maxn - s[net(l, r)]) <= 1)
		f[l][r] |= dfs(net(l, r), r, minn, maxn);
	if (abs(minn - s[r]) <= 1 ||
		abs(maxn - s[r]) <= 1)
		f[l][r] |= dfs(r, net(l, r), minn, maxn);
	return f[l][r];
}
void solve(int n) {
	f.clear();
	f.resize(1005, vector <int> (1005, -1));
	if (dfs(1, n, n + 1, 0) || dfs(n, 1, n + 1, 0)) puts("yes");
	else puts("no");
}

}
void solve() {
	int n = read();
	for (int i = 1; i <= n; i++)
		s[i] = read();
	subtask1::solve(n);
}
int main() {
	/* freopen("cookieann.in", "r", stdin); */
	/* freopen("cookieann.out", "w", stdout); */
	int T = read();
	while (T--) solve();
	return 0;
}
