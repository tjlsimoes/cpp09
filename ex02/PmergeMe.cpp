/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:03:02 by tjorge-l          #+#    #+#             */
/*   Updated: 2026/01/12 11:03:02 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other)
{
	(void)other;
}
PmergeMe& PmergeMe::operator=(const PmergeMe& other)
{
    (void)other;
    return *this;
}
PmergeMe::~PmergeMe() {}

long _jacobsthal_number(long n) {
	if (n < 0) return 0; 

	long pow2 = 1L << (n + 1);           // 2^(n+1)
	long sign = (n % 2 == 0) ? 1 : -1;

	return (pow2 + sign) / 3;
}

void PmergeMe::sort_vec(std::vector<int>& vec)
{
	_merge_insertion_sort<std::vector<int> >(vec, 1);
}

void PmergeMe::sort_deque(std::deque<int>& deque)
{
    _merge_insertion_sort<std::deque<int> >(deque, 1);
}