/*
 * CommonTypes.h
 *
 *  Created on: 2015年7月15日
 *      Author: weimi_000
 */

#ifndef INCLUDE_COMMONTYPES_H_
#define INCLUDE_COMMONTYPES_H_


#include <sys/time.h>

typedef struct timeval	TimeStamp;

enum CSEType
{
  IN_CSE = 1,
  MN_CSE = 2,
  ASN_CSE = 3,
};

// also used for MemberType
enum ResourceType
{
  // Normal Resources

  ACCESS_CONTROL_POLICY = 1,
  AE = 2,
  CONTAINER = 3,
  CONTENT_INSTANCE = 4,
  CSE_BASE = 5,
  DELIVERY = 6,
  EVENT_CONFIG = 7,
  EXEC_INSTANCE = 8,
  GROUP = 9,
  LOCATION_POLICY = 10,
  MGMT_CMD = 11,
  MGMT_OBJ = 12,
  SERVICE_SUB_PROFILE = 13, // m2mServiceSubscriptionProfile
  NODE = 14,
  POLLING_CHANNEL = 15,
  REMOTE_CSE = 16,
  REQUEST = 17,
  SCHEDULE = 18,
  SERVICE_SUB_NODE = 19,    // serviceSubscribedNode
  STATS_COLLECT = 20,
  STATS_CONFIG = 21,
  SUBSCRIPTION = 22,
  SERVICE_SUB_APP_RULE = 23,    // serviceSubscribedAppRule

  MEMBER_MIXED = 24,	// for MemberType only

  // Announced Resources, not for MemberType

  ACCESS_CONTROL_POLICY_ANNC = 10001,
  AE_ANNC = 10002,
  CONTAINER_ANNC = 10003,
  CONTENT_INSTANCE_ANNC = 10004,
  GROUP_ANNC = 10005,
  LOCATION_POLICY_ANNC = 10006,
  MGMT_OBJ_ANNC = 10007,
  NODE_ANNC = 10008,
  REMOTE_CSE_ANNC = 10009,
  SCHEDULE_ANNC = 10010,

  // Virtual Resources, not for MemberType

  LATEST = 90001,
  OLDEST = 90002,
  FAN_OUT_POINT = 90003,
  POLLING_CHANNEL_URI = 90004,
};

#endif /* INCLUDE_COMMONTYPES_H_ */
