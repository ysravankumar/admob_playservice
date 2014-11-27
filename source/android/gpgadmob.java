/*
java implementation of the gpgadmob extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;
import com.ideaworks3d.marmalade.LoaderActivity;

import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.view.Gravity;
import android.widget.FrameLayout;
import android.widget.FrameLayout.LayoutParams;

class gpgadmob
{
	public class BannerAdListener extends AdListener
	{
		String m_strAdUnitId;
		String m_strTestDevice;
		AdView m_adView;
		AdSize m_iAdType;
		int m_iX;
		int m_iY;
		int m_iW;
		int m_iH;
		boolean m_bIsClicked;
		
		FrameLayout.LayoutParams m_layoutParams;
		
		public void onAdLoaded() 
		{
			//displayInterstitial();
		}
		  public void onAdFailedToLoad(int errorCode) {}
		  public void onAdOpened() {}
		  public void onAdClosed() {}
		  public void onAdLeftApplication() {m_bIsClicked=true;}
	}
	
	BannerAdListener bannerListener = new BannerAdListener();
	
	public class InterestialListerner extends AdListener {

		InterstitialAd m_interstitial;
		String m_strAdUnitId;
		String m_strTestDevice;

		boolean m_bIsShown;
		boolean m_bWasShown;
		boolean m_bIsReady;
		boolean m_bIsFail;
		boolean m_bIsClicked;

		
		public void onAdLoaded() 
		{
			m_bIsReady = true;
		}
		public void onAdFailedToLoad(int errorCode) 
		{
			m_bIsFail = true;
			m_bIsReady = false;
		}
		public void onAdOpened() 
		{
			m_bIsShown = true;
		}
		public void onAdClosed() 
		{
			m_bIsShown = false;
			m_bWasShown = true;
			m_bIsReady = false;
		}
		public void onAdLeftApplication() 
		{
			m_bIsClicked=true;
		}
		
	};

	InterestialListerner interstitialListener = new InterestialListerner();
    public int AdmobInit(String adUnitId, int adType, int x, int y)
    {		
		bannerListener.m_strAdUnitId = adUnitId;
		if (adType == 1)
			bannerListener.m_iAdType = AdSize.BANNER;
		else if(adType == 5)
			bannerListener.m_iAdType = AdSize.SMART_BANNER;
		bannerListener.m_iX = x;
		bannerListener.m_iY = y;
        return 0;
    }
    public int AdmobTestDevice(String szTestDeviceID)
    {
		bannerListener.m_strTestDevice = szTestDeviceID;
		interstitialListener.m_strTestDevice = szTestDeviceID;
        return 0;
    }
    public int AdmobResize(int ad_type)
    {
        return 0;
    }
    public int AdmobShow()
    {
		AdmobHide();
		
		bannerListener.m_layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT, FrameLayout.LayoutParams.WRAP_CONTENT);
		bannerListener.m_layoutParams.leftMargin = bannerListener.m_iX;
		bannerListener.m_layoutParams.topMargin = bannerListener.m_iY;
		bannerListener.m_layoutParams.gravity = Gravity.NO_GRAVITY;
		bannerListener.m_bIsClicked = false;        
		bannerListener.m_adView = new AdView(LoaderActivity.m_Activity);
		bannerListener.m_adView.setAdSize(AdSize.BANNER);
        bannerListener.m_adView.setAdUnitId(bannerListener.m_strAdUnitId);
		bannerListener.m_adView.setLayoutParams(bannerListener.m_layoutParams);

		LoaderActivity.m_Activity.addContentView(bannerListener.m_adView, bannerListener.m_layoutParams);				
				
		AdRequest.Builder adRequestBuilder = new AdRequest.Builder();
        
		if (bannerListener.m_strTestDevice.length() > 0)
			adRequestBuilder.addTestDevice(bannerListener.m_strTestDevice);	

		bannerListener.m_adView.setAdListener(bannerListener);
		bannerListener.m_adView.loadAd(adRequestBuilder.build());
        return 0;
    }
    public int AdmobRefresh()
    {
		AdmobShow();
        return 0;
    }
    public int AdmobHide()
    {
		if (bannerListener.m_adView != null) {

			ViewGroup vg = (ViewGroup) bannerListener.m_adView.getParent();
			if (vg != null) {
				vg.removeView(bannerListener.m_adView);
			}
			bannerListener.m_adView.destroy();
			bannerListener.m_adView = null;
		}
        return 0;
    }
    public int AdmobMove(int orientation, int x, int y)
    {
		bannerListener.m_iX = x;
		bannerListener.m_iY = y;
        return 0;
    }
    public int AdmobInterestialPreload(String adUnitId)
    {
		interstitialListener.m_bIsShown = false;
		interstitialListener.m_bWasShown = false;
		interstitialListener.m_bIsReady = false;
		interstitialListener.m_bIsFail = false;
		interstitialListener.m_bIsClicked = false;
		interstitialListener.m_strAdUnitId = adUnitId;
		
		interstitialListener.m_interstitial = new InterstitialAd(LoaderActivity.m_Activity);
		interstitialListener.m_interstitial.setAdUnitId(adUnitId);
		
		AdRequest.Builder adRequestBuilder = new AdRequest.Builder();
        
        if (interstitialListener.m_strTestDevice.length() > 0)
			adRequestBuilder.addTestDevice(interstitialListener.m_strTestDevice);	
	  
		interstitialListener.m_interstitial.setAdListener(interstitialListener);

		// Begin loading your interstitial
		interstitialListener.m_interstitial.loadAd(adRequestBuilder.build());
        return 0;
    }
    public boolean AdmobInterestialIsReady()
    {
        return interstitialListener.m_bIsReady;
    }
    public boolean AdmobInterestialIsShown()
    {
        return interstitialListener.m_bIsShown;
    }
    public boolean AdmobInterestialWasShown()
    {
        return interstitialListener.m_bWasShown;
    }
    public boolean AdmobInterestialHasBeenUsed()
    {
        return false;
    }
    public int AdmobInterestialShow()
    {
		interstitialListener.m_interstitial.show();
		interstitialListener.m_bIsShown = true;
        return 0;
    }
    public int AdmobInterestialHide()
    {
        return 0;
    }
    public boolean AdmobBannerIsClicked()
    {
        return bannerListener.m_bIsClicked;
    }
    public boolean AdmobInterestialIsClicked()
    {
        return interstitialListener.m_bIsClicked;
    }
}
