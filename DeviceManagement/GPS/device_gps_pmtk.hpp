/*************************************************************************\
 * Documentation
\*************************************************************************/
/**
 * @file     device_gps_pmtk.hpp
 * @brief
 * @details
 * @version  0.1
 */
#pragma once
/*************************************************************************\
 * Includes
\*************************************************************************/

/*************************************************************************\
 * Defines
\*************************************************************************/
typedef enum PMTK_gpsPmtkMessageType
{
  PMTK_MESSAGE_TYPE_ACK                  = 001,
  PMTK_MESSAGE_TYPE_SYS_MSG              = 010,
  PMTK_MESSAGE_TYPE_TXT_MSG              = 011,
  PMTK_MESSAGE_TYPE_CMD_HOT_START        = 101,
  PMTK_MESSAGE_TYPE_CMD_WARM_START       = 102,
  PMTK_MESSAGE_TYPE_CMD_COLD_START       = 103,
  PMTK_MESSAGE_TYPE_CMD_FULL_COLD_START  = 104,
  PMTK_MESSAGE_TYPE_SET_NMEA_UPDATERATE  = 220,
  PMTK_MESSAGE_TYPE_SET_NMEA_BAUDRATE    = 251,
  PMTK_MESSAGE_TYPE_API_SET_DGPS_MODE    = 301,
  PMTK_MESSAGE_TYPE_API_Q_DGPS_MODE      = 401,
  PMTK_MESSAGE_TYPE_API_DT_DGPS_MODE     = 501,
  PMTK_MESSAGE_TYPE_API_SET_SBAS_ENABLED = 313,
  PMTK_MESSAGE_TYPE_API_Q_SBAS_ENABLED   = 413,
  PMTK_MESSAGE_TYPE_DT_SBAS_ENABLED      = 513,
  PMTK_MESSAGE_TYPE_API_SET_NMEA_OUTPUT  = 314,
  PMTK_MESSAGE_TYPE_API_Q_NMEA_OUTPUT    = 414,
  PMTK_MESSAGE_TYPE_API_DT_NMEA_OUTPUT   = 514,
  PMTK_MESSAGE_TYPE_API_SET_SBAS_MODE    = 319,
  PMTK_MESSAGE_TYPE_API_Q_SBAS_MODE      = 419,
  PMTK_MESSAGE_TYPE_API_DT_SBAS_MODE     = 519,
  PMTK_MESSAGE_TYPE_Q_RELEASE            = 605,
  PMTK_MESSAGE_TYPE_DT_RELEASE           = 705,
  PMTK_MESSAGE_TYPE_Q_EPO_INFO           = 607,
  PMTK_MESSAGE_TYPE_DT_EPO_INFO          = 707,
  PMTK_MESSAGE_TYPE_CMD_CLEAR_EPO        = 127,
#if defined(DEVICE_GPS_MTK3318_H) || defined(DEVICE_GPS_MTK3329_H)
  PMTK_MESSAGE_TYPE_SET_NAV_SPEED_THRESHOLD = 397,
#elif defined(DEVICE_GPS_MTK3339_H)
  PMTK_MESSAGE_TYPE_SET_NAV_SPEED_THRESHOLD = 386,
#endif
  PMTK_MESSAGE_TYPE_Q_NAV_THRESHOLD           = 447,
  PMTK_MESSAGE_TYPE_DT_NAV_THRESHOLD          = 527,
  PMTK_MESSAGE_TYPE_CMD_STANDBY_MODE          = 161,
  PMTK_MESSAGE_TYPE_SET_AL_DEE_CFG            = 223,
  PMTK_MESSAGE_TYPE_CMD_PERIODIC_MODE         = 225,
  PMTK_MESSAGE_TYPE_CMD_AIC_MODE              = 286,
  PMTK_MESSAGE_TYPE_CMD_EASY_ENABLE           = 869,
  PMTK_MESSAGE_TYPE_LOCUS_CONFIG              = 187,
  PMTK_MESSAGE_TYPE_API_SET_DATUM             = 330,
  PMTK_MESSAGE_TYPE_API_Q_DATUM               = 430,
  PMTK_MESSAGE_TYPE_API_DT_DATUM              = 530,
  PMTK_MESSAGE_TYPE_API_SET_SUPPORT_QZSS_NMEA = 351,
  PMTK_MESSAGE_TYPE_API_SET_STOP_QZSS         = 352,
  PMTK_MESSAGE_TYPE_TypesOfMessages
} PMTK_gpsPmtkMessageTypes_t;
/*************************************************************************\
 * End of file
\*************************************************************************/
