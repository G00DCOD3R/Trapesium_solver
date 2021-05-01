#define pb push_back
#define mp make_pair
#define fi first
#define se second 
#define all(...) begin(__VA_ARGS__) , end(__VA_ARGS__)
#define boost {ios_base::sync_with_stdio(false); cin.tie(); cout.tie();}


#include <bits/stdc++.h>
using namespace std;
#define random_shuffle(...) shuffle(__VA_ARGS__, rng)
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); // quick randomization 


typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef vector <int> vi;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
constexpr ll nax = 2e5+6969, inf = 2e9+6969;

inline int random(const int & a, const int &b) 
{
	return uniform_int_distribution<int>(a,b)(rng);
}

ll Factorial[20],dFactorial[30];
vi chances {6904, 14165, 19659, 20757, 22197, 23036, 29251, 35953};
inline ll Pow(ll a, const ll & b) 
{
	ll B = abs(b);
	int roots = random(0,3);
	while(roots && ((B&1) == 0))
	{
		B >>= 1;
		roots--;
	}
	ll w = 1;
	while(B) 
	{
		if(B&1) 
		{
			w = w * a;
			if(w > inf) return -1;
		}
		a = a * a;
		if(a > inf) return -1;
		B >>= 1;
	}
	return w;
}
inline ll C(const ll & n, const ll & k) 
{
	ll w = 1;
	for(ll i=n-k+1;i<=n;i++) 
	{
		w = w * i;
		if(w > inf) return -1;
	}
	if(k <= 15) w /= Factorial[k];
	for(ll i=2;i<=k;i++) w /= i;
	return w;
}

ll conv(const vector<PLL> & v) 
{
	stack <ll> s;
	for(auto e: v) 
	{
		//  cout << e.fi << " " << e.se << "\n";
		if(e.fi == 0) s.push(e.se);
		else if(e.fi == 2)
		{
			ll a = s.top();
			s.pop();
			ll b = s.top(), w = 0;
			s.pop();
			switch(e.se) 
			{
				case 0: 
					w = a + b;
				break;
				case 1: 
					w = a * b;
				break;
				case 2: 
					w = b - a;
				break;
				case 3: 
					if(a == 0) return -1;
					w = b / a;
					if(w * a != b) return -1;
				break;
				case 4: 
					if(a > 30) return -1;
					w = Pow(b, a);
					if(w == -1) return -1;
				break;
				case 5: 
					ll B = abs(b);
					ll A = abs(a);
					if(B < A) swap(A,B);
					if(abs(B - A) > 15) return -1;
					if(B <= 12) w = Factorial[B] / Factorial[A] / Factorial[B-A];
					else w = C(B, min(B,B-A));
					if(w == -1) return -1;
				break;
			}
			s.push(w);
			if(abs(w) > inf) return -1;
		}
		else
		{
			ll a = s.top(), w = 0;
			s.pop();
			switch (e.se)
			{
				case 0: 
					if(abs(a) > 12) return -1;
					w = Factorial[abs(a)];
					if(w == -1) return -1;
				break;
				case 1: 
					if(abs(a) > 21) return -1;
					w = dFactorial[abs(a)];
				break;
			}
			s.push(w);
			if(abs(w) > inf) return -1;
		}
	}
	ll ans = s.top();
	return ans;
}
void show(const vector <PLL> & v) 
{
	for(auto e: v) 
	{
		if(e.fi == 0) cout << e.se << " ";
		else if(e.fi == 2) 
		{
			switch(e.se)
			{
			case 0: 
				cout << "+ ";
			break;
			case 1: 
				cout << "* ";
			break;
			case 2: 
				cout << "- ";
			break;
			case 3: 
				cout << "/ ";
			break;
			case 4: 
				cout << "^ ";
			break;
			case 5: 
				cout << "C ";
			break;
			}
		}
		else 
		{
			if(e.se == 0) cout << "! ";
			else if(e.se == 1) cout << "!! ";
		}
	}
	puts("");
}

vector <ll> nums;

vector <PLL> get_random() 
{
	random_shuffle(all(nums));
	int pos = 0, balance = 0;
	int can_fact = random(0, 4);
	vector <PLL> ans;
	while(pos < nums.size())
	{
		int choice = 0;
		if(balance == 0) 
		{
			balance = 1;
			ans.pb(mp(0, nums[pos]));
			pos++;
		}
		else if(balance == 1)
		{
			choice = random(0,1);
			if(choice == 0 || can_fact == 0) 
			{
				ans.pb(mp(0, nums[pos]));
				pos++;
				balance++;
			}
			else
			{
				can_fact--;
				ans.pb(mp(1, random(0,1)));
			}
		}
		else
		{
			choice = random(0, 2);
			int bad = 0;
			if(ans.end()[-1].fi == 1) bad = random(0, 3);
			if((can_fact == 0 && choice == 1) || (bad)) choice = random(0,1) * 2;
			if(choice == 0) 
			{
				ans.pb(mp(0, nums[pos]));
				pos++;
				balance++;
			}
			else 
			{
				if(can_fact == 0 || (bad)) choice = random(1, 23036);
				else choice = random(1, 35953);
				int who = 1;
				for(int j=0;j<8;j++) if(chances[j] >= choice) 
				{
					who = j;
					break;
				}
				if(who < 6)
				{
					ans.pb(mp(2, who));
					balance--;
				}
				else ans.pb(mp(1, who - 6));
			}
		}
	}
	//  cout << "bal: " << balance << "\n";
	can_fact = min(can_fact, 2);
	while(balance > 1) 
	{
		int choice;
		if(can_fact == 0) choice = random(1, 23036);
		else choice = random(1, 35953);
		int who = 1;
		for(int j=0;j<8;j++) if(chances[j] >= choice) 
		{
			who = j;
			break;
		}
		if(who < 6)
		{
			ans.pb(mp(2, who));
			balance--;
		}
		else ans.pb(mp(1, who - 6));
	}
	return ans;
}

vector <PLL> try_minor(const vector <PLL> & v) 
{
	int can_fact = random(0, 3);
	vector <PLL> nw;
	vector <ll> order;
	for(auto e: v) 
	{
		int add_fact = random(0,2);
		if(e.fi == 2) 
		{
			int choice = random(0,3);
			if(choice == 0) 
			{
				nw.pb(e);
				continue;
			}
			if(e.se == 0) 
			{
				int choice = random(0, 6);
				if(choice == 0) nw.pb(mp(2,1));
				else nw.pb(mp(2,2));
			}
			else if(e.se == 2) nw.pb(mp(2,0));
			else nw.pb(e);
		}
		else if(e.fi == 0 && can_fact > 0 && add_fact != 0) 
		{
			can_fact--;
			nw.pb(e);
			order.pb(e.se);
			nw.pb(mp(1,random(0,1)));
		}
		else
		{
			int choice = random(0,1);
			if(e.fi == 0) order.pb(e.se);
			if(e.fi == 1 && choice) continue;
			nw.pb(e);
		}
	}
	int N = order.size();
	for(int i=0;i<N-1;i++) 
	{
		int choice = random(i, N-1);
		if(abs(order[i] - order[choice]) <= random(0,4)) swap(order[i], order[choice]);
	}
	int cnt = 0;
	for(auto & e: nw) if(e.fi == 0) 
	{
		e.se = order[cnt];
		cnt++;
	}
	return nw;
}

ll best = 0;

int main(int argc, char * argv[])
{
	srand(chrono::steady_clock::now().time_since_epoch().count());
	int my_id = atoi(argv[1]);
	string space;
	for(int i=0;i<5*my_id;i++) space += "	 ";
	
	Factorial[0] = 1;
	for(ll i = 1; i <= 15; i++) Factorial[i] = Factorial[i-1] * i;
	dFactorial[0] = dFactorial[1] = 1;
	for(ll i = 2; i <= 21; i++) dFactorial[i] = dFactorial[i-2] * i;
	
	
	int n;
	ll target;
	cin >> n;
	nums.resize(n);
	for(auto &e: nums) cin >> e;
	cin >> target;
	
	//  some debugging stuff:
	
	//  vector <PLL> v{};
	//  show(v);
	//  ll ans = conv(v);
	//  cout << ans << "\n";
	//  return 0;
	
	vector <PLL> Ans;
	
	for(int i=0;i<1000;i++) 
	{
		vector <PLL> tmp;
		tmp = get_random();
		ll cur = conv(tmp);
		if(abs(cur - target) < abs(target - best)) 
		{
			best = cur;
			Ans = tmp;
		}
	}
	
	int reps = 1'000'000;
	int cnt = 1;
	int last_change = 0;
	for(int i=0;;i++) 
	{
		vector <PLL> tmp;
		tmp = get_random();
		ll cur = conv(tmp);
		if(i % 1000000 == 0) cerr << space << "progress: " <<  i / 1000000 << " (" << abs(target - best) << ")\n";
		
		bool succes_impr = false;
		
		if(abs(cur - target) < target / 20) 
		{
			//  cerr << space << "try to improve\n";
			ll old_cur = cur;
			vector <PLL> old_tmp = tmp;
			for(int j=0;j<100000;j++) 
			{
				tmp = try_minor(old_tmp);
				cur = conv(tmp);
				if(abs(cur - target) < abs(target - old_cur))
				{
					old_cur = cur;
					old_tmp = tmp;
				}
			}
			cur = old_cur;
			tmp = old_tmp;
			succes_impr = true;
		}
		if(abs(cur - target) < abs(target - best)) 
		{
			//  if(succes_impr) cerr << space << "successfull improv.\n";
			//  cout << cur << "\n";
			ll old_best = best;
			Ans = tmp;
			best = cur;
			for(int j=0;j<1000000;j++) 
			{
				tmp = try_minor(Ans);
				cur = conv(tmp);
				if(abs(cur - target) < abs(target - best))
				{
					Ans = tmp;
					best = cur;
					j = 0;
				}
			}
			
			cur = best;
			ll delta = abs(cur - target);
			cerr << space << old_best << " -> " << cur << " (+" <<  abs(target - old_best) - abs(cur - target) << ", delta=" << delta << ")\n";
			
			string file = "sol" + to_string(my_id) + ".out"; // if you want to compute all the answers
			//  string file = "sol.out"; // if you want only the best
			freopen(file.c_str(),"w",stdout);
			puts("all done, best result so far: ");
			show(Ans);
			printf("which is: %lld\n", best);
			//  cnt++;
			if(best == target) break;
			last_change = 0;
		}
		last_change++;
		
	}
	cerr << space << "FINAL ANSWER =  " << best << "\n";
	return 0;
}
