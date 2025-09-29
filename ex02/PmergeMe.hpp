#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <exception>
#include <cstdlib>
#include <cstring>
#include <limits>


class PmergeMe
{
	private:
		int _N;
		int _k;

		std::vector< int > _v;
		std::vector< int > _sortedV;

		std::list< int > _lst;
		std::list< int > _sortedLst;

		PmergeMe();
		PmergeMe(const PmergeMe &);
		PmergeMe &operator=(const PmergeMe &);

		bool find(int) const;
		public:

			PmergeMe(int);
			~PmergeMe();

			void push(int);
			bool isSorted();
			void mergeInsertSortVector();

			template<typename T>
			void print(T container, const std::string &str);

			template<typename T>
			void insertionSort(T &container);

			template<typename T>
			void mergeSort(T &container, T &target);

			template<typename T>
			void merge(std::pair<T, T> &lst, T &target);

			template<typename T>
			std::pair<T, T> split(T &container);

			void sort();
};	