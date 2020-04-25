#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <list>
using namespace std;
template <typename T>
class Node
{
public:
	string key_;
	T value_;
	Node<T>*next_;
	Node(string key,T val) : key_(key),value_(val),next_(nullptr){}
	~Node()
	{
		if(next_ != nullptr)
			delete next_;
	}
};
template <typename T>
class Hashtable
{
	Node<T>** table_;
	int currentSize_;
	int tableSize_;
	int hashFunction(string key);
	void rehash();
public:
    explicit Hashtable(int = 7);
    Hashtable(const Hashtable& rhs);
    Hashtable& operator=(const Hashtable& rhs);
    Hashtable(Hashtable&& rhs);
    Hashtable& operator=(Hashtable&& rhs);
    void insert(string key,T value);
    void erase(string key);
    T& operator[](string key);
    class iterator
    {
    	Node<T>**table;
		Node<T>*currentNode_;
		int index;
		int tableSize_;
	public:
		using iterator_category = forward_iterator_tag;
        using value_type = T;
        using difference_type = T;
        using pointer = T*;
        using reference = T&;
		iterator(Node<T>**tab,Node<T>*cur,int size,int in);
		bool operator==(const iterator& rhs);
		iterator& operator++();
		bool operator!=(const iterator& rhs);
		pair<string,T>operator*();
		void print();
    };
    bool operator!=(const Hashtable& rhs);
    iterator begin();
    iterator end();
    iterator search(string key);
};
template <typename T>
int Hashtable<T>::hashFunction(string key)
{
	int index = 0;
	int power = 1;
	for(int j = 0;j < key.size();++j)
	{
		index = index + (key[j] % power) % tableSize_;
		index = index % tableSize_;
		power = (power * 27) % tableSize_;
	}
	return index;
}
template <typename T>
void Hashtable<T>::rehash()
{
	Node<T>**oldTable = table_;
	int oldtableSize = tableSize_;
	tableSize_ = 2 * tableSize_;//approximation find next prime no
	table_ = new Node<T>*[tableSize_];
	for(int i = 0;i < tableSize_;++i)
	table_[i] = nullptr;
	currentSize_ = 0;
	//shift the elements from oldtable to newtable
	for(int i = 0;i < oldtableSize;++i)
	{
		Node<T>*current = oldTable[i];
        while(current)
        {
            insert(current->key_,current -> value_);
            current = current -> next_;
        }
        if(oldTable[i] != nullptr)
            delete oldTable[i];
	}
	delete [] oldTable;
}
//default parameters should be declare,not to be used in definition
template<typename T>
Hashtable<T>::Hashtable(int size)
{
	tableSize_ = size;
	table_ = new Node<T>*[tableSize_];
	currentSize_ = 0;
	for(int i = 0;i < tableSize_;++i)
		table_[i] = nullptr;
}
//default copy constructor use shallow copy we need deep copy
//copy constructor
//we can access private memebers of a class within class,evne these are of another instance
template<typename T>
Hashtable<T>::Hashtable(const Hashtable& rhs)
{
	table_ = new Node<T>*[rhs.tableSize_];
	tableSize_ = rhs.tableSize_;
	currentSize_ = 0;
	for(int i = 0;i < tableSize_;++i)
		table_[i] = nullptr;
	for(int i = 0;i < tableSize_;++i)
	{
		Node<T>*current = rhs.table_[i];
		while(current)
		{
			insert(current -> key_,current -> value_);
			current = current -> next_;
		}		
	}
}
template<typename T>
bool Hashtable<T>::operator!=(const Hashtable& rhs)
{
	return table_ != rhs.table_;
}
//copy assignment operator
template<typename T>
Hashtable<T>& Hashtable<T>::operator=(const Hashtable& rhs)
{
	//check for self assignment
	if(*this != rhs)
	{
		table_ = new Node<T>*[rhs.tableSize_];
		tableSize_ = rhs.tableSize_;
		currentSize_ = 0;
		for(int i = 0;i < tableSize_;++i)
			table_[i] = nullptr;
		for(int i = 0;i < tableSize_;++i)
		{
			Node<T>*current = rhs.table_[i];
			while(current)
			{
				insert(current -> key_,current -> value_);
				current = current -> next_;
			}		
		}
    }
	return *this;
}
	//move constructor
	//move resource owned by rvalue object to be moved to lvalue without copying
	//move ownership of resources from one object to another
template<typename T>
Hashtable<T>::Hashtable(Hashtable&& rhs)
{
	table_ = rhs.table_;
	currentSize_ = rhs.currentSize_;
	tableSize_ = rhs.tableSize_;
	rhs.tableSize_ = 0;
	rhs.currentSize_ = 0;
	rhs.table_ = nullptr;
}
	//move assignment
template<typename T>
Hashtable<T>& Hashtable<T>::operator=(Hashtable&& rhs)
{
	//release current object
	delete []table_;
	if(*this != rhs)
	{
		table_ = rhs.table_;
		currentSize_ = rhs.currentSize_;
		tableSize_ = rhs.tableSize_;
		rhs.tableSize_ = 0;
		rhs.currentSize_ = 0;
		rhs.table_ = nullptr;
	}
	return *this;
}
template<typename T>
void Hashtable<T>::insert(string key,T value)
{
	int idx = hashFunction(key);
	Node<T>*newNode = new Node<T>(key,value);
	newNode -> next_ = table_[idx];
	table_[idx] = newNode;
	++currentSize_;
		//rehash
	float load_factor = currentSize_/(1.0 * tableSize_);
	if(load_factor > 1.0)
		rehash();
}
template<typename T>
void Hashtable<T>::erase(string key)
{
	int index = hashFunction(key);
	Node<T>*prev = nullptr;
	Node<T>*current = table_[index];
	while(current)
	{
		if(current -> key_ == key)
		{
			if(prev == nullptr)
				table_[index] = current -> next_;
			else
				prev -> next_ = current -> next_;
			break;
		}
		current = current -> next_;
	}
}
template<typename T>
T& Hashtable<T>::operator[](string key)
{
	int index = hashFunction(key);
	Node<T>*current = table_[index];
	T garbage;
	while(current)
	{
		if(current -> key_ == key)
			return current -> value_;
		current = current -> next_;
	}
	Node<T>*result = nullptr;
	if(!current)
	{

		insert(key,garbage);
		index = hashFunction(key);
		current = table_[index];
		while(current)
		{
			if(current -> key_ == key)
			{
				result = current;
				break;
			}
		}
	}
	return result -> value_;
}
template<typename T>
Hashtable<T>::iterator::iterator(Node<T>**tab,Node<T>*cur,int size,int in):table(tab),currentNode_(cur),index(in),tableSize_(size)
{
}
template<typename T>
bool Hashtable<T>::iterator::operator==(const iterator& rhs)
{
	return currentNode_->key_ == rhs.currentNode_->key_;
}
template<typename T>
typename Hashtable<T>::iterator& Hashtable<T>::iterator::operator++()
{
	currentNode_ = currentNode_ -> next_;
	if(!currentNode_)
	{
		int i = 0;
		for(i = index+1;i < tableSize_;++i)
		{
			if(table[i])
			{
				index = i;
				currentNode_ = table[i];
				break;
			}
		}
		if(i == tableSize_)
		{
			index == tableSize_;
			Node<T>*current = new Node<T>("",T());
		    currentNode_ = current;
		}
	}
	return *this;
}
//lvalue bound to lvalue reference
//rvlaue bound to rvalue refrence or constant lvalue reference
template<typename T>
bool Hashtable<T>::iterator::operator!=(const iterator& rhs) 
{
	return !(currentNode_->key_ == rhs.currentNode_ -> key_);
}
template<typename T>
pair<string,T> Hashtable<T>::iterator::operator*()
{
	pair<string,T>result;
	result.first = currentNode_ -> key_;
	result.second = currentNode_ -> value_;
	return result;
}
template<typename T>
void Hashtable<T>::iterator::print()
{
	for(int i = 0;i < tableSize_;++i)
	{
		cout << "Bucket : " << i << " -> ";
		Node<T>*current = table[i];
		while(current)
		{
			cout << current -> key_ << " " << current -> value_ << "  ";
			current = current -> next_;
		}
		cout << endl;
	}
}
//typename is method for indicating that a dependent name is a type
template<typename T>
typename Hashtable<T>::iterator Hashtable<T>::begin()
{
	Node<T>*current;
	int index = 0;
	for(int i = 0;i < tableSize_;++i)
	{
		if(table_[i] != nullptr)
		{
			index = i;
			current = table_[i];
			break;
		}
	}
	return iterator(table_,current,tableSize_,index);
}
template<typename T>
typename Hashtable<T>::iterator Hashtable<T>::end()
{
	Node<T>*current = new Node<T>("",T());
	return iterator(table_,current,tableSize_,tableSize_);
}
template<typename T>
typename Hashtable<T>::iterator Hashtable<T>::search(string key)
{
	int index = hashFunction(key);
	Node<T>*current = table_[index];
	while(current)
	{
		if(current -> key_ == key)
			return iterator(table_,current,tableSize_,index);
		current = current -> next_;
	}
	Node<T>*temp = new Node<T>("",T());
	return iterator(table_,temp,tableSize_,tableSize_);
}

//define swap function
template <typename T>
void swap(T& a,T& b)
{
	T temp(move(a));
	a = move(b);
	b = move(a);
}
