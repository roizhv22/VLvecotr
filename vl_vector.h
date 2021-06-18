//
// Created by roizh on 16/06/2021.
//

#ifndef vl_vector_H_
#define vl_vector_H_
#include <iostream>
#include <iterator>



template <typename T, size_t StaticCapacity = 16>
class vl_vector {
 private:
  size_t _vec_size;
  size_t _vec_capacity;
  T* _data;
  T stk_array[StaticCapacity];
  bool is_static;

  /**
   * CapC method for clacluting vec size changes. This method are only for
   * internal usage.
   * @param new_elements additioal elemnts to the vector.
   * @return new size by instructions.
   */
  size_t cap_c(size_t size,size_t new_elements){
    if(size + new_elements <= StaticCapacity){
        return StaticCapacity;
      }
    else{
        size_t clac = (3*(size + new_elements)) / 2;
        return clac;
      }
  }
  /**
   * a private method to manage vector size .
   * @param new_capacity the new capacity of the vector.
   */
  void increase_vec_size(size_t new_capacity){
    T* new_data;
    try{
       new_data = new T[new_capacity];
    }
    catch (std::bad_alloc)
      {
        throw;
      }
    for (size_t i = 0; i < _vec_size; ++i)
      {
        new_data[i] = _data[i];
      }
    T* temp = _data;
    _data = new_data;
    is_static = false;
    if (_vec_capacity != StaticCapacity){
      delete[] temp;
    }
    _vec_capacity = new_capacity;
  }

 public:

                            /************
                            *    CTR    *
                            ************/

  /**
   * default ctr.
   */
  vl_vector(): _vec_size(0), _vec_capacity(StaticCapacity), _data(stk_array),
  is_static(true){}

/**
 * sequence based ctr
 * @tparam InputIterator an iterator of T type elemnts.
 * @param first begin of seq
 * @param last end of seq.
 */
  template<class InputIterator>
  vl_vector(InputIterator first, InputIterator last)
  {
    size_t num_of_elements = std::distance (first, last); //STL algorithm.
    _vec_size = num_of_elements;
    _vec_capacity = StaticCapacity;
    is_static = true;
    _data = stk_array;
    size_t cap = cap_c (0, num_of_elements);
    if (cap != StaticCapacity)
      {
        try{_data = new (std::nothrow) T[cap];}
        catch (std::bad_alloc&){throw;}
        _vec_capacity = cap;
        is_static = false;
      }
    size_t ind = 0;
    while(first != last){
        _data[ind] = *first;
        first++; ind++;
      }
  }
/**
 * single-value ctr
 * @param count number of apperances.
 * @param val given val T.
 */
  vl_vector(size_t count, T val){
    size_t cap = cap_c (0, count);
    is_static = true;
    _data = stk_array;
    _vec_capacity = StaticCapacity;
    if(cap != StaticCapacity){
        try{_data = new T[count];}
        catch(std::bad_alloc&){throw;}
        is_static = false;
        _vec_capacity = cap;
    }
    for (size_t i = 0; i < count; ++i)
      {
        _data[i] = val;
      }
    _vec_size = count;
  }
  /**
   * cpy ctr
   * @param other vec object to copy from.
   */
  vl_vector(const vl_vector<T,StaticCapacity>& other){
    _vec_capacity = other._vec_capacity;
    _vec_size = other._vec_size;
    is_static = true;
    _data = stk_array;
    if (other._vec_capacity != StaticCapacity){
      try{_data = new T[other._vec_capacity];}
      catch (std::bad_alloc&){throw;}
      is_static = false;
    }
    for (size_t i = 0; i <other._vec_size ; ++i)
      {
        _data[i] = other._data[i];
      }
  }

  /**
   * dcr, frees memory if the capacity is not the Static capacity.
   */
  ~vl_vector(){
    if (_vec_capacity > StaticCapacity){
      delete[] _data;
    }
  }

                              /************
                              * Iterators *
                              ************/

    /*
     * Iterators has been defined as T* pointers that accepts all
     * random-accsse operations. All traits has been assign automaticlly.
     */
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  /**
   * begin(), end(), cbegin() and cend() function for the iterator.
   * @return iterator (T*)
   */
  iterator begin(){return _data;}
  iterator end(){return _data+_vec_size;}
  const_iterator begin() const {const T* temp = _data; return temp;}
  const_iterator end() const {const T* temp = _data+_vec_size; return temp;}
  const_iterator cbegin()const {const T* temp = _data; return temp;}
  const_iterator cend()const {const T* temp = _data+_vec_size; return temp;}


  /**
  * rbegin(), rend(), crbegin() and crend() function for the reverse_iterator.
  * @return reverse_iterator (std::reverse_iterator<iterator>)
  */
  reverse_iterator rbegin() noexcept{
    return std::make_reverse_iterator (_data+(_vec_size));
  }
  reverse_iterator rend() noexcept{
    return std::make_reverse_iterator (_data);
  }

  const_reverse_iterator rbegin() const noexcept{
    return std::make_reverse_iterator (_data+(_vec_size));
  }

  const_reverse_iterator rend() const noexcept{
    return std::make_reverse_iterator (_data);
  }

  const_reverse_iterator crbegin() const noexcept{
    const_iterator it = _data + (_vec_size);
    auto temp = std::make_reverse_iterator (it);
    return temp;
  }
  const_reverse_iterator  crend() const noexcept{
    return std::make_reverse_iterator (_data);
  }

                          /*****************
                          * Public Methods *
                          *****************/

 /**
 * size getter
 * @return the current vec size.
 */
  size_t size() const {return _vec_size;}
  /**
   * capacity getter
   * @return current vec capacity.
   */
  size_t capacity() const {return _vec_capacity;}

  /**
   * Get the data array from vec.
   * @return the data array ptr.
   */
  T* data() const {return _data;}

  /**
   * is vec is empty aka size == 0.
   * @return bool expression on given state.
   */
  bool empty() const {return _vec_size == 0;}

  /**
   * returning the givning element in the given index in the vector.
   * @param ind an index.
   * @return the Value of (copy and not reference).
   */
  T at(const size_t ind) const {
    if(ind >= _vec_size || ind<0){
        throw std::out_of_range("Out of vector index.");
    }
    return _data[ind];
  }

  /**
   * A method that checks if a given T value is in the vector.
   * @param val T type.
   * @return bool val if the element in the vector.
   */
  bool contains (const T& val) const {
    for (size_t i = 0; i < _vec_size; ++i)
      {
        if (val == _data[i]){
            return true;
          }
      }
    return false;
  }
  /**
   * push_back() method accepts a Value and pushes it to the end
   * of the vector. if resizing is needed it will call to the increase_vec_size
   * methodd.
   * @param val T type value.
   */
  void push_back(T val){
    if (_vec_size == _vec_capacity){
      size_t new_cap = cap_c (_vec_size, 1);
        increase_vec_size (new_cap);
    }
      *(_data+_vec_size) = val;
    _vec_size++;
  }

  /**
   * An insert method. accepting an iterator as a marker in the vector
   * and a value and will insert it to the left of the giving itartor value.
   * @param it Iterator (T*)
   * @param val T value
   * @return an iterator to the new element.
   */
  iterator insert(const_iterator it, T val){
    size_t mark = std::distance (cbegin(), it);
    if (_vec_size == _vec_capacity){
        size_t new_cap = cap_c (_vec_size, 1);
        increase_vec_size (new_cap);
      }
      iterator rev_it = end();
      iterator ass_it = end()+1;
    if (_vec_size +1 == _vec_capacity){ //a guard in order to prevent
      // unwanted assigment in a block that is almost full.
      rev_it--; ass_it--;
    }
    while(rev_it != _data+mark){
      *(ass_it) = *(rev_it);
      ass_it--;rev_it--;
    }
    *(ass_it) = *(rev_it);
    *rev_it = val;
    _vec_size++;
    return _data+mark;
  }
  /**
   * Additioal insert method that copies a sequance of elemnt represented by
   * two iterators.
   * @tparam InputIterator An iterator that is STL approved./
   * @param position an vector iterator to a giving postion.
   * @param first Input it
   * @param last Input it marking the last (not icnlusive) elemnt to be added.
   * @return iterator to the first new element.
   */
  template<typename InputIterator>
  iterator insert(const_iterator position,
                  const InputIterator first, const InputIterator last){
    size_t mark = std::distance (cbegin(), position);
    size_t num_of_elem = std::distance (first, last);
    if (_vec_size+num_of_elem > _vec_capacity){
        size_t new_cap = cap_c (_vec_size, num_of_elem);
        //Distance not includes last iterator value.
        increase_vec_size (new_cap);
      }
    iterator rev_it = end();
    iterator ass_it = end()+(num_of_elem);
    if (_vec_size +num_of_elem == _vec_capacity){ //a guard in order to prevent
        // unwanted assigment in a block that is almost full.
        rev_it--; ass_it--;
      }
    while(rev_it != _data+(mark)){
        *(ass_it) = *(rev_it);
        ass_it--;rev_it--;
      }
    *(ass_it) = *(rev_it);
    std::copy (first, last, _data+mark);
    _vec_size += num_of_elem;
    return _data+mark;
  }

  /**
   * Pop_back method removes the last elemnts from the vector.
   */
  void pop_back(){
    if(_vec_size == 0){
        return;
    }
    _vec_size--;
    if (_vec_size == StaticCapacity){ //Only possible case of returning to
      //stack array using this method.
        for (size_t i = 0; i < StaticCapacity; ++i)
          {
            stk_array[i] = _data[i];
          }
        T* temp = _data;
        _data = stk_array;
        delete[] temp;
        _vec_size = StaticCapacity;
        _vec_capacity = StaticCapacity;
        is_static = true;
      }
  }
  /**
   * erase method that deletes the element in a giving postion
   * @param it a vector iterator marking the element to be deleteded.
   * @return an iterator to the element that is next to the element that
   * was deleted.
   */
  iterator erase(const_iterator  it){
    size_t mark = std::distance (cbegin(), it);
    _vec_size--;
    if (_vec_size == StaticCapacity){
        int j = 0;
        for (size_t i = 0; i <_vec_size ; ++i)
          {
            if (i == mark){j++;}
            else{
              stk_array[i] = _data[j];
              j++;
            }
          }
        T* temp = _data;
        _data = stk_array;
        delete[] temp;
        _vec_size = StaticCapacity;
        _vec_capacity = StaticCapacity;
        is_static = true;
      }
    else{
      iterator ass_it = begin() + mark;
      iterator mark_it = begin() + mark + 1;
      while(ass_it != end()){
          *ass_it = *mark_it;
          mark_it++; ass_it++;
      }
    }
    return _data + mark;
  }
  /**
   * a erase method that will delete a sequance of elements from the vector.
   * @param first the first element to be deleted represented by an iterator.
   * @param last the last (not icnlusive) element to be deleted represented
   * by iterator.
   * @return an iterator to the first element that was next to the sequance.
   */
  iterator erase(const_iterator first,const_iterator last){
    size_t dist_from_first = std::distance (cbegin(), first);
    size_t mark = std::distance (first, last);
    if ((_vec_size - mark <= StaticCapacity) && is_static == false){
      const_iterator it = cbegin();
      T* cur_ptr = stk_array;
      while(it != first){
        *cur_ptr = *it;
        cur_ptr++; it++;
      }
      it = last; // jump to next segment.
      while(it != end()){
        *cur_ptr = *it;
        cur_ptr++; it++;
      }
      T* temp = _data;
      _data = stk_array;
      delete[] temp;
      _vec_capacity = StaticCapacity;
      is_static = true;
    }
    else{
    iterator ass_it = begin() + dist_from_first;
    iterator mark_it = begin() + (dist_from_first + mark);
    while(mark_it != end()){
        *ass_it = *mark_it;
        mark_it++; ass_it++;
    }
      }
    _vec_size -= mark;
    return _data + dist_from_first;
  }
  /**
   * clear function deletes all elemnts from the vector and returning it's
   * capacity to the Static capacity that was declared.
   */
  void clear(){
    if(!is_static){
      T* temp = _data;
      _data = stk_array;
      delete[] temp;
      is_static = true;
      _vec_capacity = StaticCapacity;
      is_static = true;
    }
    _vec_size = 0;
  }

                           /************
                           * Operators *
                           ************/

  /**
   * Assigment operator.
   * @param other A vector<T,StaticCapacity> obejct. passed by const ref.
   * @return A Vector that has the same data as the copied vector.
   */
  vl_vector<T, StaticCapacity>& operator=(const vl_vector<T,StaticCapacity>&
      other)
  {
    if (this == &other)
      {
        return *this;
      }
    if (other.is_static)
      {
        for (size_t i = 0; i < other._vec_size; ++i)
          {
            stk_array[i] = other._data[i];
          }
        if (!is_static)
          {
            T *temp = _data;
            delete[] temp;
          }
          is_static = true;
        _data = stk_array;
      }
    else
      {
        T *temp;
        try{temp = new T[other._vec_capacity];}
        catch (std::bad_alloc&){throw;}
        for (size_t i = 0; i < other._vec_size; ++i)
          {
            temp[i] = other._data[i];
          }
        if (!is_static){
          T* temp2 = _data;
          delete[] temp2;
        }
        is_static = false;
        _data = temp;
      }
    _vec_size = other._vec_size;
    _vec_capacity = other._vec_capacity;
    return *this;
  }
  /**
   * [] operator, accepts an index and return a reference to the value in the
   * giving index.
   * @param ind size_t index
   * @return reference to the data[index] element.
   */
  T& operator[](size_t ind)const noexcept{
    if (ind<_vec_size){
        return _data[ind];
    }
  }

  /**
   * == operator, checks if two vectors has the same size and the exact same
   * elements.
   * @param a first vec isntance
   * @param b sec vec instance
   * @return True if identical/ False if not.
   */
  friend bool operator==(const vl_vector<T, StaticCapacity>& a,
      const vl_vector<T, StaticCapacity>& b) {
    if(a._vec_size != b._vec_size){
        return false;
    }
    for (size_t i = 0; i < a._vec_size; ++i)
      {
        if (a._data[i] != b._data[i]){
            return false;
        }
      }
    return true;
  }
  /**
   * != operator, based on == only returns the negate of the ==.
   * @param a first vec isntance
   * @param b sec vec instance
   * @return True if not identical/ False if they are.
   */
  friend bool operator!=(const vl_vector<T, StaticCapacity>& a,
                         const vl_vector<T, StaticCapacity>& b){
    return !(a == b);
  }
};

#endif //vl_vector_H_
