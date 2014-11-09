#include "ClientNetwork.hpp"

#include "BoostOpenSslConnectSocket.hpp"
#include "BoostSslCtxClient.hpp"

ClientNetwork::ClientNetwork()
: _connect(false)
{
    BoostSslCtxClient ctx;
    BoostSslCtx &ctxref = ctx;
    _socket = std::unique_ptr<IConnectSocket>(new BoostOpenSslConnectSocket(_ios, ctxref));
}

ClientNetwork::~ClientNetwork()
{

}

bool ClientNetwork::connect(int port, std::string host, const std::string &id)
{
	if (!_socket->connect(host, port))
		_connect = false;
	else
	{
		int version = 0x312E3076;
		std::vector<uint8_t> result;
		HandshakeResult test;

		_socket->write(&version, sizeof(version));
		_socket->write(id.c_str(), id.size() + 1);
		_socket->read(result, 2);
		try
		{
			test.from_bytes(result);
			_connect = true;
		}
		catch (std::runtime_error)
		{
			_connect = false;
		}
	}
	return (_connect);
}

bool ClientNetwork::isConnected() const
{
    return (_connect);
}

ClientNetwork &ClientNetwork::operator<<(const APacket &packet)
{
	if (_socket->isConnected())
		(*_socket) << packet;
	else
        _connect = false;
    return (*this);
}

ClientNetwork &ClientNetwork::operator>>(APacket &packet)
{
	if (_socket->isConnected())
		(*_socket) >> packet;
	else
		_connect = false;
	return (*this);
}
