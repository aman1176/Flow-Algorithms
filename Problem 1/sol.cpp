/*
AUTHOR: Aman Raj
College:IIT JODHPUR
Branch:CSE
LANG: C++
*/

using namespace std;

typedef     int ll;
#include <bits/stdc++.h>


//setbase - cout << setbase (16); cout << 100 << endl; Prints 64
//setfill -   cout << setfill ('x') << setw (5); cout << 77 << endl; prints xxx77
//setprecision - cout << setprecision (14) << f << endl; Prints x.xxxx
//cout.precision(x)  cout<<fixed<<val;  // prints x digits after decimal in val
#define fast  ios_base::sync_with_stdio(false); cin.tie(0);  cout.tie(0);
#define all(a) a.begin(),a.end()
//#define mod 998244353





#define inf 1e18
//#define mod 3
#define flush fflush(stdout)

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef cc_hash_table<ll, ll, hash< ll > > ht;

// find_by_order()  // order_of_key
typedef tree<
    pair<ll,ll>,
    null_type,
    less<pair<ll,ll> >,
    rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_set;




ll mod=1e9+7;

ll power1(ll a, ll b)//a raised to power b
   {  if(b<=0) return 1; if(b==1) return a;
       ll c=power1(a,b/2);
        c*=c;c%=mod;if(b%2==1) c*=a;c%=mod;
        return c;
   }
   ll mi(ll a)
   { ll c= power1(a,mod-2);

     return c;
   }



 struct less_then_greater {
    template<typename T, typename U>
    bool operator()(T const& lhs, U const& rhs) const {
        if (lhs.first < rhs.first) return true;
        if (rhs.first < lhs.first) return false;
        return lhs.second > rhs.second;
    }
};

 /*std::priority_queue<std::pair<int, int>,
                    std::vector<std::pair<int, int>>,
                    less_then_greater
                    > pq;*/
ll gcd(ll a,ll b)
{
    if(b==0)return a;
    return gcd(b,a%b);
}
//cout<<"Case #"<<tt<<": "<<ans<<endl;

void self_min(ll &a,ll b)
{
    a=min(a,b);
}



//long double c=1.618033988749894848207210029666924810953787527978420257568359375;
ll n;
vector<vector<ll > > v;
vector<vector<int>> capacity;


int bfs(int s, int t, vector<int>& parent) {

    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, 1e9});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : v[cur]) {
            if (parent[next] == -1 && capacity[cur][next]>0) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                //cout<<new_flow<<endl;
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        //cout<<new_flow<<endl;
            if(new_flow==0)break;
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}
int main()
{  fast;
   //ofstream cout("output.txt");
  ll h,w,N;cin>>h>>w>>N;
  vector<pair<ll,ll> > vr(N),vc(N);
  for(ll i=0;i<N;i++)
  {
      ll a,b,c,d;cin>>a>>b>>c>>d;a--;b--;c--;d--;
      vr[i]={a,c};vc[i]={b,d};
  }
  //source is 0
  //sink is N-1
  // we have 1 2 3 4 5 6
  n=1+1+h+w+N+N;
  ll s2=1,e2=h,s3=h+1,e3=h+N,s4=h+N+1,e4=h+N+N,s5=h+2*N+1,e5=h+2*N+w,s6=n-1;
  // cout<<s2<<" "<<s3<<" "<<s4<<" "<<e4<<endl;
   v.resize(n);
   capacity.resize(n,vector<int> (n,0) );
   for(ll i=s2;i<=e2;i++){v[0].push_back(i);v[i].push_back(0);capacity[0][i]=1; }
   for(ll i=s5;i<=e5;i++){v[i].push_back(n-1);v[n-1].push_back(i);capacity[i][n-1]=1;  }
   //now from row to all n
  // 3 and 4
  for(ll i=0;i<N;i++)
  {
      v[s3+i].push_back(s4+i);
      v[s4+i].push_back(s3+i);
      capacity[s3+i][s4+i]=1;
  }
   for(ll i=0;i<N;i++)
   {

       ll r1=vr[i].first,c1=vc[i].first,r2=vr[i].second,c2=vc[i].second;

       for(ll j=s2+r1;j<=s2+r2;j++)
       {
        v[j].push_back(s3+i);v[s3+i].push_back(j);capacity[j][s3+i]=1;
       }
       for(ll j=s5+c1;j<=s5+c2;j++)
       {
           v[i+s4].push_back(j);v[j].push_back(i+s4);capacity[i+s4][j]=1;
       }
   }
//   cout<<n<<endl;
//   for(int i=0;i<n;i++)
//   {  cout<<i<<"-> ";
//       for(auto x:v[i])cout<<x<<" ";cout<<endl;
//   }
//  for(ll i=0;i<n;i++)
//  {
//      for(ll j=0;j<n;j++)cout<<capacity[i][j];cout<<endl;
//  }
   cout<<maxflow(0,n-1);
    return 0;
}


