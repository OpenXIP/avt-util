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

/**
 * @version	January 2010
 * @author Jie Zheng
 */

#include <Inventor/errors/SoMemoryError.h>
#include <Inventor/fields/SoMFVec2f.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbBox.h>
#include <xip/inventor/core/SoXipSFDataImage.h>
#include <xip/inventor/core/SoXipDataImage.h>
#include <xip/inventor/core/SbXipImage.h>
#include <xip/inventor/core/SbXipImageAdaptor.h>
#include "SoContourVoxelizer.h"

SO_ENGINE_SOURCE( SoContourVoxelizer );

SoContourVoxelizer::SoContourVoxelizer ()
{

    SO_ENGINE_CONSTRUCTOR( SoContourVoxelizer );

	SO_ENGINE_ADD_INPUT(       point, (0, 0, 0) );
	SO_ENGINE_ADD_INPUT(  coordIndex, (0) );
	point.setNum(0);
	coordIndex.setNum(0);

    SO_ENGINE_DEFINE_ENUM_VALUE( type, BIT_MASK);        // bit mask 
    SO_ENGINE_DEFINE_ENUM_VALUE( type, BYTE_MASK);       // byte mask
    SO_ENGINE_SET_SF_ENUM_TYPE( maskType, type );
    SO_ENGINE_ADD_INPUT( maskType, (BIT_MASK) );

    SO_ENGINE_ADD_INPUT( width, (0) );
	SO_ENGINE_ADD_INPUT( height,(0) );
	SO_ENGINE_ADD_INPUT( depth, (0) );
	SO_ENGINE_ADD_INPUT( modelMatrix, (1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1) );
	SO_ENGINE_ADD_INPUT( execute, () );

	SO_ENGINE_ADD_OUTPUT( mask, SoXipSFDataImage );

	m_maskImage = 0;
	mMaskOutput = 0;
	m_actionNeeded = false;

}

SoContourVoxelizer::~SoContourVoxelizer ()
{
	if( mMaskOutput )
	{
		mMaskOutput->unref();
		mMaskOutput = 0;
	}
}

void
SoContourVoxelizer::initClass ()
{
	SO_ENGINE_INIT_CLASS( SoContourVoxelizer, SoEngine, "Engine" );
}
    
void
SoContourVoxelizer::inputChanged (SoField* whichField)
{
	if (whichField == &execute)
    {
		m_actionNeeded = true;
    }
}

void
SoContourVoxelizer::evaluate()
{
	if (m_actionNeeded)
	{
		try
		{
			unsigned int numPoints = point.getNum();
			unsigned int numIndices = coordIndex.getNum();

			// Check inputs for proper values
			SbXipImageDimensions dimensions( width.getValue(), height.getValue(), depth.getValue() );

			// Create a new mask only if current dimensions doesn't match
			if ( (dimensions != m_maskImageDimensions) && (dimensions[0] > 0) && (dimensions[1] > 0) && (dimensions[2] > 0) )
			{	
				// Reset output
				if( mMaskOutput )
				{
					mMaskOutput->unref();
					mMaskOutput = 0;
				}

				m_maskImageDimensions = dimensions;

				// Allocate output mask
				m_maskImage = new SbXipImage( dimensions,
					SbXipImage::UNSIGNED_BYTE, 
					8, 
					1,
					SbXipImage::INTERLEAVED,
					maskType.getValue() == BIT_MASK ? SbXipImage::PACKED_LUMINANCE : SbXipImage::LUMINANCE,
					modelMatrix.getValue() );

				if( !m_maskImage )
				{
					SoMemoryError::post( "Mask image" );
				}
				
				// Reset mask
				m_maskImage->zero();
			}

			// Make sure inputs are correct
			if (m_maskImage)
				m_maskImage->zero();

			if(  numPoints >= 3 && m_maskImage )
			{
				m_maskImage->zero();

				const SbVec3f* pointPtr = point.getValues(0);
//				const int* coordIndexPtr = coordIndex.getValues(0);

				for( unsigned int i = 0; i < numIndices; ++ i )
				{
					SoMFVec2f point2DTemp;

					// Add point index to temporary list
					for (int j = 0; j < numPoints; j++)
					{
						SbVec3f tmp = pointPtr[j];
						int index = (int) (.5 + tmp[2] * (float) (dimensions[2]));
						if (index == i+1)
						{
							SbVec2f point;
							point[0] = (int) (.5 + tmp[0] * (float) (dimensions[0]));
							point[1] = (int) (.5 + tmp[1] * (float) (dimensions[1]));
						
							point2DTemp.set1Value( point2DTemp.getNum(), point );
						}
					}

					
					// If -1 is found, and we have at least 3 points
					if( point2DTemp.getNum() >= 3 )
					{
						int z = i;
						if( z < 0 || z >= dimensions[2] )
						{
							// Skip this contour
							continue ;
						}


						if( maskType.getValue()== BYTE_MASK )
						{
							SbXipImageInterleavedPixelPtr<unsigned char> it( m_maskImage, z );

							for (int p = 0; p < dimensions[1]; p++)
							{
								int xl = dimensions[0];
								int xr = 0;

								getLineSpan(xl, xr, p, point2DTemp);
								for ( int q = xl ; q <= xr ; q++ )
								{
									it( p, q ) = 255;
								}
							}
							//for (int p = 0; p < point2DTemp.getNum(); p++)
							//{
							//	int x = point2DTemp[p][0];
							//	int y = point2DTemp[p][1];

							//	it( y, x ) = 255;
							//}

							//for( int r = 0; r < dimensions[1]; ++ r )
							//for( int c = 0; c < dimensions[0]; ++ c )
							//{
							//	if( imageRows[r][c] )
							//		it( r, c ) = 255;
							//}
						}
						else
						{
							SbXipImagePackedPixelSlicePtr it( m_maskImage, z );

							for (int p = 0; p < dimensions[1]; p++)
							{
								int xl = dimensions[0];
								int xr = 0;

								getLineSpan(xl, xr, p, point2DTemp);
								for ( int q = xl ; q <= xr ; q++ )
								{
									it.setTrue( p, q );
								}
							}
							
							//for( int r = 0; r < dimensions[1]; ++ r )
							//for( int c = 0; c < dimensions[0]; ++ c )
							//{
							//	if( imageRows[r][c] )
							//		it.setTrue( r, c );                                
							//}
						}
					}
				}
			}

			mMaskOutput = new SoXipDataImage();
			if( !mMaskOutput )
			{
				SoMemoryError::post( "Mask data image" );
			}

			mMaskOutput->set( m_maskImage );
			mMaskOutput->ref();
		}
		catch( ... )
		{
			SoDebugError::post( __FILE__, "Unexpected error in evaluate()" );
		}
	
		m_actionNeeded = false;

	}

	SO_ENGINE_OUTPUT( mask, SoXipSFDataImage, setValue( mMaskOutput ) );
}


void SoContourVoxelizer::getLineSpan(int &xl, int &xr, int line, SoMFVec2f &points)
{
	for (int i = 0; i < points.getNum(); i++)
	{
		SbVec2f point = points[i];
		if (point[1] == line)
		{
			if (point[0] < xl)
				xl = point[0];
			if (point[0] > xr)
				xr = point[0];
		}
	}
}
