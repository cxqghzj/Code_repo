#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define F(i,a,b) for(int i=a;i<=b;i++)
#define Debug(x) cerr<<"------------"<<x<<"---------------"<<endl;

const int N=2e5+5;

inline int read();

int T=1;

int n,m,a[N];
char c;
int l,r;

signed main(){
	//freopen(".in","r",stdin);
	/* freopen("data.in","w",stdout); */
	srand(time(0));
	while(T--){
		n=rand()%100+1;
		cout<<n<<endl;
		for(int i=1;i<=n;i++){
			int xxx;
			xxx=rand();
			if(xxx%2) xxx=1;
			else xxx=-1;
			cout<<xxx*rand()<<" ";
		}
		cout<<endl;
		m=rand()%10+1;
		cout << m << endl;
		for(int i=1;i<=m;i++){
			int opt = rand();
			if(opt%6==0){
				l=rand()%n+1;
				r=rand()%n+1;
				n++;
				cout<<"I"<<" "<<l<<" "<<r<<endl;
			}
			if(opt%6==1){
				l=rand()%n+1;
				n--;
				cout<<"D"<<" "<<l<<endl;
			}
			if(opt%6==2){
				int l=rand()%n+1,r=rand()%n+1;
				cout<<"R"<<" "<<l<<" "<<r<<endl;
			}
			if(opt%6==3||opt%6==5||opt%6==4){
				int l=rand()%n+1,r=rand()%n+1;
				if(l>r) swap(l,r);
				cout<<"Q"<<" "<<l<<" "<<r<<endl;
			}
		}
	}
	return 0;
}

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-') f*=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<3)+(x<<1)+(c^48);
		c=getchar();
	}
	return x*f;
}
