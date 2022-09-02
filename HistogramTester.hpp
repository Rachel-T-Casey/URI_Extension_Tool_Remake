#ifndef HISTOGRAM_TESTER_HPP
#define HISTOGRAM_TESTER_HPP
#include "RequestExtender.hpp"
    /**
     * Unit test class for functions in the Histogram class
     * 
     * To use, call the respective test function to test the behavior of any given function,
     * or testAll to test if test cases for all functions pass. A test returns true to indicate
     * that it passed, or false to indicate that the test failed 
     * 
     * @return Returns true if the respective function passed all test cases, or false if the 
     * function failed at least one test case
    */ 
    class HistogramTester : public RequestExtender::Histogram {
        bool testNormalize();
        bool testNormalizeDataset();
        bool testFillBins();
        bool testBins();
        bool testBinSize();
        bool testHistogram();
        bool testAll();
    };

#endif