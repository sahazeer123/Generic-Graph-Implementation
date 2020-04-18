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
	int hashFunction(string key)
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
	void rehash()
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
public:
	Hashtable(int size=7)
	{
		tableSize_ = size;
		table_ = new Node<T>*[tableSize_];
		currentSize_ = 0;
		for(int i = 0;i < tableSize_;++i)
			table_[i] = nullptr;
	}
	void insert(string key,T value)
	{
		int idx = hashFunction(key);
		Node<T>*newNode = new Node<T>(key,value);
		newNode -> next_ = table_[idx];
		table_[idx] = newNode;
		++currentSize_;
		//rehash
		float load_factor = currentSize_/(1.0 * tableSize_);
		if(load_factor > 0.7)
			rehash();
	}
	T* search(string key)
	{
		int index = hashFunction(key);
		Node<T>*current = table_[index];
		while(current)
		{
			if(current -> key_ == key)
				return &(current-> value_);
			current = current -> next_;
		}
		return nullptr;//T*
	}
	void erase(string key)
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
	T& operator[](string key)
	{
		T * f = search(key);
		if(f == nullptr)
		{
			T garbage;
			insert(key,garbage);
			f = search(key);
		}
		return *f;
	}
	class iterator
	{
		Node<T>**table;
		Node<T>*currentNode_;
		int index;
		int tableSize_;
	public:
		iterator(Node<T>**tab,Node<T>*cur,int size,int in):table(tab),currentNode_(cur),index(in),tableSize_(size){}
		bool operator==(const iterator& rhs)
		{
			return currentNode_->key_ == rhs.currentNode_->key_;
		}
		iterator& operator++()
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
		bool operator!=(const iterator& rhs) 
		{
			return !(currentNode_->key_ == rhs.currentNode_ -> key_);
		}
		pair<string,T>operator*()
		{
			pair<string,T>result;
			result.first = currentNode_ -> key_;
			result.second = currentNode_ -> value_;
			return result;
		}
		void print()
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
	};
	iterator begin()
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
	iterator end()
	{
		Node<T>*current = new Node<T>("",T());
		return iterator(table_,current,tableSize_,tableSize_);
	}
};

int main()
{
	Hashtable<int> phoneBook;
	phoneBook.insert("Shaji",903);
	phoneBook.insert("Ludei",90903);
	phoneBook.insert("Kiri",9093);
	phoneBook.insert("CHei",9031);
	phoneBook.insert("Abbai",9023);
	phoneBook.insert("Ummi",9033);
	phoneBook.insert("Ammi",90);
	phoneBook.insert("Anchi",03);
	for(Hashtable<int>::iterator it = phoneBook.begin();it != phoneBook.end();++it)
		cout << (*it).first << " " << (*it).second << endl;
  	return 0;
}