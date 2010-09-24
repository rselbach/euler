#include <cstdlib>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <deque>
#include <limits>
#include <iomanip>
#include <vector>

using namespace std;

#define INFINITE 1000000

class place
{
public:
	const string name;
	double probability;
	bool visited;
	unsigned int distance;    // distance from source in optimal path
	place *previous; // prev node in optimal path
	place(const string n, double prob)
		:name(n),probability(prob),visited(false),
		 distance(INFINITE), previous(0) {};
	list<pair<place*,unsigned int> > neighbors;

	// we'll keep distances from other places
	map<place*,unsigned int> distances;

	unsigned int get_distance(place *);

	void relax(place* hop, unsigned int  weight);	
};

// xunxex
place *xunxex;

class home
{
private:
	double best_ev;
	void read_file(const string);
	place* extract_min(list<place*> *l);
	void init_distances() {
		for (list<place*>::iterator i = places.begin(); i != places.end(); i++)
			for (list<place*>::iterator j = places.begin(); j != places.end(); j++)
				if (*i == *j)
					(*i)->distances[*j] = 0;
				else
					(*i)->distances[*j] = INFINITE;
	}
	void calculate_expected_value(place *cur_place, double weight_sum, double exp_value, double remain_prob);
	bool is_connected();
protected:
	place *source_place;
	list<place*> places;
	void find_shortest_path();

	map<const string,place*> places_map;
public:
	void add_place(const string name, double prob) {
#ifdef DEBUG
		cout << "Adding place " << name << " (" << prob << ")" << endl;
#endif
		place *p = new place(name, prob);
		places.push_back(p);
		places_map.insert(pair<const string, place*>(name, p));
		if (source_place == NULL) 
			source_place = p;
		
	}
	void connect(const string p1, const string p2, unsigned int dist) {
#ifdef DEBUG
		cout << "Connecting " << p1 << " with " << p2 << endl;
#endif
		place *one = places_map.find(p1)->second;
		place *two = places_map.find(p2)->second;
		one->neighbors.push_back(pair<place*,unsigned int>(two,dist));
		two->neighbors.push_back(pair<place*,unsigned int>(one,dist));
		one->distances[two] = dist;
		two->distances[one] = dist;
		
	}


	double get_expected_value();

	void build(const string filename) {
		read_file(filename);
	}
	home(const string filename)
		: source_place(0), best_ev(INFINITE) {
		build(filename);
	}

	~home() {

		for (list<place*>::iterator i = places.begin() ; i != places.end(); i++ ) 
			delete *i;
		places.clear();

	}
};

void place::relax(place* hop, unsigned int weight)
{
	if ((distance == INFINITE) || (distance > (hop->distance + weight))) {
		distance = hop->distance + weight;
		previous = hop;
	}
}

place* home::extract_min(list<place*> *l)
{
	place *min = l->front();
	l->pop_front();
	return min;
}

bool sort_by_near(place *p1, place *p2)
{
	return (xunxex->distances[p1] < xunxex->distances[p2]);
}

void home::calculate_expected_value(place *cur_place, double weight_sum, double exp_value, double remain_prob) {
	cur_place->visited = true;
	exp_value += cur_place->probability * weight_sum;

	remain_prob -= cur_place->probability;
       	double remain_score = weight_sum * remain_prob;
	bool at_end = true;

	for(list<place*>::iterator i = places.begin(); (exp_value < best_ev) && (i != places.end()); i++) {
		if(!(*i)->visited) {
			at_end = false;
			
        		if (exp_value + remain_score < best_ev) { 
				calculate_expected_value((*i), weight_sum + cur_place->distances[*i], exp_value, remain_prob);
			} else break;
		}
	}
 
	if(at_end) {
		if(exp_value < best_ev) {
			best_ev = exp_value;
		}
	}
 
	cur_place->visited = false;
}

bool home::is_connected()
{
	for(list<place*>::iterator i = places.begin(); i != places.end(); i++)
		for(list<place*>::iterator j = i; j != places.end(); j++)
			if((*i)->distances[*j] == INFINITE) {
				best_ev = -1;
				return false;
			}
	return true;
}

void home::find_shortest_path()
{
#ifdef DEBUG
        for (list<place*>::iterator i = places.begin(); i != places.end(); i++)
                for (list<place*>::iterator j = places.begin(); j != places.end(); j++) {
                        cout << (*i)->name << " <--> " << (*j)->name << " : " << (*i)->distances[*j] << endl;
                }
#endif
	for (list<place*>::iterator k = places.begin(); k != places.end(); k++)
		for (list<place*>::iterator i = places.begin(); i != places.end(); i++)
			for (list<place*>::iterator j = places.begin(); j != places.end(); j++) {
				(*i)->distances[*j] = min((*i)->distances[*j],
							  (*i)->distances[*k] + (*k)->distances[*j]);
				(*j)->distances[*i] = (*i)->distances[*j];

			}

#ifdef DEBUG
	cout << "===== AFTER SHORTEST PATH =====" << endl;
	for (list<place*>::iterator i = places.begin(); i != places.end(); i++)
                for (list<place*>::iterator j = places.begin(); j != places.end(); j++) {
			cout << (*i)->name << " <--> " << (*j)->name << " : " << (*i)->distances[*j] << endl;
		}
#endif

}

double home::get_expected_value()
{
	find_shortest_path();
	if (is_connected()) {
		calculate_expected_value(places.front(), 0, 0, 1.0);
		return best_ev;
	} else
		return -1;
}

void home::read_file(const string filename) 
{
	ifstream infile;
	infile.open(filename.c_str());

	// file is assume to be proper
	// get number of locations
	int nloc;
	infile >> nloc;

	// read locations
	for (int i = 0; i < nloc; i++) {
		string name;
		double prob;
		infile >> name >> prob;
		add_place(name.c_str(), prob);
	}
	init_distances();
	// get number of connections
	int nconn;
	infile >> nconn;
	// read connections
	for (int i = 0; i < nconn; i++) {
		string name1, name2;
		int dist;
		infile >> name1 >> name2 >> dist;
		connect(name1.c_str(), name2.c_str(), dist);
	}
}

int main(int argc, char *argv[])
{
	assert(argv[1] != NULL);

	const char *filename = (const char*)argv[1];
	home *h = new home(filename);
	double ev = h->get_expected_value();
	cout << setiosflags(ios::fixed) <<  setprecision(2) << ev << endl;
	delete h;
	return 0;
}
