#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
#include <set>
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
const int N = 1e5 + 5, mod = 1e9 + 7;
array <int, N> s;

namespace Subtask1 {

set <int> isl;
	
void main(int n) {
	int ans = 0;
	for (int T = 0; T < 1 << n; T++) {
		int siz = 0, maxn = 0;
		isl.clear();
		for (int i = 1; i <= n; i++) {
			if (!(T & (1 << (i - 1)))) continue;
			maxn = max(s[i], maxn);
			isl.insert(s[i]);
			siz++;
		}
		ans += maxn - isl.size();
	}
	write(ans % mod), puts("");
}

}
void Mod(int &x) {
	if (x >= mod) x -= mod;
	if (x < 0) x += mod;	
}
int pow_(int x, int k, int p) {
	int ans = 1;
	while (k) {
		if (k & 1) ans = ans * x % p;
		x = x * x % p;
		k >>= 1;
	}
	return ans;
}
array <int, N> fac, inv;
void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = fac[i - 1] * i % mod;
	inv[n] = pow_(fac[n], mod - 2, mod);
	for (int i = n; i; i--)
		inv[i - 1] = inv[i] * i % mod;
}
int C(int n, int m) {
	if (n < m) return 0;
	return fac[n] * inv[m] % mod * inv[n - m] % mod;	
}
signed main() {
	freopen("monster.in", "r", stdin);
	freopen("monster.out", "w", stdout);
	int n = read();
	for (int i = 1; i <= n; i++)
		s[i] = read();
//	Subtask1::main(n);
	sort(s.begin() + 1, s.begin() + 1 + n);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans += s[i] * pow_(2, i - 1, mod) % mod;
		Mod(ans);
	}
	init(n);
	for (int i = 1; i <= n; i++) {
		int siz = 1;
		while (s[i + 1] == s[i]) siz++, i++;
		for (int j = 1; j <= siz; j++) {
			ans += C(siz, j) * pow_(-1, j, mod) % mod * pow_(2, n - j, mod) % mod;
			Mod(ans);
		}
	}
	write(ans), puts("");
	return 0;
}
