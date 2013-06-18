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

#include "SoLoadContour.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
SO_ENGINE_SOURCE( SoLoadContour );

SoLoadContour::SoLoadContour(void)
{
	SO_ENGINE_CONSTRUCTOR( SoLoadContour );

	// Inputs
	SO_ENGINE_ADD_INPUT( pointFile, ("") );
	SO_ENGINE_ADD_INPUT( indexFile, ("") );

	SO_ENGINE_ADD_INPUT( execute, () );
	// Outputs
	SO_ENGINE_ADD_OUTPUT( points, SoMFVec2f );
	SO_ENGINE_ADD_OUTPUT( coordIndex,   SoMFInt32 );
}

void SoLoadContour::initClass()
{
	SO_ENGINE_INIT_CLASS( SoLoadContour, SoEngine, "SoEngine" );
}

SoLoadContour::~SoLoadContour(void)
{
}

void SoLoadContour::evaluate()
{
}

void SoLoadContour::inputChanged (SoField* whichField)
{
	if (whichField == &execute)
	{
		SbString inputPoint = pointFile.getValue();
		SbString inputIndex = indexFile.getValue();

		if (inputPoint.getLength() > 0 && inputIndex.getLength() > 0)
			loadContour(inputPoint.getString(), inputIndex.getString());
	}
}

bool SoLoadContour::loadContour(const char *point, const char *index)
{
	vector<string> pointSets;
	parseContour(point, pointSets, ",");
	
	SoMFVec2f _points;
	vector<string>::iterator it;
	for (it = pointSets.begin(); it != pointSets.end(); it++)
	{
		string item = *it;
		
		SbVec2f point;
		sscanf_s(item.c_str(), "%f %f", &point[0], &point[1]);
		_points.set1Value(_points.getNum(), point);
	}
	SO_ENGINE_OUTPUT( points, SoMFVec3f, setNum(_points.getNum()) );	
	SO_ENGINE_OUTPUT( points, SoMFVec2f, setValues(0, _points.getNum(), _points.getValues(0)) );	

	SoMFInt32 _coordIndex;
	vector<string> indexSets;
	parseContour(index, indexSets, ",");
	for (it = indexSets.begin(); it != indexSets.end(); it++)
	{
		string item = *it;
		
		int value = 0;
		sscanf_s(item.c_str(), "%d", &value);

		_coordIndex.set1Value(_coordIndex.getNum(), value);
	}
	SO_ENGINE_OUTPUT( coordIndex, SoMFInt32, setNum(_coordIndex.getNum()) );	
	SO_ENGINE_OUTPUT( coordIndex, SoMFInt32, setValues(0, _coordIndex.getNum(), _coordIndex.getValues(0)) );	

	return true;
}


bool SoLoadContour::parseContour(const char *input,vector<string>& tokens, string del)
{
	ifstream file(input);

	if(file.fail())
		return false;

	stringstream buffer;
	buffer << file.rdbuf();
	string contents(buffer.str());
	//close the file
	file.close();

	//extract the content
	string::size_type pos0 = contents.find_first_not_of("[", 0);
	string::size_type pos1 = contents.find_first_of("]", pos0);

	string str = contents.substr(pos0, pos1 - pos0);

	string delimiters = del;
	 
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		string point = str.substr(lastPos, pos - lastPos);
		tokens.push_back(point);

		// Skip delimiters. Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}

	return true;
}
