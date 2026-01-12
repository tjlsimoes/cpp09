/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 11:03:02 by tjorge-l          #+#    #+#             */
/*   Updated: 2026/01/12 11:33:35 by tjorge-l         ###   ########.fr       */
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
	merge_insertion_sort_vec(vec, 1);
}

void PmergeMe::sort_deque(std::deque<int>& deque)
{
    merge_insertion_sort_deq(deque, 1);
}

void	PmergeMe::merge_insertion_sort_vec(std::vector<int> &container, int pair_level)
{
    int pair_units_nbr = container.size() / pair_level;
    if (pair_units_nbr < 2)
        return;

    bool is_odd = pair_units_nbr % 2 == 1;

    std::vector<int>::iterator start = container.begin();
    std::vector<int>::iterator last = next(container.begin(), pair_level * (pair_units_nbr));
    std::vector<int>::iterator end = next(last, -(is_odd * pair_level));

    int jump = 2 * pair_level;
    for (std::vector<int>::iterator it = start; it != end; std::advance(it, jump))
    {
        std::vector<int>::iterator this_pair = next(it, pair_level - 1);
        std::vector<int>::iterator next_pair = next(it, pair_level * 2 - 1);
        if (_comp(next_pair, this_pair))
        {
            swap_pair(this_pair, pair_level);
        }
    }
    merge_insertion_sort_vec(container, pair_level * 2);

    std::vector<std::vector<int>::iterator> main;
    std::vector<std::vector<int>::iterator> pend;

    main.insert(main.end(), next(container.begin(), pair_level - 1));
    main.insert(main.end(), next(container.begin(), pair_level * 2 - 1));

    for (int i = 4; i <= pair_units_nbr; i += 2)
    {
        pend.insert(pend.end(), next(container.begin(), pair_level * (i - 1) - 1));
        main.insert(main.end(), next(container.begin(), pair_level * i - 1));
    }

    if (is_odd)
    {
        pend.insert(pend.end(), next(end, pair_level - 1));
    }

    int prev_jacobsthal = _jacobsthal_number(1);
    int inserted_numbers = 0;
    for (int k = 2;; k++)
    {
        int curr_jacobsthal = _jacobsthal_number(k);
        int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
		int offset = 0;
        if (jacobsthal_diff > static_cast<int>(pend.size()))
            break;
        int nbr_of_times = jacobsthal_diff;
        std::vector<std::vector<int>::iterator>::iterator pend_it = next(pend.begin(), jacobsthal_diff - 1);
        std::vector<std::vector<int>::iterator>::iterator bound_it =
            next(main.begin(), curr_jacobsthal + inserted_numbers);
        while (nbr_of_times)
        {
            std::vector<std::vector<int>::iterator>::iterator idx =
                std::upper_bound(main.begin(), bound_it, *pend_it, _comp<std::vector<int>::iterator>);
            std::vector<std::vector<int>::iterator>::iterator inserted = main.insert(idx, *pend_it);
            nbr_of_times--;
            pend_it = pend.erase(pend_it);
            std::advance(pend_it, -1);
            offset += (inserted - main.begin()) == curr_jacobsthal + inserted_numbers;
			bound_it = next(main.begin(), curr_jacobsthal + inserted_numbers - offset);
        }
        prev_jacobsthal = curr_jacobsthal;
        inserted_numbers += jacobsthal_diff;
		offset = 0;
    }

    for (ssize_t i = pend.size() - 1; i >= 0; i--)
    {
        std::vector<std::vector<int>::iterator>::iterator curr_pend = next(pend.begin(), i);
        std::vector<std::vector<int>::iterator>::iterator curr_bound =
            next(main.begin(), main.size() - pend.size() + i + is_odd);
        std::vector<std::vector<int>::iterator>::iterator idx =
            std::upper_bound(main.begin(), curr_bound, *curr_pend, _comp<std::vector<int>::iterator>);
        main.insert(idx, *curr_pend);
    }

    std::vector<int> copy;
    copy.reserve(container.size());
    for (std::vector<std::vector<int>::iterator>::iterator it = main.begin(); it != main.end(); it++)
    {
        for (int i = 0; i < pair_level; i++)
        {
            std::vector<int>::iterator pair_start = *it;
            std::advance(pair_start, -pair_level + i + 1);
            copy.insert(copy.end(), *pair_start);
        }
    }

    std::vector<int>::iterator container_it = container.begin();
    std::vector<int>::iterator copy_it = copy.begin();
    while (copy_it != copy.end())
    {
        *container_it = *copy_it;
        container_it++;
        copy_it++;
    }
}

void	PmergeMe::merge_insertion_sort_deq(std::deque<int> &container, int pair_level)
{
    int pair_units_nbr = container.size() / pair_level;
    if (pair_units_nbr < 2)
        return;

    bool is_odd = pair_units_nbr % 2 == 1;

    std::deque<int>::iterator start = container.begin();
    std::deque<int>::iterator last = next(container.begin(), pair_level * (pair_units_nbr));
    std::deque<int>::iterator end = next(last, -(is_odd * pair_level));

    int jump = 2 * pair_level;
    for (std::deque<int>::iterator it = start; it != end; std::advance(it, jump))
    {
        std::deque<int>::iterator this_pair = next(it, pair_level - 1);
        std::deque<int>::iterator next_pair = next(it, pair_level * 2 - 1);
        if (_comp(next_pair, this_pair))
        {
            swap_pair(this_pair, pair_level);
        }
    }
    merge_insertion_sort_deq(container, pair_level * 2);

    std::deque<std::deque<int>::iterator> main;
    std::deque<std::deque<int>::iterator> pend;

    main.insert(main.end(), next(container.begin(), pair_level - 1));
    main.insert(main.end(), next(container.begin(), pair_level * 2 - 1));

    for (int i = 4; i <= pair_units_nbr; i += 2)
    {
        pend.insert(pend.end(), next(container.begin(), pair_level * (i - 1) - 1));
        main.insert(main.end(), next(container.begin(), pair_level * i - 1));
    }

    if (is_odd)
    {
        pend.insert(pend.end(), next(end, pair_level - 1));
    }

    int prev_jacobsthal = _jacobsthal_number(1);
    int inserted_numbers = 0;
    for (int k = 2;; k++)
    {
        int curr_jacobsthal = _jacobsthal_number(k);
        int jacobsthal_diff = curr_jacobsthal - prev_jacobsthal;
		int offset = 0;
        if (jacobsthal_diff > static_cast<int>(pend.size()))
            break;
        int nbr_of_times = jacobsthal_diff;
        std::deque<std::deque<int>::iterator>::iterator pend_it = next(pend.begin(), jacobsthal_diff - 1);
        std::deque<std::deque<int>::iterator>::iterator bound_it =
            next(main.begin(), curr_jacobsthal + inserted_numbers);
        while (nbr_of_times)
        {
            std::deque<std::deque<int>::iterator>::iterator idx =
                std::upper_bound(main.begin(), bound_it, *pend_it, _comp<std::deque<int>::iterator>);
            std::deque<std::deque<int>::iterator>::iterator inserted = main.insert(idx, *pend_it);
            nbr_of_times--;
            pend_it = pend.erase(pend_it);
            std::advance(pend_it, -1);
            offset += (inserted - main.begin()) == curr_jacobsthal + inserted_numbers;
			bound_it = next(main.begin(), curr_jacobsthal + inserted_numbers - offset);
        }
        prev_jacobsthal = curr_jacobsthal;
        inserted_numbers += jacobsthal_diff;
		offset = 0;
    }

    for (ssize_t i = pend.size() - 1; i >= 0; i--)
    {
        std::deque<std::deque<int>::iterator>::iterator curr_pend = next(pend.begin(), i);
        std::deque<std::deque<int>::iterator>::iterator curr_bound =
            next(main.begin(), main.size() - pend.size() + i + is_odd);
        std::deque<std::deque<int>::iterator>::iterator idx =
            std::upper_bound(main.begin(), curr_bound, *curr_pend, _comp<std::deque<int>::iterator>);
        main.insert(idx, *curr_pend);
    }

    std::deque<int> copy;
    for (std::deque<std::deque<int>::iterator>::iterator it = main.begin(); it != main.end(); it++)
    {
        for (int i = 0; i < pair_level; i++)
        {
            std::deque<int>::iterator pair_start = *it;
            std::advance(pair_start, -pair_level + i + 1);
            copy.insert(copy.end(), *pair_start);
        }
    }

    std::deque<int>::iterator container_it = container.begin();
    std::deque<int>::iterator copy_it = copy.begin();
    while (copy_it != copy.end())
    {
        *container_it = *copy_it;
        container_it++;
        copy_it++;
    }
}