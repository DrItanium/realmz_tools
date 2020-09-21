//
// Created by jwscoggins on 6/21/20.
//

#ifndef MAYA_GENERICVIEW_H
#define MAYA_GENERICVIEW_H
namespace maya {
    template<typename T>
    class GenericView {
    public:
        explicit GenericView(T& v) : _raw(v) { }
    protected:
        T& _raw;

    };
} // end namespace maya

#endif //MAYA_GENERICVIEW_H
