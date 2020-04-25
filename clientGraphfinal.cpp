#include <iostream>
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <iterator>
#include <climits>
#include <set>
#include "graph.hpp"
using namespace std;
int main()
{
	Graph<int>g2;
	g2.addEdge(1,2);
	g2.addEdge(2,4);
	g2.addEdge(3,2);
	cout << g2;
	g2.topoSort();
	cout << endl;
	Graph<string>g;
	g.addEdge("Modhi","Trump");
	g.addEdge("Rahul","Yogi");
	g.addEdge("Yogi","Trump");
	g.addEdge("Prabhu","Rahul");
	g.addEdge("San","Rahul");
	g.addEdge("Yogi","San");
	g.addEdge("Trump","Yogi");
	cout << g;
	g.topoSort();
	cout << g.isCycle() << endl;
	cout << endl;
	Graph<string>g1;
	g1.addEdge("Amritsar","Delhi",true,1);
	g1.addEdge("Amritsar","Jaipur",true,4);
	g1.addEdge("Jaipur","Delhi",true,2);
	g1.addEdge("Jaipur","Mumbai",true,8);
	g1.addEdge("Bhopal","Agra",true,2);
	g1.addEdge("Mumbai","Bhopal",true,3);
	g1.addEdge("Agra","Delhi",1);
	g1.dijkstra("Amritsar");
	return 0;
}
