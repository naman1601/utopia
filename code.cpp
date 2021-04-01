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

int initial_population = 250000;
int final_population = 1000000;
int save_ratio = 99;
const int num_genes = 25;
float gene_contribution = 4;


struct node {

	bool active = false;
	float iq = 50;
	bool gene[num_genes];
};


double purge(vector<node>& v, set<int>& available, set<int>& inactive) {

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

	while(pp < (int)(0.01 * save_ratio * final_population)) {

		retval += heap.top().fe;
		v[pp] = temp[heap.top().se];
		available.insert(pp);
		heap.pop();
		pp++;
	}


	while(!heap.empty()) {

		// available.erase(heap.top().se);
		// inactive.insert(heap.top().se);
		// v[heap.top().se].active = false;
		// retval -= heap.top().fe;
		heap.pop();
		inactive.insert(pp);
		pp++;
	}

	return retval / (0.01 * save_ratio * final_population);
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

		fr(j, 0, num_genes) {

			int prob = (rand() % 2) + 1;

			if(prob == 1) {

				v[i].gene[j] = true;
				v[i].iq += gene_contribution;
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

			bool child_gene[num_genes] = {false};
			int pp = 0;
			int child_id = *(inactive.begin());
			float child_iq = 50;
			inactive.erase(child_id);

			while(pp < num_genes) {

				// set<int> used;
				// int gene_ID;

				if(v[parent_1].gene[pp] && v[parent_2].gene[pp]) {

					child_gene[pp] = true;
					child_iq += gene_contribution;

				} else if(v[parent_1].gene[pp] || v[parent_2].gene[pp]) {

					int prob = (rand() % 100) + 1;

					if(prob <= 50) {

						child_gene[pp] = true;
						child_iq += gene_contribution;
					}
				}

				pp++;
			}


			fr(i, 0, num_genes) {

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

			avg = purge(v, available, inactive);
			current_population = 0.01 * save_ratio * final_population;

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