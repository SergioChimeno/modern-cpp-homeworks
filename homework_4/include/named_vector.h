#pragma once

#include <vector>
#include <string>
#include <array>
#include <initializer_list>

namespace ipb{

    template <typename T>
    struct named_vector : public std::vector<T> {        
        std::string name_;

        named_vector(const char name[], std::initializer_list<T> l)
        : std::vector<T>(l), name_(name)
        {
        }

        inline std::string& name(){
            return name_;
        }

        inline std::vector<T> vector(){
            return *this;
        }

        inline std::size_t size() const{
            return name_.size() + std::vector<T>::size();
        }

        inline bool empty() const{
            return name_.empty() || std::vector<T>::empty();
        }
    };

}