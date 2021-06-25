//
// Created by roizh on 25/06/2021.
//

#ifndef _VL_STRING_H_
#define _VL_STRING_H_

#include "vl_vector.h"
#include <cstring>

template <size_t StaticCapacity = DEFAULT_STATIC_SIZE>
class vl_string: public vl_vector<char, StaticCapacity>{

 public:
                            /************
                            *    CTR    *
                            ************/

  vl_string(): vl_vector<char, StaticCapacity> (){
    *(this->_data) = 0;
    this->_vec_size = 1;
  }

  vl_string(const char* str): vl_vector<char, StaticCapacity>(){
    size_t len_of_str = strlen (str) + 1;  //for \0.
    size_t cap = this->cap_c (0,len_of_str);
    if(cap!= StaticCapacity){
      try{this->_data = new char[cap];}
      catch(std::bad_alloc&){throw;}
      this->is_static = false;
      }
    strcpy(this->_data, str);
    this->_vec_size = len_of_str;
    this->_vec_capacity = cap;
  }

  vl_string<StaticCapacity>(const vl_string<StaticCapacity>& other):
      vl_vector<char, StaticCapacity> (){
    this->_vec_size = other._vec_size;
    this->_vec_capacity = other._vec_capacity;
    this->is_static = other.is_static;
    if(!other.is_static){
      try{this->_data = new char[other._vec_capacity];}
      catch(std::bad_alloc&){throw;}
      }
    strcpy (this->_data, other._data);
  }

                          /*****************
                          * Public Methods *
                          *****************/

  size_t size() const override{return this->_vec_size-1;}

  bool empty() const override {return this->_vec_size == 1;}

  bool contains(const char* str) const{
    size_t len_of_new_str = strlen (str);
    if(len_of_new_str > this->_vec_size){
        return false;
    }
    char const * cur_ptr = this->_data;
    while(cur_ptr != this->end()){
        if (*cur_ptr == *str){
            size_t str_len = strlen (str);
            char const * temp = cur_ptr;
            bool flag = true;
            for (size_t i = 0; i < str_len; ++i)
              {
                if(temp[i] == 0){
                    break;
                }
                if(str[i] != temp[i]){
                  flag = false;
                    break;
                }
              }
            if (flag){
                return true;
            }
        }
        cur_ptr++;
    }
    return false;
  }

  void push_back(const char str) override{
    if (this->_vec_size == this->_vec_capacity){
        size_t new_cap = this->cap_c (this->_vec_size, 1);
        this->increase_vec_size (new_cap);
      }
    this->_data[this->_vec_size-1] = str;
    this->_data[this->_vec_size] = 0;
    this->_vec_size++;
  }

  void pop_back() override{
    if (this->empty()){
        return;
    }
    this->_vec_size--;
    this->_data[this->_vec_size-1] = 0;
    if (this->_vec_size == StaticCapacity){
        strcpy (this->stk_array, this->_data);
        char* temp = this->_data;
        this->_data = this->stk_array;
        delete[] temp;
    }
  }

  void clear() override{
    if(!this->is_static){
        char* temp = this->_data;
        this->_data =this-> stk_array;
        delete[] temp;
        this->is_static = true;
        this->_vec_capacity = StaticCapacity;
      }
    this->_vec_size = 1;
    this->_data[0] = 0;
  }

                           /************
                           * Operators *
                           ************/

  vl_string<StaticCapacity>& operator+=(const char cr){
    this->push_back (cr);
    return *this;
  }

  vl_string<StaticCapacity>& operator+=(const char* str){
    size_t len_of_str = strlen (str);
    if (this->_vec_size + len_of_str > this->_vec_capacity){
        size_t new_cap = this->cap_c (this->_vec_size, len_of_str);
        this->increase_vec_size (new_cap);
      }
    strcpy((this->_data)+ this->_vec_size-1, str);
    this->_vec_size += len_of_str;
    return *this;
  }

  vl_string<StaticCapacity>& operator+=(const vl_string<StaticCapacity>& ot){
    *this += ot.data();
    return *this;
  }

  vl_string<StaticCapacity> operator+(const char cr){
    vl_string<StaticCapacity> temp = *this;
    temp.push_back (cr);
    return temp;
  }

  vl_string<StaticCapacity> operator+(const char* cr){
    vl_string<StaticCapacity> temp = *this;
    temp += cr;
    return temp;
  }

  vl_string<StaticCapacity> operator+(const vl_string<StaticCapacity>& ot){
    vl_string<StaticCapacity> temp = *this;
    temp += ot;
    return temp;
  }

  operator const char*() const {
    return this->_data;
  }





};


#endif //_VL_STRING_H_
