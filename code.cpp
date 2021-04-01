/*
++[---------->+<]>.-[------>+<]>-.++++++++.+++++.-[->+++++<]>-.-[--->++<]>--.+.[--->+<]>---.[->+++<]>++.++++++.-------.++++++.--[--->+<]>.-[->+++<]>-..+++++++++++++.[----->++<]>.------------.+[----->+<]>.--------.+++++++++++++.-------------.--[--->+<]>-.---[->++++<]>-.++++[->+++<]>.--[--->+<]>-.[->+++<]>++.-.+++.---.-[->+++<]>.-[--->++<]>+.++++.------.[--->+<]>---.+[----->+<]>.------------.+++++++.-------.--[--->+<]>---.+++[->+++<]>++..+++++++++.---------.-[->+++<]>.+[----->+<]>+.-------------.+++++++.+.----[->+++<]>-.
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long big;
#define pbb pair<big, big>
#define pii pair<int, int>
#define fe first
#define se second
#define maxheap priority_queue
#define uset unordered_set
#define umap unordered_map
#define fr(i, s, e) for(big i = s; i < e; i++)
#define revfr(i, s, e) for(big i = s - 1; i >= e; i--)
#define speed ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define debug(text) if(do_debug) {cout << text << endl;}
#define nl "\n"

const big mod = 1000000007;
const big infinity = 1000000000000000000;
bool do_debug = false;


template <typename T> ostream& operator<<(ostream& os, vector<T>& v) {
	
	for(auto element : v) {

		os << element << " ";
	}

	return os;
}

template <typename T, typename S> ostream& operator<<(ostream& os, pair<T, S>& p) {
	
	os << "(" << p.first << ", " << p.second << ")";
	return os;
}

template <typename T> ostream& operator<<(ostream& os, set<T>& v) {

	auto endit = v.end();
	endit--;

	os << "[";
	
	for(auto it = v.begin(); it != v.end(); it++) {

		os << *it;

		if(it != endit) {

			os << ", ";
		}
	}

	os << "]";

	return os;
}

template <typename T, typename S> ostream& operator<<(ostream& os, map<T, S>& v) {
	
	auto endit = v.end();
	endit--;

	os << "{";
	
	for(auto it = v.begin(); it != v.end(); it++) {

		os << "(" << (*it).first << " : " << (*it).second << ")";

		if(it != endit) {

			os << ", ";
		}
	}

	os << "}";

	return os;
}


struct node {

	bool active = false;
	int iq = 50;
	bool gene[10];
};


double purge(vector<node>& v, set<int>& available, set<int>& inactive, int final_population) {

	double retval = 0;
	maxheap<pii> heap; //<iq, index>
	inactive.clear();
	available.clear();
	vector<node> temp(final_population);

	fr(i, 0, final_population) {

		temp[i] = v[i];
		heap.push(make_pair(v[i].iq, i));
	}

	int pp = 0;

	v.clear();
	v = vector<node>(final_population);

	while(pp < (int)(0.25 * final_population)) {

		retval += heap.top().fe;
		v[pp] = temp[heap.top().se];
		available.insert(pp);
		heap.pop();
		pp++;
	}


	while(!heap.empty()) {

		available.erase(heap.top().se);
		inactive.insert(heap.top().se);
		v[heap.top().se].active = false;
		// retval -= heap.top().fe;
		heap.pop();
		inactive.insert(pp);
		pp++;
	}

	return retval / (final_population / 4);
}


void solve() {

	srand((unsigned) time(0));

	int initial_population = 250000;
	int final_population = 1000000;
	int current_population = 0;
	int purge_count = 1;

	double avg = 0;

	vector<node> v(final_population);
	set<int> available;
	set<int> inactive;

	fr(i, 0, initial_population) {

		v[i].active = true;

		fr(j, 0, 10) {

			int prob = (rand() % 2) + 1;

			if(prob == 1) {

				v[i].gene[j] = true;
				v[i].iq += 10;
			}
		}

		avg += v[i].iq;
		available.insert(i);
		current_population++;
	}

	avg /= initial_population;
	cout << "Initial global average IQ: " << avg << endl;


	fr(i, initial_population, final_population) {

		inactive.insert(i);
	}


	while(true) {

		// cout << available << endl << inactive << endl;

		int parent_1, parent_2;

		do {

			parent_1 = (rand() % current_population);

		} while(available.find(parent_1) == available.end());

		available.erase(parent_1);

		do {

			parent_2 = (rand() % current_population);

		} while(available.find(parent_2) == available.end());

		available.erase(parent_2);

		int n_children = (rand() % 3) + 1;

		while(n_children-- > 0) {

			bool child_gene[10] = {false};
			int pp = 0;
			int child_id = *(inactive.begin());
			int child_iq = 50;
			inactive.erase(child_id);

			while(pp < 5) {

				set<int> used;
				int gene_ID;

				do {

					gene_ID = (rand() % 10);

				} while(used.find(gene_ID) != used.end());

				used.insert(gene_ID);
				child_gene[pp] = v[parent_1].gene[gene_ID];

				if(child_gene[pp]) {

					child_iq += 10;
				}

				pp++;
			}

			while(pp < 10) {

				set<int> used;
				int gene_ID;

				do {

					gene_ID = (rand() % 10);

				} while(used.find(gene_ID) != used.end());

				used.insert(gene_ID);
				child_gene[pp] = v[parent_2].gene[gene_ID];

				if(child_gene[pp]) {

					child_iq += 10;
				}

				pp++;
			}


			fr(i, 0, 10) {

				v[child_id].gene[i] = child_gene[i];
			}

			v[child_id].iq = child_iq;
			v[child_id].active = true;
			available.insert(child_id);
			current_population++;

			// cout << parent_1 << " and " << parent_2 << " gave birth. Current world population is " << current_population << endl;

			if(current_population == final_population) {

				break;
			}
		}

		if(current_population == final_population) {

			avg = purge(v, available, inactive, final_population);
			current_population = final_population / 4;

			cout << "After purge # " << purge_count++ << ", average IQ is: " << avg << endl;
		}
	}
}


int main() {
	
	speed;

	int q = 1;
	// cin >> q;

	while(q-- > 0) {

		solve();
	}

	return 0;
}