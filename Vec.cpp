#include<stdexcept>
#include<algorithm>
#include<iostream>
template<typename T>
class Vector{

private:

    T* elements;

    size_t capacity;

    size_t size;

    void reserve(size_t newCapacity)
    {
        if(newCapacity == capacity) return;

        T* newElements = new T[newCapacity];

        if(newCapacity >= size)
        {
            std::copy(elements, elements + size, newElements);
            delete [] elements;
            elements = newElements;
            capacity = newCapacity;
        }

        else
        {
            std::copy(elements, elements + newCapacity, newElements);
            delete [] elements;
            elements = newElements;
            capacity = newCapacity;
            size = newCapacity;
        }
        
    }

public:

    Vector() : elements(nullptr), capacity(0), size(0){}

    ~Vector()
    {
        delete[] elements;
    }

    Vector(const Vector& other) : capacity(other.capacity), size(other.size)
    {
        elements = new T[capacity];
        std::copy(other.elements, other.elements + size, elements);
    }

    Vector& operator=(const Vector& other)
    {
        if(this != &other)
        {
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }

        return *this;
    }

    T& operator[](size_t index)
    {
        if(index >= size)
        {
            throw std::out_of_range("Index out of range");
        }

        return elements[index];
    }

    const T& operator[](size_t index) const
    {
        if(index >= size)
        {
            throw std::out_of_range("Index out of range");
        }

        return elements[index];
    }

    size_t getSize() const
    {
        return size;
    }

    size_t getCapacity() const
    {
        return capacity;
    }

    T* begin()
    {
        return elements;
    }

    T* end()
    {
        return elements + size;
    }

    const T* begin() const
    {
        return elements;
    }

    const T* end() const
    {
        return elements + size;
    }

    void push_back(const T &val)
    {
        if(size == capacity) 
        {
            reserve(capacity == 0 ? 1 : 2 * capacity);
        }

        elements[size++] = val;
    }

    void pop_back()
    {
        if(size-- == 0)
        {
            throw std::out_of_range("Vector is empty");
        }
    }

    const T& back()
    {
        if(size == 0)
        {
            throw std::out_of_range("Vector is empty");
        }

        return elements[size - 1];
    }

    void insert(const T& val, size_t index)
    {
        if(index > size)
        {
            throw std::out_of_range("Index out of range");
        }

        if(index == capacity || size == capacity)
        {
            reserve(capacity == 0 ? 1 : 2 * capacity);
        }

        for(size_t idx = size; idx > index; idx--)
        {
            elements[idx] = elements[idx - 1];
        }

        elements[index] = val;
        ++size;
    }

    void erase(size_t index)
    {
        if(index >= size)
        {
            throw std::out_of_range("Index out of range");
        }

        for(size_t idx = index; idx < size - 1; ++idx)
        {
            elements[idx] = elements[idx + 1];
        }
        
        --size;
    }

    void resize(size_t newSize)
    {
        if(newSize <= size)
        {
            size = newSize;
        }
        else
        {
            while(newSize > capacity)
            {
                reserve(capacity == 0 ? 1 : 2 * capacity);
            }
            
            for(size_t idx = size; idx < newSize; ++ idx)
            {
                elements[idx] = 0;
            }
            size = newSize;
        }
    }

    void clear()
    {
        size = 0;
    }
    
    friend std::ostream& operator<<(std::ostream &os, const Vector &vec)
    {
        if(vec.size > 0)
        {
            for(size_t i = 0; i < vec.size - 1; ++ i)
            {
                os << vec.elements[i] << " ";
            }
            os << vec.elements[vec.size - 1];
        }
        return os;
    }

};

int main(){
    Vector<int> vec;
    std::cout<<"push_back test"<<std::endl;
    for(int i = 0; i < 10; i++){
        vec.push_back(i);
    }
    std::cout<<vec<<std::endl;

    std::cout<<"pop_back test"<<std::endl;
    vec.pop_back();
    std::cout<<vec<<std::endl;

    std::cout<<"back test"<<std::endl;
    std::cout<<vec.back()<<std::endl;

    std::cout<<"insert test"<<std::endl;
    vec.insert(99,2);
    std::cout<<vec<<std::endl;

    std::cout<<"erase test"<<std::endl;
    vec.erase(2);
    std::cout<<vec<<std::endl;

    std::cout<<"[]operator test"<<std::endl;
    std::cout<<vec[3]<<std::endl;

    std::cout<<"resize test"<<std::endl;
    vec.resize(2);
    std::cout<<vec<<std::endl;
    vec.resize(20);
    std::cout<<vec<<std::endl;

    vec[21];
    return 0;
}