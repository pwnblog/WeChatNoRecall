
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface MMServiceCenter : NSObject

+ (instancetype)defaultCenter;
- (id)getService:(Class)service;

@end


#ifndef MMCONTEXT_H
#define MMCONTEXT_H

@interface MMContext : NSObject {
    NSUInteger m_contextType;
    unsigned int m_uin;
    char m_uinStr;
    NSString *m_userName;
    NSUInteger m_userState;
    //NSRecursiveLock *m_contextLock;
    NSString *m_userMd5;
    NSString *m_userDocumentPath;
    NSString *m_userLibraryCachePath;
   // basic_string<char, std::char_traits<char>, std::allocator<char>> m_marsContext;
   //  MMLongLink *m_marsLongLink;
}


@property (readonly, nonatomic) MMServiceCenter *serviceCenter; // ivar: m_serviceCenter
//@property (readonly, nonatomic) MMExtensionCenter *extensionCenter; // ivar: m_extensionCenter
//@property (retain, nonatomic) CMainControll *mainController; // ivar: m_mainController
//@property (retain, nonatomic) NSRecursiveLock *contextLock; // ivar: _contextLock
@property (readonly, nonatomic) BOOL isRootContext;
@property (readonly, nonatomic) BOOL isUserContext;
@property (readonly, nonatomic) BOOL isInvalidContext;


-(id)getService:(Class)arg0 ;
-(BOOL)isServiceExist:(Class)arg0 ;
-(void)removeService:(Class)arg0 ;
-(void)setService:(id)arg0 for:(Class)arg1 ;
-(void)startNetworking;
-(void)stopNetworking;
-(void)marsContext;
-(void)marsLongLinkName;
-(void)registerExtension:(id)arg0 withTarget:(id)arg1 ;
-(void)unRegisterExtension:(id)arg0 withTarget:(id)arg1 ;
-(void)registerExtension:(id)arg0 withKey:(id)arg1 withTarget:(id)arg2 ;
-(void)unRegisterExtension:(id)arg0 withKey:(id)arg1 withTarget:(id)arg2 ;
-(void)unRegisterAllKeyExtension:(id)arg0 withTarget:(id)arg1 ;
-(void)callExtension:(id)arg0 selector:(SEL)arg1 block:(id)arg2 ;
-(void)callKeyExtension:(id)arg0 key:(id)arg1 selector:(SEL)arg2 block:(id)arg3 ;
-(void)callExtensionOnMainThread:(id)arg0 selector:(SEL)arg1 sync:(BOOL)arg2 block:(id)arg3 ;
-(void)callKeyExtensionOnMainThread:(id)arg0 key:(id)arg1 selector:(SEL)arg2 sync:(BOOL)arg3 block:(id)arg4 ;
-(void)callExtensionContinuously:(id)arg0 selector:(SEL)arg1 block:(id)arg2 ;
-(void)callKeyExtensionContinuously:(id)arg0 key:(id)arg1 selector:(SEL)arg2 block:(id)arg3 ;
-(void)callExtensionOnMainThreadContinuously:(id)arg0 selector:(SEL)arg1 sync:(BOOL)arg2 block:(id)arg3 ;
-(void)callKeyExtensionOnMainThreadContinuously:(id)arg0 key:(id)arg1 selector:(SEL)arg2 sync:(BOOL)arg3 block:(id)arg4 ;
-(id)init;
-(id)initWithContextType:(NSUInteger)arg0 ;
-(void)setUin:(unsigned int)arg0 userName:(id)arg1 ;
-(void)setLongLink:(id)arg0 ;
-(id)longLink;
-(void)checkExistExtensionIfNeeded;
-(id)description;
-(unsigned int)uin;
-(id)userName;
-(id)userMd5;
-(id)userDocumentPath;
-(id)userLibraryCachePath;
+(void)initialize;
+(void)initContextEnvironment;
+(instancetype)currentContext;
+(id)fastCurrentContext;
+(id)lastContext;
+(id)rootContext;
+(id)activeUserContext;
+(void)push:(id)arg0 ;
+(void)pop:(id)arg0 ;
+(void)setContext:(id)arg0 atIndex:(NSUInteger)arg1 ;
+(unsigned int)currentUin;
+(char *)currentUinStrForLog;
+(id)currentUserName;
+(id)currentUserMd5;
+(id)currentUserDocumentPath;
+(id)currentUserLibraryCachePath;


@end


#endif


@interface CContact: NSObject <NSCoding>
@property (nonatomic, copy) NSString *m_nsOwner;                        // 拥有者
@property (nonatomic, copy) NSString *m_nsNickName;                     // 用户昵称
@property (nonatomic, copy) NSString *m_nsUsrName;                      // 微信id
@property (nonatomic, copy) NSString *m_nsMemberName;
@property (nonatomic, copy) NSString *m_nsRemark;
@property(retain, nonatomic) NSString *m_nsHeadImgUrl;
@property(nonatomic) unsigned int m_uiSex;

- (id)getContactDisplayName;

/// 是不是公众号
- (BOOL)isBrandContact;
/// 是不是公众号
- (BOOL)isHolderContact;


@end

@interface CContactMgr : NSObject

- (id)getSelfContact;
- (id)getContactByName:(id)arg1;
- (id)getContactForSearchByName:(id)arg1;
- (BOOL)getContactsFromServer:(id)arg1;
- (BOOL)isInContactList:(id)arg1;
- (BOOL)addLocalContact:(id)arg1 listType:(unsigned int)arg2;
- (NSArray *)getContactList:(unsigned int)arg1 contactType:(unsigned int)arg2;
- (BOOL)deleteContactLocal:(id)arg1 listType:(unsigned int)arg2;
- (BOOL)deleteContact:(id)arg1 listType:(unsigned int)arg2;
@end

@interface WCPayInfoItem: NSObject

@property(retain, nonatomic) NSString *m_c2cNativeUrl;

@end

@interface CMessageWrap : NSObject

@property(nonatomic) unsigned int m_uiMessageType; // @synthesize m_uiMessageType;
@property(retain, nonatomic) NSString *m_nsContent; // @synthesize m_nsContent;
@property(nonatomic) long long m_n64MesSvrID; // @synthesize m_n64MesSvrID;
@property(nonatomic) unsigned int m_uiMesLocalID; // @synthesize m_uiMesLocalID;
@property(nonatomic) unsigned int m_uiCreateTime; // @synthesize m_uiCreateTime;
@property(retain, nonatomic) NSString *m_nsFromUsr; // @synthesize m_nsFromUsr;
@property(retain, nonatomic) NSString *m_nsToUsr; // @synthesize m_nsToUsr;
@property(retain, nonatomic) WCPayInfoItem *m_oWCPayInfoItem; // @dynamic m_oWCPayInfoItem;
@property(nonatomic) unsigned int m_uiAppMsgInnerType; // @dynamic m_uiAppMsgInnerType;
@property (assign, nonatomic) NSUInteger m_uiStatus;
@property (retain, nonatomic) NSString* m_nsRealChatUsr;        ///< 群消息的发信人，具体是群里的哪个人
@property (retain, nonatomic) NSString *m_nsDesc;
@property (retain, nonatomic) NSString *m_nsAppExtInfo;
@property (assign, nonatomic) NSUInteger m_uiAppDataSize;
@property (retain, nonatomic) NSString *m_nsShareOpenUrl;
@property (retain, nonatomic) NSString *m_nsShareOriginUrl;
@property (retain, nonatomic) NSString *m_nsJsAppId;
@property (retain, nonatomic) NSString *m_nsPrePublishId;
@property (retain, nonatomic) NSString *m_nsAppID;
@property (retain, nonatomic) NSString *m_nsAppName;
@property (retain, nonatomic) NSString *m_nsThumbUrl;
@property (retain, nonatomic) NSString *m_nsAppMediaUrl;
@property (retain, nonatomic) NSData *m_dtThumbnail;
@property (retain, nonatomic) NSString *m_nsTitle;
@property (retain, nonatomic) NSString *m_nsMsgSource;

@property (nonatomic, copy) NSString *m_nsLastDisplayContent;
@property (nonatomic, copy) NSString *m_nsPushContent;

@property(nonatomic) unsigned int m_uiGameType;     // 游戏类型
@property(nonatomic) unsigned int m_uiGameContent;  // 游戏内容

- (id)initWithMsgType:(long long)arg1;
- (WCPayInfoItem *)m_oWCPayInfoItem;
- (id)nativeUrl;
- (NSString *)wishingString;
- (BOOL)IsSendBySendMsg;
+ (BOOL)isSenderFromMsgWrap:(CMessageWrap *)msgWrap;

@end

@interface CMessageMgr : NSObject
- (id)GetMsg:(id)arg1 n64SvrID:(long long)arg2;
- (void)onRevokeMsg:(id)msg;
- (void)AddMsg:(id)arg1 MsgWrap:(id)arg2;
- (void)AddLocalMsg:(id)arg1 MsgWrap:(id)arg2 fixTime:(BOOL)arg3 NewMsgArriveNotify:(BOOL)arg4;
- (void)AsyncOnSpecialSession:(id)arg1 MsgList:(id)arg2;
- (id)GetHelloUsers:(id)arg1 Limit:(unsigned int)arg2 OnlyUnread:(BOOL)arg3;
- (void)AddEmoticonMsg:(NSString *)msg MsgWrap:(CMessageWrap *)msgWrap;
- (void)DelMsg:(id)arg1 MsgWrap:(id)arg2;
- (void)ResendMsg:(id)arg1 MsgWrap:(id)arg2;
- (_Bool)RevokeMsg:(id)arg1 MsgWrap:(id)arg2 Counter:(unsigned int)arg3;


@end