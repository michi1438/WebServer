/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Err_page_switch.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:06:25 by mguerga           #+#    #+#             */
/*   Updated: 2024/05/23 14:42:52 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Centralinclude.hpp"

std::string read_errpage(int err_code, RequestParser& Req, t_server srvr_used)
{
	std::string d_err_dir(ERR_DIR);
	switch (err_code)
	{
		case 301:
		{
			std::ifstream file(srvr_used.err_dir.append(ERR_301).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_301).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 301 Moved Permanently\r\nContent-Type: text/html\r\nLocation: " + Req.getURI() + "/\r\n\r\n" + content;
			return response;
		}
		case 400:
		{
			std::ifstream file(ERR_400);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 403:
		{
			std::ifstream file(srvr_used.err_dir.append(ERR_403).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_403).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 403 Forbidden\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 404:
		{
			std::ifstream file(srvr_used.err_dir.append(ERR_404).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_404).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 405:
		{
			std::ifstream file(srvr_used.err_dir.append(ERR_405).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_405).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 408:
		{
			// XXX This response is used much more since some browsers, like Chrome, Firefox 27+, and IE9, use HTTP pre-connection mechanisms to speed up surfing. 
			std::ifstream file(srvr_used.err_dir.append(ERR_408).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_408).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 408 Request Timeout\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n" + content;
			return response;
		}
		case 413:
		{
			std::ifstream file(srvr_used.err_dir.append(ERR_413).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_413).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 413 Payload Too Large\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 414:
		{
			std::ifstream file(srvr_used.err_dir.append(ERR_414).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_414).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 414 URI Too Long\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 501:
		{
			std::ifstream file(srvr_used.err_dir.append(ERR_501).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_501).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 501 Not Implemented\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 504:
		{
			std::ifstream file(srvr_used.err_dir.append(ERR_504).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_504).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 504 Gateway Timeout\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 505:
		{
			std::ifstream file(srvr_used.err_dir.append(ERR_505).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_505).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 505 HTTP Version Not Supported\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 512:
		{
			std::ifstream file(srvr_used.err_dir.append(ERR_512).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_512).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 512 Guerga is the error\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		default:
		{
			std::ifstream file(srvr_used.err_dir.append(ERR_500).c_str());
			if (file.is_open() == false)
				file.open(d_err_dir.append(ERR_500).c_str());
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
	}
}
