#include <iostream>
#include <inttypes.h>
#include <cinttypes>
#include <cmath>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sys/time.h>
#include <ctime>

typedef double TDBL ;

class Handler {
 public:
  virtual Handler *SetNext(Handler *handler) = 0;
  virtual std::vector< double > Handle(std::string request, double (*f)(double), TDBL a, TDBL b, std::vector< double > mins) = 0;
};

class AbstractHandler : public Handler {
 private:
  Handler *next_handler_;

 public:
  AbstractHandler() : next_handler_(nullptr) {
  }
  Handler *SetNext(Handler *handler) override {
    this->next_handler_ = handler;
    return handler;
  }
  std::vector< double > Handle(std::string request, double (*f)(double), TDBL a, TDBL b, std::vector< double > mins) override {
    if (this->next_handler_) {
      return this->next_handler_->Handle(request, f, a, b, mins);
    }

    return {};
  }
};