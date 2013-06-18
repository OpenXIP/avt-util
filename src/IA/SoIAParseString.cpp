/*
Copyright (c) 2010, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/* author Jie Zheng */

#include "SoIAParseString.h"

#include <vector>       // stl vector header
#include <string>       // stl vector header
using namespace std;    // saves us typing std:: before vector


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoIAParseString );

void SoIAParseString::initClass()
{
	SO_ENGINE_INIT_CLASS(SoIAParseString, SoEngine, "Engine");
}

SoIAParseString::SoIAParseString(void)
{
	SO_ENGINE_CONSTRUCTOR( SoIAParseString );

	//Initialize the input parameter
	SO_ENGINE_ADD_INPUT( seperator, ("\\") );
	SO_ENGINE_ADD_INPUT( string, ("") );
	SO_ENGINE_ADD_INPUT( index, (0) );

	//set up the output type of the engine
	SO_ENGINE_ADD_OUTPUT( output, SoSFFloat );
}

SoIAParseString::~SoIAParseString(void)
{
}

void SoIAParseString::inputChanged(SoField *whichField)
{

}

void SoIAParseString::evaluate()
{
	SbString _seperator = seperator.getValue();
	SbString _string = string.getValue();

	std::string mark(_seperator.getString());
	std::string content(_string.getString());

	vector<float> output_buffer;

	float val = 0;
	int pos = -1;
	while((pos = content.find(mark)) != -1)
	{
		std::string element = content.substr(0, pos);

		val = atof(element.c_str());
		output_buffer.push_back(val);

		std::string buffer = content.substr(pos+1, content.size()-pos-1);
		content = buffer;
	}

	val = atof(content.c_str());
	output_buffer.push_back(val);

	int _index = index.getValue();
	if (_index < 0 || _index >= output_buffer.size())
	{
		SO_ENGINE_OUTPUT(output, SoSFFloat, setValue(-1));
	}
	else
	{
		SO_ENGINE_OUTPUT(output, SoSFFloat, setValue(output_buffer[_index]));
	}
}
