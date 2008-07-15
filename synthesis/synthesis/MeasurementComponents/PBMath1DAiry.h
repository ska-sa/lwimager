//# PBMath1DAiry.h: Definitions of 1-D Airy PBMath objects
//# Copyright (C) 1996,1997,1998,2003
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This library is free software; you can redistribute it and/or modify it
//# under the terms of the GNU Library General Public License as published by
//# the Free Software Foundation; either version 2 of the License, or (at your
//# option) any later version.
//#
//# This library is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
//# License for more details.
//#
//# You should have received a copy of the GNU Library General Public License
//# along with this library; if not, write to the Free Software Foundation,
//# Inc., 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be adressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//#
//# $Id: PBMath1DAiry.h,v 19.5 2004/11/30 17:50:50 ddebonis Exp $

#ifndef SYNTHESIS_PBMATH1DAIRY_H
#define SYNTHESIS_PBMATH1DAIRY_H

#include <casa/aips.h>
#include <synthesis/MeasurementComponents/PBMath1D.h>
#include <measures/Measures.h>

namespace casa { //# NAMESPACE CASA - BEGIN

//#forward

// <summary> 
// PBMath1DAiry is a 1-D Airy Disk voltage pattern & Primary Beam
// </summary>

// <use visibility=export>

// <reviewed reviewer="" date="" tests="" demos="">

// <prerequisite>
// <li> <linkto class="PBMathInterface">PBMathInterface</linkto> class
// <li> <linkto class="PBMath1D">PBMath1D</linkto> class
// </prerequisite>
//
// <etymology>
// PBMath1DAiry: derived from  PBMath1D, implements an Airy pattern PB and VP
// </etymology>
//
// <synopsis> 
// See PBMath1D for a general synopsis of the 1D PB types.
//
// For an unblocked dish:
// VP(x) = 2 * j1(x)/x
//
// For blockage:
// areaRatio = (dish/block)^2;
// lengthRat = (dish/block);
// VP(x) = ( areaRatio* 2 * j1(x)/x - 2  j1(x*lengthRat)/(x*lengthRat) ) / (areaRatio - 1);
// </synopsis> 
//    
//
// <example>
// <srcblock>
//    PBMath1DAiry airyPB( Quantity(24.5,"m"), Quantity(2.5,"m"),
//                         Quantity(2*0.8564,"deg"), Quantity(1.0,"GHz") );
//    airyPB.applyPB( inImage, outImage, pointingDir);
// </srcblock>
// </example>
//
// <motivation>
// All of the 1-D PB types have everything in common except for the
// details of their parameterization.  This lightweight class
// deals with those differences: construction, filling the PBArray
// from construction parameters, and flushing to disk.
// </motivation>
//
// <todo asof="98/10/21">
// <li> constructor from a MS beam subtable
// <li> flush to MS beam subtable
// </todo>

 
class PBMath1DAiry : public PBMath1D {
public:

  PBMath1DAiry();

  // Instantiation from arguments; 
  // referenceFreq is used to scale maximumradius.
  // default = no squint
  // squint is the offset from pointing center if the Stokes R beam
  // useSymmetricBeam forces a fit to the squinted beam
  PBMath1DAiry(Quantity dishDiam, Quantity blockedDiam,
	       Quantity maxRad, Quantity refFreq, 
	       BeamSquint squint=BeamSquint(MDirection(Quantity(0.0, "deg"),
						       Quantity(0.0, "deg"),
						       MDirection::Ref(MDirection::AZEL)),
					    Quantity(1.0, "GHz")),
	       Bool useSymmetricBeam=False);

  // Instantiation from a row in the Beam subTable
  //PBMath1DAiry(const Table& BeamSubTable, Int row, 
  //	       Bool useSymmetricBeam=False);

  // Copy constructor
  // PBMath1DAiry(const PBMath1DAiry& other);

  // Assignment operator, by reference
  PBMath1DAiry& operator=(const PBMath1DAiry& other);

  // Clone the object
  //  CountedPtr<PBMathInterface> clone();

  //destructor
  ~PBMath1DAiry();  

  // Get the type of PB this is
  PBMathInterface::PBClass whichPBClass() { return PBMathInterface::AIRY; }  
  
  // Flush the construction parameters to disk
  // Bool flushToTable(Table& beamSubTable, Int iRow);

  // Summarize the construction data for this primary beam
  void summary(Int nValues=0);

protected:

  // Fill in vp_p array from construction parameters
  void fillPBArray();

private:    

  Quantity dishDiam_p;
  Quantity blockedDiam_p;

};


} //# NAMESPACE CASA - END

#endif
