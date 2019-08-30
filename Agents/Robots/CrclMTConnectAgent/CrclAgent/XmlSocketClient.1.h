//
// XmlClient.h
//
#pragma once
#include <deque>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/mutex.hpp>

using boost::asio::ip::tcp;
typedef boost::system::error_code error_code;
typedef std::deque<std::string> xml_message_queue;

class XMLClient  :public boost::enable_shared_from_this<XMLClient>
{
public:
	XMLClient(boost::asio::io_service&  io_service);
	void				AddMsgQueue(std::string msg);
	void				AppendBuffer(std::string read);
	bool				BufferHandler(std::string endtag="</CRCLStatus>");
	void				NotifyStop(){ _socket.close(); }
	void				ClearMsgQueue();
	void				Connect();
	void				Disconnect();
	std::string			FindLeadingElement(std::string  xml);
	void				Init(std::string ipv4, std::string port);
	bool				IsConnected();	
	bool				IsWaitingToConnect() { return _bWaitConnect;}
	std::string			LatestMsgQueue();
	size_t				SizeMsgQueue();
	void				StartAyncRead();
	void				StopConnecting();
	void				TimerReset();
	void				TagReset() { _endtag=NonsenseTag(); }
	void				SyncWrite(std::string str);

	int					_nMSServerConnectRetry;

protected:
	//void time_out(const boost::system::error_code& error) ;
	//void read_complete(const boost::system::error_code& error, size_t bytes_transferred);
	void				HandleConnect(const boost::system::error_code& error);
	size_t				bytesToRead(const error_code& error, size_t bytes_read);
	std::string			makeString(boost::asio::streambuf& streambuf, std::size_t n);
	static std::string	NonsenseTag() { return "<XXXXX>"; }
	boost::asio::deadline_timer _timer;
	//boost::asio::streambuf buff;
	std::string _current;
	std::string _next;
	std::string _endtag;
	xml_message_queue xml_msgs;
	boost::asio::io_service & _io_service;;
	boost::asio::ip::tcp::socket _socket;
	boost::mutex m;
	std::string _ipv4;
	std::string _port;
	enum { max_length = 4096 };
	char data_[max_length];
	bool _bConnected;
	bool _bWaitConnect;

};