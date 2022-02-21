
template <typename T>
class ADT_Stack {
    private:
        int size, space;
        T *items;
        bool h, k;
        int addk;
    public:
        ADT_Stack();
        ~ADT_Stack();
        bool add(const T&);
        bool remove();

};