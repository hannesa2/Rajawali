/*===============================================================================
 Copyright (c) 2019 PTC Inc. All Rights Reserved.
 
 Vuforia is a trademark of PTC Inc., registered in the United States and other
 countries.
 
 \file
 RuntimeImageSource.h
 
 \brief
 Header file for RuntimeImageSource class.
 ===============================================================================*/

#ifndef _VUFORIA_RUNTIMEIMAGESOURCE_H_
#define _VUFORIA_RUNTIMEIMAGESOURCE_H_

// Include files:
#include <Vuforia/NonCopyable.h>
#include <Vuforia/Vuforia.h>
#include <Vuforia/Vectors.h>

namespace Vuforia
{
    
/// A handle for creating a new Trackable from an image file in a DataSet.
/**
 * The RuntimeImageSource class is used to add a Trackable object to a DataSet instance
 * from existing data. Either images loaded from files or raw data created by other
 * sources are supported.
 *
 * \note Images with width or height bigger than 2048 pixels are not supported!
 */
class VUFORIA_API RuntimeImageSource : private NonCopyable
{
public:
        
    /// Set the RuntimeImageSource from raw image data.
    /**
     * Set the RuntimeImageSource to raw image data loaded by functions independent from %Vuforia.
     *
     * \note currently only unpadded image sources are correctly supported
     *
     * \param pixels the pointer to the raw pixel data
     * \param format the pixel format used by the raw data. Currently supported formats are Vuforia::GRAYSCALE, Vuforia::RGB888 and Vuforia::RGBA8888
     * \param size the size of the image in pixel (width, height)
     * \param targetWidthMeters the real world size of the target
     * \param targetName the name of the resulting trackable
     * \return returns true if the raw image data could be set, false otherwise
     */
    virtual bool setImage(void* pixels, PIXEL_FORMAT format, Vec2I size, float targetWidthMeters, const char * targetName) = 0;

    /// Set the RuntimeImageSource from file.
    /**
     * Set the RuntimeImageSource to the image found at the path provided.
     *
     * \param path the location of the image to be used as target
     * \param storageType the type of the path provided
     * \param targetWidthMeters the real world size of the target.
     * \param targetName the name of the resulting trackable
     * \return returns true if the image could be loaded, false otherwise
     */
    virtual bool setFile(const char* path, STORAGE_TYPE storageType, float targetWidthMeters, const char * targetName) = 0;
};
    
} // namespace Vuforia

#endif // _VUFORIA_RUNTIMEIMAGESOURCE_H_
