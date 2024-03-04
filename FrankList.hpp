#ifndef _FRANKLIST_HPP__
#define _FRANKLIST_HPP__
#include "FrankList.h"

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

    // template <typename input_iterator>
    // FrankList(input_iterator f, input_iterator l); //O(n)

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
    return head->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::front()
{
    return head->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::back() const
{
    return tail->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::back() 
{
    return tail->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::min() const
{
    return descHead->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::min() 
{
    return descHead->data;
}

template <typename value_type> 
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::max() const
{
    return ascHead->data;
}  

template <typename value_type> 
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::max() 
{
    return ascHead->data;
}  


    // const FrankList<value_type>& operator=(const FrankList<value_type>& rhv); //O(n)
    // const FrankList<value_type>& operator=(FrankList<value_type>&& rhv); //O(n)
    // const FrankList<value_type>& operator=(std::initializer_list<value_type> init); //O(n)

    // bool operator==(const FrankList<value_type>& rhv) const; //O(n)
    // bool operator!=(const FrankList<value_type>& rhv) const; //O(n)
    // bool operator<(const FrankList<value_type>& rhv) const; //O(n)
    // bool operator<=(const FrankList<value_type>& rhv) const; //O(n)
    // bool operator>(const FrankList<value_type>& rhv) const; //O(n)
    // bool operator>=(const FrankList<value_type>& rhv) const; //O(n)
//-----------------------------------------------------------------------------------------
 
 //   size_type remove(const_reference val); //O(n)

//-----------------------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------------------
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

#endif // _FRANKLIST_HPP__