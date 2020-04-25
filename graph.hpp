#include <iostream>
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <iterator>
#include <climits>
#include <set>
#include "unordered_map.hpp"
using namespace std;
template<typename T>
class Graph
{
	unordered_map<T,list<pair<T,int>>> adjList;
	T src;
	T dummyNode;
public:
	Graph();
	void addEdge(T,T,bool = false,int weight = 0);
	class BFSIterator
	{
	    unordered_map<T,list<pair<T,int>>>adjList;
		unordered_map<T,bool>visited;
		queue<T>Q;
		T current;
		public:
		using iterator_category = forward_iterator_tag;
        using value_type = T;
        using difference_type = T;
        using pointer = T*;
        using reference = T&;
        explicit BFSIterator(T src,unordered_map<T,list<pair<T,int>>>& list);
        bool operator==(const BFSIterator& rhs);
        bool operator!=(const BFSIterator& rhs);
        T operator*();
        BFSIterator& operator++();
	};
	BFSIterator begin();
	BFSIterator end();
	void topoSort();
	bool isCycle();
	bool isCycle(T src,unordered_map<T,bool>& visited,unordered_map<T,bool>& currentPath);
	void dijkstra(T src);
	friend class BFSIterator;
	template <typename U> friend ostream& operator<<(ostream&,Graph<U>&);
};
template<typename T>
Graph<T>::Graph()
{
	adjList = unordered_map<T,list<pair<T,int>>>();
	src = T();
	dummyNode = T();
}
template<typename T>
void Graph<T>::addEdge(T u,T v,bool bidirect,int weight)
{
	if(src == T())
		src = u;
	pair<T,int> temp;
	temp.first = v;
	temp.second = weight;
	adjList[u].push_back(temp);
	if(bidirect)
		adjList[v].push_back(temp);
}
template<typename T>
Graph<T>::BFSIterator::BFSIterator(T src,unordered_map<T,list<pair<T,int>>>& list)
{
	adjList = list;
	current = src;
	if(src != T())
	{
		visited[current] = true;
		Q.push(current);
	}
}
template<typename T>
bool Graph<T>::BFSIterator::operator==(const BFSIterator& rhs)
{
	return current == rhs.current;
}
template<typename T>
bool Graph<T>::BFSIterator::operator!=(const BFSIterator& rhs)
{
	return current != rhs.current; 
}
template<typename T>
T Graph<T>::BFSIterator::operator*()
{
	return Q.front();
}
template<typename T>
typename Graph<T>::BFSIterator& Graph<T>::BFSIterator::operator++()
{
	current = Q.front();
	Q.pop();
	for(auto neigh:adjList[current])
	{
		if(!visited[neigh.first])
		{
			Q.push(neigh.first);
			visited[neigh.first] = true;
		}
	}
	if(Q.empty())
		current = T();
	return *this;
}
template<typename T>
typename Graph<T>::BFSIterator Graph<T>::begin()
{
	return BFSIterator(src,adjList);
}
template<typename T>
typename Graph<T>::BFSIterator Graph<T>::end()
{
	return BFSIterator(dummyNode,adjList);
}
template<typename T>
void Graph<T>::topoSort()
{
	queue<T> Q;
	unordered_map<T,int>indegree;
	for(auto list : adjList)
	    indegree[list.first] = 0;
    for(auto list : adjList)
	{
	    for(auto entry : list.second)
	    	indegree[entry.first]++; 
	}
	for(auto entry : indegree)
    {
	    if(entry.second == 0)
	    	Q.push(entry.first);
	}
	while(!Q.empty())
	{
	    T current = Q.front();
	    cout << current << endl;
	    Q.pop();
	    for(auto neigh : adjList[current])
	    {
	    	indegree[neigh.first]--;
	    	if(indegree[neigh.first] == 0)
	    		Q.push(neigh.first);
	    }
	}
}
template<typename T>
bool Graph<T>::isCycle()
{
	unordered_map<T,bool>visited;
	unordered_map<T,bool>currentPath;
	return isCycle(src,visited,currentPath);
}
template<typename T>
bool Graph<T>::isCycle(T src,unordered_map<T,bool>& visited,unordered_map<T,bool>& currentPath)
{
    visited[src] = true;
	currentPath[src] = true;
	for(auto neigh:adjList[src])
	{
		if(currentPath[neigh.first] == true)
			return true;
		else if(!visited[neigh.first])
		{
			bool isPresent = isCycle(neigh.first,visited,currentPath);
			if(isPresent)
				return true;

		}
	}
	currentPath[src] = false;
	return false;
}
template<typename T>
void Graph<T>::dijkstra(T src)
{
	unordered_map<T,int>dist;
	for(auto entry:adjList)
		dist[entry.first] = INT_MAX;
	set<pair<int,T>>s;
	dist[src] = 0;
	s.insert(make_pair(0,src));
	while(!s.empty())
	{
		auto p = *(s.begin());
		T node = p.second;
		int nodeDist = p.first;
		s.erase(s.begin());
		for(auto neigh : adjList[node])
		{
			if(nodeDist + neigh.second < dist[neigh.first])
			{
				T dest = neigh.first;
				auto f = s.find(make_pair(dist[dest],dest));
				if(f != s.end())
					s.erase(f);
				dist[dest] = nodeDist + neigh.second;
				s.insert(make_pair(dist[dest],dest));
			}
		}
	}
	for(auto di : dist)
		cout << di.first << " at a distance of " << di.second <<endl;
}
template<>
class Graph<string>
{
	Hashtable<list<pair<string,int>>> adjList;
	string src;
	string dummyNode;
public:
	explicit Graph()
	{
		src = "";
		dummyNode = "";
	}
	void addEdge(string u,string v,bool bidirect = false,int weight = 0)
	{
		if(src == "")
			src = u;
		pair<string,int> temp;
		temp.first = v;
		temp.second = weight;
		adjList[u].push_back(temp);
		if(bidirect)
			adjList[v].push_back(temp);
	}

	class BFSIterator
	{
		Hashtable<list<pair<string,int>>> adjList;
		unordered_map<string,bool>visited;
		queue<string>Q;
		string current;
	public:
        using iterator_category = forward_iterator_tag;
        using value_type = string;
        using difference_type = string;
        using pointer = string*;
        using reference = string&;
 
		explicit BFSIterator(string src,Hashtable<list<pair<string,int>>> & list)
		{
			adjList = list;
			current = src;
			if(src != "")
			{
				visited[current] = true;
			    Q.push(current);
			}
		}
		bool operator==(const BFSIterator& rhs)
		{
			return current == rhs.current;
		}
		bool operator!=(const BFSIterator& rhs)
		{
			return current != rhs.current; 
		}
		string operator*()
		{
			return Q.front();
		}
		BFSIterator& operator++()
		{
			current = Q.front();
			Q.pop();
			for(auto neigh:adjList[current])
			{
				if(!visited[neigh.first])
				{
					Q.push(neigh.first);
					visited[neigh.first] = true;
				}
			}
			if(Q.empty())
				current = "";
			return *this;
		}
		
	};
	BFSIterator begin()
	{
		return BFSIterator(src,adjList);
	}
	BFSIterator end()
	{
		return BFSIterator(dummyNode,adjList);
	}
	vector<string> topoSort()
	{
	    queue<string> Q;
	    vector<string> res;
	    unordered_map<string,int>indegree;
	    for(auto list : adjList)
	    	indegree[list.first] = 0;
	    for(auto list : adjList)
	    {
	    	for(auto entry : list.second)
	    		indegree[entry.first]++; 
	    }
	    for(auto entry : indegree)
	    {
	    	if(entry.second == 0)
	    		Q.push(entry.first);
	    }
	    while(!Q.empty())
	    {
	    	string current = Q.front();
	    	Q.pop();
	    	for(auto neigh : adjList[current])
	    	{
	    		indegree[neigh.first]--;
	    		if(indegree[neigh.first] == 0)
	    			Q.push(neigh.first);
	    	}
	    }
	    return res;
	}
	bool isCycle()
	{
		unordered_map<string,bool>visited;
		unordered_map<string,bool>currentPath;
		return isCycle(src,visited,currentPath);
	}
	bool isCycle(string src,unordered_map<string,bool>& visited,unordered_map<string,bool>& currentPath)
	{
		visited[src] = true;
		currentPath[src] = true;
		for(auto neigh:adjList[src])
		{
			if(currentPath[neigh.first] == true)
				return true;
			else if(!visited[neigh.first])
			{
				bool isPresent = isCycle(neigh.first,visited,currentPath);
				if(isPresent)
					return true;

			}
		}
		currentPath[src] = false;
		return false;
	}
	void dijkstra(string src)
	{
		unordered_map<string,int>dist;
		for(auto entry:adjList)
			dist[entry.first] = INT_MAX;
		set<pair<int,string>>s;
		dist[src] = 0;
		s.insert(make_pair(0,src));
		while(!s.empty())
		{
			auto p = *(s.begin());
			string node = p.second;
			int nodeDist = p.first;
			s.erase(s.begin());
			for(auto neigh : adjList[node])
			{
				if(nodeDist + neigh.second < dist[neigh.first])
				{
					string dest = neigh.first;
					auto f = s.find(make_pair(dist[dest],dest));
					if(f != s.end())
						s.erase(f);
					dist[dest] = nodeDist + neigh.second;
				    s.insert(make_pair(dist[dest],dest));
				}
			}
		}
		for(auto di : dist)
			cout << di.first << " at a distance of " << di.second <<endl;
	}
	friend class BFSIterator;
	template <typename U> friend ostream& operator<<(ostream&,Graph<U>&);
};
template <typename T>
ostream& operator<<(ostream& out,Graph<T>& graph)
{
	for(auto x:graph.adjList)
	{
		cout << x.first << " : ";
		for(auto ele : x.second)
			cout << "--> " << ele.first;
		cout << endl;
	}
	return out;
}
