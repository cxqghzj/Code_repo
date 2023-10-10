#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
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
string read_() {
	string ans;
	char c = getchar();
	while (c < '0' || c > '1')
		c = getchar();
	while (c >= '0' && c <= '1') {
		ans += c;
		c = getchar();
	}
	return ans;
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
const int N = 1e7 + 5, M = 23;
array <int, N> p, vis;
int cnt;

void Euler(int n) {
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) {
			cnt++;
			p[cnt] = i;
		}
		for (int j = 1; i * p[j] <= n && j <= cnt; j++) {
			vis[i * p[j]] = 1;
			if (i % p[j] == 0) break;
		}
	}
}
array <string, M> mp;
array <int, N> isl;
signed main() {
	/* freopen("matrix.in", "r", stdin); */
	/* freopen("matrix.out", "w", stdout); */
	int n = read(), m = read();
	for (int i = 1; i <= n; i++)
		mp[i] = " " + read_();
	Euler(1e7);
	isl.fill(1);
	int ksl = 1;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (mp[j][i] == '0') continue;
			isl[i] *= p[j];
		}
	}
	for (int i = 0; i < (1 << n); i++) {
		int sum = 1;
		for (int j = 1; j <= n; j++) {
			if (i & (1 << (j - 1)))
				sum *= p[j];
		}
	}
	return 0;
}
