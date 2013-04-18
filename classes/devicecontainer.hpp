//
//  devicecontainer.hpp
//  p44bridged
//
//  Created by Lukas Zeller on 17.04.13.
//  Copyright (c) 2013 plan44.ch. All rights reserved.
//

#ifndef __p44bridged__devicecontainer__
#define __p44bridged__devicecontainer__

#include "p44bridged_common.hpp"


using namespace std;

class DeviceClassContainer;
typedef boost::shared_ptr<DeviceClassContainer> DeviceClassContainerPtr;

/// generic callback for signalling completion (with success/error reporting)
typedef boost::function<void (ErrorPtr aError)> CompletedCB;


/// container for all devices hosted by this application
/// - is the connection point to a vDSM
/// - contains one or multiple device class containers
///   (each representing a specific class of devices, e.g. different bus types etc.)
class DeviceContainer;
typedef boost::shared_ptr<DeviceContainer> DeviceContainerPtr;
class DeviceContainer
{
  list<DeviceClassContainerPtr> deviceClassContainers;
public:
  /// add a device class container
  /// @param aDeviceClassContainerPtr a shared_ptr to a device class container
  /// @note this is a one-time initialisation. Device class containers are not meant to be removed at runtime
  void addDeviceClassContainer(DeviceClassContainerPtr aDeviceClassContainerPtr);

  /// get a sufficiently unique identifier for this device container
  /// @return ID that identifies this container running on a specific hardware
  ///   the ID should not be dependent on the software version
  ///   the ID MUST change when same software runs on different hardware
  ///   Usually, a hardware-ID such as the MAC address is used
  string deviceContainerInstanceIdentifier();

  /// @name device detection and registration
  /// @{

  /// collect devices from all device classes
  /// @param aCompletedCB will be called when all device scans have completed
  void collectDevices(CompletedCB aCompletedCB);


  /// @}
};

#endif /* defined(__p44bridged__devicecontainer__) */
