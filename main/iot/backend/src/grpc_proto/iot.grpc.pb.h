// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: iot.proto
#ifndef GRPC_iot_2eproto__INCLUDED
#define GRPC_iot_2eproto__INCLUDED

#include "iot.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace iot {

class IOT final {
 public:
  static constexpr char const* service_full_name() {
    return "iot.IOT";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status SetShadeSchedule(::grpc::ClientContext* context, const ::iot::Schedule& request, ::iot::Status* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::iot::Status>> AsyncSetShadeSchedule(::grpc::ClientContext* context, const ::iot::Schedule& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::iot::Status>>(AsyncSetShadeScheduleRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::iot::Status>> PrepareAsyncSetShadeSchedule(::grpc::ClientContext* context, const ::iot::Schedule& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::iot::Status>>(PrepareAsyncSetShadeScheduleRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      virtual void SetShadeSchedule(::grpc::ClientContext* context, const ::iot::Schedule* request, ::iot::Status* response, std::function<void(::grpc::Status)>) = 0;
      virtual void SetShadeSchedule(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::iot::Status* response, std::function<void(::grpc::Status)>) = 0;
    };
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::iot::Status>* AsyncSetShadeScheduleRaw(::grpc::ClientContext* context, const ::iot::Schedule& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::iot::Status>* PrepareAsyncSetShadeScheduleRaw(::grpc::ClientContext* context, const ::iot::Schedule& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status SetShadeSchedule(::grpc::ClientContext* context, const ::iot::Schedule& request, ::iot::Status* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::iot::Status>> AsyncSetShadeSchedule(::grpc::ClientContext* context, const ::iot::Schedule& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::iot::Status>>(AsyncSetShadeScheduleRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::iot::Status>> PrepareAsyncSetShadeSchedule(::grpc::ClientContext* context, const ::iot::Schedule& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::iot::Status>>(PrepareAsyncSetShadeScheduleRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void SetShadeSchedule(::grpc::ClientContext* context, const ::iot::Schedule* request, ::iot::Status* response, std::function<void(::grpc::Status)>) override;
      void SetShadeSchedule(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::iot::Status* response, std::function<void(::grpc::Status)>) override;
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::iot::Status>* AsyncSetShadeScheduleRaw(::grpc::ClientContext* context, const ::iot::Schedule& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::iot::Status>* PrepareAsyncSetShadeScheduleRaw(::grpc::ClientContext* context, const ::iot::Schedule& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_SetShadeSchedule_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status SetShadeSchedule(::grpc::ServerContext* context, const ::iot::Schedule* request, ::iot::Status* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_SetShadeSchedule : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_SetShadeSchedule() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_SetShadeSchedule() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SetShadeSchedule(::grpc::ServerContext* context, const ::iot::Schedule* request, ::iot::Status* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSetShadeSchedule(::grpc::ServerContext* context, ::iot::Schedule* request, ::grpc::ServerAsyncResponseWriter< ::iot::Status>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_SetShadeSchedule<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_SetShadeSchedule : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithCallbackMethod_SetShadeSchedule() {
      ::grpc::Service::experimental().MarkMethodCallback(0,
        new ::grpc::internal::CallbackUnaryHandler< ::iot::Schedule, ::iot::Status>(
          [this](::grpc::ServerContext* context,
                 const ::iot::Schedule* request,
                 ::iot::Status* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   return this->SetShadeSchedule(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithCallbackMethod_SetShadeSchedule() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SetShadeSchedule(::grpc::ServerContext* context, const ::iot::Schedule* request, ::iot::Status* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void SetShadeSchedule(::grpc::ServerContext* context, const ::iot::Schedule* request, ::iot::Status* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  typedef ExperimentalWithCallbackMethod_SetShadeSchedule<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_SetShadeSchedule : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_SetShadeSchedule() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_SetShadeSchedule() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SetShadeSchedule(::grpc::ServerContext* context, const ::iot::Schedule* request, ::iot::Status* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_SetShadeSchedule : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_SetShadeSchedule() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_SetShadeSchedule() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SetShadeSchedule(::grpc::ServerContext* context, const ::iot::Schedule* request, ::iot::Status* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSetShadeSchedule(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_SetShadeSchedule : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    ExperimentalWithRawCallbackMethod_SetShadeSchedule() {
      ::grpc::Service::experimental().MarkMethodRawCallback(0,
        new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
          [this](::grpc::ServerContext* context,
                 const ::grpc::ByteBuffer* request,
                 ::grpc::ByteBuffer* response,
                 ::grpc::experimental::ServerCallbackRpcController* controller) {
                   this->SetShadeSchedule(context, request, response, controller);
                 }));
    }
    ~ExperimentalWithRawCallbackMethod_SetShadeSchedule() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SetShadeSchedule(::grpc::ServerContext* context, const ::iot::Schedule* request, ::iot::Status* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual void SetShadeSchedule(::grpc::ServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response, ::grpc::experimental::ServerCallbackRpcController* controller) { controller->Finish(::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "")); }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SetShadeSchedule : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_SetShadeSchedule() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::iot::Schedule, ::iot::Status>(std::bind(&WithStreamedUnaryMethod_SetShadeSchedule<BaseClass>::StreamedSetShadeSchedule, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_SetShadeSchedule() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SetShadeSchedule(::grpc::ServerContext* context, const ::iot::Schedule* request, ::iot::Status* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSetShadeSchedule(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::iot::Schedule,::iot::Status>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_SetShadeSchedule<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_SetShadeSchedule<Service > StreamedService;
};

}  // namespace iot


#endif  // GRPC_iot_2eproto__INCLUDED
