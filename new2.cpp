#include <iostream>
#include <unordered_map>
#include <queue>
#include <list>
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
		explicit BFSIterator(T src,unordered_map<T,list<T>>& list)
		{
			adjList = list;
			current = src;
			visited[current] = true;
			Q.push(current);
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
			if(Q.empty())
			{
				current = T();
			}
			else
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
			}
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
	Graph<int>g;
	g.addEdge(1, 2); 
    g.addEdge(1, 3); 
    g.addEdge(2, 3); 
    g.addEdge(3, 4); 
	for(Graph<int>::BFSIterator it = g.begin();it != g.end();++it)
	{
		cout << *it << " ";
	}
	return 0;
}