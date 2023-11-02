// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Usage notes: Список (вектор) указателей на объект
//===================================================================
// Используется : 
//===================================================================
// Использует   : <mem.h>
//===================================================================
// Oct 2002                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef KNVectorHpp
#define KNVectorHpp
//---------------------------------------------------------------------------
#include <string.h>
//---------------------------------------------------------------------------
/** Список (вектор) объектов с постоянной структурой. */
template <class T > class KNVector{
public:
    T *list;
    unsigned Max, Count;
public:
    KNVector( unsigned iMax=50 );
    KNVector( const KNVector& );
    ~KNVector();
public:
    void Add( T );
    void Insert( T,unsigned );
    unsigned GetIndex( T& );
    // очистка списка
    void Release();
    void Delete( unsigned );

    T& At(unsigned);
    T& At(unsigned) const;

    T& operator[](unsigned);
    T& operator[](unsigned) const;
//    T operator[](unsigned) const;
//    T*& operator[](unsigned);
//    T* operator[](unsigned) const;
    bool operator==(KNVector&) const;
    unsigned Size() {return Count;}
    // поменять местами
    void Move(unsigned, unsigned);
    // зарезервировать дополнительное место
    void ReservePlus(unsigned);
private:
    void CopyPlus();
};

//typedef KNVector <unsigned> KNUIntList;
//typedef KNVector <int> KNIntList;

        // =====================================
        // Implementation of templates functions
        // =====================================
template <class T >
KNVector<T>::KNVector(unsigned iMax) {
    Count=0;
    Max = iMax ? iMax:1;
    list = new T[Max];
}

template <class T >
KNVector<T>::KNVector(const KNVector& st){
    Count = st.Count;
    Max = st.Max;
    list = new T[Max];
    memcpy(list, st.list, sizeof(T)*Count);
}

template <class T >
KNVector<T>::~KNVector(){
    delete [] list;
}

template <class T >
void KNVector<T>::CopyPlus(){
    Max*=2;
    T *body = new T[Max];
    memcpy(body, list, sizeof(T)*Count);
    delete [] list;
    list = body;
}

template <class T >
void KNVector<T>::ReservePlus(unsigned delta){
//    if(!delta) return;
    Max+=delta;
    T *body = new T[Max];
    memcpy(body, list, sizeof(T)*Count);
    delete [] list;
    list = body;
}

template <class T >
void KNVector<T>::Move(unsigned n1, unsigned n2)
{
    T x = list[n1];
    list[n1] = list[n2];
    list[n2] = x;
}

template <class T >
void KNVector<T>::Add(T x){
//    if (!x) return;
    if (Count>=Max) CopyPlus();
    list[Count++] = x;
}

template <class T >
void KNVector<T>::Insert(T x,unsigned n){
    if (Count == Max) // CopyPlus()
    {
        Max*=2; T *body = new T[Max];
        if( n ) memcpy(body, list, sizeof(T)*n);
        body[n] = x;
        if( Count-n ) memmove(body+n+1, list+n, sizeof(T)*(Count-n));
        delete [] list;
        list = body;
        Count++;
        return;
    }
    if( Count-n ) memmove(list+n+1, list+n, sizeof(T)*(Count-n));
    Count++;
    list[n] = x;
}

template <class T >
unsigned KNVector<T>::GetIndex(T& x){
	for(unsigned i=0; i<Count; ++i)
		if( list[i] == x ) return i;
    return Count;
}

template <class T >
void KNVector<T>::Release(){
//    delete [] list;
    Count=0;
}

template <class T >
void KNVector<T>::Delete(unsigned n){
    if( Count-n-1 )
        memmove(list+n, list+n+1, sizeof(T)*(Count-n-1));
    Count--;
}

template <class T >
T& KNVector<T>::At(unsigned n) {
	return list[n];
//	try { return list[n]; }
//	catch (...) {return 0;}
}

template <class T >
T& KNVector<T>::At(unsigned n) const{
	return list[n];
//	try { return list[n]; }
//	catch (...) {return 0;}
}

template <class T >
T& KNVector<T>::operator[](unsigned n) {
    return list[n];
}

template <class T >
T& KNVector<T>::operator[](unsigned n) const
{
    return list[n];
}

template <class T >
bool KNVector<T>::operator==(KNVector<T> &Pr) const{
    if (Count != Pr.Count) return 0;
    return !memcmp(list, Pr.list, sizeof(T)*Count);
}

//---------------------------------------------------------------------------
#endif
