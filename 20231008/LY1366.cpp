#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
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
	while (c < 'a' || c > 'z')
		c = getchar();
	while (c >= 'a' && c <= 'z') {
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
const int N = 1.5e6 + 5, M = 28, inf = 0x7f7f7f7f;

array <array <int, M>, M> isl;
array <array <int, N>, M> cur;
array <int, M> dfn, idx;

array <int, N> f;
int main() {
	freopen("reinforce.in", "r", stdin);
	freopen("reinforce.out", "w", stdout);
	string s = read_();
	int n = s.size();
	s = " " + s;
	int tot = 0;
	for (int i = 1; i < n; i++)
		isl[s[i] - 'a'][s[i + 1] - 'a']++;
	for (int i = 1; i <= n; i++) {
		if (dfn[s[i] - 'a']) continue;
		tot++, dfn[s[i] - 'a'] = tot, idx[tot] = s[i] - 'a';
	}
	f.fill(inf);
	f[0] = 1;
	for (int T = 1; T < 1 << tot; T++) {
		for (int i = 1; i <= tot; i++) {
			if (~T & (1 << (i - 1))) continue;
			int sum = f[T ^ (1 << (i - 1))];
			for (int j = 1; j <= tot; j++) {
				if (~T & (1 << (j - 1))) continue;
				sum += isl[idx[i]][idx[j]];
			}
			f[T] = min(f[T], sum);
		}
	}
	write(f[(1 << tot) - 1]), puts("");
	return 0;
}
