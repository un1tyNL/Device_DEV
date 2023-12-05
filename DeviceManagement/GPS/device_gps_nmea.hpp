/*************************************************************************\
 * Documentation
\*************************************************************************/
/**
 * @file     device_gps_nmea.hpp
 * @brief    Defines types of nmea messages and corresponding struct typedefs.
 * @details  This file provides definitions for types and constants related to the NMEA (National Marine Electronics Association) protocol
 *           for GPS (global Positioning System) communication. The NMEA protocol is a standard for encoding and transmitting GPS data in
 *           the form of ASCII text sentences. This file includes enumerations and typedefs for various aspects of NMEA messages, such as
 *           the types of messages, geometric directions, signal quality, and fix type. It also defines a maximum length for NMEA messages
 *           and includes an external header file called "global.h". These definitions are used in GPS devices or software that communicate
 *           with GPS devices using the NMEA protocol.
 * @version  0.1
 */
#pragma once
/*************************************************************************\
 * Includes
\*************************************************************************/
#include "global.hpp"

/*************************************************************************\
 * Defines
\*************************************************************************/
/**
 * @brief Maximum length of a NMEA message is 79 characters, excluding $, [CR] and [LF].
 */
#define NMEA_GPS_MAX_SENTENCE_LENGTH (82)
/**
 * @brief Minimum length of a NMEA message is 10 characters, including $, [CR] and [LF].
 */
#define NMEA_GPS_MIN_SENTENCE_LENGTH (10)

/**
 * @brief NMEA identifier type.
 */
typedef char NMEA_gpsStringIdentifier[6];

/**
 * @brief Array holding the characters of the NMEA.
 */
typedef char NMEA_gpsStringChecksum[2];

/**
 * @brief Pointer to the NMEA sentence's checksum.
 */
typedef char (*NMEA_gpsCheckSumChars)[2];

/**
 * @brief Enumeration of NMEA message types.
 */
typedef enum NMEA_gpsMessageType
{
  MESSAGE_TYPE_GPBOD,               //!< Bearing, origin to destination
  MESSAGE_TYPE_GPBWC,               //!< Bearing and distance to waypoint, great circle
  MESSAGE_TYPE_GPGGA,               //!< global Positioning System Fix Data
  MESSAGE_TYPE_GPGLL,               //!< Geographic position, latitude / longitude
  MESSAGE_TYPE_GPGSA,               //!< GPS DOP and active satellites
  MESSAGE_TYPE_GPGSV,               //!< GPS Satellites in view
  MESSAGE_TYPE_GPHDT,               //!< GPHDT messages provide the heading (direction) in degrees from true north
  MESSAGE_TYPE_GPR00,               //!< List of waypoints in currently active route
  MESSAGE_TYPE_GPRMA,               //!< Recommended minimum specific Loran-C data
  MESSAGE_TYPE_GPRMB,               //!< Recommended minimum navigation info
  MESSAGE_TYPE_GPRMC,               //!< Recommended minimum specific GPS/Transit data
  MESSAGE_TYPE_GPRTE,               //!< Routes
  MESSAGE_TYPE_GPTRF,               //!< Transit Fix Data
  MESSAGE_TYPE_GPSTN,               //!< Multiple Data ID
  MESSAGE_TYPE_GPVBW,               //!< Dual Ground / Water Speed
  MESSAGE_TYPE_GPVTG,               //!< Track made good and ground speed
  MESSAGE_TYPE_GPWPL,               //!< Waypoint location
  MESSAGE_TYPE_GPXTE,               //!< Cross-track error, Measured
  MESSAGE_TYPE_GPZDA,               //!< Date & Time
  MESSAGE_TYPE_numberOfMessageTypes //!< NMEA_gpsnumberOfNmeaMessageTypess
} NMEA_gpsMessageTypes_e;

typedef union NMEA_sentence
{
  uint8_t(string)[NMEA_GPS_MAX_SENTENCE_LENGTH];
} NMEA_sentence_u;

/**
 * @brief Used to quickly identify which GPS sentence has been received.
 */
const uint32_t NMEA_gpsMessageIdValueLut[MESSAGE_TYPE_numberOfMessageTypes] {
  *((uint32_t *) "PBOD"), //!< Bearing, origin to destination
  *((uint32_t *) "PBWC"), //!< Bearing and distance to waypoint, great circle
  *((uint32_t *) "PGGA"), //!< global Positioning System Fix Data
  *((uint32_t *) "PGLL"), //!< Geographic position, latitude / longitude
  *((uint32_t *) "PGSA"), //!< GPS DOP and active satellites
  *((uint32_t *) "PGSV"), //!< GPS Satellites in view
  *((uint32_t *) "PHDT"), //!< GPHDT messages provide the heading (direction) in degrees from true north
  *((uint32_t *) "PR00"), //!< List of waypoints in currently active route
  *((uint32_t *) "PRMA"), //!< Recommended minimum specific Loran-C data
  *((uint32_t *) "PRMB"), //!< Recommended minimum navigation info
  *((uint32_t *) "PRMC"), //!< Recommended minimum specific GPS/Transit data
  *((uint32_t *) "PRTE"), //!< Routes
  *((uint32_t *) "PTRF"), //!< Transit Fix Data
  *((uint32_t *) "PSTN"), //!< Multiple Data ID
  *((uint32_t *) "PVBW"), //!< Dual Ground / Water Speed
  *((uint32_t *) "PVTG"), //!< Track made good and ground speed
  *((uint32_t *) "PWPL"), //!< Waypoint location
  *((uint32_t *) "PXTE"), //!< Cross-track error, Measured
  *((uint32_t *) "PZDA"), //!< Date & Time
};

/*************************************************************************\
 * NMEA variable type definitions
\*************************************************************************/
/**
 * @brief Enumeration of geometric directions.
 */
typedef enum NMEA_gpsGeometricDirection
{
  GEOMETRIC_DIRECTION_NORTH = 'N', //!< North
  GEOMETRIC_DIRECTION_EAST  = 'E', //!< East
  GEOMETRIC_DIRECTION_SOUTH = 'S', //!< South
  GEOMETRIC_DIRECTION_WEST  = 'W', //!< West
} NMEA_gpsGeometricDirection_e;

typedef enum NMEA_gpsValidity
{
  VALIDITY_VALID_DATA         = 'A', //!< valid data
  VALIDITY_NAVIGATION_WARNING = 'V'  //!< navigation receiver warning
} NMEA_gpsValidity_e;

/**
 * @brief Enumeration of signal quality values.
 */
typedef enum NMEA_gpsSignalQuality
{
  SIGNAL_QUALITY_INV = 0x0, //!< invalid
  SIGNAL_QUALITY_FIX = 0x1, //!< GPS fix
  SIGNAL_QUALITY_DIF = 0x2, //!< Diff
} NMEA_gpsSignalQuality_e;

/**
 * @brief GPS mode indicator.
 * @details The NMEA_gpsMode enum provides a list of possible values for
 * the mode indicator in some NMEA sentences.
 */
typedef enum NMEA_gpsMode
{
  MODE_AUTONOMOUS   = 'A', /**< Autonomous mode. */
  MODE_DIFFERENTIAL = 'D'  /**< Differential mode. */
} NMEA_gpsMode_t;

/**
 * @brief Enumeration of fix mode values.
 */
typedef enum NMEA_gpsFixMode
{
  FIX_MODE_MANUAL    = 'M', //!< Fix mode manual
  FIX_MODE_AUTOMATIC = 'A', //!< Fix mode automatic
} NMEA_gpsFixMode_e;

/**
 * @brief Enumeration of fix type values.
 */
typedef enum NMEA_gpsFixType
{
  FIX_TYPE_NO = 0x0, //!< Fix not available
  FIX_TYPE_2D = 0x1, //!< GPS 2D fix
  FIX_TYPE_3D = 0x2  //!< GPS 3D fix
} NMEA_gpsFixType_e;

/**
 * @brief Enumeration to indicate whether the north indication is magnetic or true.
 */
typedef enum NMEA_gpsNorthType
{
  NORTH_TYPE_MAGNETIC = 'M', //!< MAGNETIC
  NORTH_TYPE_TRUE     = 'T', //!< TRUE
  NORTH_TYPE_GRID     = 'G', //!< GRID
} NMEA_gpsNorthType_e;

/**
 * @brief Arrival status type.
 */
typedef enum NMEA_gpsArrivalStatus
{
  ARRIVAL_STATUS_ARRIVED     = 'A', //!< Arrived
  ARRIVAL_STATUS_NOT_ARRIVED = 'V'  //!< Not arrived
} NMEA_gpsArrivalStatus_e;

/**
 * @brief GPRMB steer direction type.
 */
typedef enum NMEA_gpsSteerDirection
{
  STEER_DIRECTION_LEFT  = 'L', //!< Steer Left
  STEER_DIRECTION_RIGHT = 'R'  //!< Steer Right
} NMEA_gpsSteerDirection_e;

/**
 * @brief Enumeration of speed units.
 */
typedef enum NMEA_gpsSpeedUnit
{
  SPEED_UNIT_KNOTS = 'N', //!< knots
  SPEED_UNIT_KMPH  = 'K', //!< kilometers per hour
  SPEED_UNIT_MPH   = 'M'  //!< miles per hour
} NMEA_gpsSpeedUnit_e;

/**
 * @brief Enumeration of NMEA mode indicators.
 */
typedef enum NMEA_gpsModeIndicator
{
  MODE_INDICATOR_AUTONOMOUS   = 'A', //!< Autonomous mode
  MODE_INDICATOR_DIFFERENTIAL = 'D', //!< Differential mode
  MODE_INDICATOR_ESTIMATED    = 'E', //!< Estimated/dead-reckoning mode
} NMEA_gpsModeIndicator_e;

/*************************************************************************\
 * NMEA sentence type definitions
\*************************************************************************/
/**
 * @brief   Bearing, origin to destination.
 * @details
 * $GPBOD,235.500,T,238.500,M,DEST-1,DEST-2*2D
 * #00000,1111111,2,3333333,4,555555,666666*77
 * @secreflist
 *              NO | VAL        | Description
 * @refitem 0  "0  | GPBOD      | NMEA String identifier                         "
 * @refitem 1  "1  | 235.500    | True bearing to destination, degrees           "
 * @refitem 2  "2  | T          | True bearing                                   "
 * @refitem 3  "3  | 238.500    | Magnetic bearing to destination, degrees       "
 * @refitem 4  "4  | M          | Magnetic bearing                               "
 * @refitem 5  "5  | DEST-1     | Destination waypoint ID - 6 characters maximum "
 * @refitem 6  "6  | DEST-2     | Destination waypoint ID - 6 characters maximum "
 * @refitem 7  "7  | 2D         | Checksum                                       "
 */
typedef struct NMEA_gpbod
{
  NMEA_gpsStringIdentifier identifier;     /** @ref 0 */
  float                    wptDirTrue;     /** @ref 1 */
  NMEA_gpsNorthType_e      charTrue;       /** @ref 2 */
  float                    wptDirMagnetic; /** @ref 3 */
  NMEA_gpsNorthType_e      charmagnetic;   /** @ref 4 */
  char                     wptName1[6];    /** @ref 5 */
  char                     wptName2[6];    /** @ref 6 */
  NMEA_gpsStringChecksum   checkSum;       /** @ref 7 */
} NMEA_gpbod_t;
/** @endsecreflist */

/**
 * @brief   Bearing and distance to waypoint, great circle. [done]
 * @details Sample data below
 * $GPBWC,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM*11
 * #00000,111111,2222222,3,44444444,5,66666,7,88888,9,AAAAAA,B,CCCC*DD
 * @secreflist
 *              NO | VAL        | Description
 * @refitem 0  "0  | GPGGA      | NMEA String identifier                        "
 * @refitem 1  "1  | 220516     | Timestamp                                     "
 * @refitem 2  "2  | 5130.02    | Latitude of next waypoint                     "
 * @refitem 3  "3  | N          | North/South                                   "
 * @refitem 4  "4  | 00046.34   | Longitude of next waypoint                    "
 * @refitem 5  "5  | W          | East/West                                     "
 * @refitem 6  "6  | 213.0      | True track to waypoint in degrees             "
 * @refitem 7  "7  | T          | True Track                                    "
 * @refitem 8  "8  | 218.0      | Magnetic track to waypoint degrees            "
 * @refitem 9  "9  | M          | Magnetic                                      "
 * @refitem A  "A  | 0004.6     | Range to waypoint                             "
 * @refitem B  "B  | N          | Unit of range to waypoint, N = Nautical miles "
 * @refitem C  "C  | EGLM       | Waypoint name                                 "
 * @refitem D  "D  | 11         | Checksum                                      "
 */
typedef struct NMEA_gpbpwc
{
  NMEA_gpsStringIdentifier     identifier;     /** @ref 0 */
  uint16_t                     utc;            /** @ref 1 */
  float                        latitude;       /** @ref 2 */
  NMEA_gpsGeometricDirection_e northSouth;     /** @ref 3 */
  float                        longitude;      /** @ref 4 */
  NMEA_gpsGeometricDirection_e eastWest;       /** @ref 5 */
  float                        wptDirTrue;     /** @ref 6 */
  NMEA_gpsNorthType_e          charTrue;       /** @ref 7 */
  float                        wptDirMagnetic; /** @ref 8 */
  NMEA_gpsNorthType_e          charmagnetic;   /** @ref 9 */
  float                        wptRange;       /** @ref A */
  char                         wptRangeUnit;   /** @ref B */
  char                         wptName[4];     /** @ref C */
  NMEA_gpsStringChecksum       checkSum;       /** @ref D */
} NMEA_gpbwc_t;
/** @endsecreflist */

/**
 * @brief   global Positioning System Fix Data.
 * @details
 * $GPGGA,170834,4124.8963,N,08151.6838,W,1,05,1.5,280.2,M,-34.0,M, , *18
 * #00000,111111,222222222,3,4444444444,5,6,77,888,99999,A,BBBBB,C,D,E*FF
 * @secreflist
 *              NO | VAL        | Description
 * @refitem 0  "0  | GPGGA      | NMEA String identifier                                                      "
 * @refitem 1  "1  | 161229.487 | UTC of Position                                                             "
 * @refitem 2  "2  | 3723.2475  | Latitude                                                                    "
 * @refitem 3  "3  | N          | N or S                                                                      "
 * @refitem 4  "4  | 12158.3416 | Longitude                                                                   "
 * @refitem 5  "5  | W          | E or W                                                                      "
 * @refitem 6  "6  | 1          | GPS quality indicator (0=invalid; 1=GPS fix; 2=Diff. GPS fix)               "
 * @refitem 7  "7  | 07         | Number of satellites in use [not those in view]                             "
 * @refitem 8  "8  | 1.0        | Horizontal dilution of position                                             "
 * @refitem 9  "9  | 280.2      | Antenna altitude above/below mean sea level (geoid)                         "
 * @refitem A  "A  | M          | Meters  (Antenna height unit)                                               "
 * @refitem B  "B  | -34.0      | Geoidal separation (Diff. between WGS-84 earth ellipsoid and mean sea level "
 *                                -=geoid is below WGS-84 ellipsoid)                                          "
 * @refitem C  "C  | M          | Meters  (Antenna height unit)                                               "
 * @refitem D  "D  |            | Age in seconds since last update from diff. reference station               "
 * @refitem E  "E  | 0000       | Diff. reference station ID#                                                 "
 * @refitem F  "F  | 18         | Checksum                                                                    "
 */
typedef struct NMEA_gpgga
{
  NMEA_gpsStringIdentifier     identifier;              /** @ref 0 */
  uint32_t                     utc;                     /** @ref 1 */
  float                        latitude;                /** @ref 2 */
  NMEA_gpsGeometricDirection_e northSouth;              /** @ref 3 */
  float                        longitude;               /** @ref 4 */
  NMEA_gpsGeometricDirection_e eastWest;                /** @ref 5 */
  NMEA_gpsSignalQuality_e      quality;                 /** @ref 6 */
  size_t                       satellitesInUse;         /** @ref 7 */
  float                        hDop;                    /** @ref 8 */
  float                        antHeightAmsl;           /** @ref 9 */
  char                         antHeigthAmslUnit;       /** @ref A */
  float                        geoidalSperation;        /** @ref B */
  char                         geoidalSperationUnit;    /** @ref C */
  uint8_t                      referenceStationAgeDiff; /** @ref D */
  float                        referenceStationId;      /** @ref E */
  NMEA_gpsStringChecksum       checkSum;                /** @ref F */
} NMEA_gpgga_t;
/** @endsecreflist */

/**
 * @brief   Geographic position, Latitude and Longitude.
 * @details
 * $GPGLL,3751.65,S,14507.36,E*77
 * #00000,1111111,2,33333333,4*55
 * @secreflist
 *              NO | VAL        | Description
 * @refitem 0  "0  | GPGLL      | NMEA String identifier "
 * @refitem 1  "1  | 3751.65    | Latitude               "
 * @refitem 2  "2  | S          | North or South         "
 * @refitem 3  "3  | 14507.36   | Longitude              "
 * @refitem 4  "4  | E          | East or West           "
 * @refitem 5  "5  | 77         | Checksum               "
 */
typedef struct NMEA_gpgll
{
  NMEA_gpsStringIdentifier     identifier; /** @ref 0 */
  float                        latitude;   /** @ref 1 */
  NMEA_gpsGeometricDirection_e northSouth; /** @ref 2 */
  float                        longitude;  /** @ref 3 */
  NMEA_gpsGeometricDirection_e eastWest;   /** @ref 4 */
  NMEA_gpsStringChecksum       checkSum;   /** @ref 5 */
} NMEA_gpgll_t;
/** @endsecreflist */

/**
 * @brief   GPS DOP and active satellites.
 * @details
 * $GPGSA,A,3,04,05, ,09,12, , ,24, , , , ,2.5,1.3,2.1*39
 * #00000,1,2,33,--,-,--,--,-,-,--,-,-,-,-,444,555,666*77
 * @secreflist
 *              NO | VAL        | Description
 * @refitem 0  "0  | GPGSA      | NMEA string identifier                                "
 * @refitem 1  "1  | A          | Mode (M=manual, A=automatic)                          "
 * @refitem 2  "2  | 3          | Mode (1=fix not available, 2=2D, 3=3D)                "
 * @refitem 3  "3  | 04,05,...  | IDs of satellites used for fix (space-separated list) "
 * @refitem 4  "4  | 2.5        | PDOP (dilution of precision)                          "
 * @refitem 5  "5  | 1.3        | HDOP (horizontal dilution of precision)               "
 * @refitem 6  "6  | 2.1        | VDOP (vertical dilution of precision)                 "
 * @refitem 7  "7  | 39         | Checksum                                              "
 */
typedef struct NMEA_gpgsa
{
  NMEA_gpsStringIdentifier identifier;     /** @ref 0 */
  NMEA_gpsFixMode_e        mode;           /** @ref 1 */
  NMEA_gpsFixType_e        fixMode;        /** @ref 2 */
  char                     satellites[12]; /** @ref 3 */
  float                    pdop;           /** @ref 4 */
  float                    hdop;           /** @ref 5 */
  float                    vdop;           /** @ref 6 */
  NMEA_gpsStringChecksum   checkSum;       /** @ref 7 */
} NMEA_gpgsa_t;
/** @endsecreflist */

/**
 * @brief    GPS Satellites in view.
 * @details  $GPGSV,3,1,11,03,03,11,00,04,15,27,00,06,01,00,00,13,06,29,00*74
 *           #00000,1,2,33,44,--,--,--,--,--,--,--,--,--,--,--,--,--,--,--*CC
 * @secreflist
 *              NO | VAL      | Description
 * @refitem 0  "0  | GPGSV    | NMEA string identifier                         "
 * @refitem 1  "1  | 3        | Total number of messages of this type in cycle "
 * @refitem 2  "2  | 1        | Message number                                 "
 * @refitem 3  "3  | 11       | Total number of satellites in view             "
 * @refitem 4  "4  | 03,03... | Satellite ID, elevation, azimuth, SNR          "
 * @refitem C  "C  | 74       | Checksum   s                                    "
 */
typedef struct NMEA_gpgsv
{
  NMEA_gpsStringIdentifier identifier; /** @ref 0 */
  uint8_t                  total;      /** @ref 1 */
  uint8_t                  number;     /** @ref 2 */
  uint8_t                  sats;       /** @ref 3 */
  struct
  {
    uint8_t id;                    //!< Satellite ID
    uint8_t elevation;             //!< Elevation in degrees, 90 maximum
    uint8_t azimuth;               //!< Azimuth, degrees from true north, 000 to 359
    uint8_t snr;                   //!< Signal to noise ratio, 00-99 dB (null when not tracking)
  } satellite[4];                  /** @ref 4 */
  NMEA_gpsStringChecksum checksum; /** @ref 5 */
} NMEA_gpgsv_t;
/** @endsecreflist */

/**
 * @brief   NMEA identifier for GPHDT messages.
 * @details GPHDT messages provide the heading (direction) in degrees from true north.
 * $GPHDT,338.4,T*20
 * #00000,11111,2*CC
 * @secreflist
 *              NO | VAL        | Description
 * @refitem 0  "0  | GPHDT      | NMEA String identifier                            "
 * @refitem 1  "1  | 338.4      | Heading in degrees from true north                "
 * @refitem 2  "2  | T          | Indicates whether the heading is magnetic or true "
 * @refitem 3  "3  | 20         | Checksum                                          "
 */
typedef struct NMEA_gphdt
{
  NMEA_gpsStringIdentifier identifier; /** @ref 0 */
  float                    heading;    /** @ref 1 */
  NMEA_gpsNorthType_e      headingRef; /** @ref 2 */
  NMEA_gpsStringChecksum   checkSum;   /** @ref 3 */
} NMEA_gphdt_t;
/** @endsecreflist */

/**
 * @brief   NMEA identifier for GPR00 messages.
 * @details GPR00 messages provide a list of waypoints in the currently active route.
 * $GPR00,EGLM,EGTB,EGUB,EGTK*2D
 * #00000,1111,2222,3333,4444*CC
 * @secreflist
 *              NO | VAL        | Description
 * @refitem 0  "0  | GPR00      | NMEA String identifier "
 * @refitem 1  "1  | EGLM       | Waypoint name          "
 * @refitem 2  "2  | EGTB       | Waypoint name          "
 * @refitem 3  "3  | EGUB       | Waypoint name          "
 * @refitem 4  "4  | EGTK       | Waypoint name          "
 * @refitem 5  "5  | 2D         | Checksum               "
 */
typedef struct NMEA_gpr00
{
  NMEA_gpsStringIdentifier identifier;  /** @ref 0 */
  char                     wptName1[6]; /** @ref 1 */
  char                     wptName2[6]; /** @ref 2 */
  char                     wptName3[6]; /** @ref 3 */
  char                     wptName4[6]; /** @ref 4 */
  NMEA_gpsStringChecksum   checkSum;    /** @ref 5 */
} NMEA_gpr00_t;
/** @endsecreflist */

/**
 * @brief   Recommended minimum specific GPS/Transit data.
 * @details
 * $GPRMA,A,llll.ll,N,lllll.ll,W, , ,ss.s,ccc,vv.v,W*hh
 * #00000,1,2222222,3,44444444,5,6,7,8888,999,AAAA,B*CC
 * @secreflist
 *             NO | VAL      | Description
 * @refitem 0 "0  | GPRMA    | NMEA String identifier                                    "
 * @refitem 1 "1  | A        | Data status (A=valid data; V=navigation receiver warning) "
 * @refitem 2 "2  | llll.ll  | Latitude                                                  "
 * @refitem 3 "3  | N        | N or S                                                    "
 * @refitem 4 "4  | lllll.ll | Longitude                                                 "
 * @refitem 5 "5  | W        | E or W                                                    "
 * @refitem 6 "6  |          | not used                                                  "
 * @refitem 7 "7  |          | not used                                                  "
 * @refitem 8 "8  | ss.s     | Speed over ground in knots                                "
 * @refitem 9 "9  | ccc      | Course over ground                                        "
 * @refitem A "A  | vv.v     | Variation                                                 "
 * @refitem B "B  | W        | Direction of variation (E/W)                              "
 * @refitem C "C  | hh       | Checksum                                                  "
 */
typedef struct NMEA_gprma
{
  NMEA_gpsStringIdentifier     identifier;           /** @ref 0 */
  NMEA_gpsValidity_e           validity;             /** @ref 1 */
  float                        latitude;             /** @ref 2 */
  NMEA_gpsGeometricDirection_e charLat;              /** @ref 3 */
  float                        longitude;            /** @ref 4 */
  NMEA_gpsGeometricDirection_e charLong;             /** @ref 5 */
  float                        speed;                /** @ref 8 */
  float                        course;               /** @ref 9 */
  float                        variation;            /** @ref A */
  NMEA_gpsGeometricDirection_e directionOfVariation; /** @ref B */
  NMEA_gpsStringChecksum       checkSum;             /** @ref C */
} NMEA_gprma_t;
/** @endsecreflist */

/**
 * @brief   Recommended minimum navigation information.
 * @details
 * $GPRMB,A,0.66,L,003,004,4917.24,N,12309.57,W,001.3,052.5,000.5,V*0B
 * #00000,1,2222,3,444,555,6666666,7,88888888,9,AAAAA,BBBBB,CCCCC,D*EE
 * @secreflist
 *              NO | VAL           | Description
 * @refitem 0  "0  | GPRMB         | NMEA string identifier                        "
 * @refitem 1  "1  | A             | Data status (A = OK, V = warning)             "
 * @refitem 2  "2  | 0.66          | Cross-track error (nautical miles, 9.9 max.)  "
 * @refitem 3  "3  | L             | Steer Left or Right to correct error          "
 * @refitem 4  "4  | 003           | Origin waypoint ID                            "
 * @refitem 5  "5  | 004           | Destination waypoint ID                       "
 * @refitem 6  "6  | 4917.24       | Destination waypoint latitude                 "
 * @refitem 7  "7  | N             | N or S (destination waypoint latitude)        "
 * @refitem 8  "8  | 12309.57      | Destination waypoint longitude                "
 * @refitem 9  "9  | W             | E or W (destination waypoint longitude)       "
 * @refitem A  "A  | 001.3         | Range to destination, nautical miles          "
 * @refitem B  "B  | 052.5         | True bearing to destination                   "
 * @refitem C  "C  | 000.5         | Velocity towards destination, knots           "
 * @refitem D  "D  | V             | Arrival status (A = arrived, V = not arrived) "
 * @refitem E  "E  | 0B            | Checksum                                      "
 */
typedef struct NMEA_gprmb
{
  NMEA_gpsStringIdentifier   identifier;        /** @ref 0 */
  NMEA_gpsValidity_e         dataStatus;        /** @ref 1 */
  float                      crossTrackError;   /** @ref 2 */
  NMEA_gpsSteerDirection     steerDirection;    /** @ref 3 */
  char                       originWaypoint[5]; /** @ref 4 */
  char                       destWaypoint[5];   /** @ref 5 */
  float                      destLatitude;      /** @ref 6 */
  NMEA_gpsGeometricDirection latDirection;      /** @ref 7 */
  float                      destLongitude;     /** @ref 8 */
  NMEA_gpsGeometricDirection lonDirection;      /** @ref 9 */
  float                      range;             /** @ref A */
  float                      bearing;           /** @ref B */
  float                      closingVelocity;   /** @ref C */
  NMEA_gpsArrivalStatus      arrivalStatus;     /** @ref D */
  NMEA_gpsStringChecksum     checkSum;          /** @ref E */
} NMEA_gprmb_t;
/** @endsecreflist */

/**
 * @brief   Recommended minimum specific GPS/Transit data.
 * @details
 * $GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A
 * #00000,111111,2,33333333,4,555555555,6,77777,88888,999999,AAAAA,B*CC
 * @secreflist
 *              NO | VAL        | Description
 * @refitem 0  "0  | GPRMC      | NMEA string identifier            "
 * @refitem 1  "1  | 123519     | UTC of position                   "
 * @refitem 2  "2  | A          | Data status (A = OK, V = warning) "
 * @refitem 3  "3  | 4807.038   | Latitude                          "
 * @refitem 4  "4  | N          | N or S                            "
 * @refitem 5  "5  | 01131.000  | Longitude                         "
 * @refitem 6  "6  | E          | E or W                            "
 * @refitem 7  "7  | 022.4      | Speed over ground (knots)         "
 * @refitem 8  "8  | 084.4      | Course made good (degrees true)   "
 * @refitem 9  "9  | 230394     | Date - 23rd of March 1994         "
 * @refitem A  "A  | 003.1      | Magnetic variation                "
 * @refitem B  "B  | W          | E or W                            "
 * @refitem C  "C  | 6A         | Checksum                          "
 */
typedef struct NMEA_gprmc
{
  NMEA_gpsStringIdentifier   identifier;          /** @ref 0 */
  uint32_t                   utc;                 /** @ref 1 */
  NMEA_gpsValidity_e         dataStatus;          /** @ref 2 */
  float                      latitude;            /** @ref 3 */
  NMEA_gpsGeometricDirection northSouth;          /** @ref 4 */
  float                      longitude;           /** @ref 5 */
  NMEA_gpsGeometricDirection eastWest;            /** @ref 6 */
  float                      speedOverGround;     /** @ref 7 */
  float                      course;              /** @ref 8 */
  uint32_t                   date;                /** @ref 9 */
  float                      magneticVariation;   /** @ref A */
  NMEA_gpsGeometricDirection magneticVariationEW; /** @ref B */
} NMEA_gprmc_t;

/**
 * @brief Route message.
 * @details The GPRTE message provides information about a route.
 *
 * $GPRTE,A,1,c,0,PBRCPK,PBRTO,PTELGR,PPLAND,PYAMBU,PPFAIR,PWARRN,PLISMR*75
 * #00000,1,2,3,4,555555,66666,777777,888888,999999,AAAAAA,BBBBBB,CCCCCC*DD
 * @secreflist
 *              NO | VAL           | Description
 * @refitem 0  "0  | GPRTE         | NMEA string identifier                           "
 * @refitem 1  "1  | A             | Data status (A = OK, V = warning)                "
 * @refitem 2  "2  | 1             | Total number of messages in the sequence         "
 * @refitem 3  "3  | c             | Sequence number of the current message           "
 * @refitem 4  "4  | 0             | Waypoint ID of the active waypoint               "
 * @refitem 5  "5  | PBRCPK        | Waypoint ID of the first waypoint in the route   "
 * @refitem 6  "6  | PBRTO         | Waypoint ID of the second waypoint in the route  "
 * @refitem 7  "7  | PTELGR        | Waypoint ID of the third waypoint in the route   "
 * @refitem 8  "8  | PPLAND        | Waypoint ID of the fourth waypoint in the route  "
 * @refitem 9  "9  | PYAMBU        | Waypoint ID of the fifth waypoint in the route   "
 * @refitem A  "A  | PPFAIR        | Waypoint ID of the sixth waypoint in the route   "
 * @refitem B  "B  | PWARRN        | Waypoint ID of the seventh waypoint in the route "
 * @refitem C  "C  | PLISMR        | Waypoint ID of the eighth waypoint in the route  "
 * @refitem D  "D  | 75            | Checksum                                         "
 */
typedef struct NMEA_gprte
{
  NMEA_gpsStringIdentifier identifier;      /** @ref 0 */
  NMEA_gpsValidity_e       dataStatus;      /** @ref 1 */
  int                      numMessages;     /** @ref 2 */
  int                      sequenceNum;     /** @ref 3 */
  int                      activeWaypoint;  /** @ref 4 */
  char                     waypoints[8][6]; /** @ref 5-C */
  NMEA_gpsStringChecksum   checkSum;        /** @ref D */
} NMEA_gprte_t;
/** @endsecreflist */

/**
 * @brief Transit fix data.
 * @details The GPTRF message provides information about a transit fix,
 * which is a location on a great circle that is being followed.
 *
 * $GPTRF,hhmmss.ss,LLLL.ll,a,yyyyy.yy,a,x.x,x.x,x.x,x.x,a,m,yyyyy.yy,a*hh
 * #00000,111111111,2222222,3,44444444,5,666,777,888,999,A,B,CCCCCCCC,D*EE
 * @secreflist
 *              NO | VAL           | Description
 * @refitem 0  "0  | GPTRF         | NMEA string identifier                            "
 * @refitem 1  "1  | hhmmss.ss     | UTC time at the transit fix (HHMMSS.SS)           "
 * @refitem 2  "2  | LLLL.ll       | Latitude of the transit fix (LLLL.LL)             "
 * @refitem 3  "3  | a             | N or S (latitude of the transit fix)              "
 * @refitem 4  "4  | yyyyy.yy      | Longitude of the transit fix (yyyyy.yy)           "
 * @refitem 5  "5  | a             | E or W (longitude of the transit fix)             "
 * @refitem 6  "6  | x.x           | Range to the transit fix, nautical miles          "
 * @refitem 7  "7  | x.x           | True bearing to the transit fix                   "
 * @refitem 8  "8  | x.x           | Velocity towards the transit fix, knots           "
 * @refitem 9  "9  | x.x           | Transit fix variation, degrees                    "
 * @refitem A  "A  | a             | E or W (transit fix variation)                    "
 * @refitem B  "B  | m             | Mode indicator (A = autonomous, D = differential) "
 * @refitem C  "C  | yyyyy.yy      | Reference station ID (yyyyy.yy)                   "
 * @refitem D  "D  | a             | Reference station variation direction             "
 * @refitem E  "E  | hh            | Checksum                                          "
 */
typedef struct NMEA_gptrf
{
  NMEA_gpsStringIdentifier   identifier;    /** @ref 0 */
  uint16_t                   time;          /** @ref 1 */
  float                      latitude;      /** @ref 2 */
  NMEA_gpsGeometricDirection latDir;        /** @ref 3 */
  float                      longitude;     /** @ref 4 */
  NMEA_gpsGeometricDirection lonDir;        /** @ref 5 */
  float                      range;         /** @ref 6 */
  float                      bearing;       /** @ref 7 */
  float                      velocity;      /** @ref 8 */
  float                      variation;     /** @ref 9 */
  NMEA_gpsGeometricDirection variationDir;  /** @ref A */
  NMEA_gpsMode               mode;          /** @ref B */
  float                      refStationID;  /** @ref C */
  NMEA_gpsGeometricDirection refStationDir; /** @ref D */
  NMEA_gpsStringChecksum     checkSum;      /** @ref E */
} NMEA_gptrf_t;
/** @endsecreflist */

/**
 * @brief    Multiple data ID. The GPSTN message is transmitted before each individual sentence where there is a need for the listener to
 *           determine the exact source of data in the system.
 * @details  $GPSTN,xx*22
 *           #00000,11*22
 * @secreflist
 *              NO | VAL           | Description
 * @refitem 0  "0  | GPSTN         | NMEA string identifier     "
 * @refitem 1  "1  | xx            | Talker ID number, 00 to 99 "
 * @refitem 2  "2  | 00            | Checksum                   "
 */
typedef struct NMEA_gpstn
{
  NMEA_gpsStringIdentifier identifier; /** @ref 0 */
  int                      talkerID;   /** @ref 1 */
  NMEA_gpsStringChecksum   checkSum;   /** @ref 2 */
} NMEA_gpstn_t;
/** @endsecreflist */

/**
 * @brief    Dual ground/water speed, The GPVBW message provides information about the speed of the vehicle over ground and through water.
 * @details  $GPVBW,x.x,a,x.x,a,x.x,a,x.x,a*hh
 *           #00000,111,2,333,4,555,6,777,8*99
 * @secreflist
 *              NO | VAL           | Description
 * @refitem 0  "0  | GPVBW         | NMEA string identifier         "
 * @refitem 1  "1  | x.x           | Water speed, knots             "
 * @refitem 2  "2  | a             | Water speed direction          "
 * @refitem 3  "3  | x.x           | Ground speed, knots            "
 * @refitem 4  "4  | a             | Ground speed direction         "
 * @refitem 5  "5  | x.x           | Heading, degrees               "
 * @refitem 6  "6  | a             | Heading direction              "
 * @refitem 7  "7  | x.x           | Magnitude of cross-track error "
 * @refitem 8  "8  | a             | Cross-track error direction    "
 * @refitem 9  "9  | hh            | Checksum                       "
 */
typedef struct NMEA_gpvbw
{
  NMEA_gpsStringIdentifier   identifier; /** @ref 0 */
  float                      water;      /** @ref 1 */
  NMEA_gpsGeometricDirection waterDir;   /** @ref 2 */
  float                      ground;     /** @ref 3 */
  NMEA_gpsGeometricDirection groundDir;  /** @ref 4 */
  float                      heading;    /** @ref 5 */
  NMEA_gpsGeometricDirection headingDir; /** @ref 6 */
  float                      crossTrack; /** @ref 7 */
  NMEA_gpsGeometricDirection crossDir;   /** @ref 8 */
  NMEA_gpsStringChecksum     checkSum;   /** @ref 9 */
} NMEA_gpvbw_t;
/** @endsecreflist */

/**
 * @brief    Track made good and ground speed.
 * @details  $GPVTG,054.7,T,034.4,M,005.5,N,010.2,K*48
 *           #00000,11111,2,33333,4,55555,6,77777,8*99
 * @secreflist
 *              NO | VAL        | Description
 * @refitem 0  "0  | GPVTG      | NMEA string identifier                 "
 * @refitem 1  "1  | 054.7      | Track made good (degrees true)         "
 * @refitem 2  "2  | T          | True                                   "
 * @refitem 3  "3  | 034.4      | Track made good (degrees magnetic)     "
 * @refitem 4  "4  | M          | Magnetic                               "
 * @refitem 5  "5  | 005.5      | Ground speed, knots                    "
 * @refitem 6  "6  | N          | Ground speed, knots unit               "
 * @refitem 7  "7  | 010.2      | Ground speed, kilometers per hour      "
 * @refitem 8  "8  | K          | Ground speed, kilometers per hour unit "
 * @refitem 9  "9  | 48         | Checksum                               "
 */
typedef struct NMEA_gpvtg
{
  NMEA_gpsStringIdentifier identifier;            /** @ref 0 */
  float                    trackMadeGoodTrue;     /** @ref 1 */
  NMEA_gpsNorthType_e      trueIndicator;         /** @ref 2 */
  float                    trackMadeGoodMagnetic; /** @ref 3 */
  NMEA_gpsNorthType_e      magneticIndicator;     /** @ref 4 */
  float                    groundSpeedKnots;      /** @ref 5 */
  NMEA_gpsSpeedUnit_e      knotsUnit;             /** @ref 6 */
  float                    groundSpeedKmph;       /** @ref 7 */
  NMEA_gpsSpeedUnit_e      kmphUnit;              /** @ref 8 */
  NMEA_gpsStringChecksum   checkSum;              /** @ref 9 */
} NMEA_gpvtg_t;
/** @endsecreflist */

/**
 * @brief    Waypoint location.
 * @details  $GPWPL,4917.16,N,12310.64,W,003*65
 *           #00000,1111111,2,33333333,4,555*66
 * @secreflist
 *             NO | VAL      | Description
 * @refitem 0 "0  | GPWPL    | NMEA string identifier "
 * @refitem 1 "1  | 4917.16  | Latitude               "
 * @refitem 2 "2  | N        | North or South         "
 * @refitem 3 "3  | 12310.64 | Longitude              "
 * @refitem 4 "4  | W        | East or West           "
 * @refitem 5 "5  | 003      | Waypoint ID            "
 * @refitem 6 "6  | 65       | Checksum               "
 */
typedef struct NMEA_gpwpl
{
  NMEA_gpsStringIdentifier   identifier; /** @ref 0 */
  float                      latitude;   /** @ref 1 */
  NMEA_gpsGeometricDirection northSouth; /** @ref 2 */
  float                      longitude;  /** @ref 3 */
  NMEA_gpsGeometricDirection eastWest;   /** @ref 4 */
  uint16_t                   waypointId; /** @ref 5 */
  NMEA_gpsStringChecksum     checkSum;   /** @ref 6 */
} NMEA_gpwpl_t;
/** @endsecreflist */

/**
 * @brief    NMEA GPXTE message type.
 * @details  $GPXTE,A,A,0.67,L,N*6D
 *           #00000,1,2,3333,4,5*66
 * @secreflist
 *              NO | VAL    | Description
 * @refitem 0  "0  | GPXTE  | NMEA String identifier                                                   "
 * @refitem 1  "1  | A      | Validity of cross-track error, A=valid, V=invalid                        "
 * @refitem 2  "2  | A      | Mode indicator A=Autonomous, D=Differential, E=Estimated (dead-reckoning)"
 * @refitem 3  "3  | 0.67   | Cross-track error                                                        "
 * @refitem 4  "4  | L      | Direction to steer L/R                                                   "
 * @refitem 5  "5  | N      | Distance units - Nautical miles                                          "
 * @refitem 6  "6  | 6D     | Checksum                                                                 "
 */
typedef struct NMEA_gpxte
{
  NMEA_gpsStringIdentifier identifier;     /** @ref 0 */
  NMEA_gpsValidity_e       validity;       /** @ref 1 */
  NMEA_gpsModeIndicator_e  modeIndicator;  /** @ref 2 */
  float                    error;          /** @ref 3 */
  NMEA_gpsSteerDirection_e steerDirection; /** @ref 4 */
  char                     distanceUnits;  /** @ref 5 */
  NMEA_gpsStringChecksum   checksum;       /** @ref 6 */
} NMEA_gpxte_t;
/** @endsecreflist */

/**
 * @brief    NMEA GPZDA message type.
 * @details  $GPZDA,161229.487,30,07,2021,-0400,-30*F2
 *           #00000,1111111111,22,33,4444,55555,666*77
 * @secreflist
 *              NO | VAL        | Description
 * @refitem 0  "0  | GPZDA      | NMEA String identifier                                              "
 * @refitem 1  "1  | 161229.487 | UTC time, hhmmss.ss format                                          "
 * @refitem 2  "2  | 30         | Day of the month                                                    "
 * @refitem 3  "3  | 07         | Month of the year                                                   "
 * @refitem 4  "4  | 2021       | Year                                                                "
 * @refitem 5  "5  | -0400      | Local hour difference from UTC, +/-hhmm format                      "
 * @refitem 6  "6  | -30        | Local minute difference from UTC                                    "
 * @refitem 7  "7  | F2         | Checksum                                                            "
 */
typedef struct NMEA_gpzda
{
  NMEA_gpsStringIdentifier identifier;            /** @ref 0 */
  float                    utcTime;               /** @ref 1 */
  uint8_t                  dayOfMonth;            /** @ref 2 */
  uint8_t                  monthOfYear;           /** @ref 3 */
  uint16_t                 year;                  /** @ref 4 */
  int16_t                  localHourDifference;   /** @ref 5 */
  int16_t                  localMinuteDifference; /** @ref 6 */
  NMEA_gpsStringChecksum   checksum;              /** @ref 7 */
} NMEA_gpzda_t;
/** @endsecreflist */

/**
 * @brief    Union containing all NMEA message types.
 * @details  This union is used to store any of the NMEA message types, so that they can be accessed and processed as needed.
 * @secreflist
 *             NO | VAL   | Description
 * @refitem 0 "0  | GPGLL | NMEA Geographic position, latitude / longitude message type"
 * @refitem 1 "1  | GPGGA | NMEA global Positioning System Fix Data message type"
 * @refitem 2 "2  | GPGSA | NMEA GPS DOP and active satellites message type"
 * @refitem 3 "3  | GPGSV | NMEA GPS Satellites in view message type"
 * @refitem 4 "4  | GPRMC | NMEA Recommended minimum specific GPS/Transit data message type"
 * @refitem 5 "5  | GPVTG | NMEA Track made good and ground speed message type"
 * @refitem 6 "6  | GPZDA | NMEA Date & Time message type"
 * @refitem 7 "7  | GPBOD | NMEA Bearing, origin to destination message type"
 * @refitem 8 "8  | GPBWC | NMEA Bearing and distance to waypoint, great circle message type"
 * @refitem 9 "9  | GPHDT | NMEA GPHDT messages provide the heading (direction) in degrees from true north message type"
 * @refitem A "A  | GPR00 | NMEA List of waypoints in currently active route message type"
 * @refitem B "B  | GPRMA | NMEA Recommended minimum specific Loran-C data message type"
 * @refitem C "C  | GPRMB | NMEA Recommended minimum navigation info message type"
 * @refitem D "D  | GPRTE | NMEA Routes message type"
 * @refitem E "E  | GPTRF | NMEA Transit Fix Data message type"
 * @refitem F "F  | GPSTN | NMEA Multiple Data ID message type"
 * @refitem G "G  | GPVBW | NMEA Dual Ground / Water Speed message type"
 * @refitem H "H  | GPWPL | NMEA Waypoint location message type"
 * @refitem I "I  | GPXTE | NMEA Cross-track error, Measured message type"
 */
typedef union NMEA_messageUnion
{
  NMEA_gpbod_t GPBOD; /** @ref 0 */
  NMEA_gpbwc_t GPBWC; /** @ref 1 */
  NMEA_gpgga_t GPGGA; /** @ref 2 */
  NMEA_gpgll_t GPGLL; /** @ref 3 */
  NMEA_gpgsa_t GPGSA; /** @ref 4 */
  NMEA_gpgsv_t GPGSV; /** @ref 5 */
  NMEA_gphdt_t GPHDT; /** @ref 6 */
  NMEA_gpr00_t GPR00; /** @ref 7 */
  NMEA_gprma_t GPRMA; /** @ref 8 */
  NMEA_gprmb_t GPRMB; /** @ref 9 */
  NMEA_gprmc_t GPRMC; /** @ref A */
  NMEA_gprte_t GPRTE; /** @ref B */
  NMEA_gptrf_t GPTRF; /** @ref C */
  NMEA_gpstn_t GPSTN; /** @ref D */
  NMEA_gpvbw_t GPVBW; /** @ref E */
  NMEA_gpvtg_t GPVTG; /** @ref F */
  NMEA_gpwpl_t GPWPL; /** @ref G */
  NMEA_gpxte_t GPXTE; /** @ref H */
  NMEA_gpzda_t GPZDA; /** @ref I */
} NMEA_messageTypeUnion_u;
/** @endsecreflist */
/*************************************************************************\
 * End of file
\*************************************************************************/
