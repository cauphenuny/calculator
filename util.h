#pragma once

#include <cstring>
#include "debug.h"

#define _min 1.3
#define _max 3
template<typename T>
class Dynarray {
    T* _data{nullptr};
    uint32_t _siz{0}, _cap{0};
public:
    size_t size() const {
        return _siz;
    }
    size_t reset(size_t new_n = 1) {
        delete[] _data;
        _siz = new_n;
        _cap = new_n * _min;
        _data = new T[_cap];
        return _cap;
    }
    size_t resize(size_t new_n) {
        if ((size_t)(new_n * _min) > _cap || 
            (size_t)(new_n * _max) < _cap) {
            delete[] _data;
            T* new_data = new T[(size_t)(new_n * _min)];
            memcpy(new_data, _data, sizeof(T) * _siz);
            _cap = new_n * _min;
            _siz = new_n;
            _data = new_data;
        }
        return _cap;
    }
    T& operator[](size_t index) {
        return _data[index];
    }
    const T& operator[](size_t index) const {
        return _data[index];
    }
    Dynarray& operator= (const Dynarray& d) {
        debugi << "copy\n";
        if (d._data != this->_data) {
            delete[] _data;
            _siz = d._siz;
            _cap = d._cap;
            //debugi << "capacity: " << _cap << "\n";
            _data = new T[_cap];
            //debugi << "copy " << sizeof(T) * _siz << "\n";
            memcpy(_data, d._data, sizeof(T) * _siz);
            //debugi << "done\n";
        }
        return *this;
    }
    Dynarray& operator= (Dynarray&& d) {
        debugi << "move\n";
        if (d._data != this->_data) {
            delete[] _data;
            _siz = d._siz;
            _cap = d._cap;
            _data = d._data;
            d._data = nullptr;
            //debugi << "done\n";
        }
        return *this;
    }
    Dynarray(size_t siz = 0) {
        _siz = siz;
        _cap = siz * _min;
        _data = new T[_cap];
    }
    template<typename T2>
    Dynarray(T2&& p) {
        (*this) = std::forward<T2>(p);
    }
    ~Dynarray() {
        delete[] _data;
    }
};
#undef _min
#undef _max

class printable {
public:
    virtual friend std::istream& operator>> (std::istream &, Num&) = 0;
    virtual friend std::ostream& operator<< (std::ostream &, const Num&) = 0;
}
