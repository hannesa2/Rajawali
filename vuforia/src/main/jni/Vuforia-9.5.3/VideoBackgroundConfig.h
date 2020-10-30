/*===============================================================================
Copyright (c) 2019 PTC Inc. All Rights Reserved.

Copyright (c) 2010-2014 Qualcomm Connected Experiences, Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

\file
    VideoBackgroundConfig.h

\brief
    Header file for VideoBackgroundConfig struct.
===============================================================================*/

#ifndef _VUFORIA_VIDEOBACKGROUNDCONFIG_H_
#define _VUFORIA_VIDEOBACKGROUNDCONFIG_H_

// Include files
#include <Vuforia/Vectors.h>

namespace Vuforia
{

/// Defines how the video background should be rendered.
struct VideoBackgroundConfig
{
    /// Constructor to provide basic initialization. 
    VideoBackgroundConfig()
    {
        mPosition.data[0] = 0;
        mPosition.data[1] = 0;
        mSize.data[0] = 0;
        mSize.data[1] = 0;
    }

    /// Relative position of the video background in the render target, in pixels.
    /**
     * Describes the offset of the center of video background to the
     * center of the screen (viewport) in pixels. A value of (0,0) centers the
     * video background, whereas a value of (-10,15) moves the video background
     * 10 pixels to the left and 15 pixels upwards.
     */
    Vec2I mPosition;

    /// Width and height of the video background in pixels.
    /**
     * Using the device's screen size for this parameter scales the image to
     * fullscreen. Notice that if the camera's aspect ratio is different than
     * the screen's aspect ratio this will create a non-uniform stretched
     * image.
     */
    Vec2I mSize;
};

} // namespace Vuforia

#endif //_VUFORIA_RENDERER_H_
