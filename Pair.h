//
// Created by liels on 09/12/2022.
//

#ifndef WET_1_PAIR_H
#define WET_1_PAIR_H

template<class T, class S>
class Pair
{
    private:
    T first;
    S second;

    public:
    Pair() = default;
    Pair(const T& first, const S& second):
    first(first), second(second) {}
    Pair(const Pair& p) = default;
    ~Pair() = default;

    //const getters
    T getFirst() const {return first;}
    S getSecond() const {return second;}

    //getters
    T& getFirst() {return first;}
    S& getSecond() {return second;}

    //setters
    void setFirst(const T& first) const {this->first;}
    void setSecond(const S& second) const {this->second;}

};

#endif //WET_1_PAIR_H
