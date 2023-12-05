/*************************************************************************\
 * Documentation
\*************************************************************************/
/**
 * @file     gpsCoordinates.hpp
 * @version  1.0
 * @brief    Provides a class for handling GPS coordinates, including WGS84 and MGRS notation.
 */
#pragma once

#include <cmath> // Required for trigonometric calculations

/*************************************************************************\
 * Prototypes
\*************************************************************************/
namespace GPS
{
  class gpsCoordinates
  {
  public:
    struct DMS
    {
      int degrees;
      int minutes;
      double seconds;
    };

    struct MGRS
    {
      int zone;
      char band;
      char squareLetter1;
      char squareLetter2;
      int easting;
      int northing;
    };

    struct Coordinates
    {
      double latitudeDD;
      double longitudeDD;
      DMS latitudeDMS;
      DMS longitudeDMS;
      MGRS mgrs;
    };

    /**
     * @brief  Default constructor.
     */
    gpsCoordinates();

    // Conversion functions
    DMS toDMS(double coordinate) const;
    double toDD(const DMS& coordinate) const;
    MGRS toMGRS(double latitude, double longitude) const;
    bool fromMGRS(const MGRS& mgrs, double& latitude, double& longitude) const;

    void setCoordinates(double latitude, double longitude, const MGRS& mgrs);
    bool getCoordinates(Coordinates& coords) const;

    /**
     * @brief      Calculate the distance between two gpsCoordinates objects.
     * @param[in]  origin      Origin gpsCoordinates object.
     * @param[in]  destination Destination gpsCoordinates object.
     * @return     Distance in meters.
     */
    static double distance(const gpsCoordinates& origin, const gpsCoordinates& destination);

    /**
     * @brief      Calculate the direction between two gpsCoordinates objects.
     * @param[in]  origin      Origin gpsCoordinates object.
     * @param[in]  destination Destination gpsCoordinates object.
     * @return     Direction in degrees from North.
     */
    static double direction(const gpsCoordinates& origin, const gpsCoordinates& destination);

  private:
    double latitudeDD; //!< Latitude in Decimal Degrees
    double longitudeDD; //!< Longitude in Decimal Degrees
  };
} // namespace GPS
/*************************************************************************\
 * End of file
\*************************************************************************/
