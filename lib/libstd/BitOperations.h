<<<<<<< HEAD
#ifndef __BIT_OPERATIONS_H
#define __BIT_OPERATIONS_H

template<class T> inline T operator~ (T a) { return (T)~(int)a; }
=======
#ifndef __STDLIB_BITOPERATIONS_H
#define __STDLIB_BITOPERATIONS_H

template<class T> inline T operator~ (T a) { return (T)~(int)a;}
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
template<class T> inline T operator| (T a, T b) { return (T)((int)a | (int)b); }
template<class T> inline T operator& (T a, T b) { return (T)((int)a & (int)b); }
template<class T> inline T operator^ (T a, T b) { return (T)((int)a ^ (int)b); }
template<class T> inline T& operator|= (T& a, T b) { return (T&)((int&)a |= (int)b); }
template<class T> inline T& operator&= (T& a, T b) { return (T&)((int&)a &= (int)b); }
template<class T> inline T& operator^= (T& a, T b) { return (T&)((int&)a ^= (int)b); }

<<<<<<< HEAD
#endif /* __BIT_OPERATIONS_H */
=======
#endif /* __STDLIB_BITOPERATIONS_H */
>>>>>>> 8e709b3c8584ffb4d552fdfddbc2e262bb76ed03
