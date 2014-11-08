#ifndef	SPIDER_H
# define SPIDER_H

#include <memory>
#include <string>


#include "ICircularBuffer.hpp"
#include "IConnectSocket.hpp"

class Network;

class Spider : public std::enable_shared_from_this<Spider>
{
  constexpr static unsigned	bufferSize = 1024;

public:
  Spider(const std::shared_ptr<IConnectSocket>& sock, Network& net);
  virtual ~Spider(void) = default;
  Spider(const Spider& other) = delete;
  Spider&	operator=(const Spider& other) = delete;

  void   spy();

  const std::shared_ptr<IConnectSocket>&	getSocket(void) const;

  Spider& operator<<(const std::vector<uint8_t>& buff);

  void      read(size_t size);
  void      write();

  void		onRead(size_t size);
  void		onWrite(size_t size);

  const std::string& getIdentity() const {return _identity;};

private:
  std::string _identity;

  IConnectSocket::t_writeCallback _writeCallback;
  IConnectSocket::t_readCallback _readCallback;
  std::vector<uint8_t>  _read;
  std::vector<uint8_t>  _write;
  std::shared_ptr<IConnectSocket> _socket;

  Network&      _network;
};

#endif /* SPIDER_H */
