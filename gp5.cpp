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
	template <typename U> friend ostream& operator<<(ostream&,Graph<U>&);
};
template <typename T>
ostream& operator<<(ostream& out,Graph<T>& graph)
{
	for(auto x:graph.adjList)
	{
		cout << x.first << " : ";
		for(auto ele : x.second)
			cout << "--> " << ele;
		cout << endl;
	}
	return out;
}
int main()
{
	Graph<string>g;
	g.addEdge("Modhi","Trump");
	g.addEdge("Rahul","Yogi");
	g.addEdge("Yogi","Trump");
	g.addEdge("Prabhu","Rahul");
	Graph<string>::BFSIterator it = find(g.begin(),g.end(),"Shaji");
	if(it == g.end())
		cout << "Modhi not found " << endl;
	else
		cout << "Modhi found" << endl;
	cout << g;
	return 0;
}