#ifndef UTIL_H
#define UTIL_H

template<typename T>
class MemoryPool {
    T* _data;
    size_t _siz, _cap;
    float _min, _max;
    size_t size() const {
        return _siz;
    }
    size_t reset(size_t new_n = 1) {
        if (_data != nullptr) {
            delete[] _data;
        }
        _cap = new_n * _min;
        _data = new T[_cap];
        return _cap;
    }
    size_t resize(size_t new_n) {
        if (_data != nullptr) {
            if ((size_t)(new_n * _min) > _cap || 
                (size_t)(new_n * _max) < _cap) {
                T* new_data = new T[(size_t)new_n * _min];
                memcpy(new_data, _data, sizeof(T) * _cap);
                _cap = (size_t)new_n * _min;
                _data = new_data;
                delete[] new_data;
            }
        }
        return _cap;
    }
    T& operator[](size_t index) {
        return _data[index];
    }
    const T& operator[](size_t index) const {
        return _data[index];
    }
    MemoryPool(size_t siz = 1, float min = 1.2, float max = 3) {
        _siz = siz;
        _cap = siz * _min;
        _min = min;
        _max = max;
        _data = new T[_cap];
    }
    MemoryPool(const MemoryPool& p) {
        _siz = p._siz;
        _cap = p._cap;
        _data = new T[_cap];
        memcpy(_data, p._data, sizeof(T) * _cap);
    }
    MemoryPool(MemoryPool&& p) {
        _siz = p._siz;
        _cap = p._cap;
        _data = p._data;
        p._data = nullptr;
    }
};

#endif
