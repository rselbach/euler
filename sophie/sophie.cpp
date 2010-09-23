#include <cstdlib>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <list>
#include <map>

using namespace std;

#define INFINITE -1

class place
{
public:
	const string name;
	double probability;
	bool visited;
	int distance;    // distance from source in optimal path
	place *previous; // prev node in optimal path
	place(const string n, double prob)
		:name(n),probability(prob),visited(false),
		 distance(INFINITE), previous(0) {};
	list<pair<place*,int> > neighbors;
	
};

class home
{
private:
	void read_file(const string);
protected:
	place *source_place;
	list<place*> places;
	map<const string,place*> places_map;
public:
	void add_place(const string name, double prob) {
		cout << "Adding place " << name << " (" << prob << ")" << endl;
		place *p = new place(name, prob);
		places.push_back(p);
		places_map.insert(pair<const string, place*>(name, p));
		if (source_place == NULL) 
			source_place = p;
		
	}
	void connect(const string p1, const string p2, int dist) {
		cout << "Connecting " << p1 << " with " << p2 << endl;
		place *one = places_map.find(p1)->second;
		place *two = places_map.find(p2)->second;
		one->neighbors.push_back(pair<place*,int>(two,dist));
		two->neighbors.push_back(pair<place*,int>(one,dist));
		
	}

	void find_shortest_path();
	int get_expected_value();
	void build(const string filename) {
		read_file(filename);
	}
	home(const string filename)
		: source_place(0) {
		build(filename);
	}

	~home() {

		for (list<place*>::iterator i = places.begin() ; i != places.end(); i++ ) {
			cout << "Destroying " << (*i)->name << endl;
			delete *i;
		}
		places.clear();

	}
};

void home::find_shortest_path() 
{
	source_place->distance = 0;
	
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
	h->find_shortest_path();
	delete h;
	return 0;
}
