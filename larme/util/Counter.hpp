#pragma once

namespace larme {
namespace util {

template<class T>
class Counter
{
private:
    T count;
    T limit;
public:
    Counter()
    :count(0), limit(0){
    }
    
    void reset() {
        count = 0;
    }
    bool isLimit() {
        return this->count >= this->limit;
    }
    
    T getCount() {
        return count;
    }
    void setCount(T count) {
        this->count = count;
    }
    T getLimit() {
        return count;
    }
    void setLimit(T limit) {
        this->limit = limit;
    }
    
    void add(const T& plus) {
        count += plus;
    }
    
    Counter<T>& operator++()
    {
        ++count;
        return *this;
    }
};

}}