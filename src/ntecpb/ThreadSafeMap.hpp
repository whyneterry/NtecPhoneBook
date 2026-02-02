#pragma once

#include "hash/djb2.hpp"
#include "dto/DTOs.hpp"
#include "dto/DTOUtils.hpp"
#include <map>
#include <iterator>
#include <thread>
#include <shared_mutex>
#include <optional>
#include <iostream>

namespace NTEC {
// Abstract ThreadSafeMap template class 
template <typename Key, typename Object>
class ThreadSafeMap
{
public:
	// Standart using type for self-writed containers
	using value_type = std::pair<const Key, Object>;
	using reference = value_type&;
	using const_reference = const value_type&;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

	using container_t = std::map<Key, Object>;

	std::optional<value_type> find(Key id) const;
	bool insert(const std::pair<Key, Object>& insertValue);
	size_type erase(Key id);
    bool empty() const;
	container_t copy() const;
	std::shared_ptr<container_t> copyAsShared() const;

protected:
	container_t m_phoneBook;
	mutable std::shared_mutex m_mutex;
};

template <typename Key, typename Object>
std::optional<typename ThreadSafeMap<Key, Object>::value_type> ThreadSafeMap<Key, Object>::find(Key id) const
{
	std::shared_lock lock(m_mutex);
	auto container_iterator = m_phoneBook.find(id);
	if (container_iterator != std::end(m_phoneBook))
	{
		return { *container_iterator };
	}

	return std::nullopt;
}

template <typename Key, typename Object>
bool ThreadSafeMap<Key, Object>::insert(const std::pair<Key, Object>& insertValue)
{
	std::unique_lock lock(m_mutex);
	auto [iterator, isInserted] = m_phoneBook.insert(insertValue);
	return isInserted;
}

template <typename Key, typename Object>
typename ThreadSafeMap<Key, Object>::size_type ThreadSafeMap<Key, Object>::erase(Key id)
{
	std::unique_lock lock(m_mutex);
	return m_phoneBook.erase(id);
}

template <typename Key, typename Object>
bool ThreadSafeMap<Key, Object>::empty() const
{
	std::shared_lock lock(m_mutex);
    return m_phoneBook.empty();
}

// Deep copy of phoneBook map
template <typename Key, typename Object>
typename ThreadSafeMap<Key, Object>::container_t ThreadSafeMap<Key, Object>::copy() const
{
	std::shared_lock lock(m_mutex);
	return { m_phoneBook };
}

// Copies only structure of phoneBook map and doesn't copy each Object DTO because DTOs are shared_ptrs themselves
template <typename Key, typename Object>
std::shared_ptr<typename ThreadSafeMap<Key, Object>::container_t> ThreadSafeMap<Key, Object>::copyAsShared() const
{
	std::shared_lock lock(m_mutex);
	return std::make_shared<container_t>(m_phoneBook);
}

// Specific ThreadSafeMapPhoneBook class that inherits base methods from ThreadSafeMap and provides specific
// update method
class ThreadSafeMapPhoneBook : public ThreadSafeMap<unsigned, oatpp::Object<RequestContactCreateDto>>
{
public:
	const unsigned update(const unsigned id, const oatpp::Object<RequestContactCreateDto>& newRequestContactCreateDto)
	{
		std::unique_lock lock(m_mutex);

		auto contactToUpdateIterator = m_phoneBook.find(id);
		if (contactToUpdateIterator == std::end(m_phoneBook))
		{
			throw std::invalid_argument("Key wasn't found in the ThreadSafeMap.");
		}

		auto wasNameChanged = DTOUtils::copyRequestToRequest(newRequestContactCreateDto, contactToUpdateIterator->second);
		auto newId = contactToUpdateIterator->first;
		
		if (wasNameChanged)
		{
			// If name was changed we probably should rebuild the PhoneBook, because new personName requires new ID
			newId = djb2hash(contactToUpdateIterator->second->personName);
			// If newId is equal to oldId it means that user changed name to the same one, so we're done with updating
			if (newId == id) { return newId; }
			// Next we should check that the new name that user provided is not already in the PhoneBook
			auto isExistingContactIterator = m_phoneBook.find(newId);
			if (isExistingContactIterator != std::end(m_phoneBook))
			{
				throw std::invalid_argument("User tried to change name to already existing one.");
			}
			// Now we know that user provided original new name and we can safely rebuild the PhoneBook
			m_phoneBook.insert({newId, contactToUpdateIterator->second});
			m_phoneBook.erase(contactToUpdateIterator->first);
		}
		return newId;
	}
};

}