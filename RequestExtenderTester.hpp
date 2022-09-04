#ifndef REQUEST_EXTENDER_TESTER_HPP
#define REQUEST_EXTENDER_TESTER_HPP
#include "RequestExtender.hpp"
#include "Tester.hpp"
#include <functional>

#include <vector>

/**
* Unit test class for functions in the RequestExtender class
* 
* To use, call the respective test function to test the behavior of any given function,
* or testAll to test if test cases for all functions pass. A test returns true to indicate
* that it passed, or false to indicate that the test failed 
* 
* @return Returns true if the respective function passed all test cases, or false if the 
* function failed at least one test case
*/ 

class RequestExtenderTester : public Tester{
    public:
        std::vector<bool>  testMean();
        std::vector<bool>  testSD();
        std::vector<bool>  testBuildHistogram();
        std::vector<bool>  testCanBuildHistogram();
        std::vector<bool>  testGraphHistogram();
        std::vector<bool>  testAll();
    };

#endif