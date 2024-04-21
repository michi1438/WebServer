/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestParser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:45:34 by lzito             #+#    #+#             */
/*   Updated: 2024/04/17 17:55:51 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/RequestParser.hpp"

RequestParser::RequestParser(const std::string &request)
	: _method(""), _uri(""), _version(""), _host(""), _script_name(""),
   	_is_chunked(false),	_boundary(""), _content_type(""), _content_length(0), _body("")
{
	// First line (Method, URI & Version)
	///////////////////////////////////////
	std::istringstream	request_stream(request);

	std::string	first_line;
	std::getline(request_stream, first_line);

	std::istringstream	first_line_stream(first_line);
	std::getline(first_line_stream, this->_method, ' ');
	std::getline(first_line_stream, this->_uri, ' ');
	std::getline(first_line_stream, this->_version, '\r');

	// Second line (Host)
	///////////////////////////////////////
	std::string	second_line;
	std::getline(request_stream, second_line, '\r');
	this->_host = second_line.substr(6);

	// CGI
	///////////////////////////////////////
	if (this->isCGI())
	{
		std::string URI = this->getURI();
		size_t cgiPos = URI.find("/cgi_bin/");
		this->_script_name = URI.substr(cgiPos + 9, sizeof(URI));
	}

	// Rest of headers
	///////////////////////////////////////
	// GET & DELETE METHOD
	if (this->_method == "GET")
	{
		std::string URI = this->getURI();
		size_t queryPos = URI.find("?");
		if (queryPos != std::string::npos)
		{
			std::string key;
			std::string value;

			std::istringstream query_stream(URI);
			query_stream.seekg(queryPos + 1, std::ios::cur);
			while (!query_stream.eof())
			{
				std::getline(query_stream, key, '=');
				std::getline(query_stream, value, '&');
				this->_query_param.insert(std::pair<std::string, std::string>(key, value));
			}
		}
		return;
	}
//	else if (this->_method == "DELETE")
//		return ;

	// POST METHOD
	std::string	new_line;
	std::getline(request_stream, new_line);
	while (new_line.size() != 1)
	{
		if (new_line.find("Content-Type: multipart/form-data") != std::string::npos)
		{
			std::istringstream new_line_stream(new_line);
			std::getline(new_line_stream, this->_content_type, ' ');
			std::getline(new_line_stream, this->_content_type, ';');
			std::getline(new_line_stream, this->_boundary, '=');
			std::getline(new_line_stream, this->_boundary, '\r');
		}
		else if (new_line.find("Content-Type: ") != std::string::npos)
			this->_content_type = new_line.erase(new_line.size() - 1, 1).substr(14);
		else if (new_line.find("Content-Length: ") != std::string::npos)
		{
			this->_content_length = std::atoi(new_line.erase(new_line.size() - 1, 1).substr(16).c_str());
			if (this->_content_length > 100000000) //TODO get body limit from ConfigFile
				throw 413;
		}
		else if (new_line.find("Transfer-Encoding: ") != std::string::npos)
		{
			if (new_line.find("chunked") != std::string::npos)
				this->_is_chunked = true;
		}
		std::getline(request_stream, new_line);
	}
	// Body
	for (std::string line; std::getline(request_stream, line);)
	{
		line.append("\n");
		this->_body.append(line);
	}

}

RequestParser::~RequestParser()
{
	return ;
}

void RequestParser::show() const
{
	std::cout << GREEN;
	std::cout << std::setw(50) << "----------------------------------------" << std::endl;
	std::cout << std::setw(50) << "|            REQUEST PARSER            |" << std::endl;
	std::cout << std::setw(50) << "----------------------------------------" << std::endl;
	std::cout << RESET << std::setw(20) << "METHOD : " << GREEN << this->getMethod() << "$" << std::endl;
	std::cout << RESET << std::setw(20) << "URI : " << GREEN << this->getURI() << "$" << std::endl;
	std::cout << RESET << std::setw(20) << "VERSION : " << GREEN << this->getVersion() << "$" << std::endl;
	std::cout << RESET << std::setw(20) << "HOST : " << GREEN << this->getHost() << "$" << std::endl;
	std::cout << RESET << std::setw(20) << "IS CHUNKED : " << GREEN << this->_is_chunked << "$" << std::endl;
	std::cout << RESET << std::setw(20) << "IS CGI : " << GREEN << this->isCGI() << "$" << std::endl;
	std::cout << RESET << std::setw(20) << "SCRIPT NAME : " << GREEN << this->getScriptName() << "$" << std::endl;
	std::cout << RESET << std::setw(20) << "BOUNDARY : " << GREEN << this->getBoundary() << "$" << std::endl;
	std::cout << RESET << std::setw(20) << "CONTENT TYPE : " << GREEN << this->getContentType() << "$" << std::endl;
	std::cout << RESET << std::setw(20) << "CONTENT LENGTH : " << GREEN << this->getContentLength() << "$" << std::endl;
	std::cout << RESET << std::setw(20) << "BODY : " << std::endl;
	std::cout << CYAN << this->getBody() << "$" << std::endl;

	std::cout << std::setw(20) << std::endl;
	std::cout << std::setw(20) << RESET << "QUERY" << std::endl;

	std::map<std::string, std::string>::const_iterator it;
	int num = 0;
	for (it = this->_query_param.begin(); it != this->_query_param.end(); ++it)
	{
		std::cout << std::setw(10) 
			<< "KEY n" << num << " : " << YELLOW << it->first << "$" << RESET << std::setw(10)
			<< "VALUE n" << num << " : " << YELLOW << it->second << "$" << RESET << std::endl;
		num++;
	}
	std::cout << std::setw(20) << std::endl;
}

std::string RequestParser::unchunk(std::string body) const
{
	// TODO do the actual unchunk
	return (body);
}

bool RequestParser::isChunked() const
{
	return (this->_is_chunked);
}

bool RequestParser::isCGI() const
{
	std::string URI = this->getURI();
	size_t cgiPos = URI.find("/cgi_bin/");

	if (cgiPos != std::string::npos)
		return (true);
	return (false);
}

std::string RequestParser::getMethod() const
{
	return (this->_method);
}

std::string RequestParser::getURI() const
{
	return (this->_uri);
}

std::string RequestParser::getVersion() const
{
	return (this->_version);
}

std::string RequestParser::getHost() const
{
	return (this->_host);
}

std::string RequestParser::getScriptName() const
{
	return (this->_script_name);
}

std::string RequestParser::getBoundary() const
{
	return (this->_boundary);
}

std::string RequestParser::getBody() const
{
	if (this->_is_chunked == true)
		return (this->unchunk(this->_body));
	return (this->_body);
}

std::string RequestParser::getContentType() const
{
	return (this->_content_type);
}

size_t RequestParser::getContentLength() const
{
	return (this->_content_length);
}

std::map<std::string, std::string> RequestParser::getQueryParam() const
{
	return (this->_query_param);
}