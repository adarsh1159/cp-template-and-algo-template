// ***** OREWA MONKEY D LUFFY *****
// ***** ORE WA *****
// ***** KAIZOKU-? *****
// *****  NI  *****
// *****  NARU!  *****

#include <bits/stdc++.h>
using namespace std;
#define op() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

// ---------------------------- TYPEDEFS ----------------------------
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpi;
typedef vector<pll> vpl;

// ---------------------------- CONSTANTS ----------------------------
const ll MOD = 1e9 + 7;
const ll INF = 1e18;
const ld EPS = 1e-9;

// ---------------------------- MACROS ----------------------------
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

#define yes cout << "YES\n"
#define no cout << "NO\n"
#define endl '\n'

// ? For loops
#define loop(i, n) for (auto i = 0; i < (n); i++)
#define rloop(i, n) for (auto i = (n) - 1; i >= 0; i--)
#define each(x, a) for (auto &x : a)         // for(auto &x : v)
#define reeach(x, a) for (auto it = a.rbegin(); it != a.rend(); ++it) // reverse
#define test int t; cin >> t; while (t--) solve();

// ---------------------------- PRINT HELPERS ----------------------------
template <typename Container>
void print(const Container &c) {
    for (auto &x : c) cout << x << ' ';
    cout << '\n';
}

// ---------------------------- MATH UTILITIES ----------------------------
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

bool isEven(ll n) { return !(n & 1); }
bool isOdd(ll n)  { return (n & 1); }

bool isPrime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

// ---------------------------- MODULAR ARITHMETIC ----------------------------
ll modAdd(ll a, ll b, ll m = MOD) { return ((a % m + b % m) % m + m) % m; }
ll modSub(ll a, ll b, ll m = MOD) { return ((a % m - b % m) % m + m) % m; }
ll modMul(ll a, ll b, ll m = MOD) { return ((a % m) * (b % m)) % m; }

ll modPow(ll a, ll b, ll m = MOD) {
    ll res = 1; a %= m;
    while (b > 0) {
        if (b & 1) res = modMul(res, a, m);
        a = modMul(a, a, m);
        b >>= 1;
    }
    return res;
}
ll modInv(ll a, ll m = MOD) { return modPow(a, m - 2, m); }

// ---------------------------- DEBUG (Optional) ----------------------------
// #define debug(x) cerr << #x << " = " << x << endl;
// #define debugv(v) cerr << #v << " = "; for (auto &x : v) cerr << x << " "; cerr << endl;

// ---------------------------- SOLVE FUNCTION ----------------------------
void solve() {
    //ll n; cin >> n;
    //vl a(n);
   // each(x, a) cin >> x;
   // string s;
   // cin>>s;

   
}

// ---------------------------- MAIN ----------------------------
int main() {
    op();
    test;
    // solve(); // Uncomment for single test case
    return 0;
}