#ifndef TESTER_HPP
#define TESTER_HPP

#include <memory>
#include <vector>
class Tester {
    public:

    template <typename Fn, typename ExpectedReturn, typename ...Args>
    void testCase(Fn &fn, bool expectedCrash, ExpectedReturn expectedReturn, Args... args);

    std::vector<bool> getTestResults() const { return this->testResults; }
    void clearTestCases() { this->testResults.clear();}
    private:
    template <typename Fn, typename ExpectedReturn, typename ...Args>
    bool test(Fn &fn, bool expectedCrash, ExpectedReturn expectedReturn, Args... args);
    
    std::vector<bool> testResults;
};


#include "Tester.tpp"

#endif