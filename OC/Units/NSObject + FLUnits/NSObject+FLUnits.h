//
//  NSObject+FLUnits.h
//
//  Created by 孔凡列 on 16/7/13.
//  Copyright © 2016年 clarence. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@interface NSObject (FLUnits)

// 打印所有属性以及其类型
+ (void)fl_printAllProperties;
// 返回所有方法数组
+(NSArray*)fl_methodList;

#pragma mark - 交换方法
+ (BOOL)fl_swizzleMethod:(SEL)origSel_ withMethod:(SEL)altSel_ error:(NSError**)error_;

+ (BOOL)fl_swizzleClassMethod:(SEL)origSel_ withClassMethod:(SEL)altSel_ error:(NSError**)error_;


#pragma mark - KVO

/**
 *  通过Block方式注册一个KVO，通过该方式注册的KVO无需手动移除，其会在被监听对象销毁的时候自动移除,所以下面的两个移除方法一般无需使用
 *
 *  @param keyPath 监听路径
 *  @param block   KVO回调block，obj为监听对象，oldVal为旧值，newVal为新值
 */
- (void)fl_addObserverBlockForKeyPath:(NSString*)keyPath block:(void (^)(id obj, id oldVal, id newVal))block;

/**
 *  提前移除指定KeyPath下的BlockKVO(一般无需使用，如果需要提前注销KVO才需要)
 *
 *  @param keyPath 移除路径
 */
- (void)fl_removeObserverBlockForKeyPath:(NSString *)keyPath;

/**
 *  提前移除所有的KVOBlock(一般无需使用)
 */
- (void)fl_removeAllObserverBlocks;

#pragma mark - Notification

/**
 *  通过block方式注册通知，通过该方式注册的通知无需手动移除，同样会自动移除
 *
 *  @param name  通知名
 *  @param block 通知的回调Block，notification为回调的通知对象
 */
- (void)fl_addNotificationForName:(NSString *)name block:(void (^)(NSNotification *notification))block;

/**
 *  提前移除某一个name的通知
 *
 *  @param name 需要移除的通知名
 */
- (void)fl_removeNotificationForName:(NSString *)name;

/**
 *  提前移除所有通知
 */
- (void)fl_removeAllNotification;

/**
 *  发送一个通知
 *
 *  @param name     通知名
 *  @param userInfo 数据字典
 */
- (void)fl_postNotificationWithName:(NSString *)name userInfo:(nullable NSDictionary *)userInfo;


/**
 *  解码（从文件中解析对象）
 */
- (void)decode:(NSCoder *)decoder;
/**
 *  编码（将对象写入文件中）
 */
- (void)encode:(NSCoder *)encoder;
@end

/**
 归档的实现
 */
#define FLCodingImplementation \
- (id)initWithCoder:(NSCoder *)decoder \
{ \
if (self = [super init]) { \
[self decode:decoder]; \
} \
return self; \
} \
\
- (void)encodeWithCoder:(NSCoder *)encoder \
{ \
[self encode:encoder]; \
}

NS_ASSUME_NONNULL_END
