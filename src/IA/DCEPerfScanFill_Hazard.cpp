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
*	@file    DCEPerfScanFill_Hazard..cpp
*	@brief   the implementation of utility functions to pixelize a 2D polygon into a 2D pixel buffer. Based on code from Graphics Gems I, Concave Polygon Scan Conversion by Paul S. Heckbert.
*	@author  Michael Caylus
**/

// Turn off the warnings raised by std in Debug mode
#pragma warning ( disable : 4786 )

#include <stdlib.h> 
#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include "DCEPerfScanFill_Hazard.h"

#define ALLOC(ptr, type, n)  ptr = (type *)malloc((n)*sizeof(type))

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))


typedef struct {
	float x;
	float y;

} Point2;

typedef struct {		// window: a discrete 2-D rectangle 
    int x0, y0;			// xmin and ymin 
    int x1, y1;			// xmax and ymax (inclusive) 
} Window;

typedef struct {		// a polygon edge 
	double x;			// x coordinate of edge's intersection with current scanline 
    double dx;			// change in x with respect to y 
    int i;				// edge number: edge i goes from pt[i] to pt[i+1]
} Edge;

static int n;			// number of vertices 
static Point2 *pt;		// vertices 

static int nact;		// number of active edges 
static Edge *active;	// active edge list:edges crossing scanline y 


// comparison routines for qsort 
int compare_ind(const void *u, const void *v) {return pt[*((int *)u)].y <= pt[*((int *)v)].y ? -1 : 1;}
int compare_active(const void* u,const void* v)  {return ((Edge *)u)->x <= ((Edge *)v)->x ? -1 : 1;}

void concave(int nvert,Point2 *point,Window* win, short* pixelBuffer[]);

// main function to pixelize a concave 2D polygon into a 2D pixel buffer
void scanFill( const SoMFVec2f& points2D, const SoMFInt32& index, short* pixelBuffer[], int width, int height )
{
	Window win;
	
	win.x0 = 0;
	win.y0 = 0;
	win.x1 = width;
	win.y1 = height;
	
	int numContourPts = index.getNum();

	ALLOC(pt, Point2, numContourPts );
	
	if (!pt)
		return;
	
	float x = 0;
	float y = 0;
	for ( int i = 0; i < numContourPts ; i++)
	{
		points2D[index[i]].getValue(x, y);
		pt[i].x  = x;
		pt[i].y = y;
	}

	concave(numContourPts, pt, &win, pixelBuffer );	

	if (pt) free(pt);
}


// remove edge i from active list 
static void cdelete(int i) 
{
	int j;

    for (j = 0; j < nact && active[j].i!=i; j++);
    
	if (j >= nact) 
		return;	//edge not in active list; happens at win->y0
    
	nact--;
    
	memcpy(&active[j], &active[j + 1], (nact-j)*sizeof active[0]);
}


// append edge i to end of active list 
static void cinsert(int i,int y) 
{
    int j;
    double dx;
    Point2 *p, *q;

    j = (i < n-1) ? i+1 : 0;
    if (pt[i].y < pt[j].y) 
	{
		p = &pt[i]; 
		q = &pt[j];
	}
    else		   
	{	
		p = &pt[j]; 
		q = &pt[i];
	}

    // initialize x position at intersection of edge with scanline y
    active[nact].dx = dx = (q->x - p->x)/(q->y - p->y);
    active[nact].x = dx * (y+.5 - p->y) + p->x;
    active[nact].i = i;
    nact++;
}

void spanproc(int y,int xl,int xr, short* pixelBuffer[])
{
	short* raw = pixelBuffer[y];
	for ( int i = xl ; i <= xr ; i++ )
	{
		raw[i] = 255;
	}
}

void concave(int nvert, Point2 *point, Window* win, short* pixelBuffer[])
{
    int k, y0, y1, y, i, j, xl, xr;
    int *ind = 0;	// list of vertex indices, sorted by pt[ind[j]].y 

    n = nvert;
    pt = point;
    if (n <= 0) 
		return;
    
	ALLOC(ind, int, n);
	if (!ind)
		return;

    ALLOC(active, Edge, n);
	if (!active)
		return;

    // create y-sorted array of indices ind[k] into vertex list 
    for ( k = 0; k < n; k++)
		ind[k] = k;
    
	// sort ind by pt[ind[k]].y 
	qsort(ind, n, sizeof(ind[0]), compare_ind);	

	nact = 0;										// start with empty active list 
	k = 0;											// ind[k] is next vertex to process 
    y0 = MAX(win->y0, ceil(pt[ind[0]].y-.5));		// ymin of polygon 
    y1 = MIN(win->y1, floor(pt[ind[n-1]].y-.5));	// ymax of polygon 

	// step through scanlines 
    for ( y = y0; y <= y1; y++) 
	{	 
		// scanline y is at y+.5 in continuous coordinates

		// check vertices between previous scanline and current one, if any 
		for (; k<n && pt[ind[k]].y<=y+.5; k++) {
			
			// to simplify, if pt.y = y+.5, pretend it's above invariant: y-.5 < pt[i].y <= y+.5 
			i = ind[k];	
			
			/* insert or delete edges before and after vertex i (i-1 to i,
			   and i to i+1) from active list if they cross scanline y  */

			j = i > 0 ? i-1 : n-1;		// vertex previous to i 
			
			if (pt[j].y <= y-.5)		// old edge, remove from active list 
				cdelete(j);
			else if (pt[j].y > y+.5)	// new edge, add to active list 
				cinsert(j, y);
			j = i<n-1 ? i+1 : 0;		// vertex next after i 
			
			if (pt[j].y <= y-.5)		// old edge, remove from active list 
				cdelete(i);
			else if (pt[j].y > y+.5)	// new edge, add to active list 
				cinsert(i, y);
		}

		// sort active edge list by active[j].x 
		qsort(active, nact, sizeof(active[0]), compare_active);

		// draw horizontal segments for scanline y
		for ( j = 0; j < nact; j+=2 ) 
		{	
			// span 'tween j & j+1 is inside, span tween j+1 & j+2 is outside 
			xl = ceil(active[j].x-.5);		// left end of span 
			if (xl < win->x0) 
				xl = win->x0;
			
			xr = floor(active[j+1].x-.5);	// right end of span 
			if (xr>win->x1) 
				xr = win->x1;
			
			if (xl<=xr)
				spanproc(y, xl, xr, pixelBuffer);		// draw pixels in span 
			
			// increment edge coords 
			active[j].x += active[j].dx;	
			active[j+1].x += active[j+1].dx;
		}
    }

	if (ind) 
		free(ind);

	if (active) 
		free(active);

}


