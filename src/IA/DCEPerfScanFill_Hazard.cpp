/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
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


