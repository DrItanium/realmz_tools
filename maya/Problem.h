//
// Created by jwscoggins on 6/21/20.
//

#ifndef MAYA_PROBLEM_H
#define MAYA_PROBLEM_H
#include <exception>
#include <string>

class Problem : public std::exception {
public:
    explicit Problem(const std::string& msg) noexcept : _msg(msg) { }
    ~Problem() noexcept override = default;
    std::string message() const noexcept { return _msg; }
    const char* what() const noexcept override final { return _msg.c_str(); }
    Problem& operator=(const Problem&) = delete;
private:
    std::string _msg;
};

#endif //MAYA_PROBLEM_H
