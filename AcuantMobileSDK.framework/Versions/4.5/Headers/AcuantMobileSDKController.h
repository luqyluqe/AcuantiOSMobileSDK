//
//  AcuantCardCaptureController
//  AcuantCardCapture Framework for iOS
//
//  Created by Acuant on 11/19/12.
//  Copyright (c) 2015 Acuant. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "AcuantCardProcessRequestOptions.h"
#import "AcuantError.h"
#import "AcuantCardResult.h"
#import "AcuantMedicalInsuranceCard.h"
#import "AcuantDriversLicenseCard.h"
#import "AcuantPassaportCard.h"
#import "AcuantCardType.h"

typedef enum{
    AcuantHUDLandscape = 0,
    AcuantHUDPortrait = 1
} AcuantHUDOrientation;


@protocol AcuantMobileSDKControllerCapturingDelegate <NSObject>

@required

/**
 Called to inform the delegate that a card image was captured
 @param cardImage the card image
 */
- (void)didCaptureImage:(UIImage*)cardImage scanBackSide:(BOOL)scanBackSide;

/**
 Called to inform the delegate that a barcode image was captured
 @param data the barcode string
 */
- (void)didCaptureData:(NSString*)data;


/**
 Called to inform delegate that the request failed.
 @param error the reason why the request failed
 @discussion the delegate is in charge of analysing the error sent and inform the user.
 */
- (void)didFailWithError:(AcuantError*)error;

@optional


/**
 Called to inform the delegate that the user pressed the back button
 */
- (void)didPressBackButton;

/**
 Called to inform the delegate that the framework was validated
 */
- (void)mobileSDKWasValidated:(BOOL)wasValidated;

/**
 Called to inform the delegate that the capture interface did appear
 */
- (void)cardCaptureInterfaceDidAppear;

/**
 Called to inform the delegate that the capture interface did disappear
 */
- (void)cardCaptureInterfaceDidDisappear;

/**
 Called to inform the delegate that the capture interface will disappear
 */
- (void)cardCaptureInterfaceWillDisappear;

/**
 Called to obtain the flashlight button image displayed in the card capture interface
 @return the flashlight button image
 @discussion if this method is not implemented or nil is returned, we'll display a white rounded button with "flash" text
 @discussion this delegate method is only called when presenting the card capture interface full screen. If card capture interface is presented in a UIPopOverController, this method is not called at all because a Cancel UIBarButtonItem in the UINavigationBar is used instead.
 */
- (UIImage*)imageForFlashlightButton;

/**
 Called to obtain the flashlight button position in the screen.
 @return the point where the flashlight button should be positioned
 @discussion in case this method is not implemented by the delegate, we'll set a default location for the button though we encourage you to set the position manually.
 @discussion if your application supports multiple screen sizes then you are in charge of returning the correct position for each screen size.
 */
- (CGRect)frameForFlashlightButton;

/**
 Called to show or not show the flashlight button in the card capture interface
 @return show or not show the flashlight button
 @discussion if this method is not implemented or nil is returned, we'll display a the button with "flash" text
 */
- (BOOL)showFlashlightButton;

/**
 
 Called to obtain the back button image displayed in the card capture interface
 @return the back button image
 @discussion if this method is not implemented or nil is returned, we'll display a white rounded button with "back" text
 */
- (UIImage*)imageForBackButton;

/**
 Called to obtain the back button position in the screen.
 @return the point where the back button should be positioned
 @discussion in case this method is not implemented by the delegate, we'll set a default location for the button though we encourage you to set the position manually.
 @discussion if your application supports multiple screen sizes then you are in charge of returning the correct position for each screen size.
 */
- (CGRect)frameForBackButton;

/**
 Called to show or not show the back button in the card capture interface
 @return show or not show the back button
 @discussion if this method is not implemented or nil is returned, we'll display a the button with "back" text
 */
- (BOOL)showBackButton;

/**
 Called to obtain the help image displayed in the card capture interface
 @return the help image
 @discussion if this method is not implemented or nil is returned, we'll not display a help image view
 */
- (UIImage*)imageForHelpImageView;

/**
 Called to obtain the help image position in the screen.
 @return the point where the help image should be positioned
 @discussion in case this method is not implemented by the delegate, we'll set a default location for the help image though we encourage you to set the position manually.
 @discussion if your application supports multiple screen sizes then you are in charge of returning the correct position for each screen size.
 */
- (CGRect)frameForHelpImageView;

/**
 Called to obtain the watermark Message displayed in the card capture interface
 @return the watermark Message
 @discussion if this method is not implemented or nil is returned, we'll not display a watermark Message view
 */
- (NSString*)stringForWatermarkLabel;

/**
 Called to obtain the watermark label position in the screen.
 @return the point where the watermark label should be positioned
 @discussion in case this method is not implemented by the delegate, we'll set a default location for the help image though we encourage you to set the position manually.
 @discussion if your application supports multiple screen sizes then you are in charge of returning the correct position for each screen size.
 */
- (CGRect)frameForWatermarkView;

/**
 Called to obtain the barcode error message displayed in the barcode capture interface
 @return the barcode error Message
 @discussion if this method is not implemented or nil is returned, we'll display a custom message view
 */
- (NSString*)stringForBarcodeErrorMessage;

/**
 Called to obtain the barcode title error displayed in the barcode capture interface
 @return the barcode title error
 @discussion if this method is not implemented or nil is returned, we'll display a custom message view
 */
- (NSString*)stringForBarcodeTitleError;

/**
 Called to obtain the time elapse to appear in the barcode capture interface
 @return time elapse to appear the error Message
 @discussion if this method is not implemented or nil is returned, we'll set a custom time elapse
 */
- (int)timeForBarcodeErrorMessage;

/**
 Called to set if the error message is hidden or not.
 @return hidden or not
 @discussion if this method is not implemented or nil is returned, we'll set NO as default value
 */
- (BOOL)isHiddenBarcodeErrorMessage;

@end

@protocol AcuantMobileSDKControllerProcessingDelegate <NSObject>

@required

/**
 Called to inform delegate that the request completed succesfully.
 @param result the data parsed from the card image
 */
- (void)didFinishProcessingCardWithResult:(AcuantCardResult*)result;

/**
 Called to inform delegate that the request failed.
 @param error the reason why the request failed
 @discussion the delegate is in charge of analysing the error sent and inform the user.
 */
- (void)didFailWithError:(AcuantError*)error;

@optional

/**
 Called to inform the delegate that the framework was validated
 */
- (void)mobileSDKWasValidated:(BOOL)wasValidated;

@end

@interface AcuantMobileSDKController : NSObject{}

@property (weak, nonatomic) id<AcuantMobileSDKControllerCapturingDelegate, AcuantMobileSDKControllerProcessingDelegate> mobileSDKDelegate;
/**
 Use this method to obtain an instance of the AcuantMobileSDKController if Username and password is correct
 @param key your License Key
 @param delegate your delegate
 @param cloudAddress your cloud Address
 @discussion never try to alloc/init this class, always obtain an instance through this method.
 @return the AcuantMobileSDKController instance
 */
+ (AcuantMobileSDKController*)initAcuantMobileSDKWithLicenseKey:(NSString*)key delegate:(id<AcuantMobileSDKControllerCapturingDelegate, AcuantMobileSDKControllerProcessingDelegate>)delegate andCloudAddress:(NSString*)cloudAddress;

/**
 Use this method to obtain an instance of the AcuantMobileSDKController if License key is correct
 @param key your License Key
 @param delegate your delegate
 @discussion never try to alloc/init this class, always obtain an instance through this method.
 @return the AcuantMobileSDKController instance
 */
+ (AcuantMobileSDKController*)initAcuantMobileSDKWithLicenseKey:(NSString*)key andDelegate:(id<AcuantMobileSDKControllerCapturingDelegate, AcuantMobileSDKControllerProcessingDelegate>)delegate;

/**
 Use this method to obtain an instance of the AcuantMobileSDKController if License key was set
 @discussion never try to alloc/init this class, always obtain an instance through this method.
 @return the AcuantMobileSDKController instance
 */
+ (AcuantMobileSDKController*)initAcuantMobileSDK;

/**
 Use this method to obtain an instance of the AcuantMobileSDKController if License key is correct and show the camera interface after the key was validated and approved
 @param key your License Key
 @param viewController the UIViewController object from which we'll present the card capture interface
 @param delegate the delegate of the card capture interface
 @param typeCard the type of the card capture interface
 @param isBarcodeSide the side of the card and type of capture interface
 @discussion never try to alloc/init this class, always obtain an instance through this method.
 @return the AcuantMobileSDKController instance
 */
+ (AcuantMobileSDKController*)initAcuantMobileSDKWithLicenseKey:(NSString*)key AndShowCardCaptureInterfaceInViewController:(UIViewController*)vc delegate:(id<AcuantMobileSDKControllerCapturingDelegate, AcuantMobileSDKControllerProcessingDelegate>)delegate typeCard:(AcuantCardType)typeCard region:(AcuantCardRegion)region isBarcodeSide:(BOOL)isBarcodeSide;


/**
 Use this method to present the card capture interface.
 @param viewController the UIViewController object from which we'll present the card capture interface
 @param delegate the delegate of the card capture interface
 @param typeCard the type of the card capture interface
 @param region the region of the card and type of capture interface
 @discussion a valid viewController is required
 */
- (void)showCameraInterfaceInViewController:(UIViewController*)vc delegate:(id<AcuantMobileSDKControllerCapturingDelegate>)delegate cardType:(AcuantCardType)cardType region:(AcuantCardRegion)region isBarcodeSide:(BOOL)isBarcodeSide;

/**
 Use this method to dismiss the card capture interface
 @discussion You cannot use [UIPopOverController dismissPopoverAnimated:] method to dismiss the UIPopOverController
 */
- (void)dismissCardCaptureInterface;

/**
 Use this method to start the camera
 @discussion you don't need to call this method after presenting the camera interface
 @discussion if we're already capturing video this method does nothing
 */
- (void)startCamera;

/**
 Use this method to stop the camera
 @discussion if camera is already stop, this method does nothing
 */
- (void)stopCamera;

/**
 Use this method to configure the License key
 @param key your LicenseKey
 @discussion you are in charge of setting License key on each application launch as part of the setup of the framework
 */
- (void)setLicenseKey:(NSString *)key;

/**
 Use this method to configure the Cloud Address of the server
 @param setCloudAddress the Cloud Address string including protocol, for example: https://myserver.com/
 */
- (void)setCloudAddress:(NSString *)serverBaseURL;

/**
 Use this method to activate the license key
 @param key the license key
 */
- (void)activateLicenseKey:(NSString*)key;

/**
 Use this method to set the width of the cropped image
 @param width the width of the cropped card
 @discussion you need to set the height with setHeight:(int)height to crop the image with these values
 */
-(void)setWidth:(int)width;

/**
 Use it to enable or disable the barcode Cropping
 @param canCropBarcode boolean enable or disable the watermark
 */
-(void)setCanCropBarcode:(BOOL)canCropBarcode;

/**
 Called to set a customize appear message, background color, time lenght and frame.
 @discussion in case this method in not implementd by the delegate, we'll set a default message, background color, time lenght and frame.
 */
-(void)setInitialMessage:(NSString*)message frame:(CGRect)frame backgroundColor:(UIColor*)backgroundColor duration:(int)timeLenght orientation:(AcuantHUDOrientation)orientation;

/**
 Called to set a customize finaly message, background color, time lenght and frame.
 @discussion in case this method in not implementd by the delegate, we'll set a default message, background color, time lenght and frame.
 */
-(void)setCapturingMessage:(NSString*)message frame:(CGRect)frame backgroundColor:(UIColor*)backgroundColor duration:(int)timeLenght orientation:(AcuantHUDOrientation)orientation;


/**
 Use this method to process a card.
 @param frontImage the front image of the card.
 @param backImage the back image of the card.
 @param stringData the string data of the back side of the card.
 @param delegate the delegate of the process request
 @param options the options of the process request.
 @discussion you must always provide a front image, back image is optional
 @discussion use the options object to indicate the type of card you're trying to process (i.e. License, Medical). Processing will fail if you don't provide this parameter.
 @discussion you're encourage to provide a delegate to be informed about what happened with your processing request. You can change the delegate using the cardProcessingDelegate property of this class.
 @discussion you should call this method only once and wait until your delegate is informed. If you call this method while we're already processing a card, we'll ignore your second call.
 @discussion The recommended size to this images is 1009 width and relative height to the width.
 */
- (void)processFrontCardImage:(UIImage*)frontImage
                BackCardImage:(UIImage*)backImage
                andStringData:(NSString*)stringData
                 withDelegate:(id<AcuantMobileSDKControllerProcessingDelegate>)delegate
                  withOptions:(AcuantCardProcessRequestOptions*)options;

@end
