/*
 * Internal header for the gpgadmob extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef GPGADMOB_INTERNAL_H
#define GPGADMOB_INTERNAL_H

#include "s3eTypes.h"
#include "gpgadmob.h"
#include "gpgadmob_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult gpgadmobInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult gpgadmobInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void gpgadmobTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void gpgadmobTerminate_platform();
s3eResult AdmobInit_platform(const char* adUnitId, int adType, int x, int y);

s3eResult AdmobTestDevice_platform(const char* szTestDeviceID);

s3eResult AdmobResize_platform(int ad_type);

s3eResult AdmobShow_platform();

s3eResult AdmobRefresh_platform();

s3eResult AdmobHide_platform();

s3eResult AdmobMove_platform(int orientation, int x, int y);

s3eResult AdmobInterestialPreload_platform(const char * adUnitId);

bool AdmobInterestialIsReady_platform();

bool AdmobInterestialIsShown_platform();

bool AdmobInterestialWasShown_platform();

bool AdmobInterestialHasBeenUsed_platform();

s3eResult AdmobInterestialShow_platform();

s3eResult AdmobInterestialHide_platform();

bool AdmobBannerIsClicked_platform();

bool AdmobInterestialIsClicked_platform();


#endif /* !GPGADMOB_INTERNAL_H */