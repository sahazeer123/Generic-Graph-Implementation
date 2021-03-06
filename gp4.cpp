#include <iostream>
#include <unordered_map>
#include <queue>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;
template<typename T>
class Graph
{
	unordered_map<T,list<T>>adjList;
	T src;
	T dummyNode;
public:
	explicit Graph()
	{
		adjList = unordered_map<T,list<T>>();
		src = T();
		dummyNode = T();
	}
	void addEdge(T u,T v,bool bidirect = true)
	{
		if(src == T())
			src = u;
		adjList[u].push_back(v);
		if(bidirect)
			adjList[v].push_back(u);
	}
	class BFSIterator
	{
		unordered_map<T,list<T>>adjList;
		unordered_map<T,bool>visited;
		queue<T>Q;
		T current;
	public:
        using iterator_category = forward_iterator_tag;
        using value_type = T;
        using difference_type = T;
        using pointer = T*;
        using reference = T&;
 
		explicit BFSIterator(T src,unordered_map<T,list<T>>& list)
		{
			adjList = list;
			current = src;
			if(src != T())
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
		T operator*()
		{
			return Q.front();
		}
		BFSIterator& operator++()
		{
			current = Q.front();
			Q.pop();
			for(auto neigh:adjList[current])
			{
				if(!visited[neigh])
				{
					Q.push(neigh);
					visited[neigh] = true;
				}
			}
			if(Q.empty())
				current = T();
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
	friend class BFSIterator;
};
int main()
{
	Graph<string>g;
	g.addEdge("Modhi","Trump");
	g.addEdge("Rahul","Yogi");
	g.addEdge("Yogi","Trump");
	g.addEdge("Prabhu","Rahul");
	for(auto ele : g)
		cout << ele << " ";
	return 0;
}