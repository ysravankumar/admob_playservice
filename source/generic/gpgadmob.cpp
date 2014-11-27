/*
Generic implementation of the gpgadmob extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "gpgadmob_internal.h"
s3eResult gpgadmobInit()
{
    //Add any generic initialisation code here
    return gpgadmobInit_platform();
}

void gpgadmobTerminate()
{
    //Add any generic termination code here
    gpgadmobTerminate_platform();
}

s3eResult AdmobInit(const char* adUnitId, int adType, int x, int y)
{
	return AdmobInit_platform(adUnitId, adType, x, y);
}

s3eResult AdmobTestDevice(const char* szTestDeviceID)
{
	return AdmobTestDevice_platform(szTestDeviceID);
}

s3eResult AdmobResize(int ad_type)
{
	return AdmobResize_platform(ad_type);
}

s3eResult AdmobShow()
{
	return AdmobShow_platform();
}

s3eResult AdmobRefresh()
{
	return AdmobRefresh_platform();
}

s3eResult AdmobHide()
{
	return AdmobHide_platform();
}

s3eResult AdmobMove(int orientation, int x, int y)
{
	return AdmobMove_platform(orientation, x, y);
}

s3eResult AdmobInterestialPreload(const char * adUnitId)
{
	return AdmobInterestialPreload_platform(adUnitId);
}

bool AdmobInterestialIsReady()
{
	return AdmobInterestialIsReady_platform();
}

bool AdmobInterestialIsShown()
{
	return AdmobInterestialIsShown_platform();
}

bool AdmobInterestialWasShown()
{
	return AdmobInterestialWasShown_platform();
}

bool AdmobInterestialHasBeenUsed()
{
	return AdmobInterestialHasBeenUsed_platform();
}

s3eResult AdmobInterestialShow()
{
	return AdmobInterestialShow_platform();
}

s3eResult AdmobInterestialHide()
{
	return AdmobInterestialHide_platform();
}

bool AdmobBannerIsClicked()
{
	return AdmobBannerIsClicked_platform();
}

bool AdmobInterestialIsClicked()
{
	return AdmobInterestialIsClicked_platform();
}
