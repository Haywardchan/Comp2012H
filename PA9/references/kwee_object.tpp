#ifndef __OBJECT_T_
#define __OBJECT_T_

// #include "object.hpp"

template <typename T>
object::T_pointer<T>::T_pointer(T value) {
    this->value = value;
}

template <typename T>
const std::type_info& object::T_pointer<T>::type() const {
    return typeid(this->value);
}

template <typename T>
object::object_pointer* object::T_pointer<T>::copy() const {
    T_pointer<T> *newPointer = new T_pointer<T>(this->value);
    return newPointer;
}

template <typename T> 
object::object(const T& value) {
    obj_ptr = new T_pointer<T>(value);
}

object::~object() {
    delete obj_ptr;
}

object& object::operator=(const object& other) {
    delete obj_ptr;
    obj_ptr = other.obj_ptr->copy();
    return *this;
}

object::object(const object& other) {
    obj_ptr = other.obj_ptr->copy();
}

const std::type_info& object::type() const {
    return obj_ptr->type();
}

template <typename T>
T object::cast_back() const {
    return dynamic_cast<T_pointer<T>*>(obj_ptr)->value;
}

object object::operator+(const object& other) const {
    if (this->type() != other.type())
        throw std::runtime_error("Types needed to be the same when performing +");
    object_pointer* sum_pointer = this->obj_ptr->add(*(other.obj_ptr));
    object sum_object = object();
    delete sum_object.obj_ptr;
    sum_object.obj_ptr = sum_pointer;
    return sum_object;
}

bool object::operator==(const object& other) const {
    if (this->type() != other.type())
        return false;
    return this->obj_ptr->equal(*(other.obj_ptr));
}

std::ostream& operator<<(std::ostream &os, const object& obj) {
    return obj.obj_ptr->print(os);
}
#endif // __OBJECT_T_