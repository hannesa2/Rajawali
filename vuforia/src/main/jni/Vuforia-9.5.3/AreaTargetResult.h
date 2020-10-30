/*===============================================================================
Copyright (c) 2020 PTC Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

\file
    AreaTargetResult.h

\brief
    Header file for the AreaTargetResult class. Exposes the result of 
    detecting and tracking a scanned physical environment.
===============================================================================*/

#ifndef _VUFORIA_AREATARGETRESULT_H_
#define _VUFORIA_AREATARGETRESULT_H_

// Include files
#include <Vuforia/TrackableResult.h>
#include <Vuforia/AreaTarget.h>

namespace Vuforia
{

/// Tracking data resulting from tracking an AreaTarget.
/**
 * \note Poses of AreaTarget are reported in the World Coordinate System.
 */
class VUFORIA_API AreaTargetResult : public TrackableResult
{
public:

    /// Get the Type for class 'AreaTargetResult'.
    static Type getClassType();

    /// Get the AreaTarget that participated in generating this result.
    virtual const AreaTarget& getTrackable() const = 0;

};

} // namespace Vuforia

#endif //_VUFORIA_AREATARGETRESULT_H_
