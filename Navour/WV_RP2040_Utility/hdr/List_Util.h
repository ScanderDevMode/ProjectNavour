#ifndef _RP2040_LIST_UTIL_HEADER_
#define _RP2040_LIST_UTIL_HEADER_

#include <stdlib.h>

/** \file WV_RP2040_Utility/List_Util.h
 *  \headerfile List_Util.h
 *  \defgroup WV_RP2040_List WV_RP2040_List api can be used to use List functionality.
 *  \author TheClownDev
 *
 *  \brief Api to use list functionality in code.
 *
 *  \subsection WV_RP2040_Utility APIs related to the WV_RP2040 HW.
 *  \addtogroup WV_RP2040_List
 *
 *  \include List_Util.h
*/

/*! \namespace WV_RP2040
 *  \brief Namespace for the WV_RP2040 APIs
 *  \subsection WV_RP2040_Utility
*/
namespace WV_RP2040 {

/*! \brief
 *  \ingroup WV_RP2040_List
 *  \class WV_RP2040_Node
 */
template<class T>
class WV_RP2040_Node {
private:
    T* data;

public:
    WV_RP2040_Node* next;
    WV_RP2040_Node* prev;
    
    /*! \brief Constructor
     *  \ingroup WV_RP2040_List
     */
    WV_RP2040_Node() : data(NULL), next(NULL), prev(NULL) {}

    /*! \brief Constructor
     *  \ingroup WV_RP2040_List
     */
    WV_RP2040_Node(const T& data) : data(new T(data)), next(NULL), prev(NULL) {}

    /*! \brief Copy Constructor
     *  \ingroup WV_RP2040_List
     */
    WV_RP2040_Node(const WV_RP2040_Node& reff) : data(NULL), next(NULL), prev(NULL) {
        if (reff.data) {
            this->data = new T(*(reff.data));
        }
    }

    /*! \brief Destructor
     *  \ingroup WV_RP2040_List
     */
    ~WV_RP2040_Node() {
        delete this->data;
    }

    /*! \brief Get Data
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Get the data of the node.
    *
    *   \return Returns the data stored in the node.
    */
    T getData() const {
        return *data;
    }

    /*! \brief Set Data
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Set the data of the node.
    */
    void setData(const T& data) {
        if (this->data)
            *(this->data) = data;
        else
            this->data = new T(data);
    }
};

/*!
 *  \ingroup WV_RP2040_List
 *  \class WV_RP2040_List
*/
template<class T>
class WV_RP2040_List {
private:
    int count;
    WV_RP2040_Node<T>* head;
    WV_RP2040_Node<T>* tail;

    bool isSorted;

    /*! \brief Merge two sorted lists into the current list
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Merge two sorted lists into the current list.
    */
    void merge(WV_RP2040_List<T>* left, WV_RP2040_List<T>* right) {
        int left_c = 1, right_c = 1, cursor = 1;

        while (left_c <= left->getCount() && right_c <= right->getCount()) {
            if (left->getNode(left_c)->getData() <= right->getNode(right_c)->getData()) {
                getNode(cursor)->setData(left->getNode(left_c)->getData());
                ++left_c;
            } else {
                getNode(cursor)->setData(right->getNode(right_c)->getData());
                ++right_c;
            }
            ++cursor;
        }

        while (left_c <= left->getCount()) {
            getNode(cursor)->setData(left->getNode(left_c)->getData());
            ++left_c;
            ++cursor;
        }

        while (right_c <= right->getCount()) {
            getNode(cursor)->setData(right->getNode(right_c)->getData());
            ++right_c;
            ++cursor;
        }

        delete left;
        delete right;
    }

public:

    /*! \brief Constructor
     *  \ingroup WV_RP2040_List
    */
    WV_RP2040_List() : count(0), head(NULL), tail(NULL), isSorted(false) {}

    /*! \brief Copy Constructor
     *  \ingroup WV_RP2040_List
     */
    WV_RP2040_List(const WV_RP2040_List& reff) : count(0), head(NULL), tail(NULL), isSorted(reff.isSorted) {
        WV_RP2040_Node<T>* node = reff.head;
        while (node) {
            append(node->getData());
            node = node->next;
        }
    }

    /*! \brief Operator =
     *  \ingroup WV_RP2040_List
    */
    WV_RP2040_List& operator=(const WV_RP2040_List& reff) {
        if (this != &reff) {
            clear();  // Clear existing nodes
            WV_RP2040_Node<T>* node = reff.head;
            while (node) {
                append(node->getData());
                node = node->next;
            }
            isSorted = reff.isSorted;
        }
        return *this;
    }

    /*! \brief Append
    *   \ingroup WV_RP2040_List
    *
    *   \category Global Function
    *
    *   Append a new node with the data at the end of the list.
    *
    *   \param data - The data of type T to be stored.
    *
    *   \return Returns the index of the new node, which should be size + 1.
    */
    int append(const T& data) {
        isSorted = false;

        if (count == 0) {
            head = new WV_RP2040_Node<T>(data);
            tail = head;
        } else {
            tail->next = new WV_RP2040_Node<T>(data);
            tail->next->prev = tail;
            tail = tail->next;
        }
        return ++count;
    }

    /*! \brief Prepend
    *   \ingroup WV_RP2040_List
    *
    *   \category Global Function
    *
    *   Prepend a new node with the data at the beginning of the list.
    *
    *   \param data - The data of type T to be stored.
    *
    *   \return Returns the index of the new node, which should be 1.
    */
    int prepend(const T& data) {
        isSorted = false;

        if (count == 0) {
            return append(data);
        } else {
            auto t = new WV_RP2040_Node<T>(data);
            t->next = head;
            head->prev = t;
            head = t;
            return ++count;
        }
    }

    /*! \brief Insert
    *   \ingroup WV_RP2040_List
    *
    *   \category Global Function
    *
    *   Insert a new node with the data at the specified position in the list.
    *
    *   \param data - The data of type T to be stored.
    *   \param pos - The position the data should be inserted to, 1 for beginning, count + 1 for appending
    *
    *   \return Returns the index of the new node, or -1 if the position is invalid.
    */
    int insert(const T& data, int pos) {
        if (pos < 1 || pos > count + 1) return -1;

        isSorted = false;

        if (pos == 1) {
            return prepend(data);
        } else if (pos == count + 1) {
            return append(data);
        } else {
            auto pt = getNode(pos - 1);
            auto t = new WV_RP2040_Node<T>(data);
            t->next = pt->next;
            t->prev = pt;
            pt->next->prev = t;
            pt->next = t;
            return ++count;
        }
    }

    /*! \brief Get Node
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Get the Node at position pos.
    *
    *   \param pos - The position of the node to be fetched. Starts from 1.
    *
    *   \return Returns a reference to the Node at the given position, or nullptr if the position is invalid.
    */
    WV_RP2040_Node<T>* getNode(int pos) const {
        if (pos < 1 || pos > count) return nullptr;

        if (pos == 1) return head;
        if (pos == count) return tail;

        WV_RP2040_Node<T>* t;
        int mid = count / 2;

        if (pos <= mid) {
            t = head;
            for (int i = 1; i < pos; ++i) {
                t = t->next;
            }
        } else {
            t = tail;
            for (int i = count; i > pos; --i) {
                t = t->prev;
            }
        }
        return t;
    }

    /*! \brief Get Count
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Get the total node count.
    *
    *   \return Returns the total count of list
    */
    int getCount() const {
        return count;
    }

    /*! \brief Get Sub Set
    *   \ingroup WV_RP2040_List
    *
    *   \category Global Function
    *
    *   Get the new subset list starting from the beginning and ending at end.
    *   Can be used to deep copy a list if 1 as beginning and count as ending.
    *
    *   \param begin - The starting index for the subset.
    *   \param end - The ending index for the subset.
    *
    *   \return Returns a new list if subset is possible, else returns NULL.
    */
    WV_RP2040_List<T>* getSubSet(int begin, int end) const {
        if (begin < 1 || end > count || begin > end) return NULL;

        auto t = new WV_RP2040_List<T>();
        for (int i = begin; i <= end; ++i) {
            t->append(getNode(i)->getData());
        }
        return t;
    }

    /*! \brief Merge Sort
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Sort the list with merge sort.
    */
    WV_RP2040_List<T>* mergeSort() {
        if (isSorted) return this;

        if (count < 2) {
            isSorted = true;
            return this;
        }

        int mid = count / 2;
        auto left = getSubSet(1, mid);
        auto right = getSubSet(mid + 1, count);

        left->mergeSort();
        right->mergeSort();

        merge(left, right);
        isSorted = true;

        //clean up
        delete left;
        delete right;

        return this;
    }

    /*! \brief Merge with another list
    *   \ingroup WV_RP2040_List
    *
    *   \category Global Function
    *
    *   Merge the current list with another list and sort the resulting list.
    *
    *   \param other - The other list to merge with.
    */
    void mergeWith(WV_RP2040_List<T>& other) {
        // Append nodes from the other list to this list
        WV_RP2040_Node<T>* node = other.head;
        while (node) {
            append(node->getData());
            node = node->next;
        }

        // Sort the combined list
        mergeSort();

        // Clear the other list
        other.clear();
    }

    /*! \brief Concatenate with another list
    *   \ingroup WV_RP2040_List
    *
    *   \category Global Function
    *
    *   Concatenate the current list with another list and return a new concatenated list.
    *
    *   \param other - The other list to concatenate with.
    *
    *   \return Returns a new list that is the concatenation of the current list and the other list.
    */
    WV_RP2040_List<T> concat(const WV_RP2040_List<T>& other) const {
        WV_RP2040_List<T> newList;

        // Add nodes from the current list to the new list
        WV_RP2040_Node<T>* node = head;
        while (node) {
            newList.append(node->getData());
            node = node->next;
        }

        // Add nodes from the other list to the new list
        node = other.head;
        while (node) {
            newList.append(node->getData());
            node = node->next;
        }

        return newList;
    }

    /*! \brief Split the list into two halves
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Splits the list into two halves.
    *
    *   \param start - The starting node of the list.
    *
    *   \return Returns the node at the beginning of the second half.
    */
    WV_RP2040_Node<T>* split(WV_RP2040_Node<T>* start) {
        WV_RP2040_Node<T>* slow = start;
        WV_RP2040_Node<T>* fast = start->next;

        while (fast != nullptr) {
            fast = fast->next;
            if (fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        WV_RP2040_Node<T>* second_half = slow->next;
        slow->next = nullptr;
        if (second_half != nullptr) {
            second_half->prev = nullptr;
        }

        return second_half;
    }

    /*! \brief Remove Last Node
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Remove the last node from the list.
    *
    *   \return Returns the total count of the list after removing the last node.
    */
    int removeLastNode() {
        if (count >= 1) {
            if (count == 1) {
                delete head;
                head = tail = NULL;
            } else {
                auto node = tail->prev;
                delete tail;
                tail = node;
                tail->next = NULL;
            }
            --count;
        }
        return count;
    }

    /*! \brief Remove First Node
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Remove the first node from the list.
    *
    *   \return Returns the total count of the list after removing the first node.
    */
    int removeFirstNode() {
        if (count >= 1) {
            if (count == 1) {
                delete head;
                head = tail = NULL;
            } else {
                auto node = head->next;
                delete head;
                head = node;
                head->prev = NULL;
            }
            --count;
        }
        return count;
    }

    /*! \brief Remove Node At
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Remove the node at position(pos) from the list.
    *
    *   \param pos - Position of the node to be deleted. 1 for the first Node, count for the last Node.
    *
    *   \return Returns the total count of the list after removing the node.
    */
    int removeNodeAt(int pos) {
        if (pos < 1 || pos > count) return -1;

        if (pos == 1) {
            return removeFirstNode();
        } else if (pos == count) {
            return removeLastNode();
        } else {
            auto node = getNode(pos);
            node->prev->next = node->next;
            node->next->prev = node->prev;
            delete node;
            --count;
        }
        return count;
    }

    /*! \brief Linear Search
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Searches for the value and returns the index of the first element that is found. Index starts from 1.
    *
    *   \param value - value to be found in the list.
    *
    *   \return Returns the index of the first element whose value is matching. Index starts from 1. Else returns -1.
    */
    int linearSearch(const T& value) const {
        int index = 1;
        WV_RP2040_Node<T>* node = head;
        while (node) {
            if (node->getData() == value) {
                return index;
            }
            node = node->next;
            ++index;
        }
        return -1;
    }

    /*! \brief operator[]
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   \return Returns the data at the given index. Returns 0 if out of bounds.
    */
    T operator[](const int& index) const {
        WV_RP2040_Node<T>* node = getNode(index + 1);
        return node ? node->getData() : T();
    }

    /*! \brief Binary Search
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Searches for the value and returns the index of the first element that is found. Index starts from 1.
    *
    *   \param value - value to be found in the list.
    *
    *   \param forceSearch - If the list is not sorted, then first sorts it, and then searches the value. If this is not turned on, returns -1.
    *
    *   \return Returns the index of the first element whose value is matching. Index starts from 1. Else returns -1.
    */
    int binarySearch(const T& value, bool forceSearch = false) {
        if (!isSorted && !forceSearch) return -1;

        if (count == 0) return -1;

        if (forceSearch || !isSorted) {
            mergeSort();
        }

        int left = 1;
        int right = count;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (getNode(mid)->getData() == value) {
                return mid;
            }

            if (getNode(mid)->getData() > value) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return -1;
    }

    /*! \brief Reverse List
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Reverses the list.
    */
    void reverseList() {
        if (count <= 1) return;

        WV_RP2040_Node<T>* current = head;
        WV_RP2040_Node<T>* temp = nullptr;

        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }

        if (temp) {
            head = temp->prev;
        }
    }

    /*! \brief Clear the list
    *   \ingroup WV_RP2040_List
    *
    *   \category Local Function
    *
    *   Clears the list by deleting all nodes.
    */
    void clear() {
        while (removeFirstNode() > 0);
    }

    /*! \brief Destructor
     *  \ingroup WV_RP2040_List
     */
    ~WV_RP2040_List() {
        clear();
    }
};

}

#endif
