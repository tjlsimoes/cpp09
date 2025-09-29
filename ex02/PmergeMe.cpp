#include <PmergeMe.hpp>

template<typename T>
void PmergeMe::print(T container, const std::string &str)
{
	typename T::iterator it = container.begin();
	std::cout << str;
	for (; it != container.end(); it++)
	{
		typename T::iterator check = it;
		std::cout << *it;
		if (container.size() > 10 && std::distance(container.begin(), it) == 10)
		{
			std::cout << " [...]";
			break ;
		}
		else if (++check == container.end())
			break ;
		std::cout << " ";
	}
	std::cout << std::endl;
}

template<typename T>
void PmergeMe::insertionSort(T &container)
{
	typename T::iterator it_next = container.begin();
	it_next++;
	for (; it_next != container.end(); ++it_next)
	{
		typename T::iterator it = container.begin();
		for(; it != it_next; it++)
		{
			if (*it > *it_next)
			{
				int value = *it_next;
				container.erase(it_next);
				it_next = it;
				it_next++;
				container.insert(it, value);
				break;
			}
		}
	}
}

template<typename T>
void PmergeMe::mergeSort(T &container, T &target)
{
	typename T::iterator it = container.begin();
	if (target.empty())
	{
		target.push_back(*it);
		it++;
	}

	for (; it != container.end(); it++)
	{
		typename T::iterator itt = target.begin();
		for (; itt != target.end(); itt++)
		{
			if (*it < *itt)
			{
				target.insert(itt, *it);
				break ;
			}
		}
		if (itt == target.end())
			target.push_back(*it);
	}
}

template<typename T>
void PmergeMe::merge(std::pair<T, T> &lst, T &target)
{
	T temp;
	if (lst.first.size() <= static_cast<size_t>(_k))
	{
		insertionSort<T>(lst.first);
		mergeSort<T>(lst.first, temp);
	}
	else
	{
		std::pair<T, T> lstPair = split<T>(lst.first);
		merge(lstPair, target);
		lst.first.clear();
	}
	if (lst.second.size() <= static_cast<size_t>(_k))
	{
		insertionSort<T>(lst.second);
		mergeSort<T>(lst.second, temp);
	}
	else
	{
		std::pair<T, T> lstPair = split<T>(lst.second);
		merge(lstPair, target);
		lst.second.clear();
	}
	mergeSort<T>(temp, target);
}

template<typename T>
std::pair<T, T> PmergeMe::split(T &container)
{
	T left;
	T right;
	typename T::iterator it = container.begin();
	for(size_t i = 0; i < container.size() / 2; i++)
	{
		left.push_back(*it);
		it++;
	}
	for(; it != container.end(); it++)
		right.push_back(*it);
	return (std::make_pair(left, right));
}

PmergeMe::PmergeMe() : _k(2)
{
}

PmergeMe::PmergeMe(const PmergeMe &src)
{
	*this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &src)
{
	_k = src._k;
	_v = src._v;
	_lst = src._lst;
	return (*this);
}

PmergeMe::PmergeMe(int k) : _N(0), _k(k)
{
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::push(int n)
{
	_lst.push_back(n);
	_v.push_back(n);
	_N++;
}

bool PmergeMe::find(int n) const
{
	std::list<int>::const_iterator it = _lst.begin();
	for (; it != _lst.end(); it++)
		if (n == (*it))
			return (true);
	return (false);
}

bool PmergeMe::isSorted()
{
	std::list<int>::iterator it = _lst.begin();
	std::list<int>::iterator it_temp = _lst.begin();
	for (; it != _lst.end(); it++)
	{
		if (++it_temp != _lst.end() && *it > *it_temp)
			return (false);
	}
	return (true);
}

void PmergeMe::sort()
{
	{
		clock_t start = clock();
		std::pair<std::vector<int>,std::vector<int> > vectorPair = split<std::vector<int> >(_v);
		print<std::vector<int> >(_v, "Before: ");
		merge<std::vector<int> >(vectorPair, _sortedV);
		print<std::vector<int> >(_sortedV, "After: ");
		std::cout << "time executing Sort Vector: " << static_cast<float>(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
	}
	{
		clock_t start = clock();
		std::pair<std::list<int>,std::list<int> > lstPair = split<std::list<int> >(_lst);
		merge<std::list<int> >(lstPair, _sortedLst);
		std::cout << "time executing Sort List: " << static_cast<float>(clock() - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
	}
}