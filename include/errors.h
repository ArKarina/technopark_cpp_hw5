#ifndef ERRORS_H
#define ERRORS_H

#include <exception>
#include <string>
#include <time.h>

#define NO_ERR 0

class BaseError : public std::exception {
public:
  BaseError(std::string msg, std::string filename, std::string name, int line,
            std::string title = "Error! \n") {
    error_msg = title + msg;
    error_msg += "\nFile name: " + filename;
    error_msg += "\nName: " + name;
    error_msg += "\nLine#: " + std::to_string(line);
    error_msg += "\nTime: ";
    error_msg += ctime(&error_time);
  }
  virtual const char *what() const noexcept override {
    return error_msg.c_str();
  }

protected:
  std::string error_msg;
  time_t error_time = time(NULL);
};

class IndexError : public BaseError {
public:
  IndexError(std::string msg, std::string filename, std::string name, int line,
             std::string title = "Indexing error! ")
      : BaseError(msg, filename, name, line, title){};
};

class SizeError : public BaseError {
public:
  SizeError(std::string msg, std::string filename, std::string name, int line,
            std::string title = "Size error! ")
      : BaseError(msg, filename, name, line, title){};
};

class DataError : public BaseError {
public:
  DataError(std::string msg, std::string filename, std::string name, int line,
            std::string title = "Data error! ")
      : BaseError(msg, filename, name, line, title){};
};

#endif // ERRORS_H
