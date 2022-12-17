#include "Day6.h"

#include <iostream>
#include <fstream>	//std::ifstream

namespace daySix {
	/// <summary>
	/// Returns the position of the final element of the first marker of length markerLength
	/// </summary>
	/// <param name="markerLength">length of the marker</param>
	/// <returns>position of the final element of the marker</returns>
	int GetFirstMarkerPosition(int markerLength){
		std::ifstream comDatastream("./InputFiles/Day6_CommunicationDatastreamBuffer.txt", std::ifstream::in);

		int posOfFirstMarker = 0;
		//read out data
		if (comDatastream.is_open())
		{
			std::string line{};

			//Get the input line
			std::getline(comDatastream, line);

			//look for marker
			//-(markerLength-1) cause we work with the following markerLength characters after i
			for (int i = 0; i < line.size() - (markerLength-1); i++) {
				//no duplicates -> marker is found
				if (!HasDuplicatingChar(line.substr(i, markerLength))) {
					posOfFirstMarker = i+markerLength;
					break;
				}
			}

			//close file
			comDatastream.close();
		}

		return posOfFirstMarker;
	}

	/// <summary>
	/// Should use string_view instead of string from C++ 17 on out
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	bool HasDuplicatingChar(std::string str) {
		for (int i = 0; i < str.size(); i++) {
			for (int j = i + 1; j < str.size(); j++) {

				if (str[i] == str[j])
					return true;
			}
		}
		return false;
	}
}