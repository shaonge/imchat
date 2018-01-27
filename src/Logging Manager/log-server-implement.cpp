#include "log-server-implement.h"
#include "dao-interface.h"

bool LogonServer::user_register(const std::string &user_name, const std::string	&field_name, const std::string &value) 
{
	if (isUserExisting(user_name))
		return false;
	
	addNewUser(user_name);
	
	setUserInfo( &user_name, &field_name, &value)


	return true;
}

bool LogonServer::user_log_in(const std::string &user_name) 
{
	if (!isUserExisting(user_name))
		return false;

	if (isUserOnline(user_name))
	{
		///kick out the user
	}

	setUserOnline(user_name);
	

	return true;
}

bool LogonServer::user_log_out(const std::string &user_name) 
{
	if (!isUserOnline(user_name))
		return false;
	///kick out the user


	return true;
}
