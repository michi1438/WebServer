/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Err_page_switch.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: robin <robin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:06:25 by mguerga           #+#    #+#             */
/*   Updated: 2024/05/16 17:24:00 by robin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Centralinclude.hpp"

//TODO find the real errors descriptions instead of "OK"

std::string read_errpage(int err_code, RequestParser& Req)
{
	switch (err_code)
	{
		case 301:
		{
			std::ifstream file(ERR_301);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 301 OK\r\nContent-Type: text/html\r\nLocation: " + Req.getURI() + "/\r\n\r\n" + content;
			return response;
		}
		case 400:
		{
			std::ifstream file(ERR_400);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 400 OK\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 403:
		{
			std::ifstream file(ERR_403);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 403 OK\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 404:
		{
			std::ifstream file(ERR_404);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 404 OK\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 405:
		{
			std::ifstream file(ERR_405);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 405 OK\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 408:
		{
			// XXX This response is used much more since some browsers, like Chrome, Firefox 27+, and IE9, use HTTP pre-connection mechanisms to speed up surfing. 
			std::ifstream file(ERR_408);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 408 OK\r\nContent-Type: text/html\r\nConnection: close\r\n\r\n" + content;
			return response;
		}
		case 413:
		{
			std::ifstream file(ERR_413);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string length = "300"; //TODO temporary, seems to make the response taken better by the client (??)
										//make it dynamic if it also works better on mac (avec ma vm je peux pas tester l upload de fichier > quelques ko)
			std::string response = "HTTP/1.1 413 Payload Too Large\r\nConnection: close\r\nContent-Length: " + length + "\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 414:
		{
			std::ifstream file(ERR_414);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 414 OK\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 501:
		{
			std::ifstream file(ERR_501);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 501 OK\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 504:
		{
			std::ifstream file(ERR_504);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 504 OK\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 505:
		{
			std::ifstream file(ERR_505);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 505 OK\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		case 512:
		{
			std::ifstream file(ERR_512);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 512 OK\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
		default:
		{
			std::ifstream file(ERR_500);
			std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
			std::string response = "HTTP/1.1 500 OK\r\nContent-Type: text/html\r\n\r\n" + content;
			return response;
		}
	}
}
