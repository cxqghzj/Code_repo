#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <vector>
#include <bitset>
#include <map>
#define int long long
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

const int N = 5005, mod = 1e9 + 7;
array <vector <int>, N> isl;
vector <int> tp, prl;
array <array <int, N>, N> f;

array <int, N> s, idx;
void Mod(int &x) {
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;
}
namespace Subtask1 {

map <string, bool> mp;
void main(int n) {
	for (int i = 1; i <= n; i++)
		s[i] = read();
	int ans = 0;
	for (int T = 0; T < 1 << n; T++) {
		string now = "";
		int sum = 1;
		for (int i = 1; i <= n; i++) {
			if (T & (1 << (i - 1))) {
				now += (char)(s[i] + '0');
			}
			else
				sum = sum * 2 % mod;
		}
		if (mp[now]) continue;
		mp[now] = 1;
		ans += sum, Mod(ans);
	}
	write(ans), puts("");
}

}
signed main() {
	freopen("nest.in", "r", stdin);
	freopen("nest.out", "w", stdout);
	int n = read();
	if (n <= 20) return Subtask1::main(n), 0;
	for (int i = 1; i <= n; i++)
		s[i] = read();
	for (int i = 0; i <= n; i++) {
		bitset <N> vis;
		for (int j = i + 1; j <= n; j++) {
			if (vis[s[j]]) continue;
			vis[s[j]] = 1, isl[i].push_back(j);
		}
	}
	idx[0] = 1;
	for (int i = 1; i <= n; i++)
		idx[i] = idx[i - 1] * 2 % mod;
	tp.push_back(0);
	f[0][0] = 1;
	int ans = 0;
	for (int i = 0; i <= n; i++) {
		bitset <N> vis;
		int sum = 0;
		prl.clear();
		for (auto x : tp) {
			for (auto y : isl[x]) {
				f[i + 1][y] += f[i][x];
				if (vis[y]) continue;
				vis[y] = 1, prl.push_back(y);
			}
		}
		for (int j = 0; j <= n; j++)
			sum += f[i][j], Mod(sum);
		write(sum), puts("");
		ans += sum * idx[n - i] % mod;
		Mod(ans);
		tp = prl;
	}
	write(ans), puts("");
	return 0;
}
