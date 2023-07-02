#pragma once

#include "named_vector.h"

#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
#include <algorithm>
#include <iterator>
#include <array>



namespace ipb{

template <typename T> 
T accumulate(const named_vector<T>& v){
    return std::accumulate(v.cbegin(),v.cend(),(T)0);
}

template <typename T>
int count(const named_vector<T>& v,const T& element){
    return std::count(v.cbegin(),v.cend(),element);
}

template <typename T> 
bool all_even(const named_vector<T>& v){
    return std::all_of(v.cbegin(),v.cend(),[](T e){ return e%2==0; });
}

template <typename T> 
void clamp(named_vector<T>& v, const T& low, const T& high){
    for(T& elem: v){
        elem = std::clamp(elem,low,high);
    }
}

template <typename T> 
void print(named_vector<T>& v){
    std::cout << v.name() << " : ";

    for(auto it = v.cbegin();it<v.cend()-1;it++){
        std::cout << *it << ", ";
    }

    if(!v.vector().empty()){
        std::cout << v.back();
    }
    std::cout << std::endl;
}

template <typename T> 
void fill(named_vector<T>& v, T value){
    std::fill(v.begin(),v.end(),value);
}

template <typename T> 
bool find(const named_vector<T>& v, T value){
    return std::find(v.cbegin(),v.cend(),value) != v.cend();
}

template <typename T> 
void toUpper(named_vector<T>& v){
    std::string& vectorName = v.name();
    std::transform(vectorName.begin(),vectorName.end(),vectorName.begin(),[](char c){
        return std::toupper(c);
    });
}

template <typename T> 
void sort(named_vector<T>& v){
    std::sort(v.begin(),v.end());
}

template <typename T> 
void rotate(named_vector<T>& v,int pos){
    std::rotate(v.begin(),v.begin()+pos,v.end());
}

template <typename T> 
void reverse(named_vector<T>& v){
    std::reverse(v.begin(),v.end());
}

}