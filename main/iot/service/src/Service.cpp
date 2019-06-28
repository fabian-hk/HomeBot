#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include "grpc_proto/iot.grpc.pb.h"
#include "grpc_proto/iot.pb.h"

#include "tools/Ping.h"

#include "Database.h"

#define PORT 8448

iot::Schedule controlledSchedule;

bool sendControlRequest(std::string id, std::vector<char> values);

class IotImpl final : public iot::IOT::Service {
public:
    grpc::Status SetShadeSchedule(grpc::ServerContext *serverContext,
                                  const iot::Schedule *schedule, iot::Status *status) override {
        std::cout << "Identifier: " << schedule->id() << std::endl;

        if(schedule->time() == -1) {
            std::vector<char> input;
            input.push_back(0x00);
            for (size_t i = 0; i < 3; i++) {
                std::cout << "Shade " << i << " position: " << schedule->positions(i) << std::endl;
                input.push_back(schedule->positions(i));
            }
            if(sendControlRequest(schedule->id(), input))
                status->set_status(0);
            else
                status->set_status(1);
        } else {
            controlledSchedule = *schedule;
            status->set_status(0);
        }

        return grpc::Status::OK;
    }
};

void startService() {
    // define variables
    std::string server_address = "0.0.0.0:1616";
    IotImpl service;
    bool open = false;

    // load database for iot devices
    auto db = Database::getInstance();
    std::unordered_map<std::string, std::vector<std::string>> *iotConfig;
    iotConfig = db->getIotData();

    // initialize variables
    controlledSchedule.set_time(google::protobuf::kint64max);

    // start gRPC server
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch());

        if (controlledSchedule.time() != google::protobuf::kint64max
                && controlledSchedule.time() < ms.count()) {
            std::cout << "Move shade. Time: " << controlledSchedule.time() << std::endl;

            std::vector<char> input;
            input.push_back(0x00);
            for (size_t i = 0; i < 3; i++) {
                std::cout << "Shade " << i << " position: " << controlledSchedule.positions(i) << std::endl;
                input.push_back(controlledSchedule.positions(i));
            }
            sendControlRequest(controlledSchedule.id(), input);
            controlledSchedule.set_time(google::protobuf::kint64max);
            open = true;
        }

        if(open && sendPing((*iotConfig)["phone"][0].c_str(), 500)) {
            printf("open shade\n");
            std::vector<std::string> data;
            db->getIotDataByInfo("sleep", &data);
            std::vector<char> state = {0x00, 0x00, 0x14, 0x00};
            sendControlRequest(data[0], state);
            open = false;
        }
    }
}

bool sendControlRequest(const std::string id, std::vector<char> values) {
    auto db = Database::getInstance();
    std::unordered_map<std::string, std::vector<std::string>> *iotConfig;
    iotConfig = db->getIotData();
    int sock, ret = 0;
    struct sockaddr_in serv_addr;

    const int bufferSize = 16;
    char buffer[bufferSize] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return false;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // check if id exists
    std::unordered_map<std::string, std::vector<std::string>>::const_iterator el = (*iotConfig).find(id);
    if (el == (*iotConfig).end()) {
        return false;
    }

    std::string addr = (*iotConfig)[id][0];
    if (inet_pton(AF_INET, addr.c_str(), &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return false;
    }

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return false;
    } else {
        ret = read(sock, buffer, bufferSize);
        send(sock, values.data(), values.size(), 0);
        ret = read(sock, buffer, bufferSize);
        close(sock);
        std::cout << "Received: " << (int) buffer[0] << std::endl;

        if (buffer[0] == 0) {
            return true;
        }
        return false;
    }
}

/*
 * Method for python binding
 */
std::string controlWindowShade(std::string id, std::string values, std::string configPath) {
    auto db = Database::getInstance();
    db->setConfigFilePath(configPath);
    std::vector<std::string> valuesSplit;
    boost::split(valuesSplit, values, boost::is_any_of(","));
    int tmp;
    std::vector<char> input;
    input.push_back(0x00);
    for(size_t i=0; i<3; i++) {
        tmp = std::stoi(valuesSplit[i]);
        std::cout << "Values: " << tmp << std::endl;
        if(tmp >= 0 && tmp <= 100) {
            input.push_back(tmp);
        } else {
            return "Value " + std::to_string(tmp) + " not in range";
        }
    }

    bool status = sendControlRequest(id, input);

    if (!status) {
        return "Request failed";
    }
    return "Request successful";
}

std::string getStatus(const std::string id, std::string configPath) {
    auto db = Database::getInstance();
    db->setConfigFilePath(configPath);
    std::unordered_map<std::string, std::vector<std::string>> *iotConfig;
    iotConfig = db->getIotData();
    int sock, ret = 0;
    struct sockaddr_in serv_addr;

    const int bufferSize = 16;
    char buffer[bufferSize] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return "Connection failed";
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // check if id exists
    std::unordered_map<std::string, std::vector<std::string>>::const_iterator el = (*iotConfig).find(id);
    if (el == (*iotConfig).end()) {
        return "Invalid devices selected";
    }

    std::string addr = (*iotConfig)[id][0];
    if (inet_pton(AF_INET, addr.c_str(), &serv_addr.sin_addr) <= 0) {
        return "Connection failed";
    }

    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        return "Connection failed";;
    } else {
        ret = read(sock, buffer, bufferSize);
        char payload[1] = {0x01};
        send(sock, payload, sizeof(payload), 0);
        ret = read(sock, buffer, bufferSize);
        close(sock);

        std::string retVal;
        for(size_t i=0; i<3; i++) {
            retVal += std::to_string((int) buffer[i]);
            if(i<2) {
                retVal += ",";
            }
        }

        return "Status: " + retVal;
    }
}


