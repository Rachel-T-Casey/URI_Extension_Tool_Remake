#ifndef REQUEST_EXTENSION_HPP
#define REQUEST_EXTENSION_HPP

#include "Request.hpp"

class RequestExtender : public Request
{

    private:
        void start();
        void finish();
};

#endif