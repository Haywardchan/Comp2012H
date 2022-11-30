
//member functions for T pointers
template <typename T>
object::T_pointer<T>::T_pointer(T value){
    this->value=value;
}
template <typename T>
const std::type_info& object::T_pointer<T>::type() const {
    return typeid(this->value);
}

template <typename T>
object::object_pointer* object::T_pointer<T>::copy() const {
    //deep copy:
    object_pointer* copyptr=new T_pointer<T>(this->value);
    return copyptr;
}

//member functions for objects
template <typename T> 
object::object(const T& value) {
    obj_ptr=new T_pointer<T>(value);
}

object::~object() {
    delete obj_ptr;
}

object& object::operator=(const object& other) {
    //delete current object
    delete obj_ptr;
    // //deep copy
    obj_ptr = other.obj_ptr->copy();
    return *this;
    
}

object::object(const object& other) {
    obj_ptr=other.obj_ptr->copy();
}

const std::type_info& object::type() const {
    return obj_ptr->type();
}

template <typename T>
T object::cast_back() const {
    if(obj_ptr->type()==this->type())return dynamic_cast<T_pointer<T>*>(obj_ptr)->value;
    else throw std::runtime_error("Object casting failed!");
    return 0;
}

template<typename T>
object::object_pointer* object::T_pointer<T>::sum(object_pointer* other)const{
    object_pointer* new_object_pointer=new T_pointer<T>(this->value+dynamic_cast<T_pointer<T>*>(other)->value);
    return new_object_pointer;
}
object object::operator+(const object& other) const {
    object* new_object= new object();
    new_object->obj_ptr=this->obj_ptr->sum(other.obj_ptr);
    return *new_object;
}

template<typename T>
bool object::T_pointer<T>::same_value(object_pointer* other) const{
    if(this->value==dynamic_cast<T_pointer<T>*>(other)->value)return true;
    else return false;
}

bool object::operator==(const object& other) const {
    // std::cout<<this->obj_ptr<<" "<<other.obj_ptr->copy();
    if(this->type()!=other.type())return false;
    else return this->obj_ptr->same_value(other.obj_ptr);
}
std::ostream& operator<<(std::ostream &os, const object& obj) {
    return obj.obj_ptr->output(os);
}