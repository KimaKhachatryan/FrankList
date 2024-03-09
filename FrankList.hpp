#ifndef _FRANKLIST_HPP__
#define _FRANKLIST_HPP__
#include <stdexcept>
#include "FrankList.h"

template <typename T>
std::ostream& operator<<(std::ostream& out, const monster::FrankList<T>& rhv)
{
    for (auto it = rhv.cbegin(); it != rhv.cend(); ++it) {
        out << *it << " ";
    }
    return out;
}

template <typename value_type>
monster::FrankList<value_type>::FrankList()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->ascHead = nullptr;
    this->descHead = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::FrankList(size_type size)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->ascHead = nullptr;
    this->descHead = nullptr;

    this->resize(size);  
}

template <typename value_type>
monster::FrankList<value_type>::FrankList(size_type size, const_reference init)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->ascHead = nullptr;
    this->descHead = nullptr;

    this->resize(size, init);  
}

template <typename value_type>
monster::FrankList<value_type>::FrankList(const FrankList<value_type>& rhv)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->ascHead = nullptr;
    this->descHead = nullptr;

    for (Node* tmp = rhv.head; tmp != nullptr; tmp = tmp->next) {
        this->push_back(tmp->data);
    }
}

template <typename value_type>
monster::FrankList<value_type>::FrankList(FrankList<value_type>&& rhv)
{
    this->head = rhv.head;
    this->tail = rhv.tail;
    this->ascHead = rhv.ascHead;
    this->descHead = rhv.descHead;

    rhv.head = nullptr;
    rhv.tail = nullptr;
    rhv.ascHead = nullptr;
    rhv.descHead = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::FrankList(std::initializer_list<value_type> init) 
{
    this->head = nullptr;
    this->tail = nullptr;
    this->ascHead = nullptr;
    this->descHead = nullptr;

    for (auto it = init.begin(); it != init.end(); ++it) {
        this->push_back(*it);
    }    
}

template <typename value_type>
template <typename input_iterator>
monster::FrankList<value_type>::FrankList(input_iterator f, input_iterator l)
{
    for (; f != l; ++f) {
        this->push_back(*f);
    }
}

template <typename value_type> 
monster::FrankList<value_type>::Node::Node()
{
    data = value_type();
    next = nullptr;
    prev = nullptr;
    asc = nullptr;
    desc = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::~FrankList()
{
    this->clear();
}

template <typename value_type> 
monster::FrankList<value_type>::Node::Node(value_type val)
{
    data = val;
    next = nullptr;
    prev = nullptr;
    asc = nullptr;
    desc = nullptr;
}

//--------------------------------------------------------------------

template <typename value_type>
void monster::FrankList<value_type>::swap(monster::FrankList<value_type>& rhv)
{
    std::swap(*this, rhv);
}

template <typename value_type>
std::size_t monster::FrankList<value_type>::size() const 
{
    size_type list_size = 0;
    Node* tmp = head;

    while (tmp) {
        tmp = tmp->next;
        ++list_size;
    }

    return list_size;
}

template <typename value_type>
bool monster::FrankList<value_type>::empty() const
{
    return (head == nullptr);
}

template <typename value_type>
void monster::FrankList<value_type>::resize(size_type s, const_reference init)
{
    if (size == 0) {
        this->clear();
    }

    size_type curent_size = this->size();
    if (s < curent_size) {
        for (size_type i = curent_size; i > s; --i) {
            this->pop_back();
        }
    } else if (s > curent_size) {
        for(size_type i = curent_size; i < s; ++i) {
            this->push_back(init);
        }
    } 
}

template <typename value_type>
void monster::FrankList<value_type>::clear() noexcept 
{
    if (head) {
        while (head->next) {
            head = head->next;
            delete head->prev;
        }

        delete head;
    }

    head = nullptr;
    tail = nullptr;
    ascHead = nullptr;
    descHead = nullptr;
}

template <typename value_type>
void monster::FrankList<value_type>::push_front(const_reference elem)
{
    if (!head) {
        head = new Node (elem);
        tail = head;
        ascHead = head;
        descHead = head;
        return;       
    }

    Node* tmp = head;
    tmp->prev = new Node(elem); 
    head = tmp->prev;
    head->next = tmp;

    put_in_sorted_order(head);
}

template <typename value_type> 
void monster::FrankList<value_type>::pop_front() 
{
    if (!head) {
        throw (std::out_of_range("Out of range!"));
    }

    if (head == ascHead) {
        head->asc->desc = nullptr;
        ascHead = head->asc;
    } else if (head == descHead) {
        head->desc->asc = nullptr;
        descHead = head->desc;
    } else {
        head->desc->asc = head->asc;
        head->asc->desc = head->desc;
    }

    head = head->next;
    delete head->prev;
    head->prev = nullptr;   
}

template <typename value_type>
void monster::FrankList<value_type>::push_back(const_reference elem)
{
    if (!head) {
        head = new Node (elem);
        tail = head;
        ascHead = head;
        descHead = head;
        return;
    }

    tail->next = new Node (elem);
    tail->next->prev = tail;
    tail = tail->next;
    
    put_in_sorted_order(tail);
    
}

template <typename value_type> 
void monster::FrankList<value_type>::pop_back() 
{
    if (!head) {
        throw (std::out_of_range("Out of range!"));
    }

    if (tail == ascHead) {
        tail->asc->desc = nullptr;
        ascHead = tail->asc;
    } else if (tail == descHead) {
        tail->desc->asc = nullptr;
        descHead = tail->desc;
    } else {
        tail->desc->asc = tail->asc;
        tail->asc->desc = tail->desc;
    }

    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::front() const
{
    if (!head) {
        throw (std::out_of_range("Out of range!"));
    }
    return head->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::front()
{
    if (!head) {
        throw (std::out_of_range("Out of range!"));
    }
    return head->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::back() const
{
    if (!head) {
        throw (std::out_of_range("Out of range!"));
    }
    return tail->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::back() 
{
    if (!head) {
        throw (std::out_of_range("Out of range!"));
    }
    return tail->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::min() const
{
    if (!head) {
        throw (std::out_of_range("Out of range!"));
    }
    return ascHead->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::min() 
{
    if (!head) {
        throw (std::out_of_range("Out of range!"));
    }
    return ascHead->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::max() const
{
    if (!head) {
        throw (std::out_of_range("Out of range!"));
    }
    return descHead->data;
}  

template <typename value_type> 
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::max() 
{
    if (!head) {
        throw (std::out_of_range("Out of range!"));
    }
    return descHead->data;
}  

template <typename value_type> 
const monster::FrankList<value_type>& monster::FrankList<value_type>::operator=(const FrankList<value_type>& rhv) 
{
    if (this != &rhv) {
        if (head) {
            this->clear();
        }

        this->head = nullptr;
        this->tail = nullptr;
        this->ascHead = nullptr;
        this->descHead = nullptr;

        for (Node* tmp = rhv.head; tmp != nullptr; tmp = tmp->next) {
            this->push_back(tmp->data);
        } 
    }

    return *this;
}

template <typename value_type>
const monster::FrankList<value_type>& monster::FrankList<value_type>::operator=(FrankList<value_type>&& rhv)
{
    if (this != &rhv) {
        if (head) {
            this->clear();
        }

        this->head = rhv.head;
        this->tail = rhv.tail;
        this->ascHead = rhv.ascHead;
        this->descHead = rhv.descHead;

        rhv.head = nullptr;
        rhv.tail = nullptr;
        rhv.ascHead = nullptr;
        rhv.descHead = nullptr;
    }

    return *this;
}

template <typename value_type> 
const monster::FrankList<value_type>& monster::FrankList<value_type>::operator=(std::initializer_list<value_type> init) 
{
    if (head) {
        this->clear();
    }

    for (auto it = init.begin(); it != init.end(); ++it) {
        this->push_back(*it);
    }  

    return *this;
}   

template <typename value_type> 
bool monster::FrankList<value_type>::operator==(const FrankList<value_type>& rhv) const
{
    Node* tmp_this = this->head;
    Node* tmp_rhv = rhv.head;

    while (tmp_rhv && tmp_this) {
        if (tmp_rhv->data != tmp_this->data) {
            return false;
        }

        tmp_rhv = tmp_rhv->next;
        tmp_this = tmp_this->next;
    }    

    return (tmp_rhv == nullptr && tmp_this == nullptr);
}

template <typename value_type> 
bool monster::FrankList<value_type>::operator!=(const FrankList<value_type>& rhv) const
{
    return !this->operator==(rhv);
}

template <typename value_type> 
bool monster::FrankList<value_type>::operator<(const FrankList<value_type>& rhv) const
{
    Node* tmp_this = this->head;
    Node* tmp_rhv = rhv.head;

    while (tmp_rhv && tmp_this) {
        if (tmp_rhv->data > tmp_this->data) {
            return false;
        }

        tmp_rhv = tmp_rhv->next;
        tmp_this = tmp_this->next;
    } 

    return (tmp_rhv && !tmp_this);
}

template <typename value_type> 
bool monster::FrankList<value_type>::operator>(const FrankList<value_type>& rhv) const
{
    Node* tmp_this = this->head;
    Node* tmp_rhv = rhv.head;

    while (tmp_rhv && tmp_this) {
        if (tmp_rhv->data < tmp_this->data) {
            return false;
        }

        tmp_rhv = tmp_rhv->next;
        tmp_this = tmp_this->next;
    } 

    return (!tmp_rhv && tmp_this);
}

template <typename value_type> 
bool monster::FrankList<value_type>::operator>=(const FrankList<value_type>& rhv) const
{
    return !this->operator<();
}

template <typename value_type> 
bool monster::FrankList<value_type>::operator<=(const FrankList<value_type>& rhv) const
{
    return !this->operator>();
}

//-----------------------------------------------------------------------------------------
template <typename value_type> 
typename monster::FrankList<value_type>::const_iterator monster::FrankList<value_type>::cbegin() const
{
    return const_iterator(this->head);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_iterator monster::FrankList<value_type>::cend() const
{
    return const_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_reverse_iterator monster::FrankList<value_type>::crbegin() const
{
    return const_reverse_iterator(this->tail);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_reverse_iterator monster::FrankList<value_type>::crend() const
{
    return const_reverse_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_asc_iterator monster::FrankList<value_type>::cabegin() const
{
    return const_asc_iterator(this->ascHead);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_asc_iterator monster::FrankList<value_type>::caend() const
{
    return const_asc_iterator(nullptr);
}
template <typename value_type> 
typename monster::FrankList<value_type>::const_desc_iterator monster::FrankList<value_type>::cdbegin() const
{
    return const_desc_iterator(this->descHead);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_desc_iterator monster::FrankList<value_type>::cdend() const
{
    return const_desc_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_multi_iterator monster::FrankList<value_type>::cmbegin() const
{
    return const_multi_iterator(this->head);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_multi_iterator monster::FrankList<value_type>::cmend() const
{
    return const_multi_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_multi_iterator monster::FrankList<value_type>::cmabegin() const
{
    return const_multi_iterator(this->ascHead);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_multi_iterator monster::FrankList<value_type>::cmaend() const
{
    return const_multi_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_multi_reverse_iterator monster::FrankList<value_type>::cmrbegin() const
{
    return const_multi_reverse_iterator(this->tail);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_multi_reverse_iterator monster::FrankList<value_type>::cmrend() const
{
    return const_multi_reverse_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_multi_reverse_iterator monster::FrankList<value_type>::cmrdbegin() const
{
    return const_multi_reverse_iterator(this->descHead);
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_multi_reverse_iterator monster::FrankList<value_type>::cmrdend() const
{
    return const_multi_reverse_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::iterator monster::FrankList<value_type>::begin() 
{
    return iterator(this->head);
}

template <typename value_type> 
typename monster::FrankList<value_type>::iterator monster::FrankList<value_type>::end()
{
    return iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::reverse_iterator monster::FrankList<value_type>::rbegin() 
{
    return reverse_iterator(this->tail);
}

template <typename value_type> 
typename monster::FrankList<value_type>::reverse_iterator monster::FrankList<value_type>::rend()
{
    return reverse_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::asc_iterator monster::FrankList<value_type>::abegin()
{
    return asc_iterator(this->ascHead);
}

template <typename value_type> 
typename monster::FrankList<value_type>::asc_iterator monster::FrankList<value_type>::aend() 
{
    return asc_iterator(nullptr);
}
template <typename value_type> 
typename monster::FrankList<value_type>::desc_iterator monster::FrankList<value_type>::dbegin()
{
    return desc_iterator(this->descHead);
}

template <typename value_type> 
typename monster::FrankList<value_type>::desc_iterator monster::FrankList<value_type>::dend() 
{
    return desc_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::multi_iterator monster::FrankList<value_type>::mbegin() 
{
    return multi_iterator(this->head);
}

template <typename value_type> 
typename monster::FrankList<value_type>::multi_iterator monster::FrankList<value_type>::mend() 
{
    return multi_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::multi_iterator monster::FrankList<value_type>::mabegin()
{
    return const_multi_iterator(this->ascHead);
}

template <typename value_type> 
typename monster::FrankList<value_type>::multi_iterator monster::FrankList<value_type>::maend() 
{
    return const_multi_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::multi_reverse_iterator monster::FrankList<value_type>::mrbegin() 
{
    return multi_reverse_iterator(this->tail);
}

template <typename value_type> 
typename monster::FrankList<value_type>::multi_reverse_iterator monster::FrankList<value_type>::mrend()
{
    return const_multi_reverse_iterator(nullptr);
}

template <typename value_type> 
typename monster::FrankList<value_type>::multi_reverse_iterator monster::FrankList<value_type>::mrdbegin() 
{
    return multi_reverse_iterator(this->descHead);
}

template <typename value_type> 
typename monster::FrankList<value_type>::multi_reverse_iterator monster::FrankList<value_type>::mrdend()
{
    return const_multi_reverse_iterator(nullptr);
}

//-----------------------------------------------------------------------------------------

template <typename value_type> 
template <typename iter>
iter monster::FrankList<value_type>::insert(iter pos, size_type size, const_reference val)
{
    if (!size) {
        return pos;
    }

    for (size_type i = 0; i < size; ++i) {
        pos = insert_def(pos, val);
    }

    return pos;
}

template <typename value_type> 
template <typename iter>
iter monster::FrankList<value_type>::insert(iter pos, std::initializer_list<value_type> init)
{
    for (auto it = init.begin(); it != init.end(); ++it) {
        pos = insert(pos, *it);
    }

    return pos;
}

template <typename value_type> 
template <typename iter, typename input_iterator>
iter monster::FrankList<value_type>::insert(iter pos, input_iterator f, input_iterator l)
{
    for (; f!= l; ++f) {
        pos = insert(pos, *f);
    }

    return pos;
}

template <typename value_type> 
template <typename iter>
iter monster::FrankList<value_type>::erase(iter pos) 
{
    if (pos.ptr == head) {
        ++pos;
        this->pop_front();
    } else if (pos.ptr == tail) {
        ++pos;
        this->pop_back();
    } else {
        Node* removeable = pos.ptr;
        pos.ptr = removeable->next;
        removeable->prev->next = removeable->next;
        removeable->next->prev = removeable->prev;
        removeable->asc->desc = removeable->desc;

        if (removeable == ascHead) {
            removeable->asc->desc = nullptr;
            ascHead = removeable->asc;
        } else if (removeable == descHead) {
            removeable->desc->asc = nullptr;
            descHead = tail->desc;
        } else {
            removeable->desc->asc = removeable->asc;
            removeable->asc->desc = removeable->desc;
        }

        delete removeable; 
    }

    return pos;
}
 
template <typename value_type> 
template <typename iter>
iter monster::FrankList<value_type>::erase(iter f, iter l)
{
    for (; f != l; f = this->erase(f)) 
    {}

    return f;
}

template <typename value_type> 
typename monster::FrankList<value_type>::size_type monster::FrankList<value_type>::remove(const_reference val)
{
    size_type count = 0;
    if (val == head->data) {
        this->pop_front;
    } else if (val == tail->data) {
        this->pop_back();
    }

    Node* tmp = head;
    while (tmp) {
        if (val == tmp->data) {
            monster::FrankList<value_type>::iterator it(tmp);
            this->erase(it);
            ++count;
        }
        tmp = tmp->next;
    }

    return count;
}

template <typename value_type>
template <typename unary_predicate>
monster::FrankList<value_type>::size_type monster::FrankList<value_type>::remove_if(unary_predicate func)
{
    size_type count = 0;
    for (iterator it = this->begin(); it != this->end();) {
        if (func(*it)) {
            it = this->erase(it);
            ++count;
        } else {
            ++it;
        }
    }

    return count;
}

template <typename value_type>
void monster::FrankList<value_type>::reverse()
{
    std::swap(tail, head);

    Node* tmp = head;

    while (tmp) {
        std::swap(tmp->next, tmp->prev);
        tmp = tmp->next;
    }
}

template <typename value_type>
void monster::FrankList<value_type>::sort(bool reversed) 
{
    Node* tmp = nullptr;
    if (!reversed) {
        tmp = ascHead;

        while (tmp)
        {
            tmp->next = tmp->asc;
            tmp->prev = tmp->desc;
            tmp = tmp->asc;
        }

        head = ascHead;
        tail = descHead; 
    } else {
        tmp = descHead;

        while (tmp)
        {
            tmp->next = tmp->desc;
            tmp->prev = tmp->asc;
            tmp = tmp->desc;
        }

        head = descHead;
        tail = ascHead; 
    }
}

template <typename value_type>
monster::FrankList<value_type>::iterator monster::FrankList<value_type>::find(const_reference elem)
{
    if (elem == head->data) {
        return this->begin();
    } 

    for (auto it = begin(); it != end(); ++it) {
        if (*it == elem) {
            this->organize_left(it.ptr);
            return it;
        }
    }

    return this->end();
}

template <typename value_type>
monster::FrankList<value_type>::iterator monster::FrankList<value_type>::rfind(const_reference elem)
{
    if (elem == tail->data) {
        return this->rbegin();
    }

    for (auto it = rbegin(); it != rend(); ++it) {
        if (*it == elem) {
            this->organize_right(it.ptr);
            return it;
        }
    }

    return this->rend();
}

template <typename value_type>
template <typename unary_predicate>
void monster::FrankList<value_type>::traverse(unary_predicate func, bool sorted, bool reversed)
{
    if (reversed) {
        if (sorted) {
            auto it = dbegin();
            for (; it != dend(); ++it) {
                func(*it);
            }
        } else {
            auto it = rbegin();
            for (; it != rend(); ++it) {
                func(*it);
            }
        }
    } else {
        if (sorted) {
            auto it = abegin();
            for (; it != aend(); ++it) {
                func(*it);
            }
        } else {
            auto it = begin();
            for (; it != end(); ++it) {
                func(*it);
            }
        }
    }
}

//-----------------------------------------------------------------------------------------
template <typename value_type>
void monster::FrankList<value_type>::print(bool sorted, bool reversed)
{
    Node* tmp = nullptr;

    if (sorted && reversed) {
        tmp = descHead;
        while (tmp)
        {
            std::cout << tmp->data << " ";
            tmp = tmp->desc;
        }     
    } else if (sorted && !reversed) {
        tmp = ascHead;
        while (tmp)
        {
            std::cout << tmp->data << " ";
            tmp = tmp->asc;
        }        
    } else if (!sorted && reversed) {
        tmp = tail;
        while (tmp)
        {
            std::cout << tmp->data << " ";
            tmp = tmp->prev;
        }  
    } else {
        tmp = head;
        while (tmp)
        {
            std::cout << tmp->data << " ";
            tmp = tmp->next;
        }  
    }

    std::cout << std::endl;
}

template <typename value_type>
void monster::FrankList<value_type>::put_in_sorted_order(Node* ptr)
{
    if (ptr->data <= ascHead->data) {
        ascHead->desc = ptr;
        ptr->asc = ascHead;
        ascHead = ptr;
    } else if (ptr->data > descHead->data) {
        descHead->asc = ptr;
        ptr->desc = descHead;
        descHead = ptr;
    } else {
        Node* tmp = ascHead;
        while(tmp->data < ptr->data) {
            tmp = tmp->asc;
        }

        tmp->desc->asc = ptr;
        ptr->desc = tmp->desc;
        tmp->desc = ptr;
        ptr->asc = tmp;
    }
}

template <typename value_type>
void monster::FrankList<value_type>::organize_left(Node* ptr)
{
    Node* tmp = ptr->next;
    ptr->next = ptr->prev;
    ptr->next->next = tmp;
    if (tmp) {
        tmp->prev = ptr->next;
    }    
    tmp = ptr->next->prev;
    ptr->next->prev = ptr;
    ptr->prev = tmp;
    if (tmp) {
        tmp->next = ptr;
    }

    if (head == ptr->next) {
        head = ptr;
    } if (tail == ptr) {
        tail = ptr->next;
    }
}

template <typename value_type>
void monster::FrankList<value_type>::organize_right(Node* ptr)
{
    Node* tmp = ptr->prev;
    ptr->prev = ptr->next;
    ptr->prev->prev = tmp;
    if (tmp) {
        tmp->next = ptr->prev;
    }    
    tmp = ptr->prev->next;
    ptr->prev->next = ptr;
    ptr->next = tmp;
    if (tmp) {
        tmp->prev = ptr;
    }

    if (head == ptr) {
        head = ptr->prev;
    } if (tail == ptr->prev) {
        tail = ptr;
    }
}

template <typename value_type>
template <typename iter>
iter monster::FrankList<value_type>::insert_def(iter pos, const_reference val)
{   
    //if pos is equal to begin() and list is empty
    if (!head) {
        if (!pos.ptr) {                             
            this->push_back(val);
            pos.ptr = tail;
            return pos;
        } else {
            throw (std::out_of_range("Out of range!"));
        }
    } 
    
    if (pos.ptr == head) {
        this->push_front(val);
    } else {
        Node* cur_node = pos.ptr;
        //in case of when pos = end()
        if (!cur_node) {
            this->push_back(val);
            return pos;
        }
        Node* tmp = cur_node->prev;
        cur_node->prev = new Node(val);
        cur_node->prev->next = cur_node;
        cur_node->prev->prev = tmp;
        tmp->next = cur_node->prev;

        put_in_sorted_order(cur_node->prev);
    }
    return pos;
}  

template <typename value_type>
template <typename iter>
iter monster::FrankList<value_type>::insert_rev(iter pos, const_reference val)
{   
    //if pos is equal to begin() and list is empty
    if (!head) {
        if (!pos.ptr) {                             
            this->push_back(val);
            pos.ptr = tail;
            return pos;
        } else {
            throw (std::out_of_range("Out of range!"));
        }
    } 
    
    if (pos.ptr == head) {
        this->push_front(val);
    } else {
        Node* cur_node = pos.ptr;
        //in case of pos == end()
        if (!cur_node) {
            this->push_back(val);
            return pos;
        }
        Node* tmp = cur_node->prev;
        cur_node->prev = new Node(val);
        cur_node->prev->next = cur_node;
        cur_node->prev->prev = tmp;
        tmp->next = cur_node->prev;

        put_in_sorted_order(cur_node->prev);
    }
    return ++pos;
} 

#include "iterators.hpp"
#endif // _FRANKLIST_HPP__