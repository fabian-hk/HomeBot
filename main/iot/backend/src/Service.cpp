#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "grpc_proto/iot.grpc.pb.h"
#include "grpc_proto/iot.pb.h"

std::list<const iot::Schedule*> controlTimes;

class IotImpl final : public iot::IOT::Service {
public:
    grpc::Status SetShadeSchedule(grpc::ServerContext *serverContext,
                                  const iot::Schedule *schedule, iot::Status *status) override {
        controlTimes.push_back(schedule);

        std::cout << "Time: " << schedule->time() << std::endl;
        for (size_t i = 0; i < schedule->positions_size(); i++) {
            std::cout << "Shade " << i << " position: " << schedule->positions(i) << std::endl;
        }
        status->set_status(99);
        std::cout << "Function was called" << std::endl;
        return grpc::Status::OK;
    }
};

void startService() {
    std::cout << "Starting.." << std::endl;
    std::string server_address("0.0.0.0:1616");
    IotImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // local variable definition
    const iot::Schedule *schedule;

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());

        std::list<const iot::Schedule*>::iterator iter = controlTimes.begin();
        while (iter != controlTimes.end()){
            schedule = *iter;
            if (schedule->time() < ms.count()) {

                std::cout << "Move shade" << std::endl;
                controlTimes.erase(iter++);
            } else {
                iter++;
            }

        }

    }
}
