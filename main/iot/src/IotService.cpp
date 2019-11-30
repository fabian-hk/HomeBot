#include <boost/python.hpp>

#include "Service.h"
#include "../../utils/Ping.h"

BOOST_PYTHON_MODULE(libiotservice) {
    // Add regular functions to the module.
    using namespace boost::python;
    def("control_shade", controlWindowShade);
    def("get_status",getStatus);
    def("send_ping", sendPing);
}



