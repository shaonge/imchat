#ifndef IMCHAT_LOG_SERVER_IMPLEMENT_H
#define IMCHAT_LOG_SERVER_IMPLEMENT_H

class LogonServer : boost::noncopyable
{
public:

	bool user_register(const std::string &user_name, const std::string &field_name, const std::string &value);
	bool user_log_in(const std::string &user_name);
	bool user_log_out(const std::string &user_name);
	
};

#endif