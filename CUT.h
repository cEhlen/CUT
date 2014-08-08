//
//  CUT.h
//  CUT
//
//  Created by Christoph Ehlen on 08/08/14.
//  Copyright (c) 2014 ColorFit. All rights reserved.
//

#ifndef CUT_CUT_h
#define CUT_CUT_h

#include <strstream>
#include <iostream>
#include <cmath>

#define DESCRIBE(X, Y) assert.describe((#X), [&assert] () Y)

#define IT(X, Y) assert.it((#X), [&assert] () Y)

#define TEST(X) int main(int argc, const char* argv[]) {\
CUT::TestSuite assert; \
X }

namespace CUT {

class Reporter {
    int m_indent;
    bool m_newlineNeeded;
public:
    Reporter () { m_indent = 0; m_newlineNeeded = false; }
    void ReportDescribe(const std::string& desc) {
        if (m_newlineNeeded) {
            std::cout << std::endl;
            m_newlineNeeded = false;
        }
        std::cout << std::string(m_indent, ' ') << desc << std::endl;
        m_indent += 2;
    }
    
    void ReportIt(const std::string& desc) {
        if (m_newlineNeeded) {
            std::cout << std::endl;
            m_newlineNeeded = false;
        }
        std::cout << std::string(m_indent, ' ') << desc << std::endl;
        m_indent += 2;
    }
    
    void ReportAssert(const std::string& msg, bool success) {
        std::cout << std::string(m_indent, ' ');
        if (success) {
            std::cout << "\033[1;32m.\033[0m";
            m_newlineNeeded = true;
        } else {
            if (m_newlineNeeded) {
                std::cout << std::endl;
                m_newlineNeeded = false;
            }
            std::cout << "\033[1;31mX\033[0m ";
            std::cout <<  msg << std::endl;
        }
    }
    
    void End() {
        m_indent -= 2;
    }
};
    
class TestSuite {
    Reporter reporter;
public:
    template <typename Functor>
    void describe(const std::string& name, Functor functor) {
        reporter.ReportDescribe(name);
        functor();
        reporter.End();
    }
    
    template <typename Functor>
    void it(const std::string& description, Functor functor) {
        reporter.ReportIt(description);
        functor();
        reporter.End();
    }
    
    template<typename T>
    void equals(T result, T expected) {
        if(result == expected) {
            reporter.ReportAssert("", true);
        } else {
            std::strstream str;
            str << "Assertion Error: Expeted " << result << " to be EQUAL " <<  expected;
            reporter.ReportAssert(str.str(), false);
        }
    }
    
    template<typename T>
    void almost_equals(T result, T expected, int places = 5) {
        int rslt = floor(result * pow(10.0, (double)places));
        int e = floor(expected * pow(10.0, (double)places));
        if(rslt == e) {
            reporter.ReportAssert("", true);
        } else {
            std::strstream str;
            str << "Assertion Error: Expeted " << result << " to be ALMOST_EQUAL " <<  expected << " with a precision of " << places << " places";
            reporter.ReportAssert(str.str(), false);
        }
    }
};

    
}
#endif
