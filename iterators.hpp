#ifndef _ITERATOR_HPP__
#define _ITERATOR_HPP__

#include "FrankList.h"

////BASE_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::base_iterator::base_iterator(Node* ptr) :
    ptr(this->head) 
{
}

template <typename value_type>
monster::FrankList<value_type>::base_iterator::~base_iterator()
{
    this->ptr = nullptr;
} 

template <typename value_type>
bool monster::FrankList<value_type>::base_iterator::operator==(const base_iterator& rhv) const
{
    return this->ptr == rhv.ptr;
} 

template <typename value_type>
bool monster::FrankList<value_type>::base_iterator::operator!=(const base_iterator& rhv) const
{
    return this->ptr != rhv.ptr;
} 

////CONST_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::const_iterator::const_iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::const_iterator::const_iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::const_iterator::const_iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_iterator& monster::FrankList<value_type>::const_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_iterator& monster::FrankList<value_type>::const_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::const_iterator::operator*() const
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_pointer monster::FrankList<value_type>::const_iterator::operator->() const
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_iterator& monster::FrankList<value_type>::const_iterator::operator++() 
{
    this->ptr = this->ptr->next;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_iterator monster::FrankList<value_type>::const_iterator::operator++(value_type) 
{
    monster::FrankList<value_type>::const_iterator tmp = *this;
    this->ptr = this->ptr->next;
    return tmp;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_iterator& monster::FrankList<value_type>::const_iterator::operator--() 
{
    this->ptr = this->ptr->prev;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_iterator monster::FrankList<value_type>::const_iterator::operator--(value_type) 
{
    monster::FrankList<value_type>::const_iterator tmp = *this;
    this->ptr = this->ptr->prev;
    return tmp;
}

////ITERATOR

template <typename value_type>
monster::FrankList<value_type>::iterator::iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::iterator::iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::iterator::iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::iterator::operator*() 
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::pointer monster::FrankList<value_type>::iterator::operator->()
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::iterator& monster::FrankList<value_type>::iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::iterator& monster::FrankList<value_type>::iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

////CONST_REVERSE_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::const_reverse_iterator::const_reverse_iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::const_reverse_iterator::const_reverse_iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::const_reverse_iterator::const_reverse_iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_reverse_iterator& monster::FrankList<value_type>::const_reverse_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_reverse_iterator& monster::FrankList<value_type>::const_reverse_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::const_reverse_iterator::operator*() const
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_pointer monster::FrankList<value_type>::const_reverse_iterator::operator->() const
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_reverse_iterator& monster::FrankList<value_type>::const_reverse_iterator::operator--() 
{
    this->ptr = this->ptr->next;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_reverse_iterator monster::FrankList<value_type>::const_reverse_iterator::operator--(value_type) 
{
    monster::FrankList<value_type>::const_reverse_iterator tmp = *this;
    this->ptr = this->ptr->next;
    return tmp;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_reverse_iterator& monster::FrankList<value_type>::const_reverse_iterator::operator++() 
{
    this->ptr = this->ptr->prev;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_reverse_iterator monster::FrankList<value_type>::const_reverse_iterator::operator++(value_type) 
{
    monster::FrankList<value_type>::const_reverse_iterator tmp = *this;
    this->ptr = this->ptr->prev;
    return tmp;
}

////REVERSE_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::reverse_iterator::reverse_iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::reverse_iterator::reverse_iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::reverse_iterator::reverse_iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::reverse_iterator::operator*() 
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::pointer monster::FrankList<value_type>::reverse_iterator::operator->()
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::reverse_iterator& monster::FrankList<value_type>::reverse_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::reverse_iterator& monster::FrankList<value_type>::reverse_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

////CONST_ASC_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::const_asc_iterator::const_asc_iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::const_asc_iterator::const_asc_iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::const_asc_iterator::const_asc_iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_asc_iterator& monster::FrankList<value_type>::const_asc_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_asc_iterator& monster::FrankList<value_type>::const_asc_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::const_asc_iterator::operator*() const
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_pointer monster::FrankList<value_type>::const_asc_iterator::operator->() const
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_asc_iterator& monster::FrankList<value_type>::const_asc_iterator::operator++() 
{
    this->ptr = this->ptr->asc;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_asc_iterator monster::FrankList<value_type>::const_asc_iterator::operator++(value_type) 
{
    monster::FrankList<value_type>::const_asc_iterator tmp = *this;
    this->ptr = this->ptr->asc;
    return tmp;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_asc_iterator& monster::FrankList<value_type>::const_asc_iterator::operator--() 
{
    this->ptr = this->ptr->desc;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_asc_iterator monster::FrankList<value_type>::const_asc_iterator::operator--(value_type) 
{
    monster::FrankList<value_type>::const_asc_iterator tmp = *this;
    this->ptr = this->ptr->desc;
    return tmp;
}

////ASC_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::asc_iterator::asc_iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::asc_iterator::asc_iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::asc_iterator::asc_iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::asc_iterator::operator*() 
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::pointer monster::FrankList<value_type>::asc_iterator::operator->()
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::asc_iterator& monster::FrankList<value_type>::asc_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::asc_iterator& monster::FrankList<value_type>::asc_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

////CONST_DESC_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::const_desc_iterator::const_desc_iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::const_desc_iterator::const_desc_iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::const_desc_iterator::const_desc_iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_desc_iterator& monster::FrankList<value_type>::const_desc_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_desc_iterator& monster::FrankList<value_type>::const_desc_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::const_desc_iterator::operator*() const
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_pointer monster::FrankList<value_type>::const_desc_iterator::operator->() const
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_desc_iterator& monster::FrankList<value_type>::const_desc_iterator::operator--() 
{
    this->ptr = this->ptr->asc;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_desc_iterator monster::FrankList<value_type>::const_desc_iterator::operator--(value_type) 
{
    monster::FrankList<value_type>::const_desc_iterator tmp = *this;
    this->ptr = this->ptr->asc;
    return tmp;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_desc_iterator& monster::FrankList<value_type>::const_desc_iterator::operator++() 
{
    this->ptr = this->ptr->desc;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_desc_iterator monster::FrankList<value_type>::const_desc_iterator::operator++(value_type) 
{
    monster::FrankList<value_type>::const_desc_iterator tmp = *this;
    this->ptr = this->ptr->desc;
    return tmp;
}

////DESC_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::desc_iterator::desc_iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::desc_iterator::desc_iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::desc_iterator::desc_iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::desc_iterator::operator*() 
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::pointer monster::FrankList<value_type>::desc_iterator::operator->()
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::desc_iterator& monster::FrankList<value_type>::desc_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::desc_iterator& monster::FrankList<value_type>::desc_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

////CONST_MULTI_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::const_multi_iterator::const_multi_iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::const_multi_iterator::const_multi_iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::const_multi_iterator::const_multi_iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_iterator& monster::FrankList<value_type>::const_multi_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_iterator& monster::FrankList<value_type>::const_multi_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::const_multi_iterator::operator*() const
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_pointer monster::FrankList<value_type>::const_multi_iterator::operator->() const
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_iterator& monster::FrankList<value_type>::const_multi_iterator::operator--() 
{
    if (mode) {
        this->ptr = this->ptr->desc;        
    }
    this->ptr = this->ptr->prev;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_iterator monster::FrankList<value_type>::const_multi_iterator::operator--(value_type) 
{
    monster::FrankList<value_type>::const_multi_iterator tmp = *this;
    if (mode) {
        this->ptr = this->ptr->desc;        
    }
    this->ptr = this->ptr->pre;
    return tmp;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_iterator& monster::FrankList<value_type>::const_multi_iterator::operator++() 
{
    if (mode) {
        this->ptr = this->ptr->asc;        
    }
    this->ptr = this->ptr->next;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_iterator monster::FrankList<value_type>::const_multi_iterator::operator++(value_type) 
{
    monster::FrankList<value_type>::const_multi_iterator tmp = *this;
    if (mode) {
        this->ptr = this->ptr->asc;        
    }
    this->ptr = this->ptr->next;
    return tmp;
}

////MULTI_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::multi_iterator::multi_iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::multi_iterator::multi_iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::multi_iterator::multi_iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::multi_iterator::operator*() 
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::pointer monster::FrankList<value_type>::multi_iterator::operator->()
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::multi_iterator& monster::FrankList<value_type>::multi_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::multi_iterator& monster::FrankList<value_type>::multi_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

template <typename value_type>
void monster::FrankList<value_type>::const_multi_iterator::chmod()
{
    if (mode) {
        mode = false;
    } else {
        mode = true;
    }
}

////CONST_MULTI_REVERSE_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::const_multi_reverse_iterator::const_multi_reverse_iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::const_multi_reverse_iterator::const_multi_reverse_iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::const_multi_reverse_iterator::const_multi_reverse_iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_reverse_iterator& monster::FrankList<value_type>::const_multi_reverse_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_reverse_iterator& monster::FrankList<value_type>::const_multi_reverse_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_reference monster::FrankList<value_type>::const_multi_reverse_iterator::operator*() const
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::const_pointer monster::FrankList<value_type>::const_multi_reverse_iterator::operator->() const
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_reverse_iterator& monster::FrankList<value_type>::const_multi_reverse_iterator::operator++() 
{
    if (mode) {
        this->ptr = this->ptr->desc;        
    }
    this->ptr = this->ptr->prev;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_reverse_iterator monster::FrankList<value_type>::const_multi_reverse_iterator::operator++(value_type) 
{
    monster::FrankList<value_type>::const_multi_reverse_iterator tmp = *this;
    if (mode) {
        this->ptr = this->ptr->desc;        
    }
    this->ptr = this->ptr->pre;
    return tmp;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_reverse_iterator& monster::FrankList<value_type>::const_multi_reverse_iterator::operator--() 
{
    if (mode) {
        this->ptr = this->ptr->asc;        
    }
    this->ptr = this->ptr->next;
    return *this;
}

template <typename value_type>
const typename monster::FrankList<value_type>::const_multi_reverse_iterator monster::FrankList<value_type>::const_multi_reverse_iterator::operator--(value_type) 
{
    monster::FrankList<value_type>::const_multi_reverse_iterator tmp = *this;
    if (mode) {
        this->ptr = this->ptr->asc;        
    }
    this->ptr = this->ptr->next;
    return tmp;
}

////MULTI_ITERATOR

template <typename value_type>
monster::FrankList<value_type>::multi_reverse_iterator::multi_reverse_iterator(const base_iterator& rhv) 
{
    this->ptr(rhv.ptr);
}

template <typename value_type>
monster::FrankList<value_type>::multi_reverse_iterator::multi_reverse_iterator(base_iterator&& rhv) 
{
    this->ptr(rhv.ptr); 
    rhv = nullptr;
}

template <typename value_type>
monster::FrankList<value_type>::multi_reverse_iterator::multi_reverse_iterator(Node* ptr)
{
    this->ptr = ptr; 
}

template <typename value_type>
typename monster::FrankList<value_type>::reference monster::FrankList<value_type>::multi_reverse_iterator::operator*() 
{
    return this->ptr->data;
}

template <typename value_type>
typename monster::FrankList<value_type>::pointer monster::FrankList<value_type>::multi_reverse_iterator::operator->()
{
    return this->ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::multi_reverse_iterator& monster::FrankList<value_type>::multi_reverse_iterator::operator=(const base_iterator& rhv)
{
    this->ptr = rhv.ptr;
}

template <typename value_type>
const typename monster::FrankList<value_type>::multi_reverse_iterator& monster::FrankList<value_type>::multi_reverse_iterator::operator=(base_iterator&& rhv)
{
    this->ptr = rhv.ptr;
    rhv = nullptr;
}

template <typename value_type>
void monster::FrankList<value_type>::const_multi_reverse_iterator::chmod()
{
    if (mode) {
        mode = false;
    } else {
        mode = true;
    }
}


#endif //_ITERATOR_HPP__