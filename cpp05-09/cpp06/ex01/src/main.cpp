/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcherif <zcherif@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 21:51:57 by zcherif           #+#    #+#             */
/*   Updated: 2026/04/10 21:51:58 by zcherif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

int main() {
	Data myData;
	myData.stringValue = "Hello, 42!";
	myData.intValue = 42;

	std::cout << "Original Data address: " << &myData << std::endl;
	std::cout << "Original Data string: " << myData.stringValue << std::endl;
	std::cout << "Original Data int: " << myData.intValue << std::endl;

	uintptr_t raw = Serializer::serialize(&myData);
	std::cout << "\nSerialized Data (uintptr_t): " << raw << std::endl;

	Data *deserializedData = Serializer::deserialize(raw);
	std::cout << "\nDeserialized Data address: " << deserializedData << std::endl;
	
	if (deserializedData == &myData) {
		std::cout << "Success: The deserialized pointer matches the original pointer." << std::endl;
		std::cout << "Deserialized Data string: " << deserializedData->stringValue << std::endl;
		std::cout << "Deserialized Data int: " << deserializedData->intValue << std::endl;
	} else {
		std::cout << "Error: The pointers do not match." << std::endl;
	}

	return (0);
}
