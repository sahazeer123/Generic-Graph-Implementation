#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
#include <queue>
using namespace std;
template<typename T>
class Graph
{
	unordered_map<T,list<T>>adjList;
public:
	Graph()
	{
		adjList = unordered_map<T,list<T>>();
	}
	void addEdge(const T u,const T v,bool bidir = true)
	{
		adjList[u].push_back(v);
		if(bidir)
		{
			adjList[v].push_back(u);
		}
	}
	void print() const
	{
		for(auto i:adjList)
		{
			cout << i.first << "->";
			for(T  entry : i.second)
				cout << entry << ", ";
			cout << endl;
		}
	}
	void bfs(T src) 
	{
		queue<T>Q;
		unordered_map<T,bool>visited;
		Q.push(src);
		visited[src] = true;
		while(!Q.empty())
		{
			T temp = Q.front();
			cout << temp << " ";
			Q.pop();
			for(auto neigh : adjList[temp])
			{
				if(!visited[neigh])
				{
					Q.push(neigh);
					visited[neigh] = true;
				}
			}
		}
		cout << endl;
	}
	void dfs(T src)
	{
		unordered_map<T,bool>visited;
		dfsHelper(src,visited);
	}
	void dfsHelper(T src,unordered_map<T,bool>& visited)
	{
		visited[src] = true;
		cout << src << " ";
		for(auto neigh : adjList[src])
		{
			if(!visited[neigh])
				dfsHelper(neigh,visited);
		}
	}
};
int main()
{
	Graph<string> g;
	g.addEdge("Putin","Trump",false);
	g.addEdge("Putin","Modi",false);
	g.addEdge("Putin","Pope",false);
	g.addEdge("Modi","Trump",true);
	g.addEdge("Modi","Yogi",true);
	g.addEdge("Modi","Prabhu",false);
	g.print();
	g.bfs("Putin");
	g.dfs("Putin");
	return 0;
}