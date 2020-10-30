/*===============================================================================
Copyright (c) 2019 PTC Inc. All Rights Reserved.

Vuforia is a trademark of PTC Inc., registered in the United States and other 
countries.

\file
    Illumination.h

\brief
    Header file for the Illumination class.
===============================================================================*/

#ifndef _VUFORIA_ILLUMINATION_H_
#define _VUFORIA_ILLUMINATION_H_

// Include files
#include <Vuforia/System.h>
#include <Vuforia/Vectors.h>
#include <Vuforia/NonCopyable.h>

namespace Vuforia
{

/// Abstract representation of the illumination for a particular frame.
/**
 * Objects of this class contain information about the illumination in a particular
 * camera frame.
 *
 * An instance of this class can be obtained from the State. Use its returned
 * values to render augmentation using illumination consistent with the real
 * world scene.
 */
class VUFORIA_API Illumination : private NonCopyable
{
public:

    /// Returned by getAmbientIntensity() when data is not available.
    static const float AMBIENT_INTENSITY_UNAVAILABLE;

    /// Returned by getAmbientColorTemperature() when data is not available.
    static const float AMBIENT_COLOR_TEMPERATURE_UNAVAILABLE;

    /// Get the scene's ambient intensity.
    /**
     * \returns The current ambient intensity of the scene, in Lumens, or
     * AMBIENT_INTENSITY_UNAVAILABLE if the value is not available on the current
     * platform.
     *
     * This value will be valid when ARKit is being used by Vuforia Fusion.
     */
    virtual float getAmbientIntensity() const = 0;

    /// Get the scene's ambient color temperature.
    /**
     * \returns The current color temperature of the scene, in Kelvin, or
     * AMBIENT_COLOR_TEMPERATURE_UNAVAILABLE if the value is not available on
     * the current platform.
     *
     * This value will be valid when ARKit is being used by Vuforia Fusion.
     */
    virtual float getAmbientColorTemperature() const = 0;
    
    /// Get the scene's intensity correction values
    /**
     * \returns a floating point intensity value which can be applied to a
     * shader when rendering the color for an augmentation to reflect the
     * ambient light in the scene.
     *
     * Intensity correction usage is described here,
     * https://library.vuforia.com/content/vuforia-library/en/articles/Solution/using-vuforia-fusion-illumination.html
     *
     * Intensity correction is a value that can be applied directly to a shader. Values
     * are in the range (0.0, 1.0), zero is black and 1.0 is white.
     *
     * If rendering in gamma space divide by 0.466 (middle grey in gamma) and multiply
     * by the final rendered color.
     *
     * In a linear space use pow(intensityCorrection, 2.2)/0.18
     * pow(intensityCorrection, 2.2) converts to linear space and then the value is
     * normalized by dividing by 0.18 middle grey in linear space.
     *
     * The value will always be valid for use. 0.466 (middle grey) is used in cases where
     * the platform does not supply a value.
     *
     * This value will differ from the default when ARCore is being used by Vuforia Fusion.
     */
    virtual float getIntensityCorrection() const = 0;
    
    /// Get the scene's color correction values
    /**
      * \returns a Vec4F which contains RGBA color correction
      * values which can be applied to a shader when rendering the color for an
      * augmentation to reflect the ambient light in the scene.
      *
      * Color correction usage is described here,
      * https://library.vuforia.com/content/vuforia-library/en/articles/Solution/using-vuforia-fusion-illumination.html
      *
      * All values are reported in gamma space where gamma is 2.2.
      * When used in a gamma space component wise multiply the values with the final
      * calculated color.
      *
      * In a linear color space convert to linear using pow(colorCorrection[i], 2.2) and
      * then component wise multiply the values with the final calculated color component.
      *
      * The values will always be valid for use. 1.0 is used in cases where
      * the platform does not supply values.
      *
      * This value will differ from the default when ARCore is being used by Vuforia Fusion.
      */
    virtual Vec4F getColorCorrection() const = 0;
    
    virtual ~Illumination() {}
};

} // namespace Vuforia

#endif // _VUFORIA_ILLUMINATION_H_
