
#include "wechat.h"


%hook CMessageMgr
// -(void)DelMsg:(id)arg0 MsgList:(id)arg1 DelAll:(BOOL)arg2 {
// 	%orig(NULL, arg1, 1);
// }

- (void)onRevokeMsg:(CMessageWrap *)arg1  {
	
	NSString *msgContent = arg1.m_nsContent;

	NSString *(^parseParam)(NSString *, NSString *,NSString *) = ^NSString *(NSString *content, NSString *paramBegin,NSString *paramEnd) {
		NSUInteger startIndex = [content rangeOfString:paramBegin].location + paramBegin.length;
		NSUInteger endIndex = [content rangeOfString:paramEnd].location;
		NSRange range = NSMakeRange(startIndex, endIndex - startIndex);
		return [content substringWithRange:range];
	};

	NSString *session = parseParam(msgContent, @"<session>", @"</session>");
	NSString *newmsgid = parseParam(msgContent, @"<newmsgid>", @"</newmsgid>");

	NSString *language = [[NSLocale preferredLanguages] firstObject];
	NSString *fromUsrName;

	NSUInteger lang_type=0; // english
//	NSLog(@"device language:%@", language);
	if ([language rangeOfString:@"zh"].location!=NSNotFound)
	{
		lang_type=1;
		fromUsrName = parseParam(msgContent, @"<![CDATA[", @"撤回了一条消息");
	}
	else if([language rangeOfString:@"en"].location!=NSNotFound)
		fromUsrName = parseParam(msgContent, @"<![CDATA[", @"recalled a message");
	else
		fromUsrName = @"Someone"; // TODO: Fix this name
	
	
	CMessageWrap *revokemsg = [self GetMsg:session n64SvrID:[newmsgid integerValue]];
	BOOL isSender = [%c(CMessageWrap) isSenderFromMsgWrap:arg1];

	NSString *newMsgContent = @"";
	NSArray *revoke_self_text = @[@"You recalled a message \n %@", @"拦截到你撤回了一条消息 \n %@"];
	NSArray *revoke_self = @[@"You recalled a message", @"拦截到你撤回了一条消息"];
	NSArray *revoke_other_text = @[@"%@ recalled \n %@", @"%@撤回消息：\n %@"];
	NSArray *revoke_other = @[@"%@ recalled a message, nice try", @"%@撤回了一条消息,然而并没有什么卵用"];

	CMessageWrap *msgWrap = [[%c(CMessageWrap) alloc] initWithMsgType:0x2710];
	if (isSender) {
		[msgWrap setM_nsFromUsr:arg1.m_nsToUsr];
		[msgWrap setM_nsToUsr:arg1.m_nsFromUsr];
		if (revokemsg.m_uiMessageType == 1) {       
			newMsgContent = [NSString stringWithFormat:revoke_self_text[lang_type],revokemsg.m_nsContent];
		} else {
			newMsgContent = revoke_self[lang_type];
		}
	} else {
		[msgWrap setM_nsToUsr:arg1.m_nsToUsr];
		[msgWrap setM_nsFromUsr:arg1.m_nsFromUsr];
		if (revokemsg.m_uiMessageType == 1) {
				newMsgContent = [NSString stringWithFormat:revoke_other_text[lang_type],fromUsrName, revokemsg.m_nsContent];
			} else {
				newMsgContent = [NSString stringWithFormat:revoke_other[lang_type],fromUsrName];
		}
	}

	[msgWrap setM_uiStatus:0x4];
	[msgWrap setM_nsContent:newMsgContent];
	[msgWrap setM_uiCreateTime:[revokemsg m_uiCreateTime]];

	[self AddLocalMsg:session MsgWrap:msgWrap fixTime:0 NewMsgArriveNotify:0];
}

%end