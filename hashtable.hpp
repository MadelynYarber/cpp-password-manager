//namespace cop4530
//size_t size= 100
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size)
{
	table_size = 0;
	table.resize(prime_below(size));
}	

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
	clear();
}	

//Go through
template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) const
{
	for(auto itr = table[myhash(k)].begin(); itr != table[myhash(k)].end(); ++itr)
	{
		if(itr->first == k)
		{	
			return true;
		}
	}
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V>& kv) const
{
	auto & whichList = table[myhash(kv.first)];
	return find(begin(whichList), end(whichList), kv) != end(whichList);
}	


template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V>& kv)
{
	int temp = table_size + 1;
	auto & whichList = table[myhash(kv.first)];
	if(find(begin(whichList), end(whichList), kv) != end(whichList))
	{
		return true;
	}	
	if(contains(kv.first) == false)
	{
		whichList.push_back(kv);
		table_size++;
	}
	else
	{
		remove(kv.first);
		whichList.push_back((kv));
		table_size++;
	}
	if (temp > table.size())
	{
		rehash();
	}
	return true;	
}


template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K, V>&& kv)
{
	int temp = table_size + 1;
	auto & whichList = table[myhash(kv.first)];
	if(std::find(begin(whichList), end(whichList), kv) != end(whichList))
	{
		return false;
	}
	if(contains(kv.first) == false)
	{
		whichList.push_back(move(kv));
		table_size++;
	}
	else
	{
		remove(kv.first);
		whichList.push_back(move(kv));
		table_size++;
	}
	if (temp > table.size())
	{
		rehash();
	}
	return true;
}


template <typename K, typename V>
bool HashTable<K, V>::remove(const K& k)
{
	auto & list = table[myhash(k)];
	for(auto itr = list.begin(); itr != list.end(); ++itr)
	{
		if(itr == end(list))
		{
			return false;
		}
		if(itr->first == k)
		{
			list.erase(itr);
			table_size--;
			return true;
		}
	}
}


template <typename K, typename V>
void HashTable<K, V>::clear()
{
	makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char* filename)
{
	ifstream instream;
	instream.clear();
	instream.open(filename);
	K key;
	V value;

	if(!instream)
	{
		return false;
	}
	while(!instream.eof())
	{
		instream >> key >> value;
		insert(make_pair(key, value));
	}
	instream.close();
	return true;
}

template <typename K, typename V>
void HashTable<K, V>::dump() const
{
	for(int i = 0; i < table.size(); i++)
	{
		cout << "v[" << i << "]: ";
		for(auto itr = table[i].begin(); itr != table[i].end(); ++itr)
		{
			if(itr != table[i].begin())
			{	
				cout << ":";
			}
			cout << itr->first << " " << itr->second;
		}
		cout << endl;
	}
}


template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char* filename) const
{
	ofstream outstream;
	outstream.open(filename);
	K key;
	V value;

	if(!outstream)
	{	
		return false;
	}
	for(int i = 0; i < table.size(); i++)
	{
		auto& whichList = table[i];
		auto itr = whichList.begin();

		if(!whichList.empty())
		{
			outstream << itr->first << " " << itr->second << endl;
			while(++itr != whichList.end())
			{
				outstream << itr->first << " " << itr->second << endl;
			}
		}
	}
	outstream.close();
	return true;
}

template <typename K, typename V>
void HashTable<K, V>::makeEmpty()
{
	table_size = 0;
	for(auto & x : table)
	{
		x.clear();
	}
}

template <typename K, typename V>
void HashTable<K, V>::rehash()
{
	auto oldLists = table;
	table.resize(prime_below(2 * table.size()));
	makeEmpty();
	for(auto & thisList : oldLists)
		for(auto & x : thisList)
			insert(move(x));
}

//check "For the myhash() function, you should use the one discussed in the slides"
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) const
{
	unsigned int hashVal = 0;

	for(auto ch : k)
	{
		hashVal = 37 * hashVal + ch;
	}
	return hashVal % table.size();
}


//check
template <typename K, typename V>
int HashTable<K, V>::getSize() const
{
	return table_size;
}


// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
		//cerr?
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

template <typename K, typename V>
int HashTable<K, V>::get_prime_below(int n)
{
	return prime_below(n);
}
