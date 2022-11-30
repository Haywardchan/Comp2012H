#include <typeinfo>
#include <iostream>

class object {
    private:
        /** 
         * TODO: Using the idea of dynamic binding, and generalization to complete the definition of struct `object_pointer` and `T_pointer` below.
         * You are ONLY allowed to modify the struct `object_pointer` and `T_pointer`.
         * You are NOT allowed to add data member to both structs.
        */
        
        // Your modification starts here.
        struct object_pointer {
            // default constructor will be          
            virtual const std::type_info& type() const = 0;
            virtual object_pointer* copy() const = 0;
            virtual object_pointer* add(const object_pointer& other) const = 0;
            virtual bool equal(const object_pointer& other) const = 0;
            virtual std::ostream& print(std::ostream& os) const = 0;
        };
        // Your modification ends here.

        // Your modification starts here.
        template <typename T>
        struct T_pointer : public object_pointer {
            T value;
            T_pointer(T value);
            const std::type_info& type() const;
            object_pointer* copy() const;
            object_pointer* add(const object_pointer& other) const {
                T_pointer<T>* sum_pointer = new T_pointer<T>(this->value + dynamic_cast<const T_pointer<T>*>(&other)->value);
                return sum_pointer;
            }
            bool equal(const object_pointer& other) const {
                return (this->value == dynamic_cast<const T_pointer<T>*>(&other)->value);
            }
            std::ostream& print(std::ostream& os) const {
                return (os << this->value);
            }
            // an alternative implementation would be to override the << operator for each T_pointer class
            // but I am unable and too lazy to do so
        };
        // Your modification ends here.
        
        object_pointer* obj_ptr;

    public:

        template <typename T>
        object(const T& value);

        object(const object& other);

        ~object();

        object& operator=(const object& other);

        const std::type_info& type() const;

        template <typename T>
        T cast_back() const;

        //Default constructor defaults a value of int 0
        object() : object(0) {}

        /**
         * Bonus part of the assignment. You may choose to or not to finish it.
         * You will need to uncomment the respective function declaration if you have implemented it.
        */

        object operator+(const object& other) const;
        bool operator==(const object& other) const;
        friend std::ostream& operator<<(std::ostream &os, const object& obj);
};

#include "object.tpp"