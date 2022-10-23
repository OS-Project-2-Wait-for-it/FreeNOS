/*
 * Copyright (C) 2019 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIBSTD_PRIORITYQUEUE_H
#define __LIBSTD_PRIORITYQUEUE_H

#include "Types.h"
#include "Macros.h"
#include "Container.h"
#include "Process.h"

/**
 * @addtogroup lib
 * @{
 *
 * @addtogroup libstd
 * @{
 */

/**
 * Array of items as a First-In-First-Out (FIFO) datastructure.
 */
template <class T, Size N> class PriorityQueue : public Container
{
  public:

    /**
     * Default constructor
     */
    PriorityQueue()
    {
        clear();
    }

    /**
     * Add item to the head of the Queue.
     *
     * @param item The item to add
     *
     * @return True if successful, false otherwise
     */
    bool push(Process* item) //smaller number has higher priority
    {
        if (m_count >= N)
        {
            return false;
        }

        m_array[m_head] = item;
        m_head = (m_head + 1) % N;
        m_count++;

        return true;
    }

    /**
     * Sort elements in queue by process priority.
     *
     * @param item The item to add
     *
     * @return True if successful, false otherwise
     */
    void sort() {
        Process* minPri;
        for(uint i = 0; i < count(); i++) {
            int index1 = i;
            for(uint j = i; j < count(); i++) {
                int index2 = j;
                if(m_array[index1]->getPriority() > m_array[index2]->getPriority()) {
                    minPri = m_array[index1];
                    m_array[index1] = m_array[index2];
                    m_array[index2] = minPri;
                }
            }
        }
    }
    // void sort()
    // {
    //     Process* minPri;

    //     int placeHolder;
    //     for(int i=0; i<m_array.count()-1; i++)
    //     {
    //         for(int j = i; j<m_array.count(); j++)
    //         {
    //             if(m_array[i].m_priority > m_array[j].m_priority) //idk if this is right
    //             {
    //                 minPri = *m_array[i];
    //                 m_array[i] = m_array[j];
    //                 //placeHolder = j;
    //                 m_array[j] = *minPri;
    //             }
    //         }
    //         //m_array[placeHolder] = m_array[i];
    //         //m_array[i] = minPri;
    //     }
    // }

    /**
     * Remove item from the tail of the Queue.
     *
     * @return Item T
     *
     * @note Do not call this function if the Queue is empty
     */
    Process* & pop()
    {
        uint idx = m_tail;
        m_tail = (m_tail + 1) % N;
        m_count--;

        return m_array[idx];
    }

    /**
     * Look if an item exists on the Queue
     *
     * @param item Item reference
     *
     * @return True if the item exists, false otherwise
     */
    bool contains(const T & item) const
    {
        for (Size i = 0; i < m_count; i++)
        {
            if (m_array[(m_tail + i) % N] == item)
                return true;
        }

        return false;
    }

    /**
     * Remove all items with the given value.
     *
     * @param value Value to remove.
     *
     * @return Number of items removed.
     */
    Size remove(T value)
    {
        const Size numItems = m_count;
        Size numRemoved = 0;

        for (Size i = 0; i < numItems; i++)
        {
            T & item = pop();

            if (item != value)
                push(item);
            else
                numRemoved++;
        }

        return numRemoved;
    }

    /**
     * Removes all items from the Queue.
     */
    virtual void clear()
    {
        m_head = 0;
        m_tail = 0;
        m_count = 0;
    }

    /**
     * Returns the maximum size of this Queue.
     *
     * @return size The maximum size of the Queue.
     */
    virtual Size size() const
    {
        return N;
    }

    /**
     * Returns the number of items in the Queue.
     *
     * @return Number of items in the Queue.
     */
    virtual Size count() const
    {
        return m_count;
    }

  private:

    /** The actual array where the data is stored. */
    T m_array[N];

    /** Head of the queue */
    uint m_head;

    /** Tail of the queue */
    uint m_tail;

    /** Number of items in the queue */
    uint m_count;
};

/**
 * @}
 * @}
 */

#endif /* __LIBSTD_QUEUE_H */
