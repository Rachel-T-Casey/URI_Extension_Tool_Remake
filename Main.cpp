#include <iostream>
#include <vector>
#include "RequestExtenderTester.hpp"
void requestExtenderTestDriver();
int main(int argc, char const *argv[]){
    requestExtenderTestDriver();
    return 0;
}

void requestExtenderTestDriver() {
    std::cout << "Beginning tests on request extender" << std::endl;
    RequestExtenderTester R;
    std::vector<bool> testResults;
    testResults = R.testMean();
    for(unsigned int i = 0; i < testResults.size(); i++){
        if(!testResults[i]) {
            std::cout << "testMean() failed test case: " << i << std::endl;
        }
        else {
            std::cout << "testMean() passed test case: " << i << std::endl;
        }

    }

}