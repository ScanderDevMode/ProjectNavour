#ifndef _RP2040_LIST_UTIL_HEADER_

#define _RP2040_LIST_UTIL_HEADER_

//#include <stdio.h>
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
 *  \brief Namspace for the WV_RP2040 APIs
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
        WV_RP2040_Node() :
            data(NULL), next(NULL), prev(NULL) 
        {
        }

        /*! \brief Constructor
         *  \ingroup WV_RP2040_List
         */
        WV_RP2040_Node(const T& data) :
            data(NULL), next(NULL), prev(NULL)
        {
            this->data = new T(data);
        }

        /*! \brief Copy Constructor
         *  \ingroup WV_RP2040_List
         */
        WV_RP2040_Node(const WV_RP2040_Node& reff) :
            data(NULL), next(NULL), prev(NULL)
        {
            this->data = new T(reff->data);
        }

        /*! \brief Destructor
         *  \ingroup WV_RP2040_List
         */
        ~WV_RP2040_Node() {
            this->next = NULL;
            delete(this->data);
        }

        /*! \brief Get Data
        *   \ingroup WV_RP2040_List
        *
        *   \category local Function
        *
        *   Get the data of the node.
        *
        *   \return Returns the data stored in the node.
        */
        T getData() {
            return *data;
        }

        /*! \brief Set Data
        *   \ingroup WV_RP2040_List
        *
        *   \category local Function
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

    public:

        /*! \brief Constructor
         *  \ingroup WV_RP2040_List
        */
        WV_RP2040_List() :
            count(0), head(NULL), tail(NULL)
        {
        }

        /*! \brief Copy Constructor
         *  \ingroup WV_RP2040_List
         */
        WV_RP2040_List(const WV_RP2040_List& reff) :
            count(0), head(NULL), tail(NULL)
        {
            this->count = reff.count;
            for (int i = 0; i < count; i++) {
                append(reff.getNode(i).getData());
            }
        }

        /*! \brief Operator =
         *  \ingroup WV_RP2040_List
        */
        WV_RP2040_List& operator=(const WV_RP2040_List& reff) {
            if (this != &reff) {
                WV_RP2040_Node<T>* node = reff.head;
                while (node != nullptr) {
                    this->append(node->data);
                    node = node->next;
                }
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
                count++;
                return 1;
            }
            else {
                tail->next = new WV_RP2040_Node<T>(data);
                tail->next->prev = tail;
                tail = tail->next;
                count++;
                return count;
            }
        }

        /*! \brief Prepend
        *   \ingroup WV_RP2040_List
        *
        *   \category Global Function
        *
        *   Prepend a new node with the data at the begining of the list.
        *
        *   \param data - The data of type T to be stored.
        *
        *   \return Returns the index of the new node, which should be 1.
        */
        int prepend(const T& data) {
            isSorted = false;

            if (count == 0) {
                return append(data);
            }
            else {
                auto t = new WV_RP2040_Node<T>(data);
                t->next = head;
                head->prev = t;
                head = t;
                count++;
                return 1;
            }
        }

        /*! \brief insert
        *   \ingroup WV_RP2040_List
        *
        *   \category Global Function
        *
        *   Append a new node with the data at the end of the list.
        *
        *   \param data - The data of type T to be stored.
        *   \param pos - The position the data should be inserted to, 1 for begining, count + 1 for appending
        *
        *   \return Returns the index of the new node, which should be size + 1.
        */
        int insert(const T& data, int pos) {
            if (count + 1 < pos || pos < 1)
                return -1;

            isSorted = false;

            if (pos == 1) {
                return prepend(data);
            }
            else if (pos == count + 1) {
                return append(data);
            }
            else {
                auto pt = getNode(pos - 1);
                auto t = new WV_RP2040_Node<T>(data);
                pt->next->prev = t;
                t->next = pt->next;
                t->prev = pt;
                pt->next = t;
                count++;
                return pos;
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
        *   \return Returns a refference to the Node at the given position.
        */
        WV_RP2040_Node<T>* getNode(int pos) {
            if (pos > count || pos < 1)
            return NULL;

            int mid = count / 2;

            if (pos == 1) {
                return head;
            }
            else if (pos == count) {
                return tail;
            }
            else if (pos > mid) {
                //start from tail and go backwards
                auto t = tail;
                for (int i = count; i > pos; i--) {
                    t = t->prev;
                }

                return t;
            }
            else {
                //start from the head and go forward
                auto t = head;
                for (int i = 1; i < pos; i++) {
                    t = t->next;
                }

                return t;
            }
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
        int getCount() {
            return count;
        }

        /*! \brief Get Sub Set
        *   \ingroup WV_RP2040_List
        *
        *   \category Global Function
        *
        *   Get the new subset list starting from the begining and ending at end.
        *   Can be used to deep copy a list if 1 as beginging and count as ending.
        *
        *   \param list - The list to get the subset from.
        *   \param begin - The starting index for the subset.
        *   \param end - The ending index for the subset.
        *
        *   \return Returns a new list if subset is possible, else returns NULL.
        */
        WV_RP2040_List<T>* getSubSet(int begin, int end) {
            if (begin > getCount() || end > getCount() || begin < 0) {
                return NULL;
            }
            
            if (begin > end) {
                begin = begin + end;
                end = begin - end;
                begin = begin - end;
            }
            
            auto t = new WV_RP2040_List<T>();

            if (begin == end) {
                t->append(getNode(begin)->getData());
                return t;
            }
            else {
                for (; begin <= end; begin++) {
                    t->append(getNode(begin)->getData());
                }
                return t;
            }
        }

        /*! \brief Merge Sort
        *   \ingroup WV_RP2040_List
        *
        *   \category Local Function
        *
        *   Sort the list with merge sort.
        *
        *   \param list - The list to be sorted.
        *   \param left - The index of the node to start sorting from. Can be 1 to start from the begining.
        *   \param right - The index of the node to end sorting at. Can be the list->count to end at the last node.
        */
        WV_RP2040_List<T>* mergeSort() {
            if (isSorted)
                return this;

            int count = getCount();

            if (count < 2) {
                isSorted = true;
                return this;
            }
            else {
                int mid = count / 2;
                int left_c = 0;
                int right_c = 0;
                int cursor = 1;
                auto left = getSubSet(1, mid);
                auto right = getSubSet(mid + 1, count);

                left->mergeSort();
                right->mergeSort();

                //sort and merge
                while (left_c < left->getCount() && right_c < right->getCount()) {
                    if (left->getNode(left_c + 1)->getData() <= right->getNode(right_c + 1)->getData()) {
                        if (getNode(cursor)->getData() != left->getNode(left_c + 1)->getData()) {
                            /*removeNodeAt(cursor);
                            insert(left->getNode(left_c + 1)->getData(), cursor);*/
                            getNode(cursor)->setData(left->getNode(left_c + 1)->getData());
                        }
                        left_c++;
                        cursor++;
                    }
                    else {
                        if (getNode(cursor)->getData() != right->getNode(right_c + 1)->getData()) {
                            /*removeNodeAt(cursor);
                            insert(right->getNode(right_c + 1)->getData(), cursor);*/
                            getNode(cursor)->setData(right->getNode(right_c + 1)->getData());
                        }
                        right_c++;
                        cursor++;
                    }
                }

                if (left_c < left->getCount() && cursor <= count) {
                    for (; left_c < left->getCount(); left_c++, cursor++) {
                        if (getNode(cursor)->getData() != left->getNode(left_c + 1)->getData()) {
                            /*removeNodeAt(cursor);
                            insert(left->getNode(left_c + 1)->getData(), cursor);*/
                            getNode(cursor)->setData(left->getNode(left_c + 1)->getData());
                        }
                    }
                }
                else if (right_c < right->getCount() && cursor <= count) {
                    for (; right_c < right->getCount(); right_c++, cursor++) {
                        if (getNode(cursor)->getData() != right->getNode(right_c + 1)->getData()) {
                            /*removeNodeAt(cursor);
                            insert(right->getNode(right_c + 1)->getData(), cursor);*/
                            getNode(cursor)->setData(left->getNode(right_c + 1)->getData());
                        }
                    }
                }

                delete left;
                delete right;

                isSorted = true;

                return this;
            }
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
                    delete(head);
                    head = tail = NULL;
                    count--;
                }
                else if (count == 2) {
                    delete(tail);
                    tail = head;
                    head->next = head->prev = NULL;
                    count--;
                }
                else {
                    auto node = getNode(count - 1);
                    node->next = NULL;
                    delete(tail);
                    tail = node;
                    count--;
                }
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
                    delete(head);
                    head = tail = NULL;
                    count--;
                }
                else if (count == 2) {
                    delete(head);
                    head = tail;
                    head->next = head->prev = NULL;
                    count--;
                }
                else {
                    auto node = head->next;
                    delete(head);
                    head = node;
                    node->prev = NULL;
                    count--;
                }
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
            if (pos > count || pos < 0)
                return -1;

            if (pos == 1)
                return removeFirstNode();
            else if (pos == count)
                return removeLastNode();
            else {
                auto t = getNode(pos - 1);
                auto tn = t->next;
                t->next = tn->next;
                tn->next->prev = t;
                delete(tn);
                count--;
            }
            return count;
        }

        //add search api
        
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
        int linearSearch( const T& value ) {
            int begin = 1;
            while (begin <= this->count) {
                if (getNode(begin)->getData() == value)
                    return begin;
                begin++;
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
        T operator[] (const int& index) {
            if (!getNode(index + 1))
                return 0;
            return getNode(index + 1)->getData();
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
        T binarySearch(const T& value, bool forceSearch) {
            if (!isSorted && !forceSearch)
                return -1;

            // Check if the list is empty
            if (this->count == 0)
                return -1;

            // If forceSearch is true or the list is not sorted, sort it using mergeSort
            if (forceSearch || !isSorted)
                mergeSort();

            int left = 1;
            int right = this->count;

            while (left <= right) { // Change condition to include equality
                int mid = left + (right - left) / 2; // Calculate mid index correctly

                if (getNode(mid)->getData() == value)
                    return mid;

                if (getNode(mid)->getData() > value)
                    right = mid - 1;
                else
                    left = mid + 1;
            }

            return -1; // Value not found
        }

        /*! \brief Reverse List
        *   \ingroup WV_RP2040_List
        *
        *   \category Local Function
        *
        *   Reverses the list.
        */
        void reverseList() {
            
            if (this->count <= 1)
                return;

            //copy the list
            WV_RP2040_List _t(this);
            
            for (int c = 1, j = this->count; c <= this->count; c++, j--) {
                getNode(c)->setData(_t.getNode(j)->getData());
            }
        }



        /*! \brief Destructor
         *  \ingroup WV_RP2040_List
         */
        ~WV_RP2040_List() {
            while (removeFirstNode() > 0);
        }
    };
}

#endif