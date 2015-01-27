#ifndef _MYDS_H
#define _MYDS_H

#include "MyHash.h"
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

class MyDS
{
public:
	MyDS()
	{
		// Initialized at 60000 to avoid expensive rehashing at larger sizes
		max_size = 60000;
		size = 0;
		nodes.resize(max_size);
	}

	~MyDS()
	{
		size = 0;
		max_size = 6000;
		nodes.clear();
	}

	void push(const string& s)
	{
		// String is hashed using MyHash functor, then modulo by max_size
		unsigned long hash = MyHash()(s) % max_size;
		
		// This particular list reference is where s will be inserted
		list<string> & hashList = nodes[hash];

		// Increment total size
		if (hashList.size() == 0) { ++size; }

		hashList.push_back(s);

		// This ensures no single list grows too large; helps to be more evenly distributed
		if (size == nodes.size() || hashList.size() >= 150)
		{
			max_size *= 4;
			rehash();
		}
	}

	bool search(const string& s)
	{
		unsigned long hash = MyHash()(s) % max_size;
		
		// The end iterator of the given list to aid in searching
		list<string>::iterator it = nodes[hash].end();

		// Returns a boolean value by utilizing the find function to search for s
		return (it != find(nodes[hash].begin(), it, s));
	}
private:
	void rehash()
	{
		list<string>::iterator it;
		
		// The new vector which will contain the original data
		vector < list<string> > newNodes(max_size);
		
		for (int i = 0; i < nodes.size(); i++)
		{
			for (it = nodes[i].begin(); it != nodes[i].end();)
			{
				// Rehashes each word of each node in nodes, creates a new list at that index 
				list<string> & newList = newNodes[MyHash()(*it) % max_size];
				
				// Inserts the string at position "it" in "nodes[i]" into the new list; then increments it
				newList.splice(newList.end(), nodes[i], it++);
			}
		}
		
		// Swap operation is less costly than another loop
		nodes.swap(newNodes);
	}

	vector< list<string> > nodes;
	int max_size;
	int size;
};

#endif