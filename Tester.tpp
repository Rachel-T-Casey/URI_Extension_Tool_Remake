#ifndef TESTER_TPP
#define TESTER_TPP
   

template <typename Fn, typename ExpectedReturn, typename ...Args>
bool Tester::test(Fn &fn, bool expectedCrash, ExpectedReturn expectedReturn, Args... args) {
    
    decltype(std::forward<Fn>(fn)(std::forward<Args>(args)...)) r;
    try {
        r = std::forward<Fn>(fn)(std::forward<Args>(args)...);
        if(expectedCrash) {
            return false;
        } else {
            return r == expectedReturn;
        }
    } catch (std::exception& ex ){return expectedCrash;} 
}

template <typename Fn, typename Er, typename ...Args>
void Tester::testCase(Fn &fn, bool ec, Er er, Args... args)
{   
    bool result = this->test(fn, ec, er, std::forward<Args>(args)...);
    this->testResults.push_back(result);
}

#endif