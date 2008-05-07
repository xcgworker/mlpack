#ifndef PARTIAL_DISTANCE_COMPUTATION_H
#define PARTIAL_DISTANCE_COMPUTATION_H

#include <fastlib/fastlib.h>
#define EPS 1.0e-5

namespace pdc {

  template<typename T>
  T DistanceEuclidean(GenVector<T>& x, GenVector<T>& y, T upper_bound) {

    DEBUG_SAME_SIZE(x.length(), y.length());
    T *vx = x.ptr();
    T *vy = y.ptr();
    index_t length = x.length();
    T s = 0;
    index_t batch = 120;
    index_t t =(index_t) ((T) length / (T) batch);
    index_t t1 = t;

    upper_bound *= upper_bound;

    
    do {
      do {
	T d = *vx++ - *vy++;
	s += d * d;
	d = *vx++ - *vy++;
	s += d * d;
	//d = *vx++ - *vy++;
	//s += d * d;
	//d = *vx++ - *vy++;
	//s += d * d;
	batch -= 2;
      }while(batch);
      if (s > upper_bound) {
	return sqrt(s) + EPS;
      }
      batch = 120;
    }while(--t);

    length = length - t1 * 120;

    while (length) {
      T d = *vx++ - *vy++;
      s += d * d;
      d = *vx++ - *vy++;
      s += d * d;
      length -= 2;
    }

    if (s > upper_bound) {
      return sqrt(s) + EPS;
    }
    else {
      return sqrt(s);
    }
    
    /* 
    do {
      T d = *vx++ - *vy++;
      s += d * d;
    } while(--length);

    return sqrt(s);
    */
  }

};

#endif
