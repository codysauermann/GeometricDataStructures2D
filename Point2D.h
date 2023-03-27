#ifndef POINT2D_H
#define POINT2D_H
#include <vector>
#include "SimplePoint2D.h"
#include <memory>
using namespace std;


class Point2D {
    private:
        class Impl;
        unique_ptr<Impl> pimpl;
        
    public:
        struct Iterator{
            public:
                using iterator_category = input_iterator_tag;
                using difference_type = ptrdiff_t;
                using value_type = SimplePoint2D;
                using pointer = SimplePoint2D*;
                using reference = SimplePoint2D&;

                Iterator() {m_ptr = nullptr;}
                Iterator(pointer ptr): m_ptr(ptr){}

                const reference operator*()const{return *m_ptr;}
                const pointer operator->(){return m_ptr;}

                Iterator& operator++()
                {
                    m_ptr++;
                    return *this;
                }
                Iterator operator++(int)
                {
                    Iterator tmp = *this; 
                    ++(*this);
                    return tmp;
                }

                friend bool operator==(const Iterator& a, const Iterator& b)
                {
                    return a.m_ptr == b.m_ptr;
                };
                friend bool operator!=(const Iterator& a, const Iterator& b)
                {
                    return a.m_ptr != b.m_ptr;
                };


            private:
                pointer m_ptr;

        };

        Point2D();
        Point2D(vector<SimplePoint2D> _pointCollection, bool _ordered);
        Point2D(vector<SimplePoint2D> _pointCollection);
        Point2D(Point2D const &sourcePoint2D);
        Point2D(Point2D &&sourcePoint2D);
        ~Point2D();
        Iterator begin();
        Iterator end();
};

#endif //POINT2D_H
