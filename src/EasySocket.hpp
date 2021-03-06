/**
*******************************************************************************
* <p><b>Project httpu</b><br/>
* </p>
* @author Keidan
*
*******************************************************************************
*/
#ifndef __EASYSOCKET_H__
#define __EASYSOCKET_H__

#include <exception>
#include <string>
#include <openssl/ssl.h>
#include <openssl/bio.h> 


namespace net {

  class EasySocketException: public std::exception {
    public:
      EasySocketException(std::string msg) : _msg(msg) { }
      virtual ~EasySocketException() = default;

      virtual const char* what() const throw() { return _msg.c_str(); }
    private:
      std::string _msg;
  };

  class EasySocket {
    public:

      EasySocket();
      ~EasySocket();
      
      /**
       * @brief Initialize the SSL stack, should be called only once in your application.
       * @return false if the initialization fail, true else.
       */
      static auto loadSSL() -> bool;

      /**
       * @brief Release the SSL stack, should be called only once in your application.
       */
      static auto unloadSSL() -> void;

      /**
       * Get the last SSL error
       */
      static auto lastErrorSSL() -> std::string;

      /**
       * @brief Connect the socket to the remote address.
       * @param host The remote address.
       * @param port The remote port.
       * @return EasySocketResult
       */
      auto connect(std::string host, int port) -> void;

      /**
       * @brief Close the socket with the remote address.
       */
      auto disconnect() -> void;

      /**
       * @brief Change the SSL status.
       * @param useSSL SSL status.
       */
      auto ssl(int useSSL) -> void;

      /**
       * @brief Get The SSL status.
       * @return bool
       */
      auto ssl() -> bool;

      /**
       * @brief Get the socket descriptor.
       * @return int
       */
      auto fd() -> int;

      /**
       * @brief Write some data to the socket descriptor.
       * @param toWrite The data to write.
       */
      auto write(const std::string toWrite) -> void;

      /**
       * @brief Read some data from the socket descriptor.
       * @param toRead The data reads.
       */
      auto read(std::string &toRead) -> void;

      /**
       * @brief Write some data to the socket descriptor.
       * @param toWrite The data to write.
       * @return EasySocket&
       */
      EasySocket& operator << (const std::string toWrite) {
	write(toWrite);
	return *this;
      }

      /**
       * @brief Read some data from the socket descriptor.
       * @param toWrite The data reads.
       * @return EasySocket&
       */
      EasySocket& operator >> (std::string &toRead) {
	read(toRead);
	return *this;
      }

      /**
       * @brief Test if EOF is reached.
       * @return bool
       */
      auto isEOF() -> bool;

    private:
      int _fd;
      bool _useSSL;
      bool _open;
      SSL_CTX *_ctx;
      SSL     *_ssl;
      static unsigned long _lib_ssl_errno;
  };

} /* namespace net */
#endif /* __EASYSOCKET_H__ */
